#include "gamedata.hpp"

GameData::GameData(Rules* rules):
	rules(rules)
{

}

GameData::~GameData() 
{
	delete rules;
}
