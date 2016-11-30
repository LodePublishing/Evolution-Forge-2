#ifndef _CORE_GLOBALSTORAGE_HPP
#define _CORE_GLOBALSTORAGE_HPP

#include <map>

#pragma warning(push, 0) 
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <uuid.hpp>
#include <singleton.hpp>
#include <loadsave.hpp>

class Rules;
class Map;
class Player;
class GoalEntry;
class Race;
class Government;
class UnitType;
class Location;

class GlobalStorage : public Singleton<GlobalStorage>, public LoadSave<GlobalStorage>
{
	friend class Singleton<GlobalStorage>;
public:
	const boost::shared_ptr<const UnitType> getUnitType(const boost::uuids::uuid unitTypeId) const;
	const boost::shared_ptr<const Location> getLocation(const boost::uuids::uuid locationId) const;
	const boost::shared_ptr<const Race> getRace(const boost::uuids::uuid raceId) const;
	const boost::shared_ptr<const GoalEntry> getGoalEntry(const boost::uuids::uuid goalEntryId) const;
	const boost::shared_ptr<const Map> getMap(const boost::uuids::uuid mapId) const;
	const boost::shared_ptr<const Government> getGovernment(const boost::uuids::uuid governmentId) const;
	const boost::shared_ptr<const Player> getPlayer(const boost::uuids::uuid playerId) const;
	const boost::shared_ptr<const Rules> getRules(const boost::uuids::uuid rulesId) const;

	std::map<const boost::uuids::uuid, const boost::shared_ptr<const UnitType> >& getGetUnitTypeMap() const;
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const Location> >& getLocationMap() const;
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const Race> >& getRaceMap() const;
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const GoalEntry> >& getGoalEntryMap() const;
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const Map> >& getMapMap() const;
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const Government> >& getGovernmentMap() const;
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const Player> >& getPlayerMap() const;
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const Rules> >& getRulesMap() const;

	void addUnitType(const boost::shared_ptr<const UnitType> unitType);
	void addLocation(const boost::shared_ptr<const Location> location);
	void addRace(const boost::shared_ptr<const Race> race);
	void addGoalEntry(const boost::shared_ptr<const GoalEntry> goalEntry);
	void addMap(const boost::shared_ptr<const Map> map);
	void addGovernment(const boost::shared_ptr<const Government> government);
	void addPlayer(const boost::shared_ptr<const Player> player);
	void addRules(const boost::shared_ptr<const Rules> rules);

	void removeUnitType(const boost::uuids::uuid unitTypeId);
	void removeLocation(const boost::uuids::uuid locationId);
	void removeRace(const boost::uuids::uuid raceId);
	void removeGoalEntry(const boost::uuids::uuid goalEntryId);
	void removeMap(const boost::uuids::uuid mapId);
	void removeGovernment(const boost::uuids::uuid governmentId);
	void removePlayer(const boost::uuids::uuid playerId);
	void removeRules(const boost::uuids::uuid rulesId);

	// call e.g. at the end of a fixture
	void clear();

private:
friend class boost::serialization::access;

	template<class Archive> 
	void serialize(Archive& ar, const unsigned int version)
	{ }

	template<class Archive>
	friend inline void save_construct_data(Archive &ar, const GlobalStorage* globalStorage, const unsigned int version) { 
		
		// const std::map<const boost::uuids::uuid, const boost::shared_ptr<const UnitType> >& unitTypeMap = globalStorage->getUnitTypeMap(); -> rules
		// const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Location> >& locationMap = globalStorage->getLocationMap(); -> Map
		const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Race> >& raceMap = globalStorage->getRaceMap();
		const std::map<const boost::uuids::uuid, const boost::shared_ptr<const GoalEntry> >& goalEntryMap = globalStorage->getGoalEntryMap();
		const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Map> >& mapMap = globalStorage->getMapMap();
		const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Government> >& governmentMap = globalStorage->getGovernmentMap();
		const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Player> >& playerMap = globalStorage->getPlayerMap();
		const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Rules> >& rulesMap = globalStorage->getRulesMap();

		if(version > 0) {
		}
		
		// order is important! there are interdependencies! maybe move them to the individual maps later... make tables out of maps and add the code there
		ar & BOOST_SERIALIZATION_NVP(rulesId)
		   & BOOST_SERIALIZATION_NVP(mapId)
		   & BOOST_SERIALIZATION_NVP(startingTime)
		   & BOOST_SERIALIZATION_NVP(playerIdList);
	} 

