#ifndef _GAMES_GAMEDATA_HPP
#define _GAMES_GAMEDATA_HPP

#include <rules.hpp>

class GameData
{
public:
	virtual const boost::shared_ptr<const Rules> getRules() const = 0;
protected:
	GameData() {}
	virtual ~GameData() {}
};

#endif // _GAMES_GAMEDATA_HPP