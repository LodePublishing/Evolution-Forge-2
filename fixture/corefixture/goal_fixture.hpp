#ifndef _CORETEST_GOALFIXTURE_HPP
#define _CORETEST_GOALFIXTURE_HPP

#include <goal.hpp>

struct Goal_Fixture
{
	Goal_Fixture();
	~Goal_Fixture();

	unsigned int test_unitTypeID;
	unsigned int test_locationID;

	unsigned int test_count;
	unsigned int test_time;

	Goal* test_goal;

	time_t seed;
};

#endif // _CORETEST_GOALFIXTURE_HPP
