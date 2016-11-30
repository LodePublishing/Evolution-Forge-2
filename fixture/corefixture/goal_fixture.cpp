#include <iostream>
#include <time.h>

#pragma warning(push, 0)  
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include "goal_fixture.hpp"

Goal_Fixture::Goal_Fixture():
	seed(time(0))
{
	boost::mt19937 generator(static_cast<boost::uint32_t>(seed));
	boost::uniform_int<> distribution(1, 100);
	boost::variate_generator<boost::mt19937&, boost::uniform_int<> > rnd(generator,  distribution); 
	std::cout << "Setting up goal fixture (seed " << seed << ")" << std::endl;

	test_unitTypeID = rnd();
	test_locationID = rnd();
	test_count = rnd();
	test_time = rnd();

	test_goal = new Goal(test_unitTypeID, test_locationID, test_count, test_time);
}

Goal_Fixture::~Goal_Fixture() 
{
	delete test_goal;
}
