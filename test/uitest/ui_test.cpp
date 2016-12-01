#ifndef WIN32
#define BOOST_TEST_DYN_LINK
#endif
#define BOOST_TEST_MODULE UI
#pragma warning(push, 0) 
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <uifixture/ui_fixture.hpp>

BOOST_FIXTURE_TEST_SUITE( UI_test, UI_Fixture )

	BOOST_AUTO_TEST_CASE (UI_constructor)
	{
		BOOST_CHECK(true);
	}

BOOST_AUTO_TEST_SUITE_END( )

