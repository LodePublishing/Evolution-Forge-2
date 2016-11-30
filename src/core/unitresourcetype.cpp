#include "unitresourcetype.hpp"

UnitResourceType::UnitResourceType(const eUnitResourceType resourceType, 
		const signed int amount,
		const std::list<std::list<boost::uuids::uuid> >& unitTypeIdList):
	resourceType(resourceType),
	amount(amount),
	unitTypeIdList(unitTypeIdList)	
{ }