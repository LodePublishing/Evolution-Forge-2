#ifndef WIN32
#define BOOST_TEST_DYN_LINK
#endif
#define BOOST_TEST_MODULE Goal

#pragma warning(push, 0) 
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <goalfixture/goalitem_fixture.hpp>
#include <goalfixture/processedgoalentry_fixture.hpp>
#include <goalfixture/processedgoal_fixture.hpp>
#include <goalfixture/goalentry_fixture.hpp>
#include <games/enums/broodwarunits.hpp>


BOOST_FIXTURE_TEST_SUITE( GoalItem_test, GoalItem_Fixture )

	BOOST_AUTO_TEST_CASE (GoalItem_constructor)
	{
		BOOST_CHECK_EQUAL(test_goalitem->getUnitTypeId(), test_unitTypeId);
		BOOST_CHECK_EQUAL(test_goalitem->getLocationId(), test_locationId);
		BOOST_CHECK_EQUAL(test_goalitem->getCount(), test_count);
		BOOST_CHECK_EQUAL(test_goalitem->getTime(), test_time);
	}

	BOOST_AUTO_TEST_CASE (GoalItem_assignment)
	{
		GoalItem new_test_goalitem2 = *test_goalitem;
		GoalItem new_test_goalitem = new_test_goalitem2;

		BOOST_CHECK_EQUAL(new_test_goalitem.getUnitTypeId(), test_unitTypeId);
		BOOST_CHECK_EQUAL(new_test_goalitem.getLocationId(), test_locationId);
		BOOST_CHECK_EQUAL(new_test_goalitem.getCount(), test_count);
		BOOST_CHECK_EQUAL(new_test_goalitem.getTime(), test_time);
	}

	BOOST_AUTO_TEST_CASE (GoalItem_constructor_bonus)
	{
	// 0 count should be ok (bonus!), also test default time
		GoalItem* test_goalitem2 = new GoalItem(test_unitTypeId, test_locationId, 0);

		BOOST_CHECK_EQUAL(test_goalitem2->getUnitTypeId(), test_unitTypeId);
		BOOST_CHECK_EQUAL(test_goalitem2->getLocationId(), test_locationId);
		BOOST_CHECK_EQUAL(test_goalitem2->getCount(), 0);
		BOOST_CHECK_EQUAL(test_goalitem2->getTime(), GoalItem::GOAL_MAX_TIME);

		delete test_goalitem2;
	}



BOOST_AUTO_TEST_SUITE_END( )




BOOST_FIXTURE_TEST_SUITE( GoalEntry_test, GoalEntry_Fixture )
	BOOST_AUTO_TEST_CASE (GoalEntry_constructor)
{	
	BOOST_CHECK_EQUAL(test_goalentry->getName(), test_goalentry_name);
	
	const GoalItem& goal1 = test_goalentry->getGoalItemList().front().front().front();
	const GoalItem& goal2 = test_goalentry->getGoalItemList().front().front().back();
	const GoalItem& goal3 = test_goalentry->getGoalItemList().front().back().front();
	const GoalItem& goal4 = test_goalentry->getGoalItemList().back().front().front();
	const GoalItem& goal5 = test_goalentry->getGoalItemList().back().front().back();

	const GoalItem& test_goal1 = test_goalentry_goalitemlist.front().front().front();
	const GoalItem& test_goal2 = test_goalentry_goalitemlist.front().front().back();
	const GoalItem& test_goal3 = test_goalentry_goalitemlist.front().back().front();
	const GoalItem& test_goal4 = test_goalentry_goalitemlist.back().front().front();
	const GoalItem& test_goal5 = test_goalentry_goalitemlist.back().front().back();
	
	BOOST_CHECK_EQUAL(goal1.getUnitTypeId(), test_goal1.getUnitTypeId());
	BOOST_CHECK_EQUAL(goal1.getLocationId(), test_goal1.getLocationId());
	BOOST_CHECK_EQUAL(goal1.getCount(), test_goal1.getCount());
	BOOST_CHECK_EQUAL(goal1.getTime(), test_goal1.getTime());

	BOOST_CHECK_EQUAL(goal2.getUnitTypeId(), test_goal2.getUnitTypeId());
	BOOST_CHECK_EQUAL(goal2.getLocationId(), test_goal2.getLocationId());
	BOOST_CHECK_EQUAL(goal2.getCount(), test_goal2.getCount());
	BOOST_CHECK_EQUAL(goal2.getTime(), test_goal2.getTime());

	BOOST_CHECK_EQUAL(goal3.getUnitTypeId(), test_goal3.getUnitTypeId());
	BOOST_CHECK_EQUAL(goal3.getLocationId(), test_goal3.getLocationId());
	BOOST_CHECK_EQUAL(goal3.getCount(), test_goal3.getCount());
	BOOST_CHECK_EQUAL(goal3.getTime(), test_goal3.getTime());

	BOOST_CHECK_EQUAL(goal4.getUnitTypeId(), test_goal4.getUnitTypeId());
	BOOST_CHECK_EQUAL(goal4.getLocationId(), test_goal4.getLocationId());
	BOOST_CHECK_EQUAL(goal4.getCount(), test_goal4.getCount());
	BOOST_CHECK_EQUAL(goal4.getTime(), test_goal4.getTime());

	BOOST_CHECK_EQUAL(goal5.getUnitTypeId(), test_goal5.getUnitTypeId());
	BOOST_CHECK_EQUAL(goal5.getLocationId(), test_goal5.getLocationId());
	BOOST_CHECK_EQUAL(goal5.getCount(), test_goal5.getCount());
	BOOST_CHECK_EQUAL(goal5.getTime(), test_goal5.getTime());
}


