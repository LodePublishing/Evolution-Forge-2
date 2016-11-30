#pragma warning(push, 0)  
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include "location_fixture.hpp"
#include "path_fixture.hpp"
#include <random_fixture.hpp>

Location_Fixture::Location_Fixture():
	test_name("Test_Location"),	
	test_position(Random_Fixture::instance().rnd()),
	test_x(Random_Fixture::instance().rnd()),
	test_y(Random_Fixture::instance().rnd()),
	test_location(boost::shared_ptr<Location>(new Location(test_name, test_position, test_x, test_y)))
{
	test_location->addPath(GlobalFixture etc... Path_Fixture::instance().test_path);
}

Location_Fixture::~Location_Fixture() 
{ }
