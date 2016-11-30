#include <iostream>
#include <time.h>

#pragma warning(push, 0)  
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include "location_fixture.hpp"

Location_Fixture::Location_Fixture():
	test_name("Test_Location"),
	seed(time(0))
{
	boost::mt19937 generator(static_cast<boost::uint32_t>(seed));
	boost::uniform_int<> distribution(1, 100);
	boost::variate_generator<boost::mt19937&, boost::uniform_int<> > rnd(generator,  distribution); 
	std::cout << "Setting up location fixture (seed " << seed << ")" << std::endl;

	test_position = rnd();
	test_coordinate = new Coordinate(rnd(), rnd());

	test_units = new Units();
	test_location = new Location(test_name, test_position, *test_coordinate, test_units);
}

Location_Fixture::~Location_Fixture() 
{
	delete test_units;
	delete test_location;
	delete test_coordinate;

	Location::resetCounter();
}