#if defined(_FMOD_SOUND) || defined(_SDL_MIXER_SOUND)

#include "soundconfiguration.hpp"

SoundConfiguration::SoundConfiguration(const boost::uuids::uuid id,
	const unsigned int musicVolume,
	const unsigned int soundVolume,
	const unsigned int soundChannels		
	):
UUID<SoundConfiguration>(id),
	musicVolume(musicVolume),
	soundVolume(soundVolume),
	soundChannels(soundChannels)
{}

SoundConfiguration::SoundConfiguration(
	const unsigned int musicVolume,
	const unsigned int soundVolume,
	const unsigned int soundChannels		
	):
UUID<SoundConfiguration>(),
musicVolume(musicVolume),
	soundVolume(soundVolume),
	soundChannels(soundChannels)
{}

#endif