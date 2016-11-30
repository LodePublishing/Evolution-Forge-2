#pragma warning(push, 0)  
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include <globalstorage.hpp>	

#include "player_fixture.hpp"
#include "goalentry_fixture.hpp"
#include "government_fixture.hpp"
#include <random_fixture.hpp>

Player_Fixture::Player_Fixture():
	test_player_name("my_player_Name"),
	test_startingUnits(), // TODO
	test_player(boost::shared_ptr<const Player>(new Player(test_player_name, GlobalStorage::instance().getGovernment(test_government_id), GlobalStorage::instance().getGoalEntry(test_goalentry_id), test_startingUnits)))
{ }

Player_Fixture::~Player_Fixture() 
{ }