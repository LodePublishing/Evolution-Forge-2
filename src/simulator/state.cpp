#include "state.hpp"

State::State(const Units& units):
	units(units)
	{}

void State::process() {
	units.process();
}