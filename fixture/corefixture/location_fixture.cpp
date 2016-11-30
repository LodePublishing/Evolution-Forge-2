#pragma warning(push, 0)  
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include "location_fixture.hpp"

Location_Fixture::Location_Fixture():
	Random_Fixture(),
	path_fixture(),

	test_name("Test_Location"),	
	test_position(rnd()),
	test_x(rnd()),
	test_y(rnd()),
	test_location(boost::shared_ptr<Location>(new Location(test_name, test_position, test_x, test_y)))
{
	test_location->addPath(path_fixture.test_path);
}

Location_Fixture::~Location_Fixture() 
{
	Location::resetCounter();
}
