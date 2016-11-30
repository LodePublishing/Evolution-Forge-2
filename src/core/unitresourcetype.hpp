#ifndef _CORE_UNITRESOURCETYPE_HPP
#define _CORE_UNITRESOURCETYPE_HPP

#include <list>

#pragma warning(push, 0)  
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/nvp.hpp>
#pragma warning(pop)

#include "enums/unitresourcetypeenums.hpp"


class UnitResourceType
{
public:
	UnitResourceType(const eUnitResourceType resourceType, 
		const std::list<std::list<unsigned int> >& unitTypeIDList, 
		const signed int amount);
	~UnitResourceType() {}


	eUnitResourceType getResourceType() const;
	
	// returns the ID of the unit type that is needed (e.g. the supply resource, a facility unit type id etc.)
	// it is a list of list, all lists in the top list are ORed (makes only sense with prerequisites)
	const std::list<std::list<unsigned int> >& getUnitTypeIDList() const;
	signed int getAmount() const;

	static const char* const ResourceType_tag_string;
	static const char* const UnitTypeIDList_tag_string;
	static const char* const Amount_tag_string;
	
private:
	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive &ar, const unsigned int version)
	{
		ar & boost::serialization::make_nvp(ResourceType_tag_string, resourceType);
		ar & boost::serialization::make_nvp(UnitTypeIDList_tag_string, unitTypeIDList);
		ar & boost::serialization::make_nvp(Amount_tag_string, amount);
		if(version > 0) {
		}
	}
	// only for serialization / deserialization
	UnitResourceType();

	eUnitResourceType resourceType;
	std::list<std::list<unsigned int> > unitTypeIDList; // corresponding unit (for some types)
	signed int amount;
};

inline eUnitResourceType UnitResourceType::getResourceType() const {
	return resourceType;
}

inline const std::list<std::list<unsigned int> >& UnitResourceType::getUnitTypeIDList() const {
	return unitTypeIDList;
}

inline signed int UnitResourceType::getAmount() const {
	return amount;
}

#endif
