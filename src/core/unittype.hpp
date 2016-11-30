#ifndef _CORE_UNITTYPE_HPP
#define _CORE_UNITTYPE_HPP

#include <string>
#include <list>
#include <vector>

#pragma warning(push, 0)  
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/assign/list_of.hpp>
#pragma warning(pop)

#include <uuid.hpp>

#include "unitresourcetype.hpp"
#include "race.hpp"
#include "enums/unitmovementtypeenums.hpp"


class UnitType : public UUID<UnitType>
{
public:
	
	UnitType(const boost::uuids::uuid id,
		const std::string& name, 
		const boost::shared_ptr<const Race> race, // TODO relevant?
		const std::list<UnitResourceType>& resources = boost::assign::list_of(UnitResourceType::NOT_BUILDABLE_TYPE),
		const bool corporeal = false,
		const unsigned int maxCount = 0,
		const unsigned int buildTime = 0,		
		const eUnitMovementType movementType = NO_MOVEMENT_TYPE,
		const unsigned int speed = 0,
		const unsigned int upgradedSpeed = 0);

	UnitType(const std::string& name, 
		const boost::shared_ptr<const Race> race,
		const std::list<UnitResourceType>& resources = boost::assign::list_of(UnitResourceType::NOT_BUILDABLE_TYPE),
		const bool corporeal = false,
		const unsigned int maxCount = 0,
		const unsigned int buildTime = 0,
		const eUnitMovementType movementType = NO_MOVEMENT_TYPE, 
		const unsigned int speed = 0,
		const unsigned int upgradedSpeed = 0);
	
	~UnitType();

	const std::string& getName() const;
	const boost::shared_ptr<const Race> getRace() const;
	const boost::uuids::uuid getRaceId() const;
	const std::list<UnitResourceType>& getResources() const; // TODO evtl Map machen
	bool isCorporeal() const;
	unsigned int getMaxCount() const;
	unsigned int getBuildTime() const;	
	eUnitMovementType getMovementType() const;
	unsigned int getSpeed() const;
	unsigned int getUpgradedSpeed();

private:
	friend class boost::serialization::access;

	template<class Archive> 
	void serialize(Archive &ar, const unsigned int version)
	{ }

	template<class Archive> friend void save_construct_data(Archive &ar, const UnitType* unitType, const unsigned int version);
	template<class Archive> friend void load_construct_data(Archive& ar, UnitType*& unitType, const unsigned int version);

	// mandatory fields
	const std::string name;
	const boost::shared_ptr<const Race> race;
	const boost::uuids::uuid raceId;
	const std::list<UnitResourceType> resources;
	// maximal number of units of this type a player can have
	const unsigned int maxCount;
	const unsigned int buildTime;
	const bool corporeal;
	const eUnitMovementType movementType;
	const unsigned int speed;	
	const unsigned int upgradedSpeed;
	
	UnitType& operator=(const UnitType& other);	
};

inline unsigned int UnitType::getBuildTime() const {
	return buildTime;
}

inline unsigned int UnitType::getMaxCount() const {
	return maxCount;
}

inline const std::string& UnitType::getName() const {
	return name;
}

inline const std::list<UnitResourceType>& UnitType::getResources() const {
	return resources;
}

inline const boost::shared_ptr<const Race> UnitType::getRace() const {
	return race;
}

inline const boost::uuids::uuid UnitType::getRaceId() const {
	return raceId;
}

inline bool UnitType::isCorporeal() const {
	return corporeal;
}

inline unsigned int UnitType::getSpeed() const {
	return speed;
}

inline unsigned int UnitType::getUpgradedSpeed() const {
	return upgradedSpeed;
}

inline eUnitMovementType UnitType::getMovementType() const {
	return movementType;
}

#endif
