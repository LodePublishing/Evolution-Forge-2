#include <iostream>
#include <time.h>

#pragma warning(push, 0)  
#include <boost/assign/list_of.hpp>
#pragma warning(pop)

#include "processedgoalentry_fixture.hpp"

ProcessedGoalEntry_Fixture::ProcessedGoalEntry_Fixture():
	Random_Fixture(),	
	playerFixture(),
	mapFixture(),
	broodwar(new Broodwar()),

	test_units(new Units()),
	test_unit1(new Unit(playerFixture.test_player, broodwar->getRules()->getUnitType(Broodwar::SCV), mapFixture.test_map->getLocationAt(1), test_units)),
	test_unit2(new Unit(playerFixture.test_player, broodwar->getRules()->getUnitType(Broodwar::COMMAND_CENTER), mapFixture.test_map->getLocationAt(1), test_units)),
	test_unit3(new Unit(playerFixture.test_player, broodwar->getRules()->getUnitType(Broodwar::TERRAN_SUPPLY), mapFixture.test_map->getLocationAt(1), test_units, 10)), // TODO required? or do it via addUnit?
	test_unit4(new Unit(playerFixture.test_player, broodwar->getRules()->getUnitType(Broodwar::MINERAL_PATCH), mapFixture.test_map->getLocationAt(1), test_units)),
	
	test_goalentry_name("my_goalentry_Name"),
	test_goalentry_goallist(init_goallist_helper()),
	test_goalentry(boost::shared_ptr<const GoalEntry>(new GoalEntry(test_goalentry_name, test_goalentry_goallist)))
{	
	// need to be in the body for now... test_unitX need an initialized test_units object!
	test_units->addUnit(test_unit1);
	test_units->addUnit(test_unit2);
	test_units->addUnit(test_unit3);
	test_units->addUnit(test_unit4);

	test_processedGoalEntry = new ProcessedGoalEntry( test_goalentry, playerFixture.test_player, mapFixture.test_map, test_units, broodwar->getRules());
}

ProcessedGoalEntry_Fixture::~ProcessedGoalEntry_Fixture() 
{
	delete test_processedGoalEntry;
}

const std::list<std::list<std::list<Goal> > >ProcessedGoalEntry_Fixture::init_goallist_helper() {
	const std::list<std::list<std::list<Goal> > > goalList = boost::assign::list_of
		(boost::assign::list_of(boost::assign::list_of(Goal(Broodwar::SPACE_MARINE, 0, 1))))
		(boost::assign::list_of(boost::assign::list_of(Goal(Broodwar::SUPPLY_DEPOT, 0, 1))));
	return goalList;
}