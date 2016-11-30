#ifndef _CORE_GAME_HPP
#define _CORE_GAME_HPP

#include <list>
#include <map>

#pragma warning(push, 0)  
#include <boost/serialization/base_object.hpp>
#include <boost/shared_ptr.hpp>
#pragma warning(pop)

#include <uuid.hpp>

#include <globalstorage.hpp>

#include "player.hpp"
#include "rules.hpp"
#include "map.hpp"

// The 'constants' class is compiled by the UI / external files
/*
User choses a game (rules), a map, the start configuration (game mode, maybe dependant on the rules), the starting time (usually 0) and the players.
Players are configured so that they include a goal. Usually, in the one-player-test scenario, it is a number of units to reach.
*/

class Units;

class Game : public LoadSave<Game>, public UUID<Game>
{
public:
	Game(const boost::shared_ptr<const Rules> rules,
		const boost::shared_ptr<const Map> map,
		const unsigned int startingTime,
		const std::list<boost::shared_ptr<const Player> > playerList);
	~Game();
	
	const boost::shared_ptr<const Map> getMap() const;
	boost::uuids::uuid getMapId() const;

	const boost::shared_ptr<const Rules> getRules() const;
	boost::uuids::uuid getRulesId() const;

	const boost::shared_ptr<const Player> getPlayer(const boost::uuids::uuid playerId) const;
	const std::list<boost::uuids::uuid> getPlayerIdList() const;

	unsigned int getStartingTime() const;
/*	1. Alle mit UUID auch Save/Load
	2. Jeweils Reload Tests dazu schreiben
	3. Global Storage lädt/schreibt alle von Platte	
	4. Tests dazu schreiben TODO*/

private:
	friend class boost::serialization::access;

	template<class Archive> 
	void serialize(Archive& ar, const unsigned int version)
	{ }

	template<class Archive>
	friend inline void save_construct_data(Archive &ar, const Game* game, const unsigned int version) { 
		const boost::uuids::uuid& rulesId = game->getRulesId();
		const boost::uuids::uuid& mapId = game->getMapId();
		const unsigned int& startingTime = game->getStartingTime();
		const std::list<boost::uuids::uuid>& playerIdList = game->getPlayerIdList();

		for(std::list<boost::uuids::uuid>::const_iterator i = playerIdList.begin(); i != playerIdList.end(); i++) {
			GlobalStorage::instance().addPlayer(game->getPlayer(*i));
		}
		GlobalStorage::instance().addMap(game->getMap());
		GlobalStorage::instance().addRules(game->getRules());
		// TODO delete function!
		if(version > 0) {
		}

		ar & BOOST_SERIALIZATION_NVP(rulesId)
		   & BOOST_SERIALIZATION_NVP(mapId)
		   & BOOST_SERIALIZATION_NVP(startingTime)
		   & BOOST_SERIALIZATION_NVP(playerIdList);
	} 

	template<class Archive> 
	friend inline void load_construct_data(Archive& ar, Game*& game, const unsigned int version)
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

	const boost::shared_ptr<const Rules> rules;
	const boost::uuids::uuid rulesId;

	const boost::shared_ptr<const Map> map;
	const boost::uuids::uuid mapId;
	
	const unsigned int startingTime;

	const std::list<boost::shared_ptr<const Player> > playerList;
	std::list<boost::uuids::uuid> playerIdList;
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const Player> > playerMap; // playerId -> player	

	Game& operator=(const Game& other);
};

inline const boost::shared_ptr<const Player> Game::getPlayer(const boost::uuids::uuid playerId) const {
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Player> >::const_iterator i = playerMap.find(playerId);
	if(i == playerMap.end()) {
		throw std::exception();
	}
	return i->second;
}

inline const std::list<boost::uuids::uuid> Game::getPlayerIdList() const {
	return playerIdList;
}

inline const boost::shared_ptr<const Rules> Game::getRules() const {
	return rules;
}

inline const boost::shared_ptr<const Map> Game::getMap() const {
	return map;
}

inline boost::uuids::uuid Game::getMapId() const {
	return mapId;
}

inline boost::uuids::uuid Game::getRulesId() const {
	return rulesId;
}

inline unsigned int Game::getStartingTime() const {
	return startingTime;
}

#endif // _CORE_GAME_HPP
