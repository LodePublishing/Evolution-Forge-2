#pragma warning(push, 0) 
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <goalentry_fixture.hpp>

BOOST_FIXTURE_TEST_SUITE( GoalEntry_test, GoalEntry_Fixture )
	BOOST_AUTO_TEST_CASE (GoalEntry_constructor)
{	
	BOOST_CHECK_EQUAL(test_goalentry->getName(), test_goalentry_name);
	
	const Goal& goal1 = test_goalentry->getGoalList().front().front().front();
	const Goal& goal2 = test_goalentry->getGoalList().front().front().back();
	const Goal& goal3 = test_goalentry->getGoalList().front().back().front();
	const Goal& goal4 = test_goalentry->getGoalList().back().front().front();
	const Goal& goal5 = test_goalentry->getGoalList().back().front().back();

	const Goal& test_goal1 = test_goalentry_goallist.front().front().front();
	const Goal& test_goal2 = test_goalentry_goallist.front().front().back();
	const Goal& test_goal3 = test_goalentry_goallist.front().back().front();
	const Goal& test_goal4 = test_goalentry_goallist.back().front().front();
	const Goal& test_goal5 = test_goalentry_goallist.back().front().back();
	
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
