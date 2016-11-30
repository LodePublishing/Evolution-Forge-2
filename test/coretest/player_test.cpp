#pragma warning(push, 0) 
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <player_fixture.hpp>

BOOST_FIXTURE_TEST_SUITE( Player_test, Player_Fixture )

	BOOST_AUTO_TEST_CASE (Player_constructor)
{
	BOOST_CHECK_EQUAL(test_player->getName(), test_player_name);
	BOOST_CHECK_EQUAL(test_player->getGovernment()->getName(), test_government_name);
	BOOST_CHECK_EQUAL(test_player->getGoalEntry()->getName(), test_goalEntryFixture.test_goalentry_name);
}


BOOST_AUTO_TEST_SUITE_END( )
