#pragma warning(push, 0)  
#include <boost/assert.hpp>
#pragma warning(pop)

#include "unittype.hpp"

UnitType::UnitType(const std::string& name, 
	const Race* race,
	const unsigned int buildTime,
	const unsigned int maxCount,	
	const bool corporeal,
	const eUnitMovementType movementType, 
	const unsigned int speed,
	const std::list<UnitResourceType>& resources):
	name(name),
	race(race),
	raceID(race->getID()),
	buildTime(buildTime),
	maxCount(maxCount),
	corporeal(corporeal),
	movementType(movementType),
	speed(speed),
	resources()
{
	this->resources.insert(this->resources.begin(), resources.begin(), resources.end());
}
/*
UnitType::UnitType(const std::string& name, 
	const Race* race,
	const eBuildable buildable,
	const std::vector<UnitResourceType>& resources):
name(name),
	race(race),
	raceID(race->getID()),
	buildable(buildable),
	resources(resources),
	battleStats(NULL)
{	
}
*/

UnitType::~UnitType() {}

/*
UnitType& UnitType::operator=(const UnitType& other) {
	


	name = other.name;
	buildable = other.buildable;
	this->race = other.race;
	this->raceID = other.raceID;
	this->
	
	battleStats = other.getBattleStats();

	resources.clear();
	resources.insert(resources.begin(), other.resources.begin(), other.resources.end());

	return *this;
}*/

// needs to be called after deserialization
void UnitType::setRace(const Race* race) {
	BOOST_ASSERT(race->getID() == raceID);

	this->race = race;
}

const char* const UnitType::Name_tag_string = "name";
const char* const UnitType::Race_tag_string = "race";
const char* const UnitType::BuildTime_tag_string = "time";
const char* const UnitType::MaxCount_tag_string = "max";
const char* const UnitType::ResourceList_tag_string = "resource_list";
const char* const UnitType::Corporeal_tag_string = "corporeal";
const char* const UnitType::MovementType_tag_string = "movement_type";
const char* const UnitType::Speed_tag_string = "speed";

const unsigned int UnitType::MAX_COUNT = 999;
