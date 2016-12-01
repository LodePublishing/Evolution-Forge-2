#ifndef _GAMES_BROODWAR_HPP
#define _GAMES_BROODWAR_HPP
// TODO abstrakte Klasse für alle Games

#include "gamedata.hpp"
#include <misc/miscellaneous.hpp>

class BroodWar : public GameData
{
public:
	BroodWar();
	~BroodWar();

private:
	boost::uuids::uuid BROODWAR_ID;

	boost::shared_ptr<const Race> neutralRace;
	boost::shared_ptr<const Race> terraRace;
	boost::shared_ptr<const Race> protossRace;
	boost::shared_ptr<const Race> zergRace;

	const std::map<const unsigned int, const boost::uuids::uuid> init_raceidmap_helper() const;
	const std::map<const unsigned int, const boost::uuids::uuid> init_unitidmap_helper() const;	
	const std::list<boost::shared_ptr<const Race> > init_racelist_helper() const;	
	const std::list<boost::shared_ptr<const UnitType> > init_unittypelist_helper();
};

#endif // _GAME_BROODWAR_HPP
