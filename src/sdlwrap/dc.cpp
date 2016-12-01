#include "dc.hpp"
#include <cstdlib>

#include <misc/exceptions.hpp>
#include <sstream>
#include <lang/text_storage.hpp>
#include <misc/ids.hpp>
#include <guicore/pen_storage.hpp>

#pragma warning(push, 0)  
#include <string.h>
#include <wchar.h>
#pragma warning(pop)

// ---- INIITIALIZATION ----

DC::DC(Uint32 initflags):
	surface(NULL),
	oldSurface(NULL),
	pressedRectangle(false),
	brush(),
	darkBrush(),
	pen(),
	darkPen(),
	pressedPen(),
	darkPressedPen(),
	textColor(),
	endBrush(),
	endDarkBrush(),
	endPen(),
	endDarkPen(),
	endPressedPen(),
	endDarkPressedPen(),
	endTextColor(),

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
	brightness(100), // 100%
	defaultCursor(initAndGetDefaultCursor(initflags))
{
	atexit(SDL_Quit);
}

SDL_Cursor* DC::initAndGetDefaultCursor(Uint32 initflags) {
	if ( SDL_Init(initflags) < 0 ) {
		throw SDLException("ERROR (DC::initSDL()): Could not initialize SDL (" + std::string(SDL_GetError()) + ").");
	}
	return SDL_GetCursor();
}


DC::~DC()
{
	SDL_SetCursor(defaultCursor);
	//	SDL_FreeSurface(surface); TODO?
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

	changedRectangles.push_back(Rect(0, 0, max_x, max_y));

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

	if((rect.getLeft() >= max_x) || (rect.getTop() >= max_y) || (rect.getRight() < 0) || (rect.getBottom() < 0)) {
		return;
	}

	// cut borders
	Point p = Point(rect.getLeft() < 0  ? 0 : rect.getLeft(),
		rect.getTop() < 0   ? 0 : rect.getTop());
	Size s = Size(rect.getRight()  >= max_x ? max_x - rect.getLeft() : rect.getWidth(),
		rect.getBottom() >= max_y ? max_y - rect.getTop()  : rect.getHeight());

	std::list<Rect> rects = Rect(p, s).removeRects(changedRectangles);
	changedRectangles.insert(changedRectangles.end(), rects.begin(), rects.end());
}



void DC::updateScreen()
{
	BOOST_ASSERT(surface);
	//	SDL_UpdateRect(surface, 0, 0, this->getMaxX(), this->getMaxY());
	/*if(rand()%2 == 0) {
		setDarkPen(PenStorage::instance().get(IDS::BORDER_PEN_ID));
		setPen(PenStorage::instance().get(IDS::BORDER_PEN_ID));
	} else {
		setDarkPen(PenStorage::instance().get(IDS::UNIT_TYPE_4_BOLD_PEN_ID));
		setPen(PenStorage::instance().get(IDS::UNIT_TYPE_4_BOLD_PEN_ID));
	}*/
	/*setBrightness(100);
	for(std::list<Rect>::const_iterator i = changedRectangles.begin(); i != changedRectangles.end(); i++) {
		//DrawEmptyRectangle(i->getTopLeft().getX()+1, i->getTopLeft().getY()+1, i->getWidth()-2, i->getHeight()-2);
		//std::cout << "changed rectangle : " << i->toString() << std::endl;
	}*/

	int changedRectanglesCount = changedRectangles.size();

	if(changedRectanglesCount > 0) {
	if ( (surface->flags & SDL_DOUBLEBUF) == SDL_DOUBLEBUF ) {
			SDL_Flip(surface);
			std::cout << "Flip!" << std::endl;
		} else 
	{
		SDL_Rect* changedSDLRectangles = new SDL_Rect[changedRectanglesCount];
		int j = 0;
		for(std::list<Rect>::const_iterator i = changedRectangles.begin(); i != changedRectangles.end(); i++) {
			changedSDLRectangles[j] = Rect::createRect(*i);
			j++;
		}
		SDL_UpdateRects(surface, changedRectanglesCount, changedSDLRectangles);
		delete[] changedSDLRectangles; 
		}
	}
	changedRectangles.clear();
}




