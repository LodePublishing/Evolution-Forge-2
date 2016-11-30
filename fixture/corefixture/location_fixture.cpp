#include <random_fixture.hpp>
#include <globalstorage.hpp>

#include "location_fixture.hpp"


Location_Fixture::Location_Fixture():
	test_name("Test Location"),	
	test_x(Random_Fixture::instance().rnd()),
	test_y(Random_Fixture::instance().rnd()),
	test_location(boost::shared_ptr<Location>(new Location(test_name, test_x, test_y))),

	test_target_location(boost::shared_ptr<Location>(new Location(test_name, test_x, test_y))),
	test_distance(Random_Fixture::instance().rnd()),
	test_path(boost::shared_ptr<Path>(new Path(test_location->getId(), test_target_location->getId(), test_distance)))
{
	test_location->addPath(test_path);
	GlobalStorage::instance().addLocation(test_location);	
	GlobalStorage::instance().addLocation(test_target_location);
}

Location_Fixture::~Location_Fixture() 
{ 
	GlobalStorage::instance().removeLocation(test_location->getId());	
	GlobalStorage::instance().removeLocation(test_target_location->getId());
}
