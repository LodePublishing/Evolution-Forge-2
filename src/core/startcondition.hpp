#ifndef _CORE_STARTCONDITION_HPP
#define _CORE_STARTCONDITION_HPP

#include <list>
#include <map>

#pragma warning(push, 0)  
#include <boost/shared_ptr.hpp>
#pragma warning(pop)

#include <misc/uuid.hpp>
#include "units.hpp"
#include "player.hpp"

// The 'constants' class is compiled by the UI / external files
/*
User choses a game (rules), a map, the start configuration (game mode, maybe dependant on the rules), the starting time (usually 0) and the players.
Players are configured so that they include a goal. Usually, in the one-player-test scenario, it is a number of units to reach.
*/


class StartCondition : public UUID<StartCondition>
{
public:
	StartCondition(const std::string& name,
		const unsigned int startingTime,
		const boost::shared_ptr<const Units> units,
		const std::list<boost::shared_ptr<const Player> > playerList);
	StartCondition(const boost::uuids::uuid id,
		const std::string& name,
		const unsigned int startingTime,
		const boost::shared_ptr<const Units> units,
		const std::list<boost::shared_ptr<const Player> > playerList);
	~StartCondition();

	const std::string& getName() const;

	const boost::shared_ptr<const Player>& getPlayer(const boost::uuids::uuid playerId) const;
	const std::list<boost::uuids::uuid>& getPlayerIdList() const;

	const boost::shared_ptr<const Units>& getUnits() const;
	const boost::uuids::uuid getUnitsId() const;

	unsigned int getStartingTime() const;

private:
	const std::string name;
	const unsigned int startingTime;

	const boost::shared_ptr<const Units> units;
	const boost::uuids::uuid unitsId;
	

	const std::list<boost::shared_ptr<const Player> > playerList;
	const std::list<boost::uuids::uuid> playerIdList;
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Player> > playerMap; // playerId -> player	

	const std::list<boost::uuids::uuid> initialize_playeridlist_helper() const;
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Player> > initialize_playermap_helper() const;

	StartCondition& operator=(const StartCondition& other);
	StartCondition(const StartCondition& other);
};

inline const std::string& StartCondition::getName() const {
	return name;
}

inline const boost::shared_ptr<const Player>& StartCondition::getPlayer(const boost::uuids::uuid playerId) const {
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Player> >::const_iterator i = playerMap.find(playerId);
	if(i == playerMap.end()) {
		throw std::exception();
	}
	return i->second;
}

inline const std::list<boost::uuids::uuid>& StartCondition::getPlayerIdList() const {
	return playerIdList;
}

inline const boost::shared_ptr<const Units>& StartCondition::getUnits() const {
	return units;
}

inline const boost::uuids::uuid StartCondition::getUnitsId() const {
	return units->getId();
}

inline unsigned int StartCondition::getStartingTime() const {
	return startingTime;
}


#endif // _CORE_STARTCONDITION_HPP
