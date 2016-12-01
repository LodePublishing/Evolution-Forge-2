#include "rules.hpp"

Rules::Rules(const std::string& name, 
	const std::list<boost::shared_ptr<const Race> > raceList,
	const std::list<boost::shared_ptr<const UnitType> > unitTypeList):
name(name),
	unitTypeList(unitTypeList),
	unitTypeIdList(),
	unitTypeMap(),
	raceList(raceList),
	raceIdList(),
	raceMap()
{
	initialize();
}

Rules::Rules(
	const boost::uuids::uuid id,
	const std::string& name, 
	const std::list<boost::shared_ptr<const Race> > raceList,
	const std::list<boost::shared_ptr<const UnitType> > unitTypeList):
UUID<Rules>(id),
	name(name),
	unitTypeList(unitTypeList),
	unitTypeIdList(),
	unitTypeMap(),
	raceList(raceList),
	raceIdList(),
	raceMap()
{
	initialize();
}

Rules::~Rules()
{
}

void Rules::initialize()
{
	for(std::list<boost::shared_ptr<const Race> >::const_iterator i = raceList.begin(); i != raceList.end(); i++) {
		raceMap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const Race> >((*i)->getId(), *i));
		raceIdList.push_back((*i)->getId());
	}
	for(std::list<boost::shared_ptr<const UnitType> >::const_iterator i = unitTypeList.begin(); i != unitTypeList.end(); i++) {
		unitTypeMap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const UnitType> >((*i)->getId(), *i));
		unitTypeIdList.push_back((*i)->getId());
	}

}

// TODO make const unit type? How to load from disk then?
const boost::shared_ptr<const UnitType> Rules::getUnitType(boost::uuids::uuid unitTypeId) const {
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const UnitType> >::const_iterator i = unitTypeMap.find(unitTypeId);
	if(i == unitTypeMap.end()) {
		throw std::exception();
	}
	return i->second;
}


const boost::shared_ptr<const Race> Rules::getRace(boost::uuids::uuid raceId) const {
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Race> >::const_iterator i = raceMap.find(raceId);
	if(i == raceMap.end()) {
		throw std::exception();
	}
	return i->second;
}
