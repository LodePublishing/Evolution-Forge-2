#pragma warning(push, 0)  
#include <boost/assert.hpp>
#pragma warning(pop)

#include "unittype.hpp"

UnitType::UnitType(const unsigned int id,
		const std::string& name, 
		const boost::shared_ptr<const Race> race,
		const unsigned int buildTime,
		const unsigned int maxCount,		
		const bool corporeal,
		const eUnitMovementType movementType, 
		const unsigned int speed,
		const std::list<UnitResourceType>& resources):
	ID<UnitType>(id),
	name(name),
	race(race),
	raceId(race->getId()),
	buildTime(buildTime),
	maxCount(maxCount),
	corporeal(corporeal),
	movementType(movementType),
	speed(speed),
	resources(resources)
{ }

UnitType::UnitType(const std::string& name, 
	const boost::shared_ptr<const Race> race,
	const unsigned int buildTime,
	const unsigned int maxCount,	
	const bool corporeal,
	const eUnitMovementType movementType, 
	const unsigned int speed,
	const std::list<UnitResourceType>& resources):
	name(name),
	race(race),
	raceId(race->getId()),
	buildTime(buildTime),
	maxCount(maxCount),
	corporeal(corporeal),
	movementType(movementType),
	speed(speed),
	resources(resources)
{ }

UnitType::~UnitType() {}

const unsigned int UnitType::MAX_COUNT = 999;
