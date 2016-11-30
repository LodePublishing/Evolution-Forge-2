#ifdef WIN32
	#define BOOST_TEST_MODULE GoalTest
#endif

#pragma warning(push, 0)  
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <processedgoal_fixture.hpp>

BOOST_FIXTURE_TEST_SUITE( ProcessedGoal_test, ProcessedGoal_Fixture )

	BOOST_AUTO_TEST_CASE (ProcessedGoal_constructor)
	{
		BOOST_CHECK_EQUAL(test_processedgoal->isHaveable(), test_isHaveable);
		BOOST_CHECK_EQUAL(test_processedgoal->isBuildable(), test_isBuildable);
		BOOST_CHECK_EQUAL(test_processedgoal->isBuildableAtStart(), test_isBuildableAtStart);

	}

BOOST_AUTO_TEST_SUITE_END( )
