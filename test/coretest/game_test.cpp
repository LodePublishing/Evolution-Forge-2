#ifdef WIN32
	#define BOOST_TEST_MODULE CoreTest
#endif

#pragma warning(push, 0) 
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <game_fixture.hpp>


BOOST_FIXTURE_TEST_SUITE( Gametest, Game_Fixture )

	BOOST_AUTO_TEST_CASE (Game_constructor)
{
	BOOST_CHECK_EQUAL(test_game->getPlayer(playerFixture.test_player->getId())->getId(), playerFixture.test_player->getId());
	BOOST_CHECK_EQUAL(test_game->getPlayer(playerFixture.test_player->getId())->getName(), playerFixture.test_player_name);
	BOOST_CHECK_EQUAL(test_game->getPlayer(playerFixture.test_player->getId())->getGoalEntry()->getName(), playerFixture.test_player->getGoalEntry()->getName());
	BOOST_CHECK_EQUAL(test_game->getMap()->getName(), mapFixture.test_map_name);
	BOOST_CHECK_EQUAL(test_game->getRules()->getName(), rulesFixture.test_rules_name);
	BOOST_CHECK_EQUAL(test_game->getStartingTime(), test_startingTime);
}



BOOST_AUTO_TEST_CASE ( Game_reload_test )
{
	// remove previously written files
	std::remove(test_filename_xml.c_str());
	// save the game
	Game::saveToXML(test_game.get(), test_filename_xml, test_filename);

	// reload the map
	Game* new_game_xml2 = NULL;
	Game::loadFromXML(new_game_xml2, test_filename_xml, test_filename);
	const boost::shared_ptr<Game> new_game_xml(new_game_xml2);
	//std::remove(test_filename_xml.c_str());

	// should be the same as the old one. (except for the pointer values)
	BOOST_CHECK_EQUAL(new_game_xml->getPlayer(playerFixture.test_player->getId())->getId(), playerFixture.test_player->getId());
	BOOST_CHECK_EQUAL(new_game_xml->getPlayer(playerFixture.test_player->getId())->getName(), playerFixture.test_player->getName());
	BOOST_CHECK_EQUAL(new_game_xml->getPlayer(playerFixture.test_player->getId())->getGoalEntry()->getName(), playerFixture.test_player->getGoalEntry()->getName());
	BOOST_CHECK_EQUAL(new_game_xml->getMap()->getName(), mapFixture.test_map_name);
	BOOST_CHECK_EQUAL(new_game_xml->getRules()->getName(), rulesFixture.test_rules_name);
	BOOST_CHECK_EQUAL(new_game_xml->getStartingTime(), test_startingTime);
}


BOOST_AUTO_TEST_SUITE_END( )
