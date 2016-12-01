#if defined(_FMOD_SOUND) || defined(_SDL_MIXER_SOUND)

#ifndef _SOUND_CONFIGURATION_HPP
#define _SOUND_CONFIGURATION_HPP

#pragma warning(push, 0)  
#include <boost/uuid/uuid.hpp>
#include <boost/assert.hpp>
#pragma warning(pop)

#include <misc/uuid.hpp>
#include <misc/loadsave.hpp>

class SoundConfiguration : public UUID<SoundConfiguration>, public LoadSave<SoundConfiguration>
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
friend class boost::serialization::access;

	template<class Archive> 
	void serialize(Archive &ar, const unsigned int version)
	{ }	

	template<class Archive>
	inline friend void save_construct_data(Archive &ar, SoundConfiguration* soundConfiguration, const unsigned int version) { 

		const boost::uuids::uuid& id = guiConfiguration->getId();

		const unsigned int& musicVolume = soundConfiguration->getMusicVolume();
		const unsigned int& soundVolume = soundConfiguration->getSoundVolume();
		const unsigned int& soundChannels = soundConfiguration->getSoundChannels();
				
		if(version > 0) {
		}

		ar & BOOST_SERIALIZATION_NVP(id)
		   & BOOST_SERIALIZATION_NVP(musicVolume)
		   & BOOST_SERIALIZATION_NVP(soundVolume)
		   & BOOST_SERIALIZATION_NVP(soundChannels)		
	}

	template<class Archive> 
	inline friend void load_construct_data(Archive& ar, SoundConfiguration*& soundConfiguration, const unsigned int version)
	{
		boost::uuids::uuid& id;

		unsigned int musicVolume;
		unsigned int soundVolume;
		unsigned int soundChannels;

		ar & BOOST_SERIALIZATION_NVP(id)
		   & BOOST_SERIALIZATION_NVP(musicVolume)
		   & BOOST_SERIALIZATION_NVP(soundVolume)
		   & BOOST_SERIALIZATION_NVP(soundChannels);
		
		if(version > 0) {
		}

		::new(soundConfiguration)SoundConfiguration(id, musicVolume, soundVolume, soundChannels);
	}

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