// ----- DC INTERFACE: -----

const std::string DC::printHardwareInformation()
{
	// TODO: uebersetzen bzw. dem Aufrufer nur Daten uebergeben
	SDL_Rect **modes;
	std::ostringstream os;
	os.str("");
	modes = SDL_ListModes(NULL, SDL_SWSURFACE);
	if(modes == (SDL_Rect **)0) {
		os << "* " << TextStorage::instance().get(IDS::START_SDL_NO_MODES_AVAILABLE_TEXT_ID)->getText() << std::endl;
	}
	else
	{
		if(modes == (SDL_Rect **)-1) {
			os << "* " << TextStorage::instance().get(IDS::START_SDL_ALL_RESOLUTIONS_AVAILABLE_TEXT_ID)->getText() << std::endl;
		} else
		{
			os << "* " << TextStorage::instance().get(IDS::START_SDL_AVAILABLE_MODES_TEXT_ID)->getText();
			for(unsigned int i=0; modes[i]; ++i) {
				os << "  " << modes[i]->w << " x " << modes[i]->h;
			}
			os << std::endl;
		}
	}
	const SDL_VideoInfo* hardware = SDL_GetVideoInfo();
	os << " - " << TextStorage::instance().get(IDS::START_SDL_MAX_COLOR_DEPTH_TEXT_ID)->getText() << (unsigned int)hardware->vfmt->BitsPerPixel;
	//	if(hardware->hw_available) os << "\n- " << TextStorage::instance().get(IDS::START_SDL_HARDWARE_SURFACES_POSSIBLE_TEXT_ID)->getText();
	if(hardware->wm_available) os << "\n - " << TextStorage::instance().get(IDS::START_SDL_WINDOW_MANAGER_AVAILABLE_TEXT_ID)->getText();
	if(hardware->blit_hw) os << "\n - " << TextStorage::instance().get(IDS::START_SDL_HARDWARE_TO_HARDWARE_BLITS_ACCELERATED_TEXT_ID)->getText();
	if(hardware->blit_hw_CC) os << "\n - " << TextStorage::instance().get(IDS::START_SDL_HARDWARE_TO_HARDWARE_COLORKEY_BLITS_ACCELERATED_TEXT_ID)->getText();
	if(hardware->blit_hw_A) os << "\n - " << TextStorage::instance().get(IDS::START_SDL_HARDWARE_TO_HARDWARE_ALPHA_BLITS_ACCELERATED_TEXT_ID)->getText();
	if(hardware->blit_sw) os << "\n - " << TextStorage::instance().get(IDS::START_SDL_SOFTWARE_TO_HARDWARE_BLITS_ACCELERATED_TEXT_ID)->getText();
	if(hardware->blit_sw_CC) os << "\n - " << TextStorage::instance().get(IDS::START_SDL_SOFTWARE_TO_HARDWARE_COLORKEY_BLITS_ACCELERATED_TEXT_ID)->getText();
	if(hardware->blit_sw_A)	os << "\n - " << TextStorage::instance().get(IDS::START_SDL_SOFTWARE_TO_HARDWARE_ALPHA_BLITS_ACCELERATED_TEXT_ID)->getText();
	if(hardware->blit_fill)	os << "\n - " << TextStorage::instance().get(IDS::START_SDL_COLOR_FILLS_ACCELERATED_TEXT_ID)->getText();
	if(hardware->video_mem>0) {
		std::string memoryString = TextStorage::instance().get(IDS::START_SDL_TOTAL_VIDEO_MEMORY_TEXT_ID)->getText();
		std::list<std::string> parameterList;
		parameterList.push_back(boost::lexical_cast<std::string>(hardware->video_mem));
		Misc::formatString(memoryString, parameterList);
		os << "\n - " << memoryString;
	}
	//	Total amount of video memory: " << hardware->video_mem << "kb";

	return os.str();
}




