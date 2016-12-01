#pragma warning(push, 0)  
#include <boost/assert.hpp>
#pragma warning(pop)

#include "unittype.hpp"


UnitType::UnitType(const boost::uuids::uuid id,
	const std::string& name, 
	const boost::shared_ptr<const Race> race,
	const std::list<UnitResourceType>& resources,
	const bool corporeal,
	const unsigned int maxCount,	
	const unsigned int buildTime,	
	const eUnitMovementType movementType, 
	const unsigned int speed,
	const unsigned int upgradedSpeed):
UUID<UnitType>(id),
	name(name),
	race(race),
	raceId(race->getId()),
	resources(resources),
	corporeal(corporeal),
	maxCount(maxCount),
	buildTime(buildTime),	
	movementType(movementType),
	speed(speed),
	upgradedSpeed(upgradedSpeed)
{ }

UnitType::UnitType(const std::string& name, 
	const boost::shared_ptr<const Race> race,
	const std::list<UnitResourceType>& resources,
	const bool corporeal,
	const unsigned int maxCount,	
	const unsigned int buildTime,	
	const eUnitMovementType movementType, 
	const unsigned int speed,
	const unsigned int upgradedSpeed):
name(name),
	race(race),
	raceId(race->getId()),
	resources(resources),
	corporeal(corporeal),
	maxCount(maxCount),
	buildTime(buildTime),	
	movementType(movementType),
	speed(speed),
	upgradedSpeed(upgradedSpeed)
{ }

UnitType::~UnitType() {}