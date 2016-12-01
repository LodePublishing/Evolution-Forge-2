#ifndef _GOALTEST_PROCESSEDGOALFIXTURE_HPP
#define _GOALTEST_PROCESSEDGOALFIXTURE_HPP

#include <goal/processedgoal.hpp>

struct ProcessedGoal_Fixture
{
	const bool test_isHaveable;
	const bool test_isBuildable;

	const boost::shared_ptr<const ProcessedGoal> test_processedgoal;

	ProcessedGoal_Fixture();
	virtual ~ProcessedGoal_Fixture();
};


#endif // _GOALTEST_PROCESSEDGOALFIXTURE_HPP
