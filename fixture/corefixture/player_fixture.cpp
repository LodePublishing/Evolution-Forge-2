#include <misc/randomgenerator.hpp>

#include "player_fixture.hpp"
#include <core/player_storage.hpp>
#include <core/core_directories.hpp>

Player_Fixture::Player_Fixture():
	governmentFixture(),

	test_player_name("my_player_Name" + RandomGenerator::instance().rndString()),
	test_player(new Player(test_player_name, governmentFixture.test_government)),
	test_playerMap(init_playermap_helper())
{ 
	CoreDirectories::initTemp("temp");

	PlayerStorage::instance(test_playerMap);	
}

Player_Fixture::~Player_Fixture() 
{ 
	CoreDirectories::initTemp("temp");

	PlayerStorage::clear();

	CoreDirectories::init();
}


const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Player> > Player_Fixture::init_playermap_helper() {
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const Player> > playerMap;
	playerMap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const Player> >(test_player->getId(), test_player));
	return playerMap;
}
