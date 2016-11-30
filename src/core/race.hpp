#ifndef _CORE_RACE_HPP
#define _CORE_RACE_HPP

#include <string>

#pragma warning(push, 0)  
#include <boost/serialization/base_object.hpp>
#pragma warning(pop)

#include <uuid.hpp>


class Race : public UUID<Race>
{
public:
	Race(const boost::uuids::uuid id, const std::string& name);
	Race(const std::string& name);
	~Race();

	const std::string& getName() const;

private:
	friend class boost::serialization::access;

	template<class Archive> 
	void serialize(Archive &ar, const unsigned int version)
	{ }

	template<class Archive>
	friend inline void save_construct_data(Archive &ar, const Race* race, const unsigned int version) { 

		const boost::uuids::uuid& id = race->getId();
		const std::string& name = race->getName();

		if(version > 0) {
		}

		ar & BOOST_SERIALIZATION_NVP(id)
		   & BOOST_SERIALIZATION_NVP(name);
	}

	template<class Archive> 
	inline friend void load_construct_data(Archive& ar, Race*& race, const unsigned int version)
	{
		boost::uuids::uuid id;
		std::string name;

		ar & BOOST_SERIALIZATION_NVP(id)
		   & BOOST_SERIALIZATION_NVP(name);

		if(version > 0) {
		}

		::new(race)Race(id, name);
	}

	const std::string name;

	Race& operator=(const Race& other);
};

inline const std::string& Race::getName() const {
	return name;
}

#endif // _CORE_RACE_HPP
