#include <iostream>
#include <time.h>

#pragma warning(push, 0)  
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include "path_fixture.hpp"

Path_Fixture::Path_Fixture():
	seed(time(0))
{
	boost::mt19937 generator(static_cast<boost::uint32_t>(seed));
	boost::uniform_int<> distribution(1, 100);
	boost::variate_generator<boost::mt19937&, boost::uniform_int<> > rnd(generator,  distribution); 
	std::cout << "Setting up path fixture (seed " << seed << ")" << std::endl;

	test_source_position = rnd();
	test_target_position = rnd();
	test_distance = rnd();

	test_path = new Path(test_source_position, test_target_position, test_distance);
}

Path_Fixture::~Path_Fixture() 
{
	delete test_path;
	Path::resetCounter();
}