#include "dc.hpp"
#include <cstdlib>

#include <misc/exceptions.hpp>
#include <sstream>
#include <lang/text_storage.hpp>
#include <misc/ids.hpp>

// ---- INIITIALIZATION ----

DC::DC(Uint32 initflags):
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
	brightness(0),
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


const char* DC::dcVersion = "2.00";
