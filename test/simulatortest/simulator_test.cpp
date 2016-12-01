#ifndef WIN32
#define BOOST_TEST_DYN_LINK
#endif
#define BOOST_TEST_MODULE Simulator
#pragma warning(push, 0) 
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <simulatorfixture/simulator_fixture.hpp>

BOOST_FIXTURE_TEST_SUITE( Simulator_test, Simulator_Fixture )

	BOOST_AUTO_TEST_CASE (Simulator_constructor)
	{
		BOOST_CHECK(true);
	}

BOOST_AUTO_TEST_SUITE_END( )

