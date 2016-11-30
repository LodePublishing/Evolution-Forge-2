#include "globalstorage.hpp"

#include "rules.hpp"
#include "map.hpp"
#include "player.hpp"
#include "goalentry.hpp"
#include "race.hpp"

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

void GlobalStorage::addGoalEntry(const boost::shared_ptr<const GoalEntry> goalEntry) {
	goalEntryMap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const GoalEntry> >(goalEntry->getId(), goalEntry));
}

void GlobalStorage::addRace(const boost::shared_ptr<const Race> race) {
	raceMap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const Race> >(race->getId(), race));
}

void GlobalStorage::addGovernment(const boost::shared_ptr<const Government> government) {
	governmentMap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const Government> >(government->getId(), government));
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

void GlobalStorage::removeGoalEntry(const boost::uuids::uuid goalEntryId) {
	goalEntryMap.erase(goalEntryMap.find(goalEntryId));
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
	goalEntryMap.clear();
	mapMap.clear();
	governmentMap.clear();
	playerMap.clear();
	rulesMap.clear();
}
