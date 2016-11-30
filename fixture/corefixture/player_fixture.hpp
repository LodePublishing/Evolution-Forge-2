#ifndef _COREFIXTURE_PLAYERFIXTURE_HPP
#define _COREFIXTURE_PLAYERFIXTURE_HPP

#include <string>

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <player.hpp>

#include <random_fixture.hpp>

#include "goalentry_fixture.hpp"
#include "government_fixture.hpp"


struct Player_Fixture : public Random_Fixture
{
	Player_Fixture();
	~Player_Fixture();

	const std::string test_player_name;
	const Government_Fixture test_governmentFixture;
	const GoalEntry_Fixture test_goalEntryFixture;
	const boost::shared_ptr<const Units> test_startingUnits;

	boost::shared_ptr<const Player> test_player;
};

#endif // _COREFIXTURE_PLAYERFIXTURE_HPP
