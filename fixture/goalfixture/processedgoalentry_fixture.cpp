#include <iostream>
#include <time.h>

#pragma warning(push, 0)  
#include <boost/assign/list_of.hpp>
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include "processedgoalentry_fixture.hpp"

ProcessedGoalEntry_Fixture::ProcessedGoalEntry_Fixture():
	goalEntry_Fixture(),
	player_Fixture(),
	map_Fixture(),
	broodwar(new Broodwar()),
	seed(time(0))
{	
	boost::mt19937 generator(static_cast<boost::uint32_t>(seed));
	boost::uniform_int<> distribution(1, 100);
	boost::variate_generator<boost::mt19937&, boost::uniform_int<> > rnd(generator,  distribution); 
	std::cout << "Setting up processed goal entry fixture (seed " << seed << ")" << std::endl;

	//test goal entry , start units anpassen!

//	mapFixture.test_units

	test_processedGoalEntry = new ProcessedGoalEntry(goalEntry_Fixture.test_goalentry, player_Fixture.test_player, *map_Fixture.test_map, *map_Fixture.test_units, broodwar->getRules());
}

ProcessedGoalEntry_Fixture::~ProcessedGoalEntry_Fixture() 
{
	delete test_processedGoalEntry;
	delete broodwar;
}