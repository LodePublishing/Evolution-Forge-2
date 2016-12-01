#ifndef _MAIN_CONFIGURATION_HPP
#define _MAIN_CONFIGURATION_HPP

#include <list>
#include <map>
#include <string>

#pragma warning(push, 0)  
#include <boost/serialization/base_object.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/uuid/uuid.hpp>
#pragma warning(pop)

#include <misc/singleton.hpp>
#include <misc/loadsave.hpp>

// TODO Default configuration
// TODO evtl Liste machen mit Konstanten -> Einfaches Hinzufügen von Optionen möglich

class MainConfiguration : public LoadSave<MainConfiguration>, public Singleton<MainConfiguration>
{
	friend class Singleton<MainConfiguration>;
public:
	const boost::uuids::uuid getLanguageId() const;

private:
	friend class boost::serialization::access;

	template<class Archive> 
	void serialize(Archive& ar, const unsigned int version)
	{ }

	template<class Archive>
	inline friend void save_construct_data(Archive &ar, MainConfiguration* mainConfiguration, const unsigned int version);

	template<class Archive> 
	inline friend void load_construct_data(Archive& ar, MainConfiguration*& mainConfiguration, const unsigned int version);

	const boost::uuids::uuid languageId;

	MainConfiguration();
	~MainConfiguration();
);

inline const boost::uuids::uuid MainConfiguration::getLanguageId() const {
	return languageId;
}


template<class Archive>
void save_construct_data(Archive &ar, MainConfiguration* mainConfiguration, const unsigned int version) { 

	const boost::uuids::uuid& languageId = mainConfiguration->getLanguageId();

	if(version > 0) {
	}

	ar & BOOST_SERIALIZATION_NVP(languageId);
} 

template<class Archive> 
void load_construct_data(Archive& ar, MainConfiguration*& mainConfiguration, const unsigned int version)
{
	boost::uuids::uuid languageId;

	ar & BOOST_SERIALIZATION_NVP(languageId);

	if(version > 0) {
	}

	mainConfiguration->languageId = languageId;
}

#endif // _MAIN_CONFIGURATION_HPP



