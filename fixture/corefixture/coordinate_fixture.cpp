#include <iostream>
#include <time.h>

#pragma warning(push, 0)  
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include "coordinate_fixture.hpp"

Coordinate_Fixture::Coordinate_Fixture():
	seed(time(0))
{
	boost::mt19937 generator(static_cast<boost::uint32_t>(seed));
	boost::uniform_int<> distribution(1, 100);
	boost::variate_generator<boost::mt19937&, boost::uniform_int<> > rnd(generator,  distribution); 
	std::cout << "Setting up coordinate fixture (seed " << seed << ")" << std::endl;

	test_x = rnd();
	test_y = rnd();

	test_coordinate = new Coordinate(test_x, test_y);
}

Coordinate_Fixture::~Coordinate_Fixture() 
{
	delete test_coordinate;
}
