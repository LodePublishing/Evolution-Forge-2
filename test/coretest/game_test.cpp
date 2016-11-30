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
	//BOOST_CHECK_EQUAL(test_game->getPlayer(playerFixture.test_player->getID()).getName(), playerFixture.test_player_name);
	BOOST_CHECK_EQUAL(test_game->getMap()->getName(), mapFixture.test_map_name);
	BOOST_CHECK_EQUAL(test_game->getRules()->getName(), rulesFixture.test_rules_name);
	BOOST_CHECK_EQUAL(test_game->getStartingUnits()->getUnitList().back()->getID(), test_unit3->getID());
	BOOST_CHECK_EQUAL(test_game->getStartingTime(), test_startingTime);
}



BOOST_AUTO_TEST_CASE ( Game_reload_test )
{
	// remove previously written files
	std::remove(test_filename_xml.c_str());
	// save the game
	Game::saveToXML(*test_game, test_filename_xml, test_filename);

	// reload the map
	Game* new_game_xml = new Game();
	Game::loadFromXML(*new_game_xml, test_filename_xml, test_filename);
	std::remove(test_filename_xml.c_str());

	//new_game_xml->initialize(); TODO

	// should be the same as the old one. (except for the pointer values)
//	BOOST_CHECK_EQUAL(new_game_xml->getPlayer(playerFixture.test_player->getID())->getName(), playerFixture.test_player_name);
/*	BOOST_CHECK_EQUAL(new_game_xml->getMap()->getName(), mapFixture.test_map_name); TODO
	BOOST_CHECK_EQUAL(new_game_xml->getRules()->getName(), rulesFixture.test_rules_name);*/
	BOOST_CHECK_EQUAL(new_game_xml->getStartingUnits()->getUnitList().back()->getID(), test_unit3->getID());
	BOOST_CHECK_EQUAL(new_game_xml->getStartingTime(), test_startingTime);
		
	delete new_game_xml;
}


BOOST_AUTO_TEST_SUITE_END( )