#include "race.hpp"

Race::Race(const std::string& name):
	name(name)
{}


Race::Race(const boost::uuids::uuid id, const std::string& name):
	UUID<Race>(id),
	name(name)
{}

Race::~Race()
{}