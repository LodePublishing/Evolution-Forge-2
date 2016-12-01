#include <misc/randomgenerator.hpp>

#include "size_fixture.hpp"


Size_Fixture::Size_Fixture() :
	test_width(RandomGenerator::instance().rnd()),
	test_height(RandomGenerator::instance().rnd()),
	test_size(new Size(test_width, test_height)),

	test_target_width(RandomGenerator::instance().rnd()),
	test_target_height(RandomGenerator::instance().rnd()),
	test_target_size(new Size(test_target_width, test_target_height))
{ }

Size_Fixture::~Size_Fixture() 
{ }