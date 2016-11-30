#ifndef _COREFIXTURE_GAMEFIXTURE_HPP
#define _COREFIXTURE_GAMEFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <game.hpp>

#include <random_fixture.hpp>

#include "units_fixture.hpp"
#include "rules_fixture.hpp"
#include "map_fixture.hpp"
#include "player_fixture.hpp"


struct Game_Fixture : public Random_Fixture
{
	Game_Fixture();
	~Game_Fixture();

	const Units_Fixture unitsFixture;
	const Rules_Fixture rulesFixture;
	const Map_Fixture mapFixture;
	const Player_Fixture playerFixture;

	unsigned int test_startingTime;

	const boost::shared_ptr<Units> test_units;
	const boost::shared_ptr<Unit> test_unit1;
	const boost::shared_ptr<Unit> test_unit2;
	const boost::shared_ptr<Unit> test_unit3;
	
	boost::shared_ptr<Game> test_game;

	const std::string test_filename_xml;
	const std::string test_filename;
};

#endif // _COREFIXTURE_GAMEFIXTURE_HPP
