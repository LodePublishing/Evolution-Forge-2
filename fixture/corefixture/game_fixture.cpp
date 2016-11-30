#include <iostream>
#include <time.h>

#pragma warning(push, 0)  
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include "game_fixture.hpp"

Game_Fixture::Game_Fixture():
	unitsFixture(),
	rulesFixture(),
	mapFixture(),
	test_filename_xml("demofile_game.txt"),
	test_filename("demofile_game"),
	seed(time(0))
{
	boost::mt19937 generator(static_cast<boost::uint32_t>(seed));
	boost::uniform_int<> distribution(1, 100);
	boost::variate_generator<boost::mt19937&, boost::uniform_int<> > rnd(generator,  distribution); 
	std::cout << "Setting up game fixture (seed " << seed << ")" << std::endl;

	test_unit1 = new Unit(unitsFixture.unitFixture.unitType1,  unitsFixture.test_player, mapFixture.locations[0]);
	test_unit2 = new Unit(unitsFixture.unitFixture.unitType1,  unitsFixture.test_player, mapFixture.locations[0]);
	test_unit3 = new Unit(unitsFixture.unitFixture.unitType2,  unitsFixture.test_player, mapFixture.locations[0]);

	test_startingTime = rnd();

	test_game = new Game(rulesFixture.test_rules, mapFixture.test_map, mapFixture.test_units, test_startingTime);
	//test_game->addPlayer(playerFixture.test_player);
}

Game_Fixture::~Game_Fixture()
{
	delete test_game;
}
