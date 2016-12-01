#ifndef _GUI_GUI_HPP
#define _GUI_GUI_HPP

#if defined(_FMOD_SOUND) || defined(_SDL_MIXER_SOUND)
#include <sound/sound.hpp>
#include <sound/music.hpp>
#endif 

#include <set>
#include <map>
#include <math.h>

#include "enums/textid.hpp"
#include "tooltip.hpp"
#include "window.hpp"
#include "guiconfiguration.hpp"

#pragma warning(push, 0)
#include <boost/assert.hpp>
#pragma warning(pop)

class Gui : public UUID<Gui> {
	public:
		Gui(const boost::uuids::uuid id, const std::string& title, const boost::shared_ptr<const GuiConfiguration> guiConfiguration);
		Gui(const std::string& title, const boost::shared_ptr<const GuiConfiguration> guiConfiguration);
		~Gui();

		const std::string& getTitle() const;
		const boost::uuids::uuid getGuiConfigurationId() const;

		void process();
		bool isMouseInside(const Rect& rect) const;
		void setMouse(const Point& p, SDL_Object* root_object);
		const Point& getMouse() const;

		void leftDown(const Point& mouse, SDL_Object* root_object);
		void leftUp(const Point& mouse, SDL_Object* root_object);
		void rightDown(const Point& mouse, SDL_Object* root_object);
		void rightUp(const Point& mouse, SDL_Object* root_object);

		void wheelUp();
		void wheelDown();

		void wheelToTop();
		void wheelToBottom();

		
		Uint16 getMaxX() const;
		Uint16 getMaxY() const;

		bool isWindowSelected() const;
		Window* getCurrentWindow() const; 
		void setWindowSelected(const bool selected = true);
		void setCurrentWindow(Window* window);
		void resetWindow();	

		SDL_PixelFormat* getCurrentPixelFormat() const;

		static const std::string& getVersion();

		void setToolTip(ToolTip* tooltip);
		ToolTip* getToolTip() const;
		void setToolTipParent(const Object* parent);
		const Object* getToolTipParent() const;

//		void setCursor(Cursor* cursor);

		bool isFullScreen() const;
		Size getResolutionSize() const;
		eBitDepth getBitDepth() const;

		bool setBitDepth(const eBitDepth bit_depth);
		bool setFullScreen(const bool full_screen);
		bool setResolutionSize(const Size& size);

		void addMessage(const std::string& msg);
		const std::list<std::string>& getRemainingMessages() const;
		void clearMessages();

		void resetScreen();

// ------------------ SOUND AND MUSIC START -----------------------
#if defined(_FMOD_SOUND) || defined(_SDL_MIXER_SOUND)
//		bool setMusicVolume(const unsigned int music_volume);
//		bool setSoundVolume(const unsigned int sound_volume);

		void playSound(Sound* play_sound, const unsigned int x);
		void playMusic(Music* play_music, const bool loop = true);
		Sound* loadSound(const std::string file_name) const;
		Music* loadMusic(const std::string file_name) const;

		void stopMusic();

		void releaseSoundEngine();

#ifdef _SDL_MIXER_SOUND
		static void transitionMusic(void);
		static void soundChannelDone(int channel);
#endif

#endif
// ------------------ SOUND AND MUSIC END -----------------------
		
		

		

		std::string printHardwareInformation();
		std::string printSurfaceInformation(DC* surface);

private:
		void init();
		const std::string title;

		DC* dc;
		SDL_Cursor* defaultCursor;
		static std::string GVERSION;
		std::list<std::string> remainingMessages;

		const boost::shared_ptr<const GuiConfiguration> guiConfiguration;

		ToolTip* tooltip;
		const Object* toolTipParent;
		Window* currentWindow;
		bool windowSelected;

		// TODO currentButton


		unsigned int mouseType;
		Point mouse;


		
// ------------------ SOUND AND MUSIC BEGIN -----------------------
#if defined(_FMOD_SOUND) || defined(_SDL_MIXER_SOUND)

		void initSoundEngine();

		void printSoundInformation() const;
		void clearSoundsToPlay();
		void clearSoundChannels();
		void processSoundChannels();
	
		bool soundInitialized;
		std::list<std::pair<Sound*, float> > soundsToPlay;

#ifdef _FMOD_SOUND
		FMOD::Channel* musicChannel;
		FMOD::System* soundEngine;
		std::list<FMOD::Channel*> soundChannel;
#elif _SDL_MIXER_SOUND
		// need to be static because of callback functions!
		static Mix_Music* currentMusic;
		static Mix_Music* nextMusic;
		static std::list<int> soundChannel;
#endif
#endif
// ------------------ SOUND AND MUSIC END -----------------------


	static std::map<const eTextId, const boost::uuids::uuid> textMap;
	static std::map<const eTextId, const boost::uuids::uuid> initTextMap();
	
};

inline const std::string& Gui::getTitle() const {
	return title;
}

inline const boost::uuids::uuid Gui::getGuiConfigurationId() const {
	return guiConfiguration->getId();
}


inline Size Gui::getResolutionSize() const {
	if(!dc->getSurface()) {
		return guiConfiguration->getResolutionSize();
	}
	return dc->getSize();
}


inline eBitDepth Gui::getBitDepth() const {
	if(!dc->getSurface()) {
		return guiConfiguration->getBitDepth();
	}
	return dc->getBitDepth();
}

inline bool Gui::isFullScreen() const {
	if(!dc->getSurface()) {
		return guiConfiguration->isFullScreen();
	}
	return dc->isFullScreen();
}


inline const std::list<std::string>& Gui::getRemainingMessages() const {
	return remainingMessages;
}

inline void Gui::clearMessages() {
	remainingMessages.clear();
}



inline void Gui::setToolTip(ToolTip* tooltip) {
	this->tooltip = tooltip;
}

inline ToolTip* Gui::getToolTip() const {
	return this->tooltip;
}

inline void Gui::setToolTipParent(const Object* parent) {
	this->toolTipParent = parent;
}

inline const Object* Gui::getToolTipParent() const {
	return toolTipParent;
}


inline const std::string& Gui::getVersion() {
	return GVERSION;
}

inline SDL_PixelFormat* Gui::getCurrentPixelFormat() const {
	BOOST_ASSERT(dc);
	BOOST_ASSERT(dc->getSurface());
	return dc->getSurface()->format;
}

inline bool Gui::isWindowSelected() const {
	return this->windowSelected;
}

inline Window* Gui::getCurrentWindow() const {
	return this->currentWindow;
}

inline void Gui::setWindowSelected(const bool selected) {
	windowSelected = selected;
}

inline void Gui::setCurrentWindow(Window* window) {
	currentWindow = window;
}

inline const Point& Gui::getMouse() const {
	return mouse;
}

inline bool Gui::isMouseInside(const Rect& rect) const {
	return rect.isTopLeftCornerInside(mouse);
}

inline Uint16 Gui::getMaxX() const {
	BOOST_ASSERT(dc);
	return dc->getMaxX();
}

inline Uint16 Gui::getMaxY() const {
	BOOST_ASSERT(dc);
	return dc->getMaxY();
}





#endif // _GUI_GUI_HPP



