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

#include "unittype.hpp"
#include "id.hpp"

struct UnitLocalNeutralKey
{
	UnitLocalNeutralKey():locationId(0),unitTypeId(0) {}
	UnitLocalNeutralKey(unsigned int locationId, unsigned int unitTypeId):locationId(locationId),unitTypeId(unitTypeId) {}

	unsigned int locationId;
	unsigned int unitTypeId;

	bool operator<(const UnitLocalNeutralKey& A) const { return locationId + unitTypeId * 10 < A.locationId + A.unitTypeId * 10; }
};

struct UnitLocalKey
{
	UnitLocalKey():locationId(0),playerId(0),unitTypeId(0) {}
	UnitLocalKey(unsigned int locationId, unsigned int playerId, unsigned int unitTypeId):locationId(locationId),playerId(playerId),unitTypeId(unitTypeId) {}

	unsigned int locationId;
	unsigned int playerId;
	unsigned int unitTypeId;

	bool operator<(const UnitLocalKey& A) const { return playerId + locationId * 10 + unitTypeId * 100 < A.playerId + A.locationId * 10 + A.unitTypeId * 100; }
};

struct UnitGlobalKey
{
	UnitGlobalKey():playerId(0),unitTypeId(0) {}
	UnitGlobalKey(unsigned int playerId, unsigned int unitTypeId):playerId(playerId),unitTypeId(unitTypeId) {}

	unsigned int playerId;
	unsigned int unitTypeId;

	bool operator<(const UnitGlobalKey& A) const { return playerId + unitTypeId * 10 < A.playerId + A.unitTypeId * 10; }
};

class Player;
class Location;
class Units;
class Unit;

/**
* A single unit / building / research etc.
*/
class Unit : public ID<Unit>,  public boost::enable_shared_from_this<Unit>
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
	Unit(const unsigned int id,
		const boost::shared_ptr<const Player> player, 
		const boost::shared_ptr<const UnitType> unitType,
		const boost::shared_ptr<const Location> location,
		const boost::shared_ptr<const Location> goalLocation,
		const unsigned int count,
		const unsigned int remainingMovementTime,
		const unsigned int remainingConstructionTime,
		const std::list<unsigned int> occupiedFacilityIdList,
		const std::list<unsigned int> constructingUnitIdList
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
	unsigned int getPlayerId() const;
	unsigned int getUnitTypeId() const;
	unsigned int getLocationId() const;
	unsigned int getGoalLocationId() const;

	const std::list<boost::shared_ptr<Unit> > & getOccupiedFacilityList() const;
	const std::list<unsigned int>& getOccupiedFacilityIdList() const;
	const std::list<boost::shared_ptr<Unit> > & getConstructingUnitList() const;
	const std::list<unsigned int>& getConstructingUnitIdList() const;

	const UnitLocalNeutralKey& getLocalNeutralKey() const; // for goals
	const UnitLocalKey& getLocalKey() const;
	const UnitGlobalKey& getGlobalKey() const;

	void cancelConstruction(const boost::shared_ptr<const Unit> unit);
	void removeFromConstruction(const boost::shared_ptr<const Unit> unit);
	bool addToConstruction(const boost::shared_ptr<const Unit> unit);
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

		const unsigned int& id = unit->getId();
		const unsigned int& playerId = unit->getPlayerId();
		const unsigned int& unitTypeId = unit->getUnitTypeId();
		const unsigned int& locationId = unit->getLocationId();
		const unsigned int& goalLocationId = unit->getLocationId();
		const unsigned int& count = unit->getCount();
		const unsigned int& remainingMovementTime = unit->getRemainingMovementTime();
		const unsigned int& remainingConstructionTime = unit->getRemainingConstructionTime();
		const std::list<unsigned int>& occupiedFacilityIdList = unit->getOccupiedFacilityIdList();
		const std::list<unsigned int>& constructingUnitIdList = unit->getConstructingUnitIdList();

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
		unsigned int id;
		unsigned int playerId;
		unsigned int unitTypeId;
		unsigned int locationId;
		unsigned int goalLocationId;
		unsigned int count;
		unsigned int remainingMovementTime;
		unsigned int remainingConstructionTime;
		std::list<unsigned int> occupiedFacilityIdList;
		std::list<unsigned int> constructingUnitIdList;

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
			GLOBAL_STORAGE.getPlayer(playerId), 
			GLOBAL_STORAGE.getUnitType(unitTypeId), 			
			GLOBAL_STORAGE.getLocation(locationId), 
			GLOBAL_STORAGE.getLocation(goalLocationId),
			count,
			remainingMovementTime,
			remainingConstructionTime,
			occupiedFacilityIdList,
			constructingUnitIdList);
	}


	const boost::shared_ptr<const Player> player;
	const unsigned int playerId;

	// unit type never changes
	const boost::shared_ptr<const UnitType> unitType;
	const unsigned int unitTypeId;

	// variable can change
	boost::shared_ptr<const Location> location;
	unsigned int locationId;

	boost::shared_ptr<const Location> goalLocation;
	unsigned int goalLocationId;
	
	// not const: need to be initialized later
	boost::shared_ptr<Units> globalUnits;

	unsigned int count;
	unsigned int remainingConstructionTime; // == 0? complete!		
	unsigned int remainingMovementTime;

	// a game rule might require multiple facilities for the construction of this unit
	std::list<boost::shared_ptr<Unit> > occupiedFacilityList;
	std::list<unsigned int> occupiedFacilityIdList;
	std::list<boost::shared_ptr<Unit> > constructingUnitList;
	std::list<unsigned int> constructingUnitIdList;

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

inline unsigned int Unit::getPlayerId() const {
	return playerId;
}

inline const boost::shared_ptr<const UnitType> Unit::getUnitType() const {
	return unitType;
}

inline unsigned int Unit::getUnitTypeId() const {
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

inline unsigned int Unit::getLocationId() const {
	return locationId;
}

inline unsigned int Unit::getGoalLocationId() const {
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

inline const std::list<unsigned int>& Unit::getOccupiedFacilityIdList() const {
	return occupiedFacilityIdList;
}

inline const std::list<boost::shared_ptr<Unit> >& Unit::getConstructingUnitList() const {
	return constructingUnitList;
}

inline const std::list<unsigned int>& Unit::getConstructingUnitIdList() const {
	return constructingUnitIdList;
}

#endif
