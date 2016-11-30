#ifndef _CORE_UNIT_HPP
#define _CORE_UNIT_HPP

#include <vector>
#include <list>
#include <map>

#pragma warning(push, 0)  
#include <boost/serialization/base_object.hpp>
#pragma warning(pop)

#include "unittype.hpp"
#include "id.hpp"

struct UnitLocalNeutralKey
{
	UnitLocalNeutralKey():locationID(0),unitTypeID(0) {}
	UnitLocalNeutralKey(unsigned int locationID, unsigned int unitTypeID):locationID(locationID),unitTypeID(unitTypeID) {}

	unsigned int locationID;
	unsigned int unitTypeID;

	bool operator<(const UnitLocalNeutralKey& A) const { return locationID + unitTypeID * 10 < A.locationID + A.unitTypeID * 10; }
};

struct UnitLocalKey
{
	UnitLocalKey():locationID(0),playerID(0),unitTypeID(0) {}
	UnitLocalKey(unsigned int locationID, unsigned int playerID, unsigned int unitTypeID):locationID(locationID),playerID(playerID),unitTypeID(unitTypeID) {}

	unsigned int locationID;
	unsigned int playerID;
	unsigned int unitTypeID;

	bool operator<(const UnitLocalKey& A) const { return playerID + locationID * 10 + unitTypeID * 100 < A.playerID + A.locationID * 10 + A.unitTypeID * 100; }
};

struct UnitGlobalKey
{
	UnitGlobalKey():playerID(0),unitTypeID(0) {}
	UnitGlobalKey(unsigned int playerID, unsigned int unitTypeID):playerID(playerID),unitTypeID(unitTypeID) {}

	unsigned int playerID;
	unsigned int unitTypeID;

	bool operator<(const UnitGlobalKey& A) const { return playerID + unitTypeID * 10 < A.playerID + A.unitTypeID * 10; }
};

class Player;
class Location;
class Units;

/**
 * A single unit / building / research etc.
 */
class Unit : public ID<Unit>
{
	public:
		// Create Unit
		Unit(const UnitType* unitType,
			 const Player* player,
			 // location needs to be changed for moving!
			 Location* location,

			 const unsigned int remainingConstructionTime = 0,
			 std::list<Unit*> occupiedFacility = std::list<Unit*>()
			 );
		~Unit();

		// initializes the unit pointers and references according to the Id
		// this is important if the object was deserialized and needs the pointers corresponding to the IDs
		void initializePointers(std::map<unsigned int, Unit*>& units, 
			std::map<unsigned int, Location*>& locations);

		/**
		 * Move the unit towards goal 
		 */
		void process();


		/**
		 *  Is this unit occupied by building another unit? 
		 *  (e.g. a facility, a morping unit etc.)
		 */
		bool isAvailable() const;
		bool isMoving() const;
		bool isConstructing() const;
		bool isUnderConstruction() const;
		unsigned int getRemainingMovementTime() const;
		unsigned int getRemainingConstructionTime() const;

		const Player* getPlayer() const;
		const UnitType* getUnitType() const;
		Location* getLocation() const;
		Location* getGoalLocation() const;
		unsigned int getPlayerId() const;
		unsigned int getUnitTypeId() const;
		unsigned int getLocationId() const;
		unsigned int getGoalLocationId() const;

		const UnitLocalNeutralKey& getLocalNeutralKey() const; // for goals
		const UnitLocalKey& getLocalKey() const;
		const UnitGlobalKey& getGlobalKey() const;
		void cancelConstruction(Unit* unit);
		void removeFromConstruction(Unit* unit);
		bool addToConstruction(Unit* unit);
		void clearConstructions();
		void removeUnit();
		// sets new goal location (and movement time etc. - different to assignGoalLocation which only sets the goal location variable to fit the goalLocationID)
		void setGoalLocation(Location* location);
		
		// assignment functions after serialization:
		void assignPlayer(Player* player);
		void assignUnitType(const UnitType* unitType);
		void assignLocation(Location* location);
		void assignGoalLocation(Location* location);

		void addOccupiedFacility(Unit* facility);
		void addConstructingUnit(Unit* unit);

		static const char* const PlayerID_tag_string;
		static const char* const UnitTypeID_tag_string;
		static const char* const LocationID_tag_string;
		static const char* const GoalLocationID_tag_string;

		static const char* const RemainingMovingTime_tag_string;
		static const char* const RemainingConstructionTime_tag_string;

		static const char* const OccupiedFacilitiesIDsList_tag_string;
		static const char* const ConstructingUnitsIDsList_tag_string;

	private:
		friend class boost::serialization::access;
		template<class Archive> void serialize(Archive &ar, const unsigned int version)
		{
			ar & boost::serialization::make_nvp(ID_tag_string, id);
			ar & boost::serialization::make_nvp(PlayerID_tag_string, playerId);
			ar & boost::serialization::make_nvp(UnitTypeID_tag_string, unitTypeId);
			ar & boost::serialization::make_nvp(LocationID_tag_string, locationId);
			ar & boost::serialization::make_nvp(GoalLocationID_tag_string, goalLocationId);
			ar & boost::serialization::make_nvp(RemainingMovingTime_tag_string, remainingMovementTime);
			ar & boost::serialization::make_nvp(RemainingConstructionTime_tag_string, remainingConstructionTime);
			ar & boost::serialization::make_nvp(OccupiedFacilitiesIDsList_tag_string, occupiedFacility);
			ar & boost::serialization::make_nvp(ConstructingUnitsIDsList_tag_string, constructingUnit);
			if(version > 0) {
			}
		}
		// only for serialization / deserialization
		Unit():player(NULL),unitType(NULL),location(NULL),goalLocation(NULL) {}
		
	// temporary variables (won't be saved directly, only through their IDs maybe)
		const Player* player;
		const UnitType* unitType;
		Location* location;
		Location* goalLocation;
		unsigned int remainingConstructionTime; // == 0? complete!		
		unsigned int remainingMovementTime;
		std::list<Unit*> occupiedFacility;
		std::list<Unit*> constructingUnit;
		UnitLocalKey unitLocalKey;
		UnitGlobalKey unitGlobalKey;
		UnitLocalNeutralKey unitLocalNeutralKey;

// when loading a unit, then UnitTypes, GamePlayers, MapLocations etc. have to be already loaded
		unsigned int playerId;
		unsigned int unitTypeId;
		unsigned int locationId;
		unsigned int goalLocationId;
		// a game rule might require multiple facilities for the construction of this unit
		std::list<unsigned int> occupiedFacilityId;
		std::list<unsigned int> constructingUnitId;


		Unit& operator=(const Unit& other);
};

inline bool Unit::isUnderConstruction() const {
	return remainingConstructionTime > 0;
}

inline bool Unit::isMoving() const {
	return remainingMovementTime > 0;
}

inline bool Unit::isConstructing() const {
	return constructingUnit.size() > 0;
}

inline bool Unit::isAvailable() const {
	return !isConstructing() && !isMoving() && !isUnderConstruction();
}

inline const Player* Unit::getPlayer() const {
	return player;
}

inline unsigned int Unit::getPlayerId() const {
	return playerId;
}

inline const UnitType* Unit::getUnitType() const {
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

inline Location* Unit::getLocation() const {
	return location;
}

inline Location* Unit::getGoalLocation() const {
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



#endif
