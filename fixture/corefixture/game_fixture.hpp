#ifndef _CORE_FIXTURE_GAMEFIXTURE_HPP
#define _CORE_FIXTURE_GAMEFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <core/game.hpp>

#include "player_fixture.hpp"
#include "map_fixture.hpp"
#include "startcondition_fixture.hpp"

struct Game_Fixture
{
	const Player_Fixture playerFixture;
	const Map_Fixture mapFixture;
	const StartCondition_Fixture startConditionFixture;
	const std::string test_name;
	
	const boost::shared_ptr<const Game> test_game;
	
	Game_Fixture();
	virtual ~Game_Fixture();
	
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Game> > test_gameMap;

private:
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Game> > init_gamemap_helper();
};

#endif // _CORE_FIXTURE_GAMEFIXTURE_HPP
