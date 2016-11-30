#ifndef _CORE_RACE_HPP
#define _CORE_RACE_HPP

#include <string>

#pragma warning(push, 0)  
#include <boost/serialization/base_object.hpp>
#pragma warning(pop)

#include "id.hpp"

class Race : public ID<Race>
{
public:
	Race(const std::string& name);
	~Race();

	const std::string& getName() const;

private:
	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive &ar, const unsigned int version)
	{
		ar & boost::serialization::make_nvp(ID_tag_string, id);
		ar & boost::serialization::make_nvp(Name_tag_string, name);
		if(version > 0) {
		}
	}	
	// only use for serialization / deserialization
	Race();	

	std::string name;

	static const char* const Name_tag_string;
};

inline const std::string& Race::getName() const {
	return name;
}


#endif // _CORE_RACE_HPP
