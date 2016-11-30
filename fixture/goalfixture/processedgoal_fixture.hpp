#ifndef _GOALTEST_PROCESSEDGOALFIXTURE_HPP
#define _GOALTEST_PROCESSEDGOALFIXTURE_HPP

#include <processedgoal.hpp>
#include <random_fixture.hpp>

struct ProcessedGoal_Fixture : public Random_Fixture
{
	ProcessedGoal_Fixture();
	~ProcessedGoal_Fixture();

	const bool test_isHaveable;
	const bool test_isBuildable;

	ProcessedGoal* test_processedgoal;
};


#endif // _GOALTEST_PROCESSEDGOALFIXTURE_HPP
