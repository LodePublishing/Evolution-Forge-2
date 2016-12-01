#if defined(_FMOD_SOUND) || defined(_SDL_MIXER_SOUND)

#ifndef _SOUND_CONFIGURATION_HPP
#define _SOUND_CONFIGURATION_HPP

#pragma warning(push, 0)  
#include <boost/uuid/uuid.hpp>
#include <boost/assert.hpp>
#pragma warning(pop)

#include <misc/uuid.hpp>

class SoundConfiguration : public UUID<SoundConfiguration>
{
	public:
		SoundConfiguration(const boost::uuids::uuid id,
			const unsigned int musicVolume,
			const unsigned int soundVolume,
			const unsigned int soundChannels		
			);
		SoundConfiguration(
			const unsigned int musicVolume,
			const unsigned int soundVolume,
			const unsigned int soundChannels		
			);

		bool isMusic() const;
		bool isSound() const;
		unsigned int getMusicVolume() const;
		unsigned int getSoundVolume() const;
		unsigned int getSoundChannels() const;

		static const boost::shared_ptr<const SoundConfiguration> getDefaultConfiguration();

	private:
		const unsigned int musicVolume;
		const unsigned int soundVolume;
		const unsigned int soundChannels;

		static const boost::shared_ptr<const SoundConfiguration> defaultConfiguration;
};

inline unsigned int SoundConfiguration::getSoundChannels() const {
	return soundChannels;
}

inline unsigned int SoundConfiguration::getMusicVolume() const {
	return musicVolume;
}

inline unsigned int SoundConfiguration::getSoundVolume() const {
	return soundVolume;
}

inline bool SoundConfiguration::isMusic() const {
	return musicVolume > 0;
}

inline bool SoundConfiguration::isSound() const {
	return soundVolume > 0;
}

#endif // _SOUND_CONFIGURATION_HPP


#endif