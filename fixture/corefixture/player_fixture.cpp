#pragma warning(push, 0)  
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include <globalstorage.hpp>	

#include "player_fixture.hpp"

Player_Fixture::Player_Fixture():
	Random_Fixture(),
	test_player_name("my_player_Name"), 
	test_governmentFixture(),
	test_goalEntryFixture(),
	test_startingUnits(), // TODO
	test_player(boost::shared_ptr<const Player>(new Player(test_player_name, test_governmentFixture.test_government, test_goalEntryFixture.test_goalentry, test_startingUnits)))
{
	GLOBAL_STORAGE.addPlayer(test_player);
}

Player_Fixture::~Player_Fixture() 
{ 
	Player::resetCounter();
}