const std::string DC::printSurfaceInformation()
{
	BOOST_ASSERT(surface);

	std::ostringstream os; os.str("");
	os << surface->w << " x " << surface->h << " @ " << (unsigned int)(surface->format->BitsPerPixel);
	if (surface->flags & SDL_SWSURFACE) os << "\n- " << TextStorage::instance().get(IDS::START_SDL_SURFACE_STORED_IN_SYSTEM_MEMORY_TEXT_ID)->getText();
	//Surface is stored in system memory";
	else if(surface->flags & SDL_HWSURFACE) os << "\n- " << TextStorage::instance().get(IDS::START_SDL_SURFACE_STORED_IN_VIDEO_MEMORY_TEXT_ID)->getText();
	//			Surface is stored in video memory";
	if(surface->flags & SDL_ASYNCBLIT) os << "\n- " << TextStorage::instance().get(IDS::START_SDL_SURFACE_USES_ASYNCHRONOUS_BLITS_TEXT_ID)->getText();
	//urface uses asynchronous blits if possible";
	if(surface->flags & SDL_ANYFORMAT) os << "\n- " << TextStorage::instance().get(IDS::START_SDL_SURFACE_ALLOWS_ANY_PIXEL_FORMAT_TEXT_ID)->getText();
	if(surface->flags & SDL_HWPALETTE) os << "\n- " << TextStorage::instance().get(IDS::START_SDL_SURFACE_HAS_EXCLUSIVE_PALETTE_TEXT_ID)->getText();
	if(surface->flags & SDL_DOUBLEBUF) os << "\n- " << TextStorage::instance().get(IDS::START_SDL_SURFACE_IS_DOUBLE_BUFFERED_TEXT_ID)->getText();
	if(surface->flags & SDL_OPENGL) os << "\n- " << TextStorage::instance().get(IDS::START_SDL_SURFACE_HAS_OPENGL_CONTEXT_TEXT_ID)->getText();
	if(surface->flags & SDL_OPENGLBLIT) os << "\n- " << TextStorage::instance().get(IDS::START_SDL_SURFACE_SUPPORTS_OPENGL_BLITTING_TEXT_ID)->getText();
	if(surface->flags & SDL_RESIZABLE) os << "\n- " << TextStorage::instance().get(IDS::START_SDL_SURFACE_IS_RESIZABLE_TEXT_ID)->getText();
	if(surface->flags & SDL_HWACCEL) os << "\n- " << TextStorage::instance().get(IDS::START_SDL_SURFACE_BLIT_USES_HARDWARE_ACCELERATION_TEXT_ID)->getText();
	//Surface blit uses hardware acceleration";
	if(surface->flags & SDL_SRCCOLORKEY) os << "\n- " << TextStorage::instance().get(IDS::START_SDL_SURFACE_USES_COLORKEY_BLITTING_TEXT_ID)->getText();
	//Surface use colorkey blitting";
	if(surface->flags & SDL_RLEACCEL) os << "\n- " << TextStorage::instance().get(IDS::START_SDL_COLORKEY_BLITTING_RLE_ACCELERATED_TEXT_ID)->getText();
	//Colorkey blitting is accelerated with RLE";
	if(surface->flags & SDL_SRCALPHA) os << "\n- " << TextStorage::instance().get(IDS::START_SDL_BLIT_USES_ALPHA_BLENDING_TEXT_ID)->getText();
	//	Surface blit uses alpha blending";
	if(surface->flags & SDL_PREALLOC) os << "\n- " << TextStorage::instance().get(IDS::START_SDL_SURFACE_USES_PREALLOCATED_MEMORY_TEXT_ID)->getText();
	if(SDL_MUSTLOCK(surface)) os << "\n- " << TextStorage::instance().get(IDS::START_SDL_SURFACE_NEEDS_LOCKING_TEXT_ID)->getText();

	return os.str();
}





