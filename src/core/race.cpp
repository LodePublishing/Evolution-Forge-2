#include "race.hpp"

Race::Race(const std::string& name):
	name(name)
{}


Race::Race(const unsigned int id, const std::string& name):
	ID<Race>(id),
	name(name)
{}

Race::~Race()
{}