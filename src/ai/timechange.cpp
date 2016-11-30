#include "timechange.hpp"


TimeChange::TimeChange(const Player& player, const Units* const units, const Rules& rules)
{
	// TODO optimize, precalculate
	for(std::list<UnitType>::const_iterator unitType = rules.getUnitTypeList().begin(); unitType != rules.getUnitTypeList().end(); unitType++) {
		// if unitType is resource type, calculate distances, gathering speed, modifiers etc.
	}
}

TimeChange::~TimeChange() {
}