// ---- DRAWING
#if 0 
TODO
void DC::DrawBrightenedBitmap(const SDL_Surface* bitmap, const Sint16 x, const Sint16 y, const Rect& clip_rect, const Uint8 brightness) const
{
//	if(brightness == 100)
//	{
		SDL_SetAlpha((SDL_Surface*)bitmap, SDL_SRCALPHA, static_cast<Uint8>(brightness * 255 / 100));
		DrawBitmap(bitmap, x, y, clip_rect);
		SDL_SetAlpha((SDL_Surface*)bitmap, SDL_SRCALPHA, 255);
		return;
//	}
//	double brightness_percent = brightness / 100;
/*	SDL_Surface* neu = SDL_CreateRGBSurface(SDL_SWSURFACE, bitmap->w, bitmap->h, 8, 0, 0, 0, 0);
	Uint32* pc = (Uint32*)(bitmap->pixels);
	Uint32* dst = (Uint32*)(neu->pixels);

	for(unsigned int i = bitmap->w * bitmap->h; i--;)
	{
		Uint8 r,g,b;
		SDL_GetRGB(*pc, bitmap->format, &r, &g, &b);
//		r = r/2;// * brightness_percent; if(r > 255) r = 255;
//		g = g/2;// * brightness_percent; if(g > 255) g = 255;
//		b = b/2;// * brightness_percent; if(b > 255) b = 255;
		*dst = SDL_MapRGB(bitmap->format, r, g, b);
		++pc;
		++dst;
	}
	DrawBitmap(neu, x, y, clip_rect);
	SDL_FreeSurface(neu);*/
		//TODO
}

void DC::DrawBrightenedBitmap(const SDL_Surface* bitmap, const Sint16 x, const Sint16 y, const Uint8 brightness) const
{
//	if(brightness == 100)
//	{
		SDL_SetAlpha((SDL_Surface*)bitmap, SDL_SRCALPHA, static_cast<Uint8>(brightness * 255 / 100));
		DrawBitmap(bitmap, x, y);
		SDL_SetAlpha((SDL_Surface*)bitmap, SDL_SRCALPHA, 255);
		return;
//	}

//	double brightness_percent = brightness / 100;
/*	SDL_Surface* neu = SDL_CreateRGBSurface(SDL_SWSURFACE, bitmap->w, bitmap->h, 8, 0, 0, 0, 0);
	Uint32* pc = (Uint32*)(bitmap->pixels);
	Uint32* dst = (Uint32*)(neu->pixels);

	for(unsigned int i = bitmap->w * bitmap->h; i--;)
	{
		Uint8 r,g,b;
		SDL_GetRGB(*pc, bitmap->format, &r, &g, &b);
//		r = r /2;//* brightness_percent; if(r > 255) r = 255;
//		g = g /2;//* brightness_percent; if(g > 255) g = 255;
//		b = b /2;//* brightness_percent; if(b > 255) b = 255;
//		*((Uint32*)((Uint8*)surface->pixels + (Ycenter-i)*surface->pitch + ((Xcenter - radius)<<2) )) = pen_col;
		*dst = SDL_MapRGB(bitmap->format, r, g, b);
		++pc;
		++dst;
	}
	DrawBitmap(neu, x, y);
	SDL_FreeSurface(neu);*/
}
#endif

void DC::DrawBitmap(const SDL_Surface* bitmap, const Sint16 x, const Sint16 y) const
{
	if((x + bitmap->w >= getMaxX())||(y + bitmap->h >= getMaxY()) || (x < 0) || (y < 0))
	{
		DrawBitmap(bitmap, x, y, Rect(0, 0, getMaxX(), getMaxY()));
		return;
	}
	SDL_Rect drect = Rect::createRect(x, y, 0, 0);
	SDL_BlitSurface((SDL_Surface*)bitmap , NULL, surface, &drect);
}


// clipped bitmap
void DC::DrawBitmap(const SDL_Surface* bitmap, const Sint16 x, const Sint16 y, const Rect& clip_rect) const
{
	SDL_Rect srect = Rect::createRect(0, 0, (Uint16)(bitmap->w), (Uint16)(bitmap->h));
	SDL_Rect drect = Rect::createRect(x, y, 0, 0);

	if((clip_rect.getLeft() > x + srect.w) || (clip_rect.getTop() > y + srect.h) || (clip_rect.getBottom() < y) || (clip_rect.getRight() < x)) {
		return;
	}
	if(clip_rect.getLeft() > x)
	{
		srect.x = clip_rect.getLeft() - x;
		srect.w -= srect.x;
		drect.x = clip_rect.getLeft();
	}
	if(clip_rect.getTop() > y)
	{
		srect.y = clip_rect.getTop() - y;
		srect.h -= srect.y;
		drect.y = clip_rect.getTop();
	}
	if(clip_rect.getRight() < x + srect.w) {
		srect.w = clip_rect.getRight() - x;
	}	
	if(clip_rect.getBottom() < y + srect.h) {
		srect.h = clip_rect.getBottom() - y;
	}
	
	SDL_BlitSurface((SDL_Surface*)bitmap , &srect, surface, &drect);
}

