#ifndef _CORE_UNIT_HPP
#define _CORE_UNIT_HPP

#include <vector>
#include <list>
#include <map>

#pragma warning(push, 0)  
#include <boost/serialization/base_object.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#pragma warning(pop)

#include <uuid.hpp>

#include "unittype.hpp"


struct UnitLocalNeutralKey
{
//	UnitLocalNeutralKey():locationId(0),unitTypeId(0) {}
	UnitLocalNeutralKey(boost::uuids::uuid locationId, boost::uuids::uuid unitTypeId) : locationId(locationId), unitTypeId(unitTypeId) {}

	boost::uuids::uuid locationId;
	boost::uuids::uuid unitTypeId;

	bool operator<(const UnitLocalNeutralKey& other) const { return locationId < other.locationId || (locationId == other.locationId && unitTypeId < other.unitTypeId); }
};

struct UnitLocalKey
{
//	UnitLocalKey():locationId(0),playerId(0),unitTypeId(0) {}
	UnitLocalKey(boost::uuids::uuid locationId, boost::uuids::uuid playerId, boost::uuids::uuid unitTypeId) : locationId(locationId), playerId(playerId), unitTypeId(unitTypeId) {}

	boost::uuids::uuid locationId;
	boost::uuids::uuid playerId;
	boost::uuids::uuid unitTypeId;

	bool operator<(const UnitLocalKey& other) const { return locationId < other.locationId || (locationId == other.locationId && playerId < other.playerId) || (locationId == other.locationId && playerId == other.playerId && unitTypeId < other.unitTypeId);}
};

struct UnitGlobalKey
{
//	UnitGlobalKey():playerId(0),unitTypeId(0) {}
	UnitGlobalKey(boost::uuids::uuid playerId, boost::uuids::uuid unitTypeId):playerId(playerId),unitTypeId(unitTypeId) {}

	boost::uuids::uuid playerId;
	boost::uuids::uuid unitTypeId;

	bool operator<(const UnitGlobalKey& other) const { return playerId < other.playerId || (playerId == other.playerId && unitTypeId < other.unitTypeId); }
};

class Player;
class Location;
class Units;
class Unit;

/**
* A single unit / building / research etc.
*/
class Unit : public UUID<Unit>,  public boost::enable_shared_from_this<Unit>
{
public:
	// Create Unit
	Unit(const boost::shared_ptr<const Player> player,
		const boost::shared_ptr<const UnitType> unitType,
		const boost::shared_ptr<const Location> location,
		const boost::shared_ptr<Units> globalUnits,
		const unsigned int count = 1,
		const unsigned int remainingConstructionTime = 0,
		const std::list<boost::shared_ptr<Unit> > occupiedFacilityList = std::list<boost::shared_ptr<Unit> >()
		);
	Unit(const boost::uuids::uuid id,
		const boost::shared_ptr<const Player> player, 
		const boost::shared_ptr<const UnitType> unitType,
		const boost::shared_ptr<const Location> location,
		const boost::shared_ptr<const Location> goalLocation,
		const unsigned int count,
		const unsigned int remainingMovementTime,
		const unsigned int remainingConstructionTime,
		const std::list<boost::uuids::uuid> occupiedFacilityIdList,
		const std::list<boost::uuids::uuid> constructingUnitIdList
		);
	~Unit();

	/**
	* Move the unit towards goal 
	*/
	void process();

	/**
	*  Is this unit occupied by building another unit? 
	*  (e.g. a facility, a morping unit etc.)
	*/
	unsigned int getCount() const;
	void changeCount(signed int count);
	bool isAvailable() const;
	bool isMoving() const;
	bool isConstructing() const;
	bool isUnderConstruction() const;
	unsigned int getRemainingMovementTime() const;
	unsigned int getRemainingConstructionTime() const;

	const boost::shared_ptr<const Player> getPlayer() const;
	const boost::shared_ptr<const UnitType> getUnitType() const;
	const boost::shared_ptr<const Location> getLocation() const;
	const boost::shared_ptr<const Location> getGoalLocation() const;
	boost::uuids::uuid getPlayerId() const;
	boost::uuids::uuid getUnitTypeId() const;
	boost::uuids::uuid getLocationId() const;
	boost::uuids::uuid getGoalLocationId() const;

