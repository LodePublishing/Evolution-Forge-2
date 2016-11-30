#ifndef _CORETEST_PLAYERFIXTURE_HPP
#define _CORETEST_PLAYERFIXTURE_HPP

#include <string>

#include <player.hpp>
#include "goalentry_fixture.hpp"

struct Player_Fixture
{
	Player_Fixture();
	~Player_Fixture();

	const std::string test_player_name;
	const std::string test_government_name;
	const GoalEntry_Fixture test_goalEntryFixture;

	Player* test_player;

	time_t seed;
};

#endif // _CORETEST_PLAYERFIXTURE_HPP
