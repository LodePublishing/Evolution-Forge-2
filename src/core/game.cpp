#pragma warning(push, 0)  
#include <boost/assert.hpp>
#pragma warning(pop)

#include "game.hpp"
#include "units.hpp"

Game::Game(const boost::shared_ptr<const Rules> rules,
	const boost::shared_ptr<const Map> map,
	const unsigned int startingTime,
	const std::list<boost::shared_ptr<const Player> > playerList):
	rules(rules),
	rulesId(rules->getId()),
	map(map),
	mapId(map->getId()),	
	startingTime(startingTime),
	playerList(playerList),
	playerIdList(),
	playerMap()
{
	for(std::list<boost::shared_ptr<const Player> >::const_iterator i = playerList.begin(); i != playerList.end(); i++) {
		playerIdList.push_back((*i)->getId());
		playerMap.insert(std::pair<const unsigned int, const boost::shared_ptr<const Player> >((*i)->getId(), *i));
	}
}

Game::~Game()
{}
