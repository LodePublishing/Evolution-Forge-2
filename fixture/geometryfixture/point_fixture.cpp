#include <misc/randomgenerator.hpp>

#include "point_fixture.hpp"


Point_Fixture::Point_Fixture() :
	test_x(RandomGenerator::instance().rnd()),
	test_y(RandomGenerator::instance().rnd()),
	test_point(new Point(test_x, test_y)),

	test_target_x(RandomGenerator::instance().rnd()),
	test_target_y(RandomGenerator::instance().rnd()),
	test_target_point(new Point(test_target_x, test_target_y))

{ }

Point_Fixture::~Point_Fixture() 
{ }