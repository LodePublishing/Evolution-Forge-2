#include <random_fixture.hpp>
#include <globalstorage.hpp>

#include "player_fixture.hpp"


Player_Fixture::Player_Fixture():
	governmentFixture(),

	test_player_name("my_player_Name"),
	test_startingUnits(), // TODO
	test_player(boost::shared_ptr<const Player>(new Player(test_player_name, governmentFixture.test_government, test_startingUnits)))
{ 
	GlobalStorage::instance().addPlayer(test_player);
}

Player_Fixture::~Player_Fixture() 
{ 
	GlobalStorage::instance().removePlayer(test_player->getId());
}