#ifndef _GAMES_WARCRAFT_HPP
#define _GAMES_WARCRAFT_HPP

#include "gamedata.hpp"
#include <misc/miscellaneous.hpp>

class WarCraft : public GameData
{
public:
	WarCraft();
	~WarCraft();	

private:

	boost::shared_ptr<const Race> neutralRace;
	boost::shared_ptr<const Race> humanRace;
	boost::shared_ptr<const Race> orcRace;

	const std::map<const unsigned int, const boost::uuids::uuid> init_raceidmap_helper() const;
	const std::map<const unsigned int, const boost::uuids::uuid> init_unitidmap_helper() const;	
	const std::list<boost::shared_ptr<const Race> > init_racelist_helper() const;	
	const std::list<boost::shared_ptr<const UnitType> > init_unittypelist_helper();
};
#endif // _GAME_WARCRAFT_HPP
