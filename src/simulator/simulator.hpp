#ifndef _GAME_SIMULATOR_HPP
#define _GAME_SIMULATOR_HPP

#include "state.hpp"

#include <game.hpp>
#include <buildorder.hpp>

class Simulator
{
public:
	Simulator(const Game* const game);
	void restart();
	const State& getState() const;
	const bool step();

	void createNewUnit();
	const unsigned int getTime() const;
	const bool tryBuildGene(const BuildOrder& buildOrder);
	const bool buildOrdersFinished() const;


	//mehrere populations an die Anfragen geschickt werden
	//soups evolvieren selbstständig


private:
	const Game* const game;
	State currentState;

	unsigned int time;

	// each build order represents a player
	std::list<BuildOrder> buildOrderList;
	bool isCalculationDone() const;
	void initBuildOrders();

	// temp variable for calculation of remaining time
	//void resetNeededResource();
	//std::map<unsigned int, std::vector<NeededResource>> neededResourceAvailable; // playerId -> needed resource
	//std::map<unsigned int, std::vector<NeededResource>> neededResourceTotal;
};

inline const State& Simulator::getState() const {
	return currentState;
}

inline const unsigned int Simulator::getTime() const {
	return time;
}

#endif // _GAME_SIMULATOR_HPP