void DC::DrawLine(const Sint16 x0, const Sint16 y0, const Sint16 x1, const Sint16 y1) const
{
	if(pen->getStyle()==TRANSPARENT_PEN_STYLE) {
		return;
	}
	Sint16 xx1, xx2, yy1, yy2;
	if(x0>x1) {
		xx1=x1;xx2=x0;yy1=y1;yy2=y0;
	} else {
		xx1=x0;xx2=x1;yy1=y0;yy2=y1;
	}

	if((xx1<pen->getWidth()/2) || (yy1+1<pen->getWidth()/2) || (yy2<pen->getWidth()/2) ||
		(xx2>=getMaxX() - pen->getWidth()/2)||(yy1>=getMaxY()-pen->getWidth()/2)||(yy2>=getMaxY()-pen->getWidth()/2)) {
		return;
	}
		
	if(yy1==yy2)
	{
		if(xx1==xx2) {
			return;
		}
		if(pen->getWidth()>1)
		{
			SDL_Rect rc = Rect::createRect(xx1/*-pen->getWidth()/2*/, yy1/*-pen->getWidth()/2*/, xx2 - xx1/*+pen->getWidth()*/, pen->getWidth());
			SDL_FillRect(surface, &rc, static_cast<Uint32>(getPenColor()));
		} else {
			(*this.*Draw_HLine)(xx1, yy1, xx2);
		}
	} else
	if(xx1==xx2)
	{
		if(yy1>yy2) {
			{Sint16 swp=yy1;yy1=yy2;yy2=swp;}
		}
		if(pen->getWidth()>1)
		{
			SDL_Rect rc = Rect::createRect(xx1/*-pen->getWidth()/2*/, yy1/*-pen->getWidth()/2*/, pen->getWidth(), yy2-yy1/*+pen->getWidth()*/);
			SDL_FillRect(surface, &rc, static_cast<Uint32>(getPenColor()));
		} else {
			(*this.*Draw_VLine)(xx1, yy1, yy2);
		}
	} else
	{
		(*this.*Draw_Line)(xx1, yy1, xx2, yy2);
		if(pen->getWidth()==2)
		{
//			const Color c = getPenColor();
//			const_cast<DC*>(this)->pen->setColor(Color(surface, static_cast<Uint8>(c->r()*0.5),  static_cast<Uint8>(c->g()*0.5), static_cast<Uint8>(c->b()*0.5)));
			(*this.*Draw_Line)(xx1, yy1+1, xx2, yy2+1);
			(*this.*Draw_Line)(xx1, yy1, xx2, yy2);
			(*this.*Draw_Line)(xx1, yy1-1, xx2, yy2-1);
//			const_cast<DC*>(this)->pen->setColor(c);
		}
	}
}

