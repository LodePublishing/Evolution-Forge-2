#include "unitresourcetype.hpp"

UnitResourceType::UnitResourceType(const eUnitResourceType resourceType, 
		const std::list<std::list<unsigned int> >& unitTypeIDList, 
		const signed int amount):
	resourceType(resourceType),
	unitTypeIDList(unitTypeIDList),
	amount(amount)
{}

// only for deserialization / serialization
UnitResourceType::UnitResourceType():
	resourceType(MAX_GAME_RESOURCE_TYPES),
	unitTypeIDList(),
	amount(0)
{}

const char* const UnitResourceType::ResourceType_tag_string = "type";
const char* const UnitResourceType::UnitTypeIDList_tag_string = "unittypeidList";
const char* const UnitResourceType::Amount_tag_string = "amount";