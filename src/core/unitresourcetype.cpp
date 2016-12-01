#include "unitresourcetype.hpp"

UnitResourceType::UnitResourceType(const eUnitResourceType resourceType, 
	const signed int amount,
	const std::list<std::list<boost::uuids::uuid> >& unitTypeIdList):
resourceType(resourceType),
	amount(amount),
	unitTypeIdList(unitTypeIdList)	
{ }

const UnitResourceType UnitResourceType::NOT_BUILDABLE_TYPE = UnitResourceType(NOT_BUILDABLE, 0, std::list<std::list<boost::uuids::uuid> >());