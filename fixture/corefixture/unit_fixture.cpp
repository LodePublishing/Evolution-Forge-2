#include <iostream>
#include <time.h>

#pragma warning(push, 0)  
#include <boost/assign/list_of.hpp>
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include "unit_fixture.hpp"

Unit_Fixture::Unit_Fixture():
	unitTypeFixture(), 
	playerFixture(), 
	mapFixture(),
	seed(time(0))
{	
	boost::mt19937 generator(static_cast<boost::uint32_t>(seed));
	boost::uniform_int<> distribution(1, 100);
	boost::variate_generator<boost::mt19937&, boost::uniform_int<> > rnd(generator,  distribution); 
	std::cout << "Setting up unit fixture (seed " << seed << ")" << std::endl;

	test_construction_time = rnd();
	// TODO UnitResourceType

	test_goalEntry = new GoalEntry(playerFixture.test_goalEntryFixture.test_goalentry_name, playerFixture.test_goalEntryFixture.test_goalentry_goallist);
	test_player = new Player(playerFixture.test_player_name, Government(playerFixture.test_government_name), test_goalEntry);
	
	unitType1 = new UnitType(unitTypeFixture.test_unitName1, unitTypeFixture.raceFixture.test_race, 300, unitTypeFixture.test_maxcount, true, unitTypeFixture.test_unitMovementType, 1,
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, boost::assign::list_of(boost::assign::list_of(1)), 1))
		(UnitResourceType(NEED_GLOBAL_SUPPLY_RESOURCE, boost::assign::list_of(boost::assign::list_of(2)), 1))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, boost::assign::list_of(boost::assign::list_of(3)), 50))

		(UnitResourceType(GATHERER_RESOURCES, boost::assign::list_of(boost::assign::list_of(5)(4)(1)), 1)));

	unitType2 = new UnitType(unitTypeFixture.test_unitName2, unitTypeFixture.raceFixture.test_race, 1800, unitTypeFixture.test_maxcount, true, FLYING_MOVEMENT_TYPE, 2,
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, boost::assign::list_of(boost::assign::list_of(0)), 1))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, boost::assign::list_of(boost::assign::list_of(3)), 400))
		(UnitResourceType(PRODUCE_SUPPLY_RESOURCE, boost::assign::list_of(boost::assign::list_of(6)), 10))

		(UnitResourceType(ACCEPTER_RESOURCES, boost::assign::list_of(boost::assign::list_of(3)(4)(1)), 1)));
}

Unit_Fixture::~Unit_Fixture() 
{
	delete test_goalEntry;
	delete test_player;

	delete unitType1;
	delete unitType2;

	Player::resetCounter();
	GoalEntry::resetCounter();
	Race::resetCounter();
	Unit::resetCounter();
	UnitType::resetCounter();
}