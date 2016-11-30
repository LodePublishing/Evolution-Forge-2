#pragma warning(push, 0)  
#include <boost/assert.hpp>
#pragma warning(pop)

#include "unit.hpp"
#include "location.hpp"
#include "player.hpp"
#include "units.hpp"

// create new unit
Unit::Unit(
	const boost::shared_ptr<const Player> player,
	const boost::shared_ptr<const UnitType> unitType,
	const boost::shared_ptr<const Location> location,
	const boost::shared_ptr<Units> globalUnits,
	const unsigned int count,
	const unsigned int remainingConstructionTime,
	const std::list<boost::shared_ptr<Unit> > occupiedFacilityList
	):
	player(player),
	playerId(player->getId()),
	unitType(unitType),
	unitTypeId(unitType->getId()),
	location(location),
	locationId(location->getId()),
	goalLocation(location),
	goalLocationId(location->getId()),
	globalUnits(globalUnits),
	count(count),
	remainingConstructionTime(remainingConstructionTime),
	remainingMovementTime(0),
	occupiedFacilityList(occupiedFacilityList),
	occupiedFacilityIdList(),
	constructingUnitList(),
	constructingUnitIdList(),
	unitLocalKey(location->getId(), playerId, unitType->getId()),
	unitLocalNeutralKey(location->getId(), unitType->getId()),
	unitGlobalKey(playerId, unitType->getId())
{
	for(std::list<boost::shared_ptr<Unit> >::iterator i = this->occupiedFacilityList.begin(); i != this->occupiedFacilityList.end(); i++) {
		occupiedFacilityIdList.push_back((*i)->getId());
		globalUnits->removeOneLocalAvailable((*i)->getLocalKey());
	}	
}



Unit::Unit(
	const unsigned int id,
	const boost::shared_ptr<const Player> player, 
	const boost::shared_ptr<const UnitType> unitType,
	const boost::shared_ptr<const Location> location,
	const boost::shared_ptr<const Location> goalLocation,
	const unsigned int count,
	const unsigned int remainingMovementTime,
	const unsigned int remainingConstructionTime,
	const std::list<unsigned int> occupiedFacilityIdList,
	const std::list<unsigned int> constructingUnitIdList
	):
	ID<Unit>(id),
	player(player),
	playerId(player->getId()),
	unitType(unitType),
	unitTypeId(unitType->getId()),
	location(location),
	locationId(location->getId()),
	goalLocation(goalLocation),
	goalLocationId(goalLocation->getId()),
	globalUnits(),
	count(count),
	remainingConstructionTime(remainingConstructionTime),
	remainingMovementTime(remainingMovementTime),
	occupiedFacilityList(),
	occupiedFacilityIdList(occupiedFacilityIdList),
	constructingUnitList(),
	constructingUnitIdList(constructingUnitIdList),
	unitLocalKey(location->getId(), playerId, unitType->getId()),
	unitLocalNeutralKey(location->getId(), unitType->getId()),
	unitGlobalKey(playerId, unitType->getId())
{ }

void Unit::initialize(const boost::shared_ptr<Units> units) {
	globalUnits = units;

	occupiedFacilityList.clear();
	constructingUnitList.clear();

	for(std::list<unsigned int>::const_iterator i = occupiedFacilityIdList.begin(); i != occupiedFacilityIdList.end(); i++) {
		occupiedFacilityList.push_back(units->getUnit(*i));

		globalUnits->removeOneLocalAvailable(occupiedFacilityList.back()->getLocalKey());
	}

	for(std::list<unsigned int>::const_iterator i = constructingUnitIdList.begin(); i != constructingUnitIdList.end(); i++) {
		constructingUnitList.push_back(units->getUnit(*i));
	}
}

void Unit::removeUnit() {
	globalUnits->removeUnit(shared_from_this());
}

