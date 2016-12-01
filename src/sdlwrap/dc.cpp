#include "dc.hpp"
#include <cstdlib>

#include <misc/exceptions.hpp>

// ---- INIITIALIZATION ----

DC::DC():
Singleton<DC>(),
	surface(NULL),
	oldSurface(NULL),
	pressedRectangle(false),
	brush(),
	pen(),
	textColor(),
	font(),
	// evtl gar nicht initialisieren...
	bitDepth(DEPTH_32BIT),
	bits(0),
	resolution(Size()),
	Draw_HLine(NULL),
	Draw_VLine(NULL),
	Draw_Line(NULL),
	DrawFilledRound(NULL),
	DrawFilledEdgedRound(NULL),
	DrawEmptyEdgedRound(NULL),
	DrawEmptyRound(NULL),
	DrawFilledEdgedBorderRound(NULL),
	changedRectangles(0),
	max_x(0),
	max_y(0),
	brightness(0)
{ }


DC::~DC()
{
	//	SDL_FreeSurface(surface); TODO?
}


bool DC::initSDL(const Size& current_resolution, const eBitDepth bit_depth, const Uint32 nflags, const Uint32 initflags)
{
	if ( SDL_Init(initflags) < 0 ) {
		throw SDLException("ERROR (DC::initSDL()): Could not initialize SDL (" + std::string(SDL_GetError()) + ").");
	}

	atexit(SDL_Quit);
	return setScreen(current_resolution, bit_depth, nflags);
}

bool DC::setScreen(const Size current_resolution, const eBitDepth bit_depth, const Uint32 nflags)
{
	// no action
	if((current_resolution == resolution) && (bit_depth == bitDepth) && (surface != NULL)) {
		return false;
	}

	resolution = current_resolution;
	max_x = resolution.getWidth();
	max_y = resolution.getHeight();
	switch(bit_depth)
	{
	case DEPTH_8BIT:bits = 8;break;
	case DEPTH_16BIT:bits = 16;break;
	case DEPTH_24BIT:bits = 24;break;
	case DEPTH_32BIT:bits = 32;break;
	default:BOOST_ASSERT(false);break;
	}
	//	const SDL_VideoInfo* hardware = SDL_GetVideoInfo();
	//	if(bits > (unsigned int)hardware->vfmt->BitsPerPixel)
	//		bits = (unsigned int)hardware->vfmt->BitsPerPixel; :(

	surface = SDL_SetVideoMode(max_x, max_y, bits, nflags);
	if(surface == NULL) {
		throw SDLException("ERROR (DC::setScreen()): Could not set video mode (" + std::string(SDL_GetError()) + ").");
	}

	changedRectangle[0] = Rect::createRect(0, 0, max_x, max_y);
	changedRectangles = 1;

	switch(surface->format->BitsPerPixel)
	{
	case 8:	bitDepth = DEPTH_8BIT;
		Draw_HLine = &DC::Draw_HLine_8bit;
		Draw_VLine = &DC::Draw_VLine_8bit;
		Draw_Line = &DC::Draw_Line_8bit;
		DrawFilledRound = &DC::DrawFilledRound_8bit;
		DrawFilledEdgedRound = &DC::DrawFilledEdgedRound_8bit;
		DrawEmptyEdgedRound = &DC::DrawEmptyEdgedRound_8bit;
		DrawEmptyRound = &DC::DrawEmptyRound_8bit;
		DrawFilledEdgedBorderRound = &DC::DrawFilledEdgedBorderRound_8bit;
		DrawTab = &DC::DrawTab_8bit;
		break;

	case 16:bitDepth = DEPTH_16BIT;
		Draw_HLine = &DC::Draw_HLine_16bit;
		Draw_VLine = &DC::Draw_VLine_16bit;
		Draw_Line = &DC::Draw_Line_16bit;
		DrawFilledRound = &DC::DrawFilledRound_16bit;
		DrawFilledEdgedRound = &DC::DrawFilledEdgedRound_16bit;
		DrawEmptyEdgedRound = &DC::DrawEmptyEdgedRound_16bit;
		DrawEmptyRound = &DC::DrawEmptyRound_16bit;
		DrawFilledEdgedBorderRound = &DC::DrawFilledEdgedBorderRound_16bit;
		DrawTab = &DC::DrawTab_16bit;
		break;

	case 24:bitDepth = DEPTH_24BIT;
		Draw_HLine = &DC::Draw_HLine_24bit;
		Draw_VLine = &DC::Draw_VLine_24bit;
		Draw_Line = &DC::Draw_Line_24bit;
		DrawFilledRound = &DC::DrawFilledRound_24bit;
		DrawFilledEdgedRound = &DC::DrawFilledEdgedRound_24bit;
		DrawEmptyEdgedRound = &DC::DrawEmptyEdgedRound_24bit;
		DrawEmptyRound = &DC::DrawEmptyRound_24bit;
		DrawFilledEdgedBorderRound = &DC::DrawFilledEdgedBorderRound_24bit;
		DrawTab = &DC::DrawTab_24bit;
		break;

	case 32:bitDepth = DEPTH_32BIT;
		Draw_HLine = &DC::Draw_HLine_32bit;
		Draw_VLine = &DC::Draw_VLine_32bit;
		Draw_Line = &DC::Draw_Line_32bit;
		DrawFilledRound = &DC::DrawFilledRound_32bit;
		DrawFilledEdgedRound = &DC::DrawFilledEdgedRound_32bit;
		DrawEmptyEdgedRound = &DC::DrawEmptyEdgedRound_32bit;
		DrawEmptyRound = &DC::DrawEmptyRound_32bit;
		DrawFilledEdgedBorderRound = &DC::DrawFilledEdgedBorderRound_32bit;
		DrawTab = &DC::DrawTab_32bit;
		break;

	default:BOOST_ASSERT(false);break;
	}
	return true;
}



