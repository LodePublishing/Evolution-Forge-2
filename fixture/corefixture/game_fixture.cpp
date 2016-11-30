#pragma warning(push, 0)
#include <boost/assign/list_of.hpp>
#pragma warning(pop)

#include <random_fixture.hpp>

#include "game_fixture.hpp"


Game_Fixture::Game_Fixture():
	playerFixture(),
	mapFixture(),
	unitsFixture(),
	broodwar(),

	test_startingTime(Random_Fixture::instance().rnd()),

	test_game(boost::shared_ptr<Game>(new Game(broodwar.getRules(),  mapFixture.test_map, test_startingTime, boost::assign::list_of(playerFixture.test_player)))),

	test_filename_xml("demofile_game.txt"),
	test_filename("demofile_game")
{ }

Game_Fixture::~Game_Fixture()
{ }
