#include <iostream>
#include <time.h>

#pragma warning(push, 0)  
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include "distance_fixture.hpp"

Distance_Fixture::Distance_Fixture():
	seed(time(0))
{
	boost::mt19937 generator(static_cast<boost::uint32_t>(seed));
	boost::uniform_int<> distribution(1, 100);
	boost::variate_generator<boost::mt19937&, boost::uniform_int<> > rnd(generator,  distribution); 
	std::cout << "Setting up distance fixture (seed " << seed << ")" << std::endl;

	test_width = rnd();
	test_height = rnd();

	test_distance = new Distance(test_width, test_height);
}

Distance_Fixture::~Distance_Fixture() 
{
	delete test_distance;
}
