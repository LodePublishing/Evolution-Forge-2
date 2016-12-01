#include "gamedata.hpp"

#include <core/race_storage.hpp>
#include <core/rules_storage.hpp>
#include <core/unittype_storage.hpp>
#include <core/core_directories.hpp>

const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Rules> > GameData::init_rulesmap_helper() {
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const Rules> > rulesMap;
	rulesMap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const Rules> >(rules->getId(), rules));
	return rulesMap;
}

const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Race> > GameData::init_racemap_helper() {
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const Race> > raceMap;
	
	for(std::list<boost::shared_ptr<const Race> >::const_iterator i = rules->getRaceList().begin(); i != rules->getRaceList().end(); i++) {
		raceMap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const Race> >((*i)->getId(), *i));
	}

	return raceMap;
}

const std::map<const boost::uuids::uuid, const boost::shared_ptr<const UnitType> > GameData::init_unittypemap_helper() {
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const UnitType> > unitTypeMap;
	
	for(std::list<boost::shared_ptr<const UnitType> >::const_iterator i = rules->getUnitTypeList().begin(); i != rules->getUnitTypeList().end(); i++) {
		unitTypeMap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const UnitType> >((*i)->getId(), *i));
	}

	return unitTypeMap;
}

GameData::GameData(std::map<const unsigned int, const boost::uuids::uuid> race_id_map,
			std::map<const unsigned int, const boost::uuids::uuid> unit_id_map):
	race_id_map(race_id_map),
	unit_id_map(unit_id_map)
{ }

void GameData::initRules() {
	RaceStorage::instance(init_racemap_helper());
	RulesStorage::instance(init_rulesmap_helper());
	UnitTypeStorage::instance(init_unittypemap_helper());
}

GameData::~GameData() 
{ 
	CoreDirectories::initTemp("temp");
	
	RaceStorage::clear();
	RulesStorage::clear();

	CoreDirectories::init();
}