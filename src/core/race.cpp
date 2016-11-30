#include "race.hpp"

Race::Race(const std::string& name):
	name(name)
{}

Race::~Race()
{}

// only for serialization / deserialization
Race::Race():
	name("invalid")
{
}


const char* const Race::Name_tag_string = "name";