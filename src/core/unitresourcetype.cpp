#include "unitresourcetype.hpp"

UnitResourceType::UnitResourceType(const eUnitResourceType resourceType, 
		const signed int amount,
		const std::list<std::list<unsigned int> >& unitTypeIdList):
	resourceType(resourceType),
	amount(amount),
	unitTypeIdList(unitTypeIdList)	
{ }