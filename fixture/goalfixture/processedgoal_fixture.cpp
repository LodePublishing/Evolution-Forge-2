#include <iostream>
#include <time.h>

#include <misc/randomgenerator.hpp>

#include "processedgoal_fixture.hpp"


ProcessedGoal_Fixture::ProcessedGoal_Fixture():
	test_isHaveable(RandomGenerator::instance().rnd()>49),
	test_isBuildable(RandomGenerator::instance().rnd()>49),
	test_processedgoal(boost::shared_ptr<const ProcessedGoal>(new ProcessedGoal(test_isHaveable, test_isBuildable)))
{ }

ProcessedGoal_Fixture::~ProcessedGoal_Fixture() 
{
}