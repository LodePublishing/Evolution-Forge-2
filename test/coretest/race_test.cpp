#pragma warning(push, 0) 
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <race_fixture.hpp>

BOOST_FIXTURE_TEST_SUITE( Race_test, Race_Fixture )

	BOOST_AUTO_TEST_CASE (Race_constructor )
	{
		BOOST_CHECK_EQUAL(test_race->getName(), test_race_name);
	}


BOOST_AUTO_TEST_SUITE_END( )