// TODO dp!
void DC::DrawSpline(const unsigned int c, const Point* p) const
{
	if((pen->getStyle() == TRANSPARENT_PEN_STYLE)||(c<2)) {
		return;
	}
	for(unsigned int i=c-1;i--;)
//	{
//		aalineColor(surface, p[i].x, p[i].y, p[i+1].x, p[i+1].y, static_cast<Uint32>(getPenColor()));
//		aalineColor(surface, p[i].x, p[i].y+1, p[i+1].x, p[i+1].y+1, static_cast<Uint32>(getPenColor()));
//	}
	{
/*		if((i>0)&&(i<c-2))
		{
			DrawLine(p[i].x, p[i].y + (p[i].y < p[i-1].y) + (p[i].y < p[i+1].y) - (p[i].y > p[i-1].y) - (p[i].y > p[i+1].y),
					   p[i+1].x, p[i+1].y + (p[i+1].y < p[i].y) + (p[i+1].y < p[i+2].y) - (p[i+1].y > p[i].y) - (p[i+1].y > p[i+2].y));
			DrawLine(p[i].x, p[i].y + (p[i].y < p[i-1].y) + (p[i].y < p[i+1].y) - (p[i].y > p[i-1].y) - (p[i].y > p[i+1].y) + 1,
					   p[i+1].x, p[i+1].y + (p[i+1].y < p[i].y) + (p[i+1].y < p[i+2].y) - (p[i+1].y > p[i].y) - (p[i+1].y > p[i+2].y) + 1);
		} else*/
		{
			DrawLine(dp.getX() + p[i].getX(),   dp.getY() + p[i].getY(), 
					 dp.getX() + p[i+1].getX(), dp.getY() + p[i+1].getY());
//			DrawLine(p[i].x, p[i].y+1, p[i+1].x, p[i+1].y+1);
		}
	}
}
	
void DC::DrawSpline(const unsigned int c, const Point* p, const Point s) const
{
	if((pen->getStyle() == TRANSPARENT_PEN_STYLE)||(c<2)) {
		return;
	}
	Point sp = s + dp;
	for(unsigned int i=c-1;i--;)
//	{
//		aalineColor(surface, p[i].x, p[i].y, p[i+1].x, p[i+1].y, static_cast<Uint32>(getPenColor()));
//		aalineColor(surface, p[i].x, p[i].y+1, p[i+1].x, p[i+1].y+1, static_cast<Uint32>(getPenColor()));
//	}
	{
/*		if((i>0)&&(i<c-2))
		{
			DrawLine(p[i].x, p[i].y + (p[i].y < p[i-1].y) + (p[i].y < p[i+1].y) - (p[i].y > p[i-1].y) - (p[i].y > p[i+1].y),
					   p[i+1].x, p[i+1].y + (p[i+1].y < p[i].y) + (p[i+1].y < p[i+2].y) - (p[i+1].y > p[i].y) - (p[i+1].y > p[i+2].y));
			DrawLine(p[i].x, p[i].y + (p[i].y < p[i-1].y) + (p[i].y < p[i+1].y) - (p[i].y > p[i-1].y) - (p[i].y > p[i+1].y) + 1,
					   p[i+1].x, p[i+1].y + (p[i+1].y < p[i].y) + (p[i+1].y < p[i+2].y) - (p[i+1].y > p[i].y) - (p[i+1].y > p[i+2].y) + 1);
		} else*/
		{
			DrawLine(sp.getX() + p[i].getX(),   sp.getY() + p[i].getY(), 
				     sp.getX() + p[i+1].getX(), sp.getY() + p[i+1].getY());
	//		DrawLine(s.x + p[i].x, s.y + p[i].y+1, s.x + p[i+1].x, s.y + p[i+1].y+1);
		}
	}
	
}
void DC::DrawText(const std::string& text, const Sint16 x, const Sint16 y) const 
{
	if(font->isShadow()) {
		font->DrawText(surface, Color::toSDL_Color(0,0,0), text, x+font->getSize()/6, y+font->getSize()/6);
	}

	font->DrawText(surface, *textColor, text, x, y);
	if(font->isUnderlined())
	{
		Size s = font->getTextExtent(text);
		SDL_Rect r = Rect::createRect(x, y+s.getHeight()*2/3, s.getWidth(), 1);
		SDL_FillRect(surface, &r, *textColor);
	}

}



