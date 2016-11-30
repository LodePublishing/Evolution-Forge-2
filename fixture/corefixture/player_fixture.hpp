#ifndef _COREFIXTURE_PLAYERFIXTURE_HPP
#define _COREFIXTURE_PLAYERFIXTURE_HPP

#include <string>

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <player.hpp>

#include "government_fixture.hpp"

struct Player_Fixture
{
	Government_Fixture governmentFixture;

	const std::string test_player_name;
	const boost::shared_ptr<const Units> test_startingUnits;
	const boost::shared_ptr<const Player> test_player;

	Player_Fixture();
	virtual ~Player_Fixture();
};

#endif // _COREFIXTURE_PLAYERFIXTURE_HPP
