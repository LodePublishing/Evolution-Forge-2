#include <misc/randomgenerator.hpp>

#include "location_fixture.hpp"
#include <core/location_storage.hpp>
#include <core/core_directories.hpp>

Location_Fixture::Location_Fixture():
	test_name("Test Location"),	
	test_x(RandomGenerator::instance().rnd()),
	test_y(RandomGenerator::instance().rnd()),
	test_location(new Location(test_name, test_x, test_y)),

	test_target_name("Test Target Location"),	
	test_target_x(RandomGenerator::instance().rnd()),
	test_target_y(RandomGenerator::instance().rnd()),
	test_target_location(new Location(test_target_name, test_target_x, test_target_y)),
	test_distance(RandomGenerator::instance().rnd()),
	test_path(new Path(test_location->getId(), test_target_location->getId(), test_distance)),
	test_target_path(new Path(test_target_location->getId(), test_location->getId(), test_distance)),
	test_locationMap(init_locationmap_helper())
{ 
	CoreDirectories::initTemp("temp");

	test_location->addPath(test_path);	
	test_target_location->addPath(test_target_path);

	LocationStorage::instance(test_locationMap);
}

Location_Fixture::~Location_Fixture() 
{ 
	CoreDirectories::initTemp("temp");

	LocationStorage::clear();

	CoreDirectories::init();
}

const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Location> > Location_Fixture::init_locationmap_helper() {
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const Location> > locationMap;
	locationMap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const Location> >(test_location->getId(), test_location));
	locationMap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const Location> >(test_target_location->getId(), test_target_location));
	return locationMap;
}
