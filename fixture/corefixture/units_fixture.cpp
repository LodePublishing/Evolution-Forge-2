#include <iostream>
#include <time.h>

#pragma warning(push, 0)  
#include <boost/assign/list_of.hpp>
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include "units_fixture.hpp"

Units_Fixture::Units_Fixture():	
	unitTypeFixture(), 
	unitFixture(),
	playerFixture(), 
	mapFixture(),
	seed(time(0))
{
	boost::mt19937 generator(static_cast<boost::uint32_t>(seed));
	boost::uniform_int<> distribution(1, 100);
	boost::variate_generator<boost::mt19937&, boost::uniform_int<> > rnd(generator,  distribution); 
	std::cout << "Setting up units fixture (seed " << seed << ")" << std::endl;

	test_construction_time = rnd(); // TODO UnitType

	test_goalEntry = new GoalEntry(playerFixture.test_goalEntryFixture.test_goalentry_name, playerFixture.test_goalEntryFixture.test_goalentry_goallist);
	test_player = new Player(playerFixture.test_player_name, Government(playerFixture.test_government_name), test_goalEntry);

	test_unit1 = new Unit(unitFixture.unitType1,  test_player, mapFixture.locations[0]);
	test_unit2 = new Unit(unitFixture.unitType1,  test_player, mapFixture.locations[0]);
	test_unit3 = new Unit(unitFixture.unitType2,  test_player, mapFixture.locations[0]);
}

Units_Fixture::~Units_Fixture() 
{
	delete test_goalEntry;
	delete test_player;

	GoalEntry::resetCounter();
	Race::resetCounter();
	Player::resetCounter();
}