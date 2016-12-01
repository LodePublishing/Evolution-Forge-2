#pragma warning(push, 0)  
#include <boost/assert.hpp>
#pragma warning(pop)

#include "startcondition.hpp"


StartCondition::StartCondition(const std::string& name,
	const unsigned int startingTime,
	const boost::shared_ptr<const Units> units,
	const std::list<boost::shared_ptr<const Player> > playerList):
	UUID<StartCondition>(),
	name(name),
	startingTime(startingTime),
	units(units),
	unitsId(units->getId()),
	playerList(playerList),
	playerIdList(initialize_playeridlist_helper()),
	playerMap(initialize_playermap_helper())
{ }

StartCondition::StartCondition(const boost::uuids::uuid id,
	const std::string& name,
	const unsigned int startingTime,
	const boost::shared_ptr<const Units> units,
	const std::list<boost::shared_ptr<const Player> > playerList):
	UUID<StartCondition>(id),	
	name(name),
	startingTime(startingTime),
	units(units),
	unitsId(units->getId()),
	playerList(playerList),
	playerIdList(initialize_playeridlist_helper()),
	playerMap(initialize_playermap_helper())
{ }

const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Player> > StartCondition::initialize_playermap_helper() const {
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const Player> > player_map;

	for(std::list<boost::shared_ptr<const Player> >::const_iterator i = playerList.begin(); i != playerList.end(); i++) {
		player_map.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const Player> >((*i)->getId(), *i));
	}

	return player_map;
}

const std::list<boost::uuids::uuid> StartCondition::initialize_playeridlist_helper() const {
	std::list<boost::uuids::uuid> playerid_list;

	for(std::list<boost::shared_ptr<const Player> >::const_iterator i = playerList.begin(); i != playerList.end(); i++) {
		playerid_list.push_back((*i)->getId());
	}

	return playerid_list;
}

StartCondition::~StartCondition()
{ }

