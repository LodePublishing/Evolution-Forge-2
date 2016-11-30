#pragma warning(push, 0)  
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <processedgoalentry_fixture.hpp>

// TODO aufteilen
BOOST_FIXTURE_TEST_SUITE( ProcessedGoalEntry_test, ProcessedGoalEntry_Fixture )

	BOOST_AUTO_TEST_CASE (ProcessedGoalEntry_constructor)
{
	BOOST_CHECK_EQUAL(test_processedGoalEntry->getGoalList().front().front().front().getUnitTypeId(), Broodwar::SPACE_MARINE);

	const std::list<unsigned int> testUnitList = test_processedGoalEntry->getBuildableUnits(0);
	std::list<unsigned int> unitList;
	unitList.push_back(Broodwar::SCV);
	unitList.push_back(Broodwar::COMMAND_CENTER);
	unitList.push_back(Broodwar::SUPPLY_DEPOT);
	unitList.push_back(Broodwar::BARRACKS);
	unitList.push_back(Broodwar::SPACE_MARINE);

	std::list<unsigned int>::const_iterator j = unitList.begin();
	for(std::list<unsigned int>::const_iterator i = testUnitList.begin(); i != testUnitList.end(); i++) {
		BOOST_CHECK_EQUAL(*j, *i);
		j++;
	}
}

	BOOST_AUTO_TEST_CASE (ProcessedGoalEntry_unreachable)
{

	std::list<std::list<Goal> > new_goals_1;
    std::list<Goal> new_goals_2;
    new_goals_2.push_back(Goal(Broodwar::GAS_SCV, 0, 1));
    new_goals_1.push_back(new_goals_2);
	test_processedGoalEntry->addGoal(new_goals_1);
	
	bool exception = false;
	try {
		test_processedGoalEntry->fillBuildableListAndAddGoals(broodwar->getRules(), mapFixture.test_map, playerFixture.test_player, test_units);
	} catch(...) {
		exception = true;
	}
	BOOST_CHECK_EQUAL(exception, true);
}

BOOST_AUTO_TEST_SUITE_END( )
