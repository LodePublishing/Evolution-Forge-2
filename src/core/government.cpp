#include "government.hpp"

Government::Government(const std::string name):
	name(name)
{}

Government::Government(const unsigned int id, const std::string name):
	ID<Government>(id),
	name(name)
{}


Government::~Government()
{}