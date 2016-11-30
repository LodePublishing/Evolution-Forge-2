#include <iostream>
#include <time.h>

#include <random_fixture.hpp>

#include "processedgoal_fixture.hpp"

ProcessedGoal_Fixture::ProcessedGoal_Fixture():
	test_isHaveable(Random_Fixture::instance().rnd()>49),
	test_isBuildable(Random_Fixture::instance().rnd()>49),
	test_processedgoal(boost::shared_ptr<const ProcessedGoal>(new ProcessedGoal(test_isHaveable, test_isBuildable)))
{ }

ProcessedGoal_Fixture::~ProcessedGoal_Fixture() 
{
}