// ----- SURFACE OPERATIONS


void DC::switchToSurface(SDL_Surface* temp_surface) 
{
	BOOST_ASSERT(oldSurface == NULL);
	oldSurface = surface;
	surface = temp_surface;
}

void DC::switchToOriginalSurface()
{
	BOOST_ASSERT(oldSurface);
	surface = oldSurface;
	oldSurface = NULL;
}


bool DC::setFullScreen(const bool full_screen)
{
	BOOST_ASSERT(surface);
	if(isFullScreen() != full_screen)
	{
#ifdef __linux
		SDL_WM_ToggleFullScreen(surface);
#elif WIN32
		Uint32 nflags = surface->flags;
		nflags ^= SDL_FULLSCREEN;
		surface = SDL_SetVideoMode(surface->w, surface->h, surface->format->BitsPerPixel, nflags);
#endif
		return true;
	}				
	return false;
}






// ----- SCREEN UPDATE 

void DC::addRectangle(const Rect& rect)
{
	//Größe des Rechtecks (größere testen ob sie es beinhalten, kleinere testen ob sie umgeben werden)
	//Position des Rechtecks: rechte untere Ecke, linke obere Ecke, Quadtrees, dynamisch angepasste Trees

	if((changedRectangles >= DC_MAX_CHANGED_RECTANGLES) || (rect.getLeft() >= max_x) || (rect.getTop() >= max_y) || (rect.getRight() < 0) || (rect.getBottom() < 0)) {
		return;
	}

	// cut borders
	Point p = Point(rect.getLeft() < 0  ? 0 : rect.getLeft(),
		rect.getTop() < 0   ? 0 : rect.getTop());
	Size s = Size(rect.getRight()  >= max_x ? max_x - rect.getLeft() : rect.getWidth(),
		rect.getBottom() >= max_y ? max_y - rect.getTop()  : rect.getHeight());

	SDL_Rect r = Rect::createRect(Rect(p, s));



	for(unsigned int i = 0; i < changedRectangles; i ++)
	{
		if(
			(r.x >= changedRectangle[i].x)&&
			(r.x + r.w <= changedRectangle[i].x + changedRectangle[i].w)&&
			(r.y >= changedRectangle[i].y)&&
			(r.y + r.h <= changedRectangle[i].y + changedRectangle[i].h)
			)
			return;
		if(
			(r.x <= changedRectangle[i].x)&&
			(r.x + r.w >= changedRectangle[i].x + changedRectangle[i].w)&&
			(r.y <= changedRectangle[i].y)&&
			(r.y + r.h >= changedRectangle[i].y + changedRectangle[i].h)
			)
		{
			changedRectangle[i] = r;
			return;
		}
	}

	changedRectangle[changedRectangles] = r;
	changedRectangles++;
}



void DC::updateScreen()
{
	BOOST_ASSERT(surface);
	//	SDL_UpdateRect(surface, 0, 0, this->getMaxX(), this->getMaxY());
	SDL_UpdateRects(surface, changedRectangles, changedRectangle);
	changedRectangles = 0;
}

const char* DC::dcVersion = "1.70";
