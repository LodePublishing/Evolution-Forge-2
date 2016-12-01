#ifndef _GAMES_MOO_HPP
#define _GAMES_MOO_HPP

#include "gamedata.hpp"
#include <misc/miscellaneous.hpp>

class MasterOfOrion : public GameData
{
public:
	MasterOfOrion();
	~MasterOfOrion();	

private:
	boost::shared_ptr<const Race> neutralRace;

	const std::map<const unsigned int, const boost::uuids::uuid> init_raceidmap_helper() const;
	const std::map<const unsigned int, const boost::uuids::uuid> init_unitidmap_helper() const;	
	const std::list<boost::shared_ptr<const Race> > init_racelist_helper() const;	
	const std::list<boost::shared_ptr<const UnitType> > init_unittypelist_helper();
};

#endif // _GAME_MOO_HPP
