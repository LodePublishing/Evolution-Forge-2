#include "government.hpp"

Government::Government(const std::string& name):
	name(name)
{}

Government::~Government()
{}

const char* const Government::Name_tag_string = "name";