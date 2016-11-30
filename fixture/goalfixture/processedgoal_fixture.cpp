#include <iostream>
#include <time.h>

#pragma warning(push, 0)  
#include <boost/assign/list_of.hpp>
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include "processedgoal_fixture.hpp"

ProcessedGoal_Fixture::ProcessedGoal_Fixture():
	seed(time(0))
{	
	boost::mt19937 generator(static_cast<boost::uint32_t>(seed));
	boost::uniform_int<> distribution(1, 100);
	boost::variate_generator<boost::mt19937&, boost::uniform_int<> > rnd(generator,  distribution); 
	std::cout << "Setting up processed goal fixture (seed " << seed << ")" << std::endl;

	test_isHaveable = rnd()>49;
	test_isBuildable = rnd()>49;
	test_isBuildableAtStart = test_isBuildable || (rnd()>49);
	
	test_processedgoal = new ProcessedGoal(test_isHaveable, test_isBuildable, test_isBuildableAtStart);
}

ProcessedGoal_Fixture::~ProcessedGoal_Fixture() 
{
	delete test_processedgoal;
}