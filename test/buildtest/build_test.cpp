#ifndef WIN32
#define BOOST_TEST_DYN_LINK
#endif
#define BOOST_TEST_MODULE Build
#pragma warning(push, 0) 
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <buildfixture/build_fixture.hpp>

BOOST_FIXTURE_TEST_SUITE( Build_test, Build_Fixture )

	BOOST_AUTO_TEST_CASE (Build_constructor)
	{
		BOOST_CHECK(true);
	}

BOOST_AUTO_TEST_SUITE_END( )

