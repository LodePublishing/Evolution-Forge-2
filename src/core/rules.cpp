#include "rules.hpp"

Rules::Rules(const std::string& name, 
	const std::list<boost::shared_ptr<const UnitType> > unitTypeList):
	name(name),
	unitTypeList(unitTypeList),
	unitTypeMap()
{
	initializeUnitTypes();
}

Rules::Rules(
	const unsigned int id,
	const std::string& name, 
	const std::list<boost::shared_ptr<const UnitType> > unitTypeList):
	ID<Rules>(id),
	name(name),
	unitTypeList(unitTypeList),
	unitTypeMap()
{
	initializeUnitTypes();
}

Rules::~Rules()
{
}

void Rules::initializeUnitTypes()
{
	for(std::list<boost::shared_ptr<const UnitType> >::const_iterator i = unitTypeList.begin(); i != unitTypeList.end(); i++) {
		this->unitTypeMap.insert(std::pair<const unsigned int, const boost::shared_ptr<const UnitType> >((*i)->getId(), *i));
	}	
}

// TODO make const unit type? How to load from disk then?
const boost::shared_ptr<const UnitType> Rules::getUnitType(unsigned int unitTypeId) const {
	const std::map<const unsigned int, const boost::shared_ptr<const UnitType> >::const_iterator i = unitTypeMap.find(unitTypeId);
    if(i == unitTypeMap.end()) {
		throw "Could not find unit type ID";
	}
    return i->second;
}
