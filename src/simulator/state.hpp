#ifndef _GAME_STATE_HPP
#define _GAME_STATE_HPP

#include <units.hpp>

class State
{
public:
	State() {}
	State(const Units& units);
	const Units& getUnits() const;
	void process();
private:
	Units units;
};

inline const Units& State::getUnits() const {
	return units;
}


#endif // _GAME_STATE_HPP