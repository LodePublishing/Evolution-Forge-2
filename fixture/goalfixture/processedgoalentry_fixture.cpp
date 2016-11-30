#include <iostream>
#include <time.h>

#pragma warning(push, 0)  
#include <boost/assign/list_of.hpp>
#pragma warning(pop)

#include "processedgoalentry_fixture.hpp"

ProcessedGoalEntry_Fixture::ProcessedGoalEntry_Fixture():
	playerFixture(),
	mapFixture(),
	broodwar(),

	test_units(new Units()),
	test_unit1(new Unit(playerFixture.test_player, broodwar.getRules()->getUnitType(broodwar.unit_id_map.find(Broodwar::SCV)->second), mapFixture.test_map->getLocationByIndex(0), test_units)),
	test_unit2(new Unit(playerFixture.test_player, broodwar.getRules()->getUnitType(broodwar.unit_id_map.find(Broodwar::COMMAND_CENTER)->second), mapFixture.test_map->getLocationByIndex(0), test_units)),
	test_unit3(new Unit(playerFixture.test_player, broodwar.getRules()->getUnitType(broodwar.unit_id_map.find(Broodwar::TERRAN_SUPPLY)->second), mapFixture.test_map->getLocationByIndex(0), test_units, 10)), // TODO required? or do it via addUnit?
	test_unit4(new Unit(playerFixture.test_player, broodwar.getRules()->getUnitType(broodwar.unit_id_map.find(Broodwar::MINERAL_PATCH)->second), mapFixture.test_map->getLocationByIndex(0), test_units)),
	
	test_goalentry_name("my_goalentry_Name"),
	test_goalentry_goallist(init_goallist_helper()),
	test_goalentry(boost::shared_ptr<const GoalEntry>(new GoalEntry(test_goalentry_name, test_goalentry_goallist)))
{	
	// need to be in the body for now... test_unitX need an initialized test_units object!
	test_units->addUnit(test_unit1);
	test_units->addUnit(test_unit2);
	test_units->addUnit(test_unit3);
	test_units->addUnit(test_unit4);

	test_processedGoalEntry = boost::shared_ptr<ProcessedGoalEntry>(new ProcessedGoalEntry( test_goalentry, playerFixture.test_player, mapFixture.test_map, test_units, broodwar.getRules()));
}

ProcessedGoalEntry_Fixture::~ProcessedGoalEntry_Fixture() 
{
}

const std::list<std::list<std::list<Goal> > > ProcessedGoalEntry_Fixture::init_goallist_helper() {
	const std::list<std::list<std::list<Goal> > > goalList = boost::assign::list_of
		(boost::assign::list_of(boost::assign::list_of(Goal(broodwar.unit_id_map.find(Broodwar::SPACE_MARINE)->second, mapFixture.test_map->getLocationId(0), 1))))
		(boost::assign::list_of(boost::assign::list_of(Goal(broodwar.unit_id_map.find(Broodwar::SUPPLY_DEPOT)->second, mapFixture.test_map->getLocationId(0), 1))));
	return goalList;
}