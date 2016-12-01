#ifndef WIN32
#define BOOST_TEST_DYN_LINK
#endif
#define BOOST_TEST_MODULE AI
#pragma warning(push, 0) 
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <aifixture/ai_fixture.hpp>

BOOST_FIXTURE_TEST_SUITE( AI_test, AI_Fixture )

	BOOST_AUTO_TEST_CASE (AI_constructor)
	{
		BOOST_CHECK(true);
	}

BOOST_AUTO_TEST_SUITE_END( )

