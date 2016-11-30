#pragma warning(push, 0)  
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#include <boost/assign/list_of.hpp>
#pragma warning(pop)

#include "game_fixture.hpp"

Game_Fixture::Game_Fixture():
	Random_Fixture(),
	unitsFixture(),
	rulesFixture(),
	mapFixture(),
	playerFixture(),

	test_startingTime(rnd()),

	test_units(boost::shared_ptr<Units>(new Units())),
	test_unit1(boost::shared_ptr<Unit>(new Unit(playerFixture.test_player, unitsFixture.unitFixture.unitType1, mapFixture.test_map->getLocation(0), test_units))),
	test_unit2(boost::shared_ptr<Unit>(new Unit(playerFixture.test_player, unitsFixture.unitFixture.unitType1, mapFixture.test_map->getLocation(0), test_units))),
	test_unit3(boost::shared_ptr<Unit>(new Unit(playerFixture.test_player, unitsFixture.unitFixture.unitType2, mapFixture.test_map->getLocation(0), test_units))),	
	test_game(boost::shared_ptr<Game>(new Game(rulesFixture.test_rules, mapFixture.test_map, test_startingTime, boost::assign::list_of(playerFixture.test_player)))),

	test_filename_xml("demofile_game.txt"),
	test_filename("demofile_game")
{
	test_units->addUnit(test_unit1);
	test_units->addUnit(test_unit2);
	test_units->addUnit(test_unit3);
}

Game_Fixture::~Game_Fixture()
{
	Unit::resetCounter();
}
