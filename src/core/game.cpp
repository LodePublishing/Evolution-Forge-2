#pragma warning(push, 0)  
#include <boost/assert.hpp>
#pragma warning(pop)

#include "game.hpp"
#include "units.hpp"

Game::Game(const Rules* const rules,
	const Map* const map,
	const Units* const startingUnits,
	const unsigned int startingTime):
startingUnits(new Units(*startingUnits)),
	rules(rules),
	rulesId(rules->getID()),
	map(map),
	mapId(map->getID()),	
	startingTime(startingTime)
{
}

Game::~Game()
{
	delete startingUnits;
}

void Game::assignMap(const Map* const map) {
	assert(mapId == map->getID());

	this->map = map;
}

void Game::assignRules(const Rules* const rules) {
	BOOST_ASSERT(rulesId == rules->getID());

	this->rules = rules;
}

void Game::addPlayer(const Player* player) {
	playerMap.insert(std::pair<unsigned int, const Player*>(player->getID(), player));
}

// call after deserialization to reinitialize accordingly
void Game::initialize(std::map<int, Rules*> rulesStorage, std::map<int, Map*> mapStorage) {
	assignRules(rulesStorage[rulesId]);
	assignMap(mapStorage[mapId]);
	// TODO players
}


const char* const Game::Rules_tag_string = "rules";
const char* const Game::PlayerList_tag_string = "PlayerList";
const char* const Game::Map_tag_string = "map";
const char* const Game::StartingTime_tag_string = "time";
const char* const Game::StartingUnits_tag_string = "StartingUnits";
