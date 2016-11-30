#ifndef _CORE_GLOBALSTORAGE_HPP
#define _CORE_GLOBALSTORAGE_HPP

#include <map>

#pragma warning(push, 0) 
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

class Rules;
class Map;
class Player;
class GoalEntry;
class Race;
class Government;
class UnitType;
class Location;

class GlobalStorage
{
public:
	GlobalStorage();
	~GlobalStorage();

	const boost::shared_ptr<const UnitType> getUnitType(const unsigned int unitTypeId) const;
	const boost::shared_ptr<const Location> getLocation(const unsigned int locationId) const;
	const boost::shared_ptr<const Race> getRace(const unsigned int raceId) const;
	const boost::shared_ptr<const GoalEntry> getGoalEntry(const unsigned int goalEntryId) const;
	const boost::shared_ptr<const Map> getMap(const unsigned int mapId) const;
	const boost::shared_ptr<const Government> getGovernment(const unsigned int governmentId) const;
	const boost::shared_ptr<const Player> getPlayer(const unsigned int playerId) const;
	const boost::shared_ptr<const Rules> getRules(const unsigned int rulesId) const;

	void addUnitType(const boost::shared_ptr<const UnitType> unitType);
	void addLocation(const boost::shared_ptr<const Location> location);
	void addRace(const boost::shared_ptr<const Race> race);
	void addGoalEntry(const boost::shared_ptr<const GoalEntry> goalEntry);
	void addMap(const boost::shared_ptr<const Map> map);
	void addGovernment(const boost::shared_ptr<const Government> government);
	void addPlayer(const boost::shared_ptr<const Player> player);
	void addRules(const boost::shared_ptr<const Rules> rules);

	// call e.g. at the end of a fixture
	void clear();

private:
	std::map<const unsigned int, const boost::shared_ptr<const UnitType> > unitTypeMap;
	std::map<const unsigned int, const boost::shared_ptr<const Location> > locationMap;
	std::map<const unsigned int, const boost::shared_ptr<const Race> > raceMap;
	std::map<const unsigned int, const boost::shared_ptr<const GoalEntry> > goalEntryMap;
	std::map<const unsigned int, const boost::shared_ptr<const Map> > mapMap;
	std::map<const unsigned int, const boost::shared_ptr<const Government> > governmentMap;
	std::map<const unsigned int, const boost::shared_ptr<const Player> > playerMap;
	std::map<const unsigned int, const boost::shared_ptr<const Rules> > rulesMap;
};

inline const boost::shared_ptr<const UnitType> GlobalStorage::getUnitType(const unsigned int unitTypeId) const {
	const std::map<const unsigned int, const boost::shared_ptr<const UnitType> >::const_iterator i = unitTypeMap.find(unitTypeId);
	if(i == unitTypeMap.end()) {
		throw "UnitType entry for this ID not found.";
	}
	return i->second;
}

inline const boost::shared_ptr<const Location> GlobalStorage::getLocation(const unsigned int locationId) const {
	const std::map<const unsigned int, const boost::shared_ptr<const Location> >::const_iterator i = locationMap.find(locationId);
	if(i == locationMap.end()) {
		throw "Location entry for this ID not found.";
	}
	return i->second;
}

inline const boost::shared_ptr<const Rules> GlobalStorage::getRules(const unsigned int rulesId) const {
	const std::map<const unsigned int, const boost::shared_ptr<const Rules> >::const_iterator i = rulesMap.find(rulesId);
	if(i == rulesMap.end()) {
		throw "Rules entry for this ID not found.";
	}
	return i->second;
}

inline const boost::shared_ptr<const Map> GlobalStorage::getMap(const unsigned int mapId) const {
	const std::map<const unsigned int, const boost::shared_ptr<const Map> >::const_iterator i = mapMap.find(mapId);
	if(i == mapMap.end()) {
		throw "Map entry for this ID not found.";
	}
	return i->second;
}

inline const boost::shared_ptr<const Player> GlobalStorage::getPlayer(const unsigned int playerId) const {
	const std::map<const unsigned int, const boost::shared_ptr<const Player> >::const_iterator i = playerMap.find(playerId);
	if(i == playerMap.end()) {
		throw "Player entry for this ID not found.";
	}
	return i->second;
}

inline const boost::shared_ptr<const GoalEntry> GlobalStorage::getGoalEntry(const unsigned int goalEntryId) const {
	const std::map<const unsigned int, const boost::shared_ptr<const GoalEntry> >::const_iterator i = goalEntryMap.find(goalEntryId);
	if(i == goalEntryMap.end()) {
		throw "GoalEntry entry for this ID not found.";
	}
	return i->second;
}

inline const boost::shared_ptr<const Race> GlobalStorage::getRace(const unsigned int raceId) const {
	const std::map<const unsigned int, const boost::shared_ptr<const Race> >::const_iterator i = raceMap.find(raceId);
	if(i == raceMap.end()) {
		throw "Race entry for this ID not found.";
	}
	return i->second;
}

inline const boost::shared_ptr<const Government> GlobalStorage::getGovernment(const unsigned int governmentId) const {
	const std::map<const unsigned int, const boost::shared_ptr<const Government> >::const_iterator i = governmentMap.find(governmentId);
	if(i == governmentMap.end()) {
		throw "Government entry for this ID not found.";
	}
	return i->second;
}

extern GlobalStorage GLOBAL_STORAGE;

#endif // _CORE_GLOBALSTORAGE_HPP