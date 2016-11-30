#include <iostream>
#include <time.h>

#pragma warning(push, 0)  
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include "race_fixture.hpp"

Race_Fixture::Race_Fixture():
	test_race_name("my_race_Name"),
	seed(time(0))
{
	boost::mt19937 generator(static_cast<boost::uint32_t>(seed));
	boost::uniform_int<> distribution(1, 100);
	boost::variate_generator<boost::mt19937&, boost::uniform_int<> > rnd(generator,  distribution); 
	std::cout << "Setting up race fixture (seed " << seed << ")" << std::endl;

	test_race = new Race(test_race_name);
}

Race_Fixture::~Race_Fixture() 
{

	delete test_race;
	Race::resetCounter();
}