#if 0
void DC::DrawGridEdgedRoundedRectangle(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height, const Uint16 int radius, std::list<Rect> notDrawRectList) const 
{
	return;
	if((width<2)||(height<2)) return;
	if((x>=getMaxX())||(x<0)) return;
	if((y>=getMaxY())||(y<0)) return;
	unsigned int ww = width;
	unsigned int hh = height;
	if(x+ww>=getMaxX()) ww = getMaxX() - 1 - x;
	if(y+hh>=getMaxY()) hh = getMaxY() - 1 - y;
	bool rounded = false;
	if((radius <= 1)||(ww<2*radius)||(hh<2*radius))
		rounded=true;

	signed int xx = x;
	signed int yy = y;
	unsigned int lastHeight = 0;

	std::list<Rect>::const_iterator i = notDrawRectList.begin();
	while(i!=notDrawRectList.end())
	{
		lastHeight=0;
		while((i!=notDrawRectList.end())&&(yy == i->getTop()))
		{
			DrawRectangle(xx, yy, i->getLeft() - xx, i->getHeight());
			lastHeight = i->getHeight();
			xx = i->getLeft() + i->getWidth();
			i++;
		}
		// rechter Rand
		DrawRectangle(xx, yy, x+ww - xx, lastHeight);
		// neue Zeile
		xx = x;
		yy += lastHeight;
		if((i!=notDrawRectList.end())&&(yy < i->getTop()))
		{
			DrawRectangle(xx, yy, ww, i->getTop() - yy);
			yy = i->getTop();
			xx = x;
		}
	}
	DrawRectangle(xx, yy, x+ww - xx, y + hh - yy);		
				
/*	if(rounded) {
		DrawRectangle(x,y,ww,hh);
		return;
	}
	
	if (brush->getStyle() != TRANSPARENT_BRUSH_STYLE)
		DrawFilledEdgedRound(x, y, ww, hh, radius);
	if (pen->getStyle() != TRANSPARENT_PEN_STYLE)
		DrawEmptyEdgedRound(x, y, ww, hh, radius);*/
}
#endif

void DC::DrawEmptyEdgedRoundedRectangle(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height, const Uint16 radius) const
{
	if((width<2)||(height<2)||(x>=getMaxX())||(y>=getMaxY())||(x<0)||(y<0)) {
		return;
	}
	
	Uint16 mw = width;
	Uint16 mh = height;

	if(x + width >= getMaxX()) {
		mw = getMaxX() - x;
	}
	if(y + height >= getMaxY()) {
		mh = getMaxY() - y;
	}
	
	if((radius <= 1)||(mw<2*radius)||(mh<2*radius))	{
		DrawEmptyRectangle(x,y,mw,mh);
		return;
	}

	if(pen->getStyle() != TRANSPARENT_PEN_STYLE) {
		(*this.*DrawEmptyEdgedRound)(x, y, mw, mh, radius);
	}
}

void DC::DrawEdgedRoundedRectangle(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height, const Uint16 radius) const
{
	if((width<2)||(height<2)||(x>=getMaxX())||(y>=getMaxY())||(x<0)||(y<0)) {
		return;
	}
	
	Uint16 mw = width;
	Uint16 mh = height;

	if(x + width >= getMaxX()) {
		mw = getMaxX() - x;
	}
	if(y + height >= getMaxY()) {
		mh = getMaxY() - y;
	}
	
	if((radius <= 1)||(mw<2*radius)||(mh<2*radius))	{
		DrawRectangle(x,y,mw,mh);
		return;
	}

	if(brush->getStyle() == TRANSPARENT_BRUSH_STYLE)
	{
		if(pen->getStyle() != TRANSPARENT_PEN_STYLE) {
			(*this.*DrawEmptyEdgedRound)(x, y, mw, mh, radius);
		}
	} else if(pen->getStyle() == TRANSPARENT_PEN_STYLE) {
		(*this.*DrawFilledEdgedRound)(x, y, mw, mh, radius);
	} else {
		(*this.*DrawFilledEdgedBorderRound)(x, y, mw, mh, radius); 
	}
}

void DC::DrawRoundedRectangle(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height, const Uint16 radius) const
{
	if((width<2)||(height<2)||(x+width>=getMaxX())||(y+height>=getMaxY())||(x<0)||(y<0)) {
		return;
	}
	
	if((radius <= 1)||(width<2*radius)||(height<2*radius))	{
		DrawRectangle(x,y, width, height);
		return;
	}

	if (brush->getStyle() != TRANSPARENT_BRUSH_STYLE) {
		(*this.*DrawFilledRound)(x, y, width, height, radius);
	}
	if (pen->getStyle() != TRANSPARENT_PEN_STYLE) {
		(*this.*DrawEmptyRound)(x, y, width, height, radius);
	}
}


