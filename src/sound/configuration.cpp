#if defined(_FMOD_SOUND) || defined(_SDL_MIXER_SOUND)

#include "configuration.hpp"

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
musicVolume(musicVolume),
	soundVolume(soundVolume),
	soundChannels(soundChannels)
{}

static const boost::shared_ptr<const SoundConfiguration> defaultConfiguration = boost::shared_ptr<const SoundConfiguration>(
	new SoundConfiguration("64cc1bc0-261d-11e0-ac64-0800200c9a66" 75, 75, 16));

#endif