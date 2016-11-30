#pragma warning(push, 0)  
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#include <boost/assign/list_of.hpp>
#pragma warning(pop)

#include "game_fixture.hpp"
#include "player_fixture.hpp"
#include "units_fixture.hpp"
#include "unit_fixture.hpp"
#include "rules_fixture.hpp"
#include "map_fixture.hpp"
#include <random_fixture.hpp>

Game_Fixture::Game_Fixture():
	test_startingTime(Random_Fixture::instance().rnd()),

	test_units(boost::shared_ptr<Units>(new Units())),
	test_unit1(boost::shared_ptr<Unit>(new Unit(Player_Fixture::instance().test_player.unitType1.test_map->getLocation(0), test_units))),
	test_unit2(boost::shared_ptr<Unit>(new Unit(Player_Fixture::instance().test_player.unitType1.test_map->getLocation(0), test_units))),
	test_unit3(boost::shared_ptr<Unit>(new Unit(Player_Fixture::instance().test_player.unitType2.test_map->getLocation(0), test_units))),	
	test_game(boost::shared_ptr<Game>(new Game(Rules_Fixture::instance().test_rules.test_map, test_startingTime, boost::assign::list_of(Player_Fixture::instance().test_player)))),

	test_filename_xml("demofile_game.txt"),
	test_filename("demofile_game")
{
	test_units->addUnit(test_unit1);
	test_units->addUnit(test_unit2);
	test_units->addUnit(test_unit3);
}

Game_Fixture::~Game_Fixture()
{ }