	template<class Archive> 
	friend inline void load_construct_data(Archive& ar, GlobalStorage*& game, const unsigned int version)
	{
		boost::uuids::uuid rulesId;
		boost::uuids::uuid mapId;
		unsigned int startingTime;
		std::list<boost::uuids::uuid> playerIdList;
		std::list<boost::shared_ptr<const Player> > playerList;		

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
	}


	std::map<const boost::uuids::uuid, const boost::shared_ptr<const UnitType> > unitTypeMap;
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const Location> > locationMap;
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const Race> > raceMap;
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const GoalEntry> > goalEntryMap;
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const Map> > mapMap;
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const Government> > governmentMap;
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const Player> > playerMap;
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const Rules> > rulesMap;

	GlobalStorage();
	~GlobalStorage();
};

inline const boost::shared_ptr<const UnitType> GlobalStorage::getUnitType(const boost::uuids::uuid unitTypeId) const {
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const UnitType> >::const_iterator i = unitTypeMap.find(unitTypeId);
	if(i == unitTypeMap.end()) {
		throw "UnitType entry for this UUID not found.";
	}
	return i->second;
}

inline const boost::shared_ptr<const Location> GlobalStorage::getLocation(const boost::uuids::uuid locationId) const {
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Location> >::const_iterator i = locationMap.find(locationId);
	if(i == locationMap.end()) {
		throw "Location entry for this UUID not found.";
	}
	return i->second;
}

inline const boost::shared_ptr<const Rules> GlobalStorage::getRules(const boost::uuids::uuid rulesId) const {
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Rules> >::const_iterator i = rulesMap.find(rulesId);
	if(i == rulesMap.end()) {
		throw "Rules entry for this UUID not found.";
	}
	return i->second;
}

inline const boost::shared_ptr<const Map> GlobalStorage::getMap(const boost::uuids::uuid mapId) const {
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Map> >::const_iterator i = mapMap.find(mapId);
	if(i == mapMap.end()) {
		throw "Map entry for this UUID not found.";
	}
	return i->second;
}

inline const boost::shared_ptr<const Player> GlobalStorage::getPlayer(const boost::uuids::uuid playerId) const {
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Player> >::const_iterator i = playerMap.find(playerId);
	if(i == playerMap.end()) {
		throw "Player entry for this UUID not found.";
	}
	return i->second;
}

inline const boost::shared_ptr<const GoalEntry> GlobalStorage::getGoalEntry(const boost::uuids::uuid goalEntryId) const {
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const GoalEntry> >::const_iterator i = goalEntryMap.find(goalEntryId);
	if(i == goalEntryMap.end()) {
		throw "GoalEntry entry for this UUID not found.";
	}
	return i->second;
}

inline const boost::shared_ptr<const Race> GlobalStorage::getRace(const boost::uuids::uuid raceId) const {
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Race> >::const_iterator i = raceMap.find(raceId);
	if(i == raceMap.end()) {
		throw "Race entry for this UUID not found.";
	}
	return i->second;
}

inline const boost::shared_ptr<const Government> GlobalStorage::getGovernment(const boost::uuids::uuid governmentId) const {
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Government> >::const_iterator i = governmentMap.find(governmentId);
	if(i == governmentMap.end()) {
		throw "Government entry for this UUID not found.";
	}
	return i->second;
}

#endif // _CORE_GLOBALSTORAGE_HPP