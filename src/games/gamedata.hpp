#ifndef _GAMES_GAMEDATA_HPP
#define _GAMES_GAMEDATA_HPP

#include <rules.hpp>

class GameData
{
public:
	const Rules* getRules() const;

protected:
	GameData(Rules* rules);
	~GameData();

	Rules* rules;
};

inline const Rules* GameData::getRules() const {
	return rules;
}	

#endif // _GAMES_GAMEDATA_HPP