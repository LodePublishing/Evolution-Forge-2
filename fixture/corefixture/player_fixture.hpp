#ifndef _CORE_FIXTURE_PLAYERFIXTURE_HPP
#define _CORE_FIXTURE_PLAYERFIXTURE_HPP

#include <string>

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <core/player.hpp>

#include "government_fixture.hpp"

struct Player_Fixture
{
	Government_Fixture governmentFixture;

	const std::string test_player_name;
	const boost::shared_ptr<Player> test_player;

	Player_Fixture();
	virtual ~Player_Fixture();

	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Player> > test_playerMap;

private:
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Player> > init_playermap_helper();
};

#endif // _CORE_FIXTURE_PLAYERFIXTURE_HPP
