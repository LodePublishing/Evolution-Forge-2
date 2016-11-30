#pragma warning(push, 0)  
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <processedgoalentry_fixture.hpp>

// TODO aufteilen
BOOST_FIXTURE_TEST_SUITE( ProcessedGoalEntry_test, ProcessedGoalEntry_Fixture )

	BOOST_AUTO_TEST_CASE (ProcessedGoalEntry_constructor)
{
	BOOST_CHECK_EQUAL(test_processedGoalEntry->getGoalList().front().front().front().getUnitTypeId(), broodwar.unit_id_map.find(Broodwar::SPACE_MARINE)->second);

	const std::list<boost::uuids::uuid> testUnitList = test_processedGoalEntry->getBuildableUnits(mapFixture.test_map->getLocationId(0));
	std::list<boost::uuids::uuid> unitList;
	unitList.push_back(broodwar.unit_id_map.find(Broodwar::SCV)->second);
	unitList.push_back(broodwar.unit_id_map.find(Broodwar::SPACE_MARINE)->second);
	unitList.push_back(broodwar.unit_id_map.find(Broodwar::COMMAND_CENTER)->second);
	unitList.push_back(broodwar.unit_id_map.find(Broodwar::SUPPLY_DEPOT)->second);
	unitList.push_back(broodwar.unit_id_map.find(Broodwar::BARRACKS)->second);
	

	std::list<boost::uuids::uuid>::const_iterator j = unitList.begin();
	for(std::list<boost::uuids::uuid>::const_iterator i = testUnitList.begin(); i != testUnitList.end(); i++) {
		BOOST_CHECK_EQUAL(*j, *i);
		j++;
	}
}

	BOOST_AUTO_TEST_CASE (ProcessedGoalEntry_unreachable)
{

	std::list<std::list<Goal> > new_goals_1;
    std::list<Goal> new_goals_2;
	new_goals_2.push_back(Goal(broodwar.unit_id_map.find(Broodwar::GAS_SCV)->second, mapFixture.test_map->getLocationId(0), 1));
    new_goals_1.push_back(new_goals_2);
	test_processedGoalEntry->addGoal(new_goals_1);
	
	bool exception = false;
	try {
		test_processedGoalEntry->fillBuildableListAndAddGoals(broodwar.getRules(), mapFixture.test_map, playerFixture.test_player, test_units);
	} catch(...) {
		exception = true;
	}
	BOOST_CHECK_EQUAL(exception, true);
}

BOOST_AUTO_TEST_SUITE_END( )
