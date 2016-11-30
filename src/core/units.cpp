#include "units.hpp"
#include "location.hpp"

Units::Units():
	unitList(),
	unitListMap()
	{}

// call this after filling unitList by any other means than add/removeUnit!
// for example after serialization!
void Units::calculateAvailableAndTotal() {

	for(std::list<Unit*>::const_iterator i = unitList.begin(); i != unitList.end(); i++) {
		if((*i)->isAvailable()) {
			addOneLocalAvailable((*i)->getLocalKey());
		}
		addOneLocalTotal((*i)->getLocalKey());
	}
}

Units::~Units()
{ 
	clear();
}

void Units::clear()
{
	for(std::list<Unit*>::iterator i = unitList.begin(); i != unitList.end(); i++) {
		(*i)->clearConstructions();
	}

	for(std::list<Unit*>::iterator i = unitList.begin(); i != unitList.end(); i++) {
		delete *i;
	}	
	unitList.clear();
	unitListMap.clear();
	localAvailable.clear();
	globalTotal.clear();

	// clear children? -> Graph!
}

Units::Units(const Units& object)
{
	for(std::list<Unit*>::const_iterator i = object.unitList.begin(); i != object.unitList.end(); i++) {
		addUnit(new Unit(**i));
	}
	
	// parent has to be assigned seperately!
	//parent = object.parent;
}

Units& Units::operator=(const Units& object)
{
	clear();

	//parent = NULL;

	for(std::list<Unit*>::const_iterator i = object.unitList.begin(); i != object.unitList.end(); i++) {
		addUnit(new Unit(**i));
	}

	// parent 
	//parent = object.parent;

	return(*this);
}

// simply adds a unit to the list
void Units::addUnit(Unit* unit) {
	unitList.push_back(unit);
	unitListMap[unit->getID()] = unit;

	addLocalUnit(unit);
}

void Units::removeUnit(Unit* unit) {
	BOOST_ASSERT(unit->isUnderConstruction() || getLocalTotal(unit->getLocalKey()) > 0);

	// TODO erase units that need this facility to build? maybe only primary units... TODO... resources etc. :o
	// TODO check "available"
	bool found = false;
	for(std::list<Unit*>::iterator i = unitList.begin(); i != unitList.end(); i++) {
		if((*i)->getID() == unit->getID()) {

			unitListMap.erase(unit->getID());
			unitList.erase(i);

			found = true;
			break;
		}
	}
	BOOST_ASSERT(found);

	removeLocalUnit(unit);

	//if(parent != NULL) {
	//	parent->removeUnit(unit);
	//} else {
		unit->clearConstructions();
		delete unit;
	//}
}

void Units::addLocalUnit(Unit* unit) {
	if(unit->isAvailable()) {
		addOneLocalAvailable(unit->getLocalKey());
	}
	addOneLocalTotal(unit->getLocalKey());
}

void Units::removeLocalUnit(Unit* unit) {
	if(unit->isAvailable()) {
		removeOneLocalAvailable(unit->getLocalKey());
	}
	removeOneLocalTotal(unit->getLocalKey());
}



void Units::process() {
	for(std::list<Unit*>::iterator i = unitList.begin(); i != unitList.end(); i++) {
		(*i)->process();
	}	
}

const char* const Units::UnitList_tag_string = "unit_list";