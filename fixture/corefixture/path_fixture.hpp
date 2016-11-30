#ifndef _CORETEST_PATHFIXTURE_HPP
#define _CORETEST_PATHFIXTURE_HPP

#include <path.hpp>

struct Path_Fixture
{
	Path_Fixture();
	~Path_Fixture();

	unsigned int test_source_position;
	unsigned int test_target_position;
	unsigned int test_distance;

	Path* test_path;

	time_t seed;
};

#endif // _CORETEST_PATHFIXTURE_HPP