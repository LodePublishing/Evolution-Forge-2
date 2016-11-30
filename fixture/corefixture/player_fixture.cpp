#include <iostream>
#include <time.h>

#pragma warning(push, 0)  
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include "player_fixture.hpp"

Player_Fixture::Player_Fixture():
	test_player_name("my_player_Name"), 
	test_government_name("Playersgovernment"), 
	test_goalEntryFixture(),	
	seed(time(0))
{ 
	boost::mt19937 generator(static_cast<boost::uint32_t>(seed));
	boost::uniform_int<> distribution(1, 100);
	boost::variate_generator<boost::mt19937&, boost::uniform_int<> > rnd(generator,  distribution); 
	std::cout << "Setting up player fixture (seed " << seed << ")" << std::endl;

	test_player = new Player(test_player_name, Government(test_government_name), test_goalEntryFixture.test_goalentry);
}

Player_Fixture::~Player_Fixture() 
{ 
	delete test_player;

	Player::resetCounter();
	GoalEntry::resetCounter();
}
