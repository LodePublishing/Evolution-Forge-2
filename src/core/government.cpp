#include "government.hpp"

Government::Government(const std::string name):
name(name)
{ }

Government::Government(const boost::uuids::uuid id, const std::string name):
UUID<Government>(id),
	name(name)
{ }


Government::~Government()
{ }