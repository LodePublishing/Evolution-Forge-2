#ifndef _MAIN_INIT_HPP
#define _MAIN_INIT_HPP

#if defined(_FMOD_SOUND) || defined(_SDL_MIXER_SOUND)
#include <sound/sound.hpp>
#include <sound/music.hpp>
#endif 

#include <sdl/dc.hpp>

#include "configuration.hpp"

#include <misc/singleton.hpp>


#pragma warning(push, 0)
#include <boost/assert.hpp>
#pragma warning(pop)

class Init : public Singleton<Init> // TODO LoadSave?
{
	friend class Singleton<Init>;
	public:
		void start(const std::list<std::string>& parameterList, const std::string& windowTitle);

		void loadConfigurationFile();

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
		~Init();
	private:
		Init();

		std::string printHardwareInformation();
		std::string printSurfaceInformation(DC* surface);
		
		DC* dc;		

		
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
			
};

inline Size Init::getResolutionSize() const {
	if(!dc) {
		return Configuration::getResolutionSize();
	}
	return dc->getSize();
}


inline eBitDepth Init::getBitDepth() const {
	if(!dc) {
		return Configuration::getBitDepth();
	}
	return dc->getBitDepth();
}

inline bool Init::isFullScreen() const {
	if(!dc) {
		return Configuration::isFullScreen();
	}
	return dc->isFullScreen();
}




#endif // _MAIN_INIT_HPP