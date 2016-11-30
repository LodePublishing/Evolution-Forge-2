#include "units.hpp"
#include "location.hpp"

Units::Units():
	unitList(),
	unitMap(),
	globalNeutralAvailable(),
	globalNeutralTotal(),
	globalAvailable(),
	globalTotal(),
	localAvailable(),
	localTotal(),
	localNeutralAvailable(),
	localNeutralTotal()
{ }

/// TODO, requires initializeUnitList etc.
Units::Units(const std::list<boost::shared_ptr<Unit> > unitList):
	unitList(unitList),
	unitMap(),
	globalNeutralAvailable(),
	globalNeutralTotal(),
	globalAvailable(),
	globalTotal(),
	localAvailable(),
	localTotal(),
	localNeutralAvailable(),
	localNeutralTotal()
{ 	
}


Units::~Units()
{ 
	clear();
}

void Units::clear()
{
	for(std::list<boost::shared_ptr<Unit> >::iterator i = unitList.begin(); i != unitList.end(); i++) {
		(*i)->clearConstructions();
	}

	unitList.clear();
	unitMap.clear();

	localAvailable.clear();
	localTotal.clear();
	globalAvailable.clear();
	globalTotal.clear();
	localNeutralAvailable.clear();
	localNeutralTotal.clear();
	globalNeutralAvailable.clear();
	globalNeutralTotal.clear();
}

Units::Units(const Units& object)
{
	// TODO evtl direkt einzelne Felder initialisieren, sind ja eh shared pointer? mmmh...
	for(std::list<boost::shared_ptr<Unit> >::const_iterator i = object.unitList.begin(); i != object.unitList.end(); i++) {
		addUnit(boost::shared_ptr<Unit>(new Unit(**i)));
	}
}

Units& Units::operator=(const Units& object)
{
	clear();

	for(std::list<boost::shared_ptr<Unit> >::const_iterator i = object.unitList.begin(); i != object.unitList.end(); i++) {
		addUnit(boost::shared_ptr<Unit>(new Unit(**i)));
	}

	return(*this);
}

void Units::initializeUnitList() {
	for(std::list<boost::shared_ptr<Unit> >::const_iterator i = unitList.begin(); i != unitList.end(); i++) {
		unitMap.insert(std::pair<unsigned int, const boost::shared_ptr<Unit> >((*i)->getId(), *i));
		addLocalUnit(*i);
	}
	for(std::list<boost::shared_ptr<Unit> >::const_iterator i = unitList.begin(); i != unitList.end(); i++) {
		(*i)->initialize(shared_from_this());
	}
}

// simply adds a unit to the list
void Units::addUnit(const boost::shared_ptr<Unit> unit) {
	unitList.push_back(unit);
	unitMap.insert(std::pair<unsigned int, const boost::shared_ptr<Unit> >(unit->getId(), unit));

	for(std::list<boost::shared_ptr<Unit> >::const_iterator i = unit->getOccupiedFacilityList().begin(); i != unit->getOccupiedFacilityList().end(); i++) {
		(*i)->addConstructingUnit(unit);
	}

	addLocalUnit(unit);
}

void Units::addUnits(const std::list<boost::shared_ptr<Unit> > unitList) {
	for(std::list<boost::shared_ptr<Unit> >::const_iterator i = unitList.begin(); i != unitList.end(); i++) {
		addUnit(*i);
	}
}

void Units::removeUnit(const boost::shared_ptr<Unit> unit) {
	BOOST_ASSERT(unit->isUnderConstruction() || getLocalTotal(unit->getLocalKey()) > 0);

	// TODO erase units that need this facility to build? maybe only primary units... TODO... resources etc. :o
	// TODO check "available"
	bool found = false;
	for(std::list<boost::shared_ptr<Unit> >::iterator i = unitList.begin(); i != unitList.end(); i++) {
		if((*i)->getId() == unit->getId()) {

			unitMap.erase(unit->getId());
			unitList.erase(i);

			found = true;
			break;
		}
	}
	BOOST_ASSERT(found);

	removeLocalUnit(unit);

	unit->clearConstructions();
}

void Units::addLocalUnit(const boost::shared_ptr<Unit> unit) {
	if(unit->isAvailable()) {
		addOneLocalAvailable(unit->getLocalKey());
		addOneLocalNeutralAvailable(unit->getLocalNeutralKey());
	}
	addOneLocalTotal(unit->getLocalKey());
	addOneLocalNeutralTotal(unit->getLocalNeutralKey());
}

void Units::removeLocalUnit(const boost::shared_ptr<Unit> unit) {
	if(unit->isAvailable()) {
		removeOneLocalAvailable(unit->getLocalKey());
	}
	removeOneLocalTotal(unit->getLocalKey());
}

void Units::process() {
	for(std::list<boost::shared_ptr<Unit> >::iterator i = unitList.begin(); i != unitList.end(); i++) {
		(*i)->process();
	}	
}