void DC::DrawTabRectangle(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height) const
{
	if((width<2)||(height<2)||(x+width>=getMaxX())||(y+height>=getMaxY())||(x<0)||(y<0)) {
		return;
	}
	
	(*this.*DrawTab)(x, y, width, height);
}


void DC::DrawRectangle(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height) const
{
	if((width<2)||(height<2)||(width>getMaxX())||(height>getMaxY())||(x<0)||(y<0)) {
		return;
	}

	if(brush->getStyle() != TRANSPARENT_BRUSH_STYLE) {
		SDL_Rect rc = Rect::createRect(x+pen->getWidth(), y+pen->getWidth(), width-2*pen->getWidth(), height-2*pen->getWidth());
		SDL_FillRect(surface, &rc, static_cast<Uint32>(getBrushColor()) );
	}
	DrawEmptyRectangle(x, y, width, height);
}

void DC::DrawEmptyRectangle(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height) const
{
	if(pen->getStyle()==TRANSPARENT_PEN_STYLE)  {
		return;
	}
	if((width<2)||(height<2)||(width>getMaxX())||(height>getMaxY())||(x<0)||(y<0)) {
		return;
	}
	Uint32 pen_col;
	Uint32 dark_pen_col;
	if(pressedRectangle)
	{
		pen_col = static_cast<Uint32>(getPressedPenColor());
		dark_pen_col = static_cast<Uint32>(getDarkPressedPenColor());	
	} else
	{
		pen_col = static_cast<Uint32>(getPenColor());
		dark_pen_col = static_cast<Uint32>(getDarkPenColor());
	}

	SDL_Rect rc = Rect::createRect(x-(pen->getWidth()>>1), y-(pen->getWidth()>>1), width, pen->getWidth());
	SDL_FillRect(surface, &rc, pen_col);
	
	rc = Rect::createRect(x-(pen->getWidth()>>1), y+height-1-(pen->getWidth()>>1), width, pen->getWidth());
	SDL_FillRect(surface, &rc, dark_pen_col);
	
	rc = Rect::createRect(x-(pen->getWidth()>>1), y-(pen->getWidth()>>1), pen->getWidth(), height);
	SDL_FillRect(surface, &rc, pen_col);
	
	rc = Rect::createRect(x+width-1-(pen->getWidth()>>1), y-(pen->getWidth()>>1), pen->getWidth(), height);
	SDL_FillRect(surface, &rc, dark_pen_col);
}

void DC::DrawVerticalLine(const Sint16 x0, const Sint16 y0, const Sint16 y1) const
{
	if((y1<0)||(y0>=getMaxY())||(x0<0)||(x0>=getMaxX())||(y1<y0))
	{
	//	std::ostringstream os;
	//	os.str("");
	//	os << "Line out of range: " << x0 << ", " << y0 << ", " << y1;
	//	to_error_log(os.str());
		return;
	}
	Sint16 yy0;
	Sint16 yy1;
	if(y0 < 0) {
		yy0=0;
	} else {
		yy0=y0;
	}
	if(y1>=getMaxY()) {
		yy1=getMaxY()-1;
	} else {
		yy1=y1;
	}
	(*this.*Draw_VLine)(x0, yy0, yy1);
}

void DC::DrawHorizontalLine(const Sint16 x0, const Sint16 y0, const Sint16 x1) const
{
	if((x1<0)||(x0>=getMaxX())||(y0<0)||(y0>=getMaxY())||(x1<x0))
	{
//	  std::ostringstream os;
//	  os.str("");
//	  os << "Line out of range: " << x0 << ", " << y0 << ", " << y1;
//		toLog("Line out of range");//os.str());
		return;
	}
	Sint16 xx0;
	Sint16 xx1;
	if(x0 < 0) {
		xx0=0;
	} else {
		xx0=x0;
	}
	if(x1>=getMaxX()) {
		xx1=getMaxX()-1;
	} else {
		xx1=x1;
	}
	(*this.*Draw_HLine)(xx0, y0, xx1);
}


const char* DC::dcVersion = "2.00";
