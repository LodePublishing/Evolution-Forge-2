#ifndef _COREFIXTURE_GAMEFIXTURE_HPP
#define _COREFIXTURE_GAMEFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <game.hpp>
#include <broodwar.hpp>

#include "player_fixture.hpp"
#include "map_fixture.hpp"
#include "units_fixture.hpp"

struct Game_Fixture
{
	const Player_Fixture playerFixture;
	const Map_Fixture mapFixture;
	const Units_Fixture unitsFixture;
	const Broodwar broodwar;

	const unsigned int test_startingTime;
	
	const boost::shared_ptr<Game> test_game;

	const std::string test_filename_xml;
	const std::string test_filename;

	Game_Fixture();
	virtual ~Game_Fixture();
};

#endif // _COREFIXTURE_GAMEFIXTURE_HPP
