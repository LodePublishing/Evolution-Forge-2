#pragma warning(push, 0)  
#include <boost/assert.hpp>
#pragma warning(pop)

#include "unittype.hpp"

#include <globalstorage.hpp>

UnitType::UnitType(const boost::uuids::uuid id,
	const std::string& name, 
	const boost::shared_ptr<const Race> race,
	const std::list<UnitResourceType>& resources,
	const unsigned int maxCount,	
	const unsigned int buildTime,
	const bool corporeal,
	const eUnitMovementType movementType, 
	const unsigned int speed,
	const unsigned int upgradedSpeed):
UUID<UnitType>(id),
	name(name),
	race(race),
	raceId(race->getId()),
	resources(resources),
	maxCount(maxCount),
	buildTime(buildTime),
	corporeal(corporeal),
	movementType(movementType),
	speed(speed),
	upgradedSpeed(upgradedSpeed)
{ }

UnitType::UnitType(const std::string& name, 
	const boost::shared_ptr<const Race> race,
	const std::list<UnitResourceType>& resources,
	const unsigned int maxCount,	
	const unsigned int buildTime,
	const bool corporeal,
	const eUnitMovementType movementType, 
	const unsigned int speed,
	const unsigned int upgradedSpeed):
name(name),
	race(race),
	raceId(race->getId()),
	resources(resources),
	maxCount(maxCount),
	buildTime(buildTime),
	corporeal(corporeal),
	movementType(movementType),
	speed(speed),
	upgradedSpeed(upgradedSpeed)
{ }

UnitType::~UnitType() {}

template<class Archive>
void save_construct_data(Archive &ar, const UnitType* unitType, const unsigned int version) { 

	const boost::uuids::uuid& id = unitType->getId();
	const std::string& name = unitType->getName();
	const boost::uuids::uuid& raceId = unitType->getRaceId();
	const std::list<UnitResourceType>& resources = unitType->getResources();
	const unsigned int& maxCount = unitType->getMaxCount();
	const unsigned int& buildTime = unitType->getBuildTime();
	const bool& corporeal = unitType->isCorporeal();
	const eUnitMovementType& movementType = unitType->getMovementType();
	const unsigned int& speed = unitType->getSpeed();
	const unsigned int& upgradedSpeed = unitType->getUpgradedSpeed();

	if(version > 0) {
	}

	ar & BOOST_SERIALIZATION_NVP(id)
		& BOOST_SERIALIZATION_NVP(name)
		& BOOST_SERIALIZATION_NVP(raceId)
		& BOOST_SERIALIZATION_NVP(resources)
		& BOOST_SERIALIZATION_NVP(maxCount)
		& BOOST_SERIALIZATION_NVP(buildTime)
		& BOOST_SERIALIZATION_NVP(corporeal)
		& BOOST_SERIALIZATION_NVP(movementType)
		& BOOST_SERIALIZATION_NVP(speed)
		& BOOST_SERIALIZATION_NVP(upgradedSpeed);
}

template<class Archive> 
void load_construct_data(Archive& ar, UnitType*& unitType, const unsigned int version)
{
	boost::uuids::uuid id;
	std::string name;
	boost::uuids::uuid raceId;
	std::list<UnitResourceType> resources;
	unsigned int maxCount;
	unsigned int buildTime;
	bool corporeal;
	eUnitMovementType movementType;
	unsigned int speed;
	unsigned int upgradedSpeed;

	ar & BOOST_SERIALIZATION_NVP(id)
		& BOOST_SERIALIZATION_NVP(name)
		& BOOST_SERIALIZATION_NVP(raceId)
		& BOOST_SERIALIZATION_NVP(resources)
		& BOOST_SERIALIZATION_NVP(maxCount)
		& BOOST_SERIALIZATION_NVP(buildTime)
		& BOOST_SERIALIZATION_NVP(corporeal)
		& BOOST_SERIALIZATION_NVP(movementType)
		& BOOST_SERIALIZATION_NVP(speed)
		& BOOST_SERIALIZATION_NVP(upgradedSpeed);		

	if(version > 0) {
	}

	::new(unitType)UnitType(id, name, GlobalStorage::instance().getRace(raceId), resources, maxCount, buildTime, corporeal, movementType, speed, upgradedSpeed);
}