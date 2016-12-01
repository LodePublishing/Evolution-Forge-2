#ifndef _SOUND_SOUNDPROCESSOR_HPP
#define _SOUND_SOUNDPROCESSOR_HPP

#if defined(_FMOD_SOUND) || defined(_SDL_MIXER_SOUND)
#include <sound/sound.hpp>
#include <sound/music.hpp>
#endif 

class SoundProcessor
{
public:
	
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
private:
		const boost::shared_ptr<const SoundConfiguration> soundConfiguration;

	
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
};

#endif