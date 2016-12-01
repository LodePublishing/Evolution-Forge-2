#ifndef _CORE_UNITRESOURCETYPE_HPP
#define _CORE_UNITRESOURCETYPE_HPP

#include <list>

#include <misc/uuid.hpp>

#include "enums/unitresourcetype.hpp"

class UnitResourceType
{
public:
	UnitResourceType(const eUnitResourceType resourceType, 
		const signed int amount,
		const std::list<std::list<boost::uuids::uuid> >& unitTypeIdList);
	~UnitResourceType() {}

	eUnitResourceType getResourceType() const;
	signed int getAmount() const;

	// returns the ID of the unit type that is needed (e.g. the supply resource, a facility unit type id etc.)
	// it is a list of list, all lists in the top list are ORed (makes only sense with prerequisites)
	const std::list<std::list<boost::uuids::uuid> >& getUnitTypeIdList() const;

	static const UnitResourceType NOT_BUILDABLE_TYPE;

private:
	eUnitResourceType resourceType;
	signed int amount;
	std::list<std::list<boost::uuids::uuid> > unitTypeIdList; // corresponding unit (for some types)
};

inline eUnitResourceType UnitResourceType::getResourceType() const {
	return resourceType;
}

inline signed int UnitResourceType::getAmount() const {
	return amount;
}

inline const std::list<std::list<boost::uuids::uuid> >& UnitResourceType::getUnitTypeIdList() const {
	return unitTypeIdList;
}


#endif
