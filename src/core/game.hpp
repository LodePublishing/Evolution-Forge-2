#ifndef _CORE_GAME_HPP
#define _CORE_GAME_HPP

#include <list>
#include <map>

#pragma warning(push, 0)  
#include <boost/serialization/base_object.hpp>
#pragma warning(pop)

#include "player.hpp"
#include "rules.hpp"
#include "map.hpp"

// The 'constants' class is compiled by the UI / external files
/*
User choses a game (rules), a map, the start configuration (game mode, maybe dependant on the rules), the starting time (usually 0) and the players.
Players are configured so that they include a goal. Usually, in the one-player-test scenario, it is a number of units to reach.
*/

class Units;

class Game : public LoadSave<Game>
{
public:
	Game(const Rules* const rules,
		const Map* const map,
		const Units* const startingUnits,
		const unsigned int startingTime);
	~Game();

	const Player* getPlayer(unsigned int playerID) const;
	const Units* getStartingUnits() const;
	const Map* getMap() const;
	const Rules* getRules() const;

	
	unsigned int getMapId() const;
	unsigned int getRulesId() const;

	void addPlayer(const Player* player);
	void assignMap(const Map* const map);
	void assignRules(const Rules* const rules);

	unsigned int getStartingTime() const;

	void initialize(std::map<int, Rules*> rulesStorage, std::map<int, Map*> mapStorage);

	// needs to be public to allow deserialization (loading)
	Game():startingUnits(NULL),rules(NULL),map(NULL) {}

private:
	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive &ar, const unsigned int version)
	{
		ar & boost::serialization::make_nvp(Rules_tag_string, rulesId);
		ar & boost::serialization::make_nvp(PlayerList_tag_string, playerMap);
		ar & boost::serialization::make_nvp(Map_tag_string, mapId);
		ar & boost::serialization::make_nvp(StartingTime_tag_string, startingTime);
		ar & boost::serialization::make_nvp(StartingUnits_tag_string, startingUnits);
		// paths are saved in the map! Need to be reassigned!
		if(version > 0) {
		}
	}

	std::list<unsigned int> playerList;
	std::map<unsigned int, const Player*> playerMap; // playerID -> player

	Units* startingUnits;

	const Rules* rules;
	unsigned int rulesId;

	const Map* map;
	unsigned int mapId;


	unsigned int startingTime;

	static const char* const Rules_tag_string;
	static const char* const PlayerList_tag_string;
	static const char* const Map_tag_string;	
	static const char* const StartingTime_tag_string;
	static const char* const StartingUnits_tag_string;
};

inline const Player* Game::getPlayer(unsigned int playerID) const {
	const std::map<unsigned int, const Player*>::const_iterator i = playerMap.find(playerID);
	if(i == playerMap.end()) {
		throw "Could not find player ID";
	}
	return i->second;
}


inline const Rules* Game::getRules() const {
	return rules;
}

inline const Map* Game::getMap() const {
	return map;
}

inline unsigned int Game::getMapId() const {
	return mapId;
}

inline unsigned int Game::getRulesId() const {
	return rulesId;
}

inline const Units* Game::getStartingUnits() const {
	return startingUnits;
}

inline unsigned int Game::getStartingTime() const {
	return startingTime;
}

#endif // _CORE_GAME_HPP