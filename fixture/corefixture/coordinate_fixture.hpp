#ifndef _CORETEST_COORDINATEFIXTURE_HPP
#define _CORETEST_COORDINATEFIXTURE_HPP

#include <coordinate.hpp>

struct Coordinate_Fixture
{
	Coordinate_Fixture();
	~Coordinate_Fixture();

	unsigned int test_x;
	unsigned int test_y;

	Coordinate* test_coordinate;

	time_t seed;
};

#endif // _CORETEST_COORDINATEFIXTURE_HPP