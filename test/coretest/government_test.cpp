#pragma warning(push, 0) 
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <government_fixture.hpp>

BOOST_FIXTURE_TEST_SUITE( Government_test, Government_Fixture )

	BOOST_AUTO_TEST_CASE (Government_constructor)
	{
		BOOST_CHECK_EQUAL(test_government->getName(), test_government_name);
	}

BOOST_AUTO_TEST_SUITE_END( )
