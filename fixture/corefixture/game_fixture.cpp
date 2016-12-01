#pragma warning(push, 0)
#include <boost/assign/list_of.hpp>
#pragma warning(pop)

#include <misc/randomgenerator.hpp>

#include "game_fixture.hpp"
#include <core/game_storage.hpp>
#include <core/core_directories.hpp>

Game_Fixture::Game_Fixture():
	playerFixture(),
	mapFixture(),
	startConditionFixture(),
	test_name("my game name"),

	test_game(new Game(test_name, startConditionFixture.unitsFixture.broodwar.getRules(), mapFixture.test_map, startConditionFixture.test_startcondition)),
	test_gameMap(init_gamemap_helper())
{ 
	CoreDirectories::initTemp("temp");

	GameStorage::instance(test_gameMap);
}

Game_Fixture::~Game_Fixture()
{ 
	CoreDirectories::initTemp("temp");

	GameStorage::clear();

	CoreDirectories::init();
}

const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Game> > Game_Fixture::init_gamemap_helper() {
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const Game> > gameMap;
	gameMap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const Game> >(test_game->getId(), test_game));
	return gameMap;
}