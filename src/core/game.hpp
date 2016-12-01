#ifndef _CORE_GAME_HPP
#define _CORE_GAME_HPP

#include <misc/uuid.hpp>

// The 'constants' class is compiled by the UI / external files
/*
User choses a game (rules), a map, the start configuration (game mode, maybe dependant on the rules), the starting time (usually 0) and the players.
Players are configured so that they include a goal. Usually, in the one-player-test scenario, it is a number of units to reach.
*/

#include "rules.hpp"
#include "map.hpp"
#include "startcondition.hpp"

class Game : public UUID<Game>
{
public:
	Game(const std::string& name,
		const boost::shared_ptr<const Rules>& rules,
		const boost::shared_ptr<const Map> map,
		const boost::shared_ptr<const StartCondition> startCondition);
	Game(const boost::uuids::uuid id,
		const std::string& name,
		const boost::shared_ptr<const Rules>& rules,
		const boost::shared_ptr<const Map> map,
		const boost::shared_ptr<const StartCondition> startCondition);
	~Game();

	const std::string& getName() const;

	const boost::shared_ptr<const Map>& getMap() const;
	boost::uuids::uuid getMapId() const;

	const boost::shared_ptr<const Rules>& getRules() const;
	boost::uuids::uuid getRulesId() const;

	const boost::shared_ptr<const StartCondition>& getStartCondition() const;
	boost::uuids::uuid getStartConditionId() const;

private:
	const std::string name;

	const boost::shared_ptr<const Rules> rules;
	const boost::uuids::uuid rulesId;

	const boost::shared_ptr<const Map> map;
	const boost::uuids::uuid mapId;

	const boost::shared_ptr<const StartCondition> startCondition;
	const boost::uuids::uuid startConditionId;
	
	Game& operator=(const Game& other);
	Game(const Game& other);
};

inline const std::string& Game::getName() const {
	return name;
}


inline const boost::shared_ptr<const Rules>& Game::getRules() const {
	return rules;
}

inline boost::uuids::uuid Game::getRulesId() const {
	return rulesId;
}

inline const boost::shared_ptr<const Map>& Game::getMap() const {
	return map;
}

inline boost::uuids::uuid Game::getMapId() const {
	return mapId;
}

inline const boost::shared_ptr<const StartCondition>& Game::getStartCondition() const {
	return startCondition;
}

inline boost::uuids::uuid Game::getStartConditionId() const {
	return startConditionId;
}


#endif // _CORE_GAME_HPP
