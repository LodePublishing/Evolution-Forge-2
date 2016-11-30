#include "globalstorage.hpp"

#include <rules.hpp>
#include <map.hpp>
#include <player.hpp>
#include <race.hpp>

GlobalStorage::GlobalStorage():
	unitTypeMap(),
	locationMap(),
	raceMap(),
	goalEntryMap(),
	mapMap(),
	governmentMap(),
	playerMap(),
	rulesMap()
{
	// load lists TODO? Or call this externally?
}

GlobalStorage::~GlobalStorage()
{

}

void GlobalStorage::addRules(const boost::shared_ptr<const Rules> rules) {
	rulesMap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const Rules> >(rules->getId(), rules));
}

void GlobalStorage::addMap(const boost::shared_ptr<const Map> map) {
	mapMap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const Map> >(map->getId(), map));
}

void GlobalStorage::addPlayer(const boost::shared_ptr<const Player> player) {
	playerMap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const Player> >(player->getId(), player));
}

void GlobalStorage::addRace(const boost::shared_ptr<const Race> race) {
	raceMap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const Race> >(race->getId(), race));
}

void GlobalStorage::addGovernment(const boost::shared_ptr<const Government> government) {
	governmentMap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const Government> >(government->getId(), government));
}

void GlobalStorage::addLocation(const boost::shared_ptr<const Location> location) {
	locationMap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const Location> >(location->getId(), location));
}

void GlobalStorage::addUnitType(const boost::shared_ptr<const UnitType> unittype) {
	unitTypeMap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const UnitType> >(unittype->getId(), unittype));
}



void GlobalStorage::removeUnitType(const boost::uuids::uuid unitTypeId) {
	unitTypeMap.erase(unitTypeMap.find(unitTypeId));
}

void GlobalStorage::removeLocation(const boost::uuids::uuid locationId) {
	locationMap.erase(locationMap.find(locationId));
}

void GlobalStorage::removeRace(const boost::uuids::uuid raceId) {
	raceMap.erase(raceMap.find(raceId));
}

void GlobalStorage::removeMap(const boost::uuids::uuid mapId) {
	mapMap.erase(mapMap.find(mapId));
}

void GlobalStorage::removeGovernment(const boost::uuids::uuid governmentId) {
	governmentMap.erase(governmentMap.find(governmentId));
}

void GlobalStorage::removePlayer(const boost::uuids::uuid playerId) {
	playerMap.erase(playerMap.find(playerId));
}

void GlobalStorage::removeRules(const boost::uuids::uuid rulesId) {
	rulesMap.erase(rulesMap.find(rulesId));
}


void GlobalStorage::clear() {
	unitTypeMap.clear();
	locationMap.clear();
	raceMap.clear();
	mapMap.clear();
	governmentMap.clear();
	playerMap.clear();
	rulesMap.clear();
}

/* TODO
template<class Archive>
void save_construct_data(Archive &ar, const GlobalStorage* globalStorage, const unsigned int version) { 

	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const UnitType> >& unitTypeMap = globalStorage->getUnitTypeMap();
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Location> >& locationMap = globalStorage->getLocationMap();
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Race> >& raceMap = globalStorage->getRaceMap();
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Map> >& mapMap = globalStorage->getMapMap();
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Government> >& governmentMap = globalStorage->getGovernmentMap();
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Player> >& playerMap = globalStorage->getPlayerMap();
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Rules> >& rulesMap = globalStorage->getRulesMap();

	if(version > 0) {
	}
	// TODO
	//einzeln?
	// order is important! there are interdependencies! maybe move them to the individual maps later... make tables out of maps and add the code there
	ar & BOOST_SERIALIZATION_NVP(rulesId)
		& BOOST_SERIALIZATION_NVP(mapId)
		& BOOST_SERIALIZATION_NVP(startingTime)
		& BOOST_SERIALIZATION_NVP(playerIdList);
} */
/*
template<class Archive> 
void load_construct_data(Archive& ar, GlobalStorage*& game, const unsigned int version)
{
	boost::uuids::uuid rulesId;
	boost::uuids::uuid mapId;
	unsigned int startingTime;
	std::list<boost::uuids::uuid> playerIdList;
	std::list<boost::shared_ptr<const Player> > playerList;		
	TODO
	ar & BOOST_SERIALIZATION_NVP(rulesId)
		& BOOST_SERIALIZATION_NVP(mapId)
		& BOOST_SERIALIZATION_NVP(startingTime)
		& BOOST_SERIALIZATION_NVP(playerIdList);

	for(std::list<boost::uuids::uuid>::const_iterator i = playerIdList.begin(); i != playerIdList.end(); i++) {
		playerList.push_back(GlobalStorage::instance().getPlayer(*i));
	}

	if(version > 0) {
	}

	::new(game)Game(GlobalStorage::instance().getRules(rulesId), GlobalStorage::instance().getMap(mapId), startingTime, playerList);
}*/