#ifndef _CORETEST_GAMEFIXTURE_HPP
#define _CORETEST_GAMEFIXTURE_HPP

#include <game.hpp>

#include "units_fixture.hpp"
#include "rules_fixture.hpp"
#include "map_fixture.hpp"
#include "player_fixture.hpp"

struct Game_Fixture
{
	Game_Fixture();
	~Game_Fixture();

	const Units_Fixture unitsFixture;
	const Rules_Fixture rulesFixture;
	const Map_Fixture mapFixture;
	const Player_Fixture playerFixture;

	unsigned int test_startingTime;

	Units* test_units;

	Unit* test_unit1;
	Unit* test_unit2;
	Unit* test_unit3;
	
	Game* test_game;

	const std::string test_filename_xml;
	const std::string test_filename;

	time_t seed;
};

#endif // _CORETEST_GAMEFIXTURE_HPP