	const std::list<boost::shared_ptr<Unit> > & getOccupiedFacilityList() const;
	const std::list<boost::uuids::uuid>& getOccupiedFacilityIdList() const;
	const std::list<boost::shared_ptr<Unit> > & getConstructingUnitList() const;
	const std::list<boost::uuids::uuid>& getConstructingUnitIdList() const;

	const UnitLocalNeutralKey& getLocalNeutralKey() const; // for goals
	const UnitLocalKey& getLocalKey() const;
	const UnitGlobalKey& getGlobalKey() const;

	void cancelConstruction(const boost::shared_ptr<const Unit> unit);
	void removeFromConstruction(const boost::shared_ptr<const Unit> unit);
	bool addToConstruction(const boost::shared_ptr<Unit> unit);
	void clearConstructions();
	void addOccupiedFacility(const boost::shared_ptr<Unit> facility);
	void addConstructingUnit(const boost::shared_ptr<Unit> unit);

	void removeUnit();

	// sets new goal location (and movement time etc. - different to assignGoalLocation which only sets the goal location variable to fit the goalLocationID)
	void setGoalLocation(const boost::shared_ptr<const Location> location);

	// call after deserialization of units (by Units)
	void initialize(const boost::shared_ptr<Units> units);

private:
	friend class boost::serialization::access;

	template<class Archive> 
	void serialize(Archive &ar, const unsigned int version)
	{ }

	template<class Archive>
	friend inline void save_construct_data(Archive &ar, const Unit* unit, const unsigned int version) { 

		const boost::uuids::uuid& id = unit->getId();
		const boost::uuids::uuid& playerId = unit->getPlayerId();
		const boost::uuids::uuid& unitTypeId = unit->getUnitTypeId();
		const boost::uuids::uuid& locationId = unit->getLocationId();
		const boost::uuids::uuid& goalLocationId = unit->getLocationId();
		const unsigned int& count = unit->getCount();
		const unsigned int& remainingMovementTime = unit->getRemainingMovementTime();
		const unsigned int& remainingConstructionTime = unit->getRemainingConstructionTime();
		const std::list<boost::uuids::uuid>& occupiedFacilityIdList = unit->getOccupiedFacilityIdList();
		const std::list<boost::uuids::uuid>& constructingUnitIdList = unit->getConstructingUnitIdList();

		if(version > 0) {
		}

		ar & BOOST_SERIALIZATION_NVP(id)
		   & BOOST_SERIALIZATION_NVP(playerId)
		   & BOOST_SERIALIZATION_NVP(unitTypeId)
		   & BOOST_SERIALIZATION_NVP(locationId)
		   & BOOST_SERIALIZATION_NVP(goalLocationId)
		   & BOOST_SERIALIZATION_NVP(count)
		   & BOOST_SERIALIZATION_NVP(remainingMovementTime)
		   & BOOST_SERIALIZATION_NVP(remainingConstructionTime)
		   & BOOST_SERIALIZATION_NVP(occupiedFacilityIdList)
		   & BOOST_SERIALIZATION_NVP(constructingUnitIdList);
	}

	template<class Archive> 
	inline friend void load_construct_data(Archive& ar, Unit*& unit, const unsigned int version)
	{
		boost::uuids::uuid id;
		boost::uuids::uuid playerId;
		boost::uuids::uuid unitTypeId;
		boost::uuids::uuid locationId;
		boost::uuids::uuid goalLocationId;
		unsigned int count;
		unsigned int remainingMovementTime;
		unsigned int remainingConstructionTime;
		std::list<boost::uuids::uuid> occupiedFacilityIdList;
		std::list<boost::uuids::uuid> constructingUnitIdList;

		ar & BOOST_SERIALIZATION_NVP(id)
		   & BOOST_SERIALIZATION_NVP(playerId)
		   & BOOST_SERIALIZATION_NVP(unitTypeId)
		   & BOOST_SERIALIZATION_NVP(locationId)
		   & BOOST_SERIALIZATION_NVP(goalLocationId)
		   & BOOST_SERIALIZATION_NVP(remainingMovementTime)
		   & BOOST_SERIALIZATION_NVP(remainingConstructionTime)
		   & BOOST_SERIALIZATION_NVP(occupiedFacilityIdList)
		   & BOOST_SERIALIZATION_NVP(constructingUnitIdList);

		if(version > 0) {
		}

		::new(unit)Unit(id, 
			// TODO let it depend on Rules?
			GlobalStorage::instance().getPlayer(playerId), 
			GlobalStorage::instance().getUnitType(unitTypeId), 			
			GlobalStorage::instance().getLocation(locationId), 
			GlobalStorage::instance().getLocation(goalLocationId),
			count,
			remainingMovementTime,
			remainingConstructionTime,
			occupiedFacilityIdList,
			constructingUnitIdList);
	}


