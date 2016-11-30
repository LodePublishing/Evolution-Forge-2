#pragma warning(push, 0) 
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <goal_fixture.hpp>


BOOST_FIXTURE_TEST_SUITE( Goal_test, Goal_Fixture )

	BOOST_AUTO_TEST_CASE (Goal_constructor)
	{
		BOOST_CHECK_EQUAL(test_goal->getUnitTypeId(), test_unitTypeId);
		BOOST_CHECK_EQUAL(test_goal->getLocationId(), test_locationId);
		BOOST_CHECK_EQUAL(test_goal->getCount(), test_count);
		BOOST_CHECK_EQUAL(test_goal->getTime(), test_time);
	}

	BOOST_AUTO_TEST_CASE (Goal_assignment)
	{
		Goal new_test_goal2 = *test_goal;
		Goal new_test_goal = new_test_goal2;

		BOOST_CHECK_EQUAL(new_test_goal.getUnitTypeId(), test_unitTypeId);
		BOOST_CHECK_EQUAL(new_test_goal.getLocationId(), test_locationId);
		BOOST_CHECK_EQUAL(new_test_goal.getCount(), test_count);
		BOOST_CHECK_EQUAL(new_test_goal.getTime(), test_time);
	}

	BOOST_AUTO_TEST_CASE (Goal_constructor_bonus)
	{
	// 0 count should be ok (bonus!), also test default time
		Goal* test_goal2 = new Goal(test_unitTypeId, test_locationId, 0);

		BOOST_CHECK_EQUAL(test_goal2->getUnitTypeId(), test_unitTypeId);
		BOOST_CHECK_EQUAL(test_goal2->getLocationId(), test_locationId);
		BOOST_CHECK_EQUAL(test_goal2->getCount(), 0);
		BOOST_CHECK_EQUAL(test_goal2->getTime(), Goal::GOAL_MAX_TIME);

		delete test_goal2;
	}



BOOST_AUTO_TEST_SUITE_END( )
