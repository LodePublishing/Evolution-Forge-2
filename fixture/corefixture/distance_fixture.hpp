#ifndef _CORETEST_DISTANCEFIXTURE_HPP
#define _CORETEST_DISTANCEFIXTURE_HPP

#include <distance.hpp>

struct Distance_Fixture
{
	Distance_Fixture();
	~Distance_Fixture();

	unsigned int test_width;
	unsigned int test_height;

	Distance* test_distance;

	time_t seed;
};

#endif // _CORETEST_DISTANCEFIXTURE_HPP