BOOST_AUTO_TEST_SUITE_END( )




BOOST_FIXTURE_TEST_SUITE( ProcessedGoal_test, ProcessedGoal_Fixture )

	BOOST_AUTO_TEST_CASE (ProcessedGoal_constructor)
	{
		BOOST_CHECK_EQUAL(test_processedgoal->isHaveable(), test_isHaveable);
		BOOST_CHECK_EQUAL(test_processedgoal->isBuildable(), test_isBuildable);
		BOOST_CHECK_EQUAL(test_processedgoal->wasChecked(), false);

		ProcessedGoal test_processedgoal_empty;
		BOOST_CHECK_EQUAL(test_processedgoal_empty.isHaveable(), false);
		BOOST_CHECK_EQUAL(test_processedgoal_empty.isBuildable(), false);
		BOOST_CHECK_EQUAL(test_processedgoal_empty.wasChecked(), false);
	}

BOOST_AUTO_TEST_SUITE_END( )



// TODO aufteilen
BOOST_FIXTURE_TEST_SUITE( ProcessedGoalEntry_test, ProcessedGoalEntry_Fixture )

	BOOST_AUTO_TEST_CASE (ProcessedGoalEntry_constructor)
{
	BOOST_CHECK_EQUAL(test_processedGoalEntry->getGoalList().front().front().front().getUnitTypeId(), broodwar.unit_id_map.find(SPACE_MARINE)->second);

	const std::list<boost::uuids::uuid> testUnitList = test_processedGoalEntry->getBuildableUnits(mapFixture.test_map->getLocationId(0));
	std::list<boost::uuids::uuid> unitList;
	unitList.push_back(broodwar.unit_id_map.find(SCV)->second);
	unitList.push_back(broodwar.unit_id_map.find(SPACE_MARINE)->second);
	unitList.push_back(broodwar.unit_id_map.find(COMMAND_CENTER)->second);
	unitList.push_back(broodwar.unit_id_map.find(SUPPLY_DEPOT)->second);
	unitList.push_back(broodwar.unit_id_map.find(BARRACKS)->second);
	

	std::list<boost::uuids::uuid>::const_iterator j = unitList.begin();
	for(std::list<boost::uuids::uuid>::const_iterator i = testUnitList.begin(); i != testUnitList.end(); i++) {
		BOOST_CHECK_EQUAL(*j, *i);
		j++;
	}
}

	BOOST_AUTO_TEST_CASE (ProcessedGoalEntry_unreachable)
{

	std::list<std::list<GoalItem> > new_goals_1;
    std::list<GoalItem> new_goals_2;
	new_goals_2.push_back(GoalItem(broodwar.unit_id_map.find(GAS_SCV)->second, mapFixture.test_map->getLocationId(0), 1));
    new_goals_1.push_back(new_goals_2);
	test_processedGoalEntry->addGoalItem(new_goals_1);
	
	BOOST_CHECK_THROW(test_processedGoalEntry->fillBuildableListAndAddGoals(broodwar.getRules(), mapFixture.test_map, playerFixture.test_player, test_units), std::exception);
}

BOOST_AUTO_TEST_SUITE_END( )
