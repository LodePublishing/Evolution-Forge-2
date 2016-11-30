#ifndef _COREFIXTURE_PLAYERFIXTURE_HPP
#define _COREFIXTURE_PLAYERFIXTURE_HPP

#include <string>

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <player.hpp>

struct Player_Fixture
{
	const std::string test_player_name;
	const boost::shared_ptr<const Units> test_startingUnits;
	const boost::shared_ptr<const Player> test_player;

	Player_Fixture();
	~Player_Fixture();
};

#endif // _COREFIXTURE_PLAYERFIXTURE_HPP