	const boost::shared_ptr<const Player> player;
	const boost::uuids::uuid playerId;

	// unit type never changes
	const boost::shared_ptr<const UnitType> unitType;
	const boost::uuids::uuid unitTypeId;

	// variable can change
	boost::shared_ptr<const Location> location;
	boost::uuids::uuid locationId;

	boost::shared_ptr<const Location> goalLocation;
	boost::uuids::uuid goalLocationId;
	
	// not const: need to be initialized later
	boost::shared_ptr<Units> globalUnits;

	unsigned int count;
	unsigned int remainingConstructionTime; // == 0? complete!		
	unsigned int remainingMovementTime;

	// a game rule might require multiple facilities for the construction of this unit
	std::list<boost::shared_ptr<Unit> > occupiedFacilityList;
	std::list<boost::uuids::uuid> occupiedFacilityIdList;
	std::list<boost::shared_ptr<Unit> > constructingUnitList;
	std::list<boost::uuids::uuid> constructingUnitIdList;

	UnitLocalKey unitLocalKey;
	UnitLocalNeutralKey unitLocalNeutralKey;
	const UnitGlobalKey unitGlobalKey;

	Unit& operator=(const Unit& other);
};

inline unsigned int Unit::getCount() const {
	return count;
}

inline void Unit::changeCount(signed int count) {
	this->count += count;
}

inline bool Unit::isUnderConstruction() const {
	return remainingConstructionTime > 0;
}

inline bool Unit::isMoving() const {
	return remainingMovementTime > 0;
}

inline bool Unit::isConstructing() const {
	return constructingUnitIdList.size() > 0;
}

inline bool Unit::isAvailable() const {
	return !isConstructing() && !isMoving() && !isUnderConstruction();
}

inline const boost::shared_ptr<const Player> Unit::getPlayer() const {
	return player;
}

inline boost::uuids::uuid Unit::getPlayerId() const {
	return playerId;
}

inline const boost::shared_ptr<const UnitType> Unit::getUnitType() const {
	return unitType;
}

inline boost::uuids::uuid Unit::getUnitTypeId() const {
	return unitTypeId;
}

inline const UnitGlobalKey& Unit::getGlobalKey() const {
	return unitGlobalKey;
}

inline const UnitLocalKey& Unit::getLocalKey() const {
	return unitLocalKey;
}

inline const UnitLocalNeutralKey& Unit::getLocalNeutralKey() const {
	return unitLocalNeutralKey;
}

inline const boost::shared_ptr<const Location> Unit::getLocation() const {
	return location;
}

inline const boost::shared_ptr<const Location> Unit::getGoalLocation() const {
	return goalLocation;
}

inline boost::uuids::uuid Unit::getLocationId() const {
	return locationId;
}

inline boost::uuids::uuid Unit::getGoalLocationId() const {
	return goalLocationId;
}

inline unsigned int Unit::getRemainingMovementTime() const {
	return remainingMovementTime;
}

inline unsigned int Unit::getRemainingConstructionTime() const {
	return remainingConstructionTime;
}

inline const std::list<boost::shared_ptr<Unit> >& Unit::getOccupiedFacilityList() const {
	return occupiedFacilityList;
}	

inline const std::list<boost::uuids::uuid>& Unit::getOccupiedFacilityIdList() const {
	return occupiedFacilityIdList;
}

inline const std::list<boost::shared_ptr<Unit> >& Unit::getConstructingUnitList() const {
	return constructingUnitList;
}

inline const std::list<boost::uuids::uuid>& Unit::getConstructingUnitIdList() const {
	return constructingUnitIdList;
}

#endif
