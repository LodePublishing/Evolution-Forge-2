#include "rules.hpp"


Rules::Rules(const std::string& name):
	name(name),
	raceList(),
	unitTypeMap()
{
}

Rules::~Rules()
{
}

void Rules::addUnitType(const UnitType& unitType)
{
	this->unitTypeMap.insert(std::pair<unsigned int, UnitType>(unitType.getID(), unitType));
}

void Rules::addRace(const Race& race)
{
	this->raceList.push_back(race);
}

// call after deserialization
void Rules::initializeRaces() {
	// TODO std::map
	for(std::map<unsigned int, UnitType>::iterator i = unitTypeMap.begin(); i != unitTypeMap.end(); i++) {
		bool found = false;
		for(std::list<Race>::const_iterator j = raceList.begin(); j != raceList.end(); j++) {
			if(j->getID() == i->second.getRaceID()) {
				i->second.setRace(&(*j));
				found = true;
				break;
			}
		}
		if(!found) {
			throw "Race ID of this unit type is not in the rules.";
		}
	}
}


const char* const Rules::UnitTypeMap_tag_string = "UnitTypeMap";
const char* const Rules::Name_tag_string = "name";
const char* const Rules::RaceList_tag_string = "RaceList";