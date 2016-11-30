#include <iostream>
#include <time.h>

#include "processedgoal_fixture.hpp"

ProcessedGoal_Fixture::ProcessedGoal_Fixture() :
	Random_Fixture(),	
	test_isHaveable(rnd()>49),
	test_isBuildable(rnd()>49),
	test_processedgoal(new ProcessedGoal(test_isHaveable, test_isBuildable))
{ }

ProcessedGoal_Fixture::~ProcessedGoal_Fixture() 
{
	delete test_processedgoal;
}