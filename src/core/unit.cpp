#pragma warning(push, 0)  
#include <boost/assert.hpp>
#pragma warning(pop)

#include "unit.hpp"
#include "location.hpp"
#include "player.hpp"
#include "units.hpp"

// create new unit
Unit::Unit(
	const UnitType* unitType,
	const Player* player, 
	Location* location,

	const unsigned int remainingConstructionTime,
	std::list<Unit*> occupiedFacility
	):
player(player),
	unitType(unitType),
	location(location),
	goalLocation(location),
	remainingConstructionTime(remainingConstructionTime),
	remainingMovementTime(0),
	occupiedFacility(occupiedFacility),
	constructingUnit(),
	unitLocalKey(location->getID(), player->getID(), unitType->getID()),
	unitGlobalKey(player->getID(), unitType->getID()),
	unitLocalNeutralKey(location->getID(), unitType->getID()),
	playerId(player->getID()),
	unitTypeId(unitType->getID()),
	locationId(location->getID()),
	goalLocationId(location->getID())
{
	// TODO, beim Abspeichern müssen die IDs aktualisiert werden

	location->getGlobalUnits()->addUnit(this);

	for(std::list<Unit*>::iterator i = occupiedFacility.begin(); i != occupiedFacility.end(); i++) {
		occupiedFacilityId.push_back((*i)->getID());
		(*i)->addConstructingUnit(this);
	}
}


void Unit::removeUnit() {
	location->getGlobalUnits()->removeUnit(this);
}

void Unit::clearConstructions()
{
	for(std::list<Unit*>::const_iterator u = occupiedFacility.begin(); u != occupiedFacility.end(); u++) {
		(*u)->removeFromConstruction(this);
	}

	for(std::list<Unit*>::const_iterator u = constructingUnit.begin(); u != constructingUnit.end(); u++) {
		(*u)->cancelConstruction(this);
	}
}


Unit::~Unit() {
	//if(!this->isUnderConstruction()) {
	//	location->getGlobalUnits()->removeUnit(this);
	//}

}


/*
// adds a unit to the construction queue of the unit
bool Unit::addToConstruction(Unit* unit) {
	if(isAvailable()) {
		constructingUnit.push_back(unit);
		location->getGlobalUnits()->removeOneLocalAvailable(getLocalKey());
		return true;
	} else {
		return false;
	}
	// TODO multiple construction slots?
}*/ // TODO?


void Unit::removeFromConstruction(Unit* unit) {
	bool was_constructing = isConstructing();

	for(std::list<Unit*>::iterator i = constructingUnit.begin(); i != constructingUnit.end(); i++) {
		if((*i)->getID() == unit->getID()) {
			constructingUnit.erase(i);
			if(was_constructing && !isConstructing()) {
				location->getGlobalUnits()->addOneLocalAvailable(getLocalKey());
				// TODO multiple construction slots?
			}
			return;
		}
	}
}
// TODO

void Unit::cancelConstruction(Unit* unit) {
//	location->getGlobalUnits()->removeUnit(this); 
	for(std::list<Unit*>::const_iterator u = occupiedFacility.begin(); u != occupiedFacility.end(); u++) {
		if(unit->getID() != (*u)->getID()) { // ignore the facility itself! otherwise their constructingUnits list gets corrupted TODO? Explanation
			(*u)->removeFromConstruction(this);
		}
	}
	occupiedFacility.clear();
}


void Unit::setGoalLocation(Location* goalLocation) {
	if(this->goalLocation->getID() == goalLocation->getID()) {
		remainingMovementTime = 0;
		return;
	}

	if(unitType->getSpeed() == 0) {
		// this unit should not able to move!
		BOOST_ASSERT(false);
	}

	this->goalLocation = goalLocation;

	switch(unitType->getMovementType()) {
		case NO_MOVEMENT_TYPE:
			assert(false);
			break;
		case FLYING_MOVEMENT_TYPE:
			remainingMovementTime = location->getAirDistance(goalLocation);
			break;
		case GROUND_MOVEMENT_TYPE:
			remainingMovementTime = location->getGroundDistance(goalLocation);
			break;
		case MOVEMENT_TYPE_TYPES:
		default:
			assert(false);
			break;
	}
	remainingMovementTime /=  unitType->getSpeed();
}

/**
* Move the unit towards the goal.
*/
void Unit::process() {
	if(isMoving()) {
		remainingMovementTime--;
		if(remainingMovementTime == 0) {
			location->getGlobalUnits()->removeLocalUnit(this);
			location = goalLocation;
			unitLocalKey.locationID = location->getID();
			unitLocalNeutralKey.locationID = location->getID();
			location->getGlobalUnits()->addLocalUnit(this);
		}
	} else
		// TODO maybe include the application of special UnitType / FacilityType rules
		if(isUnderConstruction()) {
			remainingConstructionTime--;
			if(remainingConstructionTime == 0) {
				// remove this unit from all construction queues of the facilities
				for(std::list<Unit*>::iterator i = occupiedFacility.begin(); i != occupiedFacility.end(); i++) {
					(*i)->removeFromConstruction(this);
				}
				occupiedFacility.clear();

				// make this unit available
				location->getGlobalUnits()->addOneLocalAvailable(getLocalKey());

			}

			// TODO , je nach Typ!
			// TODO, aufpassen beim Aufräumen, in welcher Reihenfolge was gelöscht wird! Evtl erst mal alle Listen leeren und dann erst löschen...
		}
}

void Unit::assignPlayer(Player* player) {
	BOOST_ASSERT(player->getID() == playerId);

	this->player = player;

	unitLocalKey.playerID = playerId;
	unitGlobalKey.playerID = playerId;
}

void Unit::assignUnitType(const UnitType* unitType) {
	BOOST_ASSERT(unitType->getID() == this->unitTypeId);

	this->unitType = unitType;

	unitLocalKey.unitTypeID = unitTypeId;
	unitLocalNeutralKey.unitTypeID = unitTypeId;
	unitGlobalKey.unitTypeID = unitTypeId;
}

void Unit::assignLocation(Location* location) {
	BOOST_ASSERT(location->getID() == locationId);

	this->location = location;

	unitLocalKey.locationID = locationId;
	unitLocalNeutralKey.locationID = locationId;
}

void Unit::assignGoalLocation(Location* goalLocation) {
	BOOST_ASSERT(goalLocation->getID() == goalLocationId);

	this->goalLocation = goalLocation;
}


void Unit::addOccupiedFacility(Unit* facility) {
	this->occupiedFacility.push_back(facility);
}

void Unit::addConstructingUnit(Unit* unit) {
	bool was_available = this->isAvailable();

	this->constructingUnit.push_back(unit);

	// is this facility became available again? Notify the listeners
	if(this->isAvailable() != was_available) {
		location->getGlobalUnits()->removeOneLocalAvailable(getLocalKey());
	}
}

const char* const Unit::PlayerID_tag_string = "player";
const char* const Unit::UnitTypeID_tag_string = "type";
const char* const Unit::LocationID_tag_string = "location";
const char* const Unit::GoalLocationID_tag_string = "goal_location";
const char* const Unit::RemainingMovingTime_tag_string = "remaining_movement_time";
const char* const Unit::RemainingConstructionTime_tag_string = "remaining_construction_time";
const char* const Unit::OccupiedFacilitiesIDsList_tag_string = "occupied_facilities";
const char* const Unit::ConstructingUnitsIDsList_tag_string = "constructing_units";
