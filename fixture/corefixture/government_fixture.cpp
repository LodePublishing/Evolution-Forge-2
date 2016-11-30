#include <iostream>
#include <time.h>

#pragma warning(push, 0)  
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include "government_fixture.hpp"

Government_Fixture::Government_Fixture():
	test_government_name("my_government_Name"),
	seed(time(0))
{
	boost::mt19937 generator(static_cast<boost::uint32_t>(seed));
	boost::uniform_int<> distribution(1, 100);
	boost::variate_generator<boost::mt19937&, boost::uniform_int<> > rnd(generator,  distribution); 
	std::cout << "Setting up government fixture (seed " << seed << ")" << std::endl;

	test_government = new Government(test_government_name);
}

Government_Fixture::~Government_Fixture() 
{
	delete test_government;
}