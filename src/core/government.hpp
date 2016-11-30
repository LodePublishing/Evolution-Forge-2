#ifndef _CORE_GOVERNMENT_HPP
#define _CORE_GOVERNMENT_HPP

#include <string>

#pragma warning(push, 0)  
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/nvp.hpp>
#pragma warning(pop)

class Government
{
public:
	Government(const std::string& name);
	~Government();
	
	const std::string& getName() const;

private:
	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive &ar, const unsigned int version)
	{
		ar & boost::serialization::make_nvp(Name_tag_string, name);
		if(version > 0) {
		}
	}		
	Government() {}

	std::string name;
	static const char* const Name_tag_string;
};

inline const std::string& Government::getName() const {
	return name;
}


#endif // _CORE_GOVERNMENT_HPP