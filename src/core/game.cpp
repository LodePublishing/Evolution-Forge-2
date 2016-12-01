#pragma warning(push, 0)  
#include <boost/assert.hpp>
#pragma warning(pop)

#include "game.hpp"

Game::Game(const std::string& name,
	const boost::shared_ptr<const Rules>& rules,
	const boost::shared_ptr<const Map> map,
	const boost::shared_ptr<const StartCondition> startCondition):
	
	UUID<Game>(),
	name(name),
	rules(rules),
	rulesId(rules->getId()),
	map(map),
	mapId(map->getId()),
	startCondition(startCondition),
	startConditionId(startCondition->getId())
{ }

Game::Game(const boost::uuids::uuid id,
	const std::string& name,
	const boost::shared_ptr<const Rules>& rules,
	const boost::shared_ptr<const Map> map,
	const boost::shared_ptr<const StartCondition> startCondition):
	
	UUID<Game>(id),	
	name(name),
	rules(rules),
	rulesId(rules->getId()),
	map(map),
	mapId(map->getId()),
	startCondition(startCondition),
	startConditionId(startCondition->getId())
{ }
	
Game::~Game()
{ }