#include "guiinstance.hpp"

#include <misc/exceptions.hpp>
#include <misc/log.hpp>
#include <lang/text_storage.hpp>
#include <misc/ids.hpp>

// TODO SDL_NOFRAME for intro picture!



Gui::Gui(const boost::uuids::uuid id, const std::string& title, const std::string& iconTitle, const boost::shared_ptr<const GuiConfiguration> guiConfiguration):
	UUID<Gui>(id),
	title(title),
	iconTitle(iconTitle),
	guiConfiguration(guiConfiguration)
{ }

Gui::Gui(const std::string& title, const std::string& iconTitle, const boost::shared_ptr<const GuiConfiguration> guiConfiguration):
	UUID<Gui>(),
	title(title),
	iconTitle(iconTitle),
	guiConfiguration(guiConfiguration)
{ }


Gui::~Gui()
{ }



DC* Gui::createScreen() const {
	// ------ INIT SDL AND WINDOW ------
	Uint32 nflags = SDL_INIT_NOPARACHUTE | SDL_INIT_VIDEO | SDL_INIT_TIMER;
#ifdef _SDL_MIXER_SOUND
	nflags |= SDL_INIT_AUDIO;
#endif 
	DC* dc = new DC(nflags);
	
	toInfoLog("* " + TextStorage::instance().get(IDS::START_INIT_SDL_TEXT_ID)->getText());
	toInfoLog("* " + TextStorage::instance().get(guiConfiguration->isFullScreen() ? IDS::START_SET_FULLSCREEN_MODE_TEXT_ID:IDS::START_SET_WINDOW_MODE_TEXT_ID)->getText());
	
	Uint32 flags = SDL_HWSURFACE|SDL_ASYNCBLIT|SDL_HWACCEL|SDL_HWPALETTE|SDL_SRCCOLORKEY|SDL_RLEACCEL|SDL_SRCALPHA|SDL_PREALLOC|SDL_DOUBLEBUF;
	if(guiConfiguration->isFullScreen()) {
		flags |= SDL_FULLSCREEN;
	}

	// need to be called before initialization of dc
	Size resolution_size = guiConfiguration->getResolutionSize();
	eBitDepth bit_depth = guiConfiguration->getBitDepth();

	try {
		dc->setScreen(resolution_size, bit_depth, flags);
	} catch(...) {
		delete dc;
		dc = NULL;
		throw SDLException(TextStorage::instance().get(IDS::START_UNABLE_TO_INIT_SDL_TEXT_ID)->getText() + " [SDL ERROR: \"" + SDL_GetError() + "\"]");
	}

	if ( !dc->valid() ) {
		delete dc;
		dc = NULL;
		throw SDLException(TextStorage::instance().get(IDS::START_ERROR_SETTING_VIDEO_MODE_TEXT_ID)->getText() + " [SDL ERROR: \"" + SDL_GetError() + "\"]");
	}

	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

	toInfoLog(dc->printHardwareInformation());
	toInfoLog("* " + TextStorage::instance().get(IDS::START_CREATED_SURFACE_TEXT_ID)->getText() + " " + dc->printSurfaceInformation());
	// ------ END INIT SDL AND WINDOW ------

	SDL_WM_SetCaption(title.c_str(),"");

	// ------ INIT SDL_TTF ------
	toInfoLog("* " + TextStorage::instance().get(IDS::START_INIT_SDL_TRUETYPE_FONTS_TEXT_ID)->getText());
	if(TTF_Init()==-1) {
		delete dc;
		dc = NULL;
		throw SDLException(TextStorage::instance().get(IDS::START_INIT_SDL_TTF_ERROR_TEXT_ID)->getText() + " [\"" + TTF_GetError() + "\"]");
	}
	atexit(TTF_Quit); 
	// ------ END INIT SDL_TTF ------



	return dc;
}




//void Gui::animateWaitCursor();


void Gui::resetScreen(DC* dc) const
{
	BOOST_ASSERT(dc);
	dc->setScreen(guiConfiguration->getResolutionSize(), guiConfiguration->getBitDepth(), dc->flags());
}

	
const std::string Gui::GVERSION = "2.00";
