#pragma warning(push, 0) 
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <goal_fixture.hpp>


BOOST_FIXTURE_TEST_SUITE( Goal_test, Goal_Fixture )

	BOOST_AUTO_TEST_CASE (Goal_constructor)
	{
		BOOST_CHECK_EQUAL(test_goal->getUnitTypeID(), test_unitTypeID);
		BOOST_CHECK_EQUAL(test_goal->getLocationID(), test_locationID);
		BOOST_CHECK_EQUAL(test_goal->getCount(), test_count);
		BOOST_CHECK_EQUAL(test_goal->getTime(), test_time);
	}

	BOOST_AUTO_TEST_CASE (Goal_assignment)
	{
		Goal new_test_goal = *test_goal;

		BOOST_CHECK_EQUAL(new_test_goal.getUnitTypeID(), test_unitTypeID);
		BOOST_CHECK_EQUAL(new_test_goal.getLocationID(), test_locationID);
		BOOST_CHECK_EQUAL(new_test_goal.getCount(), test_count);
		BOOST_CHECK_EQUAL(new_test_goal.getTime(), test_time);
	}


	BOOST_AUTO_TEST_CASE (Goal_constructor_bonus)
	{
	// 0 count should be ok (bonus!), also test default time
		Goal* test_goal2 = new Goal(test_unitTypeID, test_locationID, 0);

		BOOST_CHECK_EQUAL(test_goal2->getUnitTypeID(), test_unitTypeID);
		BOOST_CHECK_EQUAL(test_goal2->getLocationID(), test_locationID);
		BOOST_CHECK_EQUAL(test_goal2->getCount(), 0);
		BOOST_CHECK_EQUAL(test_goal2->getTime(), Goal::GOAL_MAX_TIME);

		delete test_goal2;
	}


BOOST_AUTO_TEST_SUITE_END( )