void Unit::clearConstructions()
{
	for(std::list<boost::shared_ptr<Unit> >::const_iterator u = occupiedFacilityList.begin(); u != occupiedFacilityList.end(); u++) {
		(*u)->removeFromConstruction(shared_from_this());
	}

	for(std::list<boost::shared_ptr<Unit> >::const_iterator u = constructingUnitList.begin(); u != constructingUnitList.end(); u++) {
		(*u)->cancelConstruction(shared_from_this());
	}
}

Unit::~Unit() {
	//if(!this->isUnderConstruction()) {
	//	globalUnits->removeUnit(this);
	//}

}

/*
// adds a unit to the construction queue of the unit
bool Unit::addToConstruction(Unit* unit) {
	if(isAvailable()) {
		constructingUnit.push_back(unit);
		globalUnits->removeOneLocalAvailable(getLocalKey());
		return true;
	} else {
		return false;
	}
	// TODO multiple construction slots?
}*/ // TODO?

void Unit::removeFromConstruction(const boost::shared_ptr<const Unit> unit) {
	bool was_constructing = isConstructing();

	for(std::list<boost::shared_ptr<Unit> >::iterator i = constructingUnitList.begin(); i != constructingUnitList.end(); i++) {
		if((*i)->getId() == unit->getId()) {
			constructingUnitList.erase(i);
			if(was_constructing && !isConstructing()) {
				globalUnits->addOneLocalAvailable(getLocalKey());
				// TODO multiple construction slots?
			}
			return;
		}
	}
}
// TODO

void Unit::cancelConstruction(boost::shared_ptr<const Unit> unit) {
//	globalUnits->removeUnit(this); 
	for(std::list<boost::shared_ptr<Unit> >::const_iterator u = occupiedFacilityList.begin(); u != occupiedFacilityList.end(); u++) {
		if(unit->getId() != (*u)->getId()) { // ignore the facility itself! otherwise their constructingUnits list gets corrupted TODO? Explanation
			(*u)->removeFromConstruction(shared_from_this());
		}
	}
	occupiedFacilityList.clear();
}


void Unit::setGoalLocation(boost::shared_ptr<const Location> goalLocation) {
	if(this->goalLocation->getId() == goalLocation->getId()) {
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
			BOOST_ASSERT(false);
			break;
		case FLYING_MOVEMENT_TYPE:
			remainingMovementTime = location->getAirDistance(goalLocation);
			break;
		case GROUND_MOVEMENT_TYPE:
			remainingMovementTime = location->getGroundDistance(goalLocation);
			break;
		case MOVEMENT_TYPE_TYPES:
		default:
			BOOST_ASSERT(false);
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
			globalUnits->removeLocalUnit(shared_from_this());
			location = goalLocation;
			unitLocalKey.locationId = location->getId();
			unitLocalNeutralKey.locationId = location->getId();
			globalUnits->addLocalUnit(shared_from_this());
		}
	} else
		// TODO maybe include the application of special UnitType / FacilityType rules
		if(isUnderConstruction()) {
			remainingConstructionTime--;
			if(remainingConstructionTime == 0) {
				// remove this unit from all construction queues of the facilities
				for(std::list<boost::shared_ptr<Unit> >::iterator i = occupiedFacilityList.begin(); i != occupiedFacilityList.end(); i++) {
					(*i)->removeFromConstruction(shared_from_this());
				}
				occupiedFacilityList.clear();

				// make this unit available
				globalUnits->addOneLocalAvailable(getLocalKey());

			}

			// TODO , je nach Typ!
			// TODO, aufpassen beim Aufr�umen, in welcher Reihenfolge was gel�scht wird! Evtl erst mal alle Listen leeren und dann erst l�schen...
		}
}

void Unit::addOccupiedFacility(const boost::shared_ptr<Unit> facility) {
	this->occupiedFacilityList.push_back(facility);
}

void Unit::addConstructingUnit(const boost::shared_ptr<Unit> unit) {
	bool was_available = this->isAvailable();

	this->constructingUnitList.push_back(unit);

	// is this facility became available again? Notify the listeners
	if(this->isAvailable() != was_available) {
		globalUnits->removeOneLocalAvailable(getLocalKey());
	}
}
