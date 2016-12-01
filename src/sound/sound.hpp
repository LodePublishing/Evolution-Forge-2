#ifndef _SOUND_SOUND_HPP
#define _SOUND_SOUND_HPP

#if defined(_FMOD_SOUND) || defined(_SDL_MIXER_SOUND)

#include "export.hpp"

#pragma warning(push, 0)  
#ifdef _FMOD_SOUND
#include <fmod.hpp>
#elif _SDL_MIXER_SOUND
#include <SDL_mixer.h>
#endif
#pragma warning(pop)

#include <misc/uuid.hpp>


class SOUND_API Sound : public UUID<Sound>
{
	public:
#ifdef _FMOD_SOUND
	    Sound(FMOD::Sound* t);
		operator FMOD::Sound*();
		(FMOD::Sound*) operator->();		
#elif _SDL_MIXER_SOUND
		Sound(Mix_Chunk* t);
		operator Mix_Chunk*();
		Mix_Chunk* operator->();		
#endif
	private:
//		std::string name;
#ifdef _FMOD_SOUND
		(FMOD::Sound)* sound;
#elif _SDL_MIXER_SOUND
		Mix_Chunk* sound;
#endif
};

#ifdef _FMOD_SOUND
	inline Sound::Sound(FMOD::Sound* t) {
		sound = t;
	}

	inline Sound::operator FMOD::Sound*() {
		return sound;
	}

	inline FMOD::Sound* Sound::operator->() {
		return sound;
	}

#elif _SDL_MIXER_SOUND
	inline Sound::Sound(Mix_Chunk* t) {
		sound = t;
	}

	inline Sound::operator Mix_Chunk*() {
		return sound;
	}

	inline Mix_Chunk* Sound::operator->() {
		return sound;
	}
#endif


#endif

#endif // _SOUND_SOUND_HPP