#pragma warning(push, 0)
#include <boost/assign/list_of.hpp>
#pragma warning(pop)

#include <misc/randomgenerator.hpp>

#include "map_fixture.hpp"
#include <core/map_storage.hpp>
#include <core/core_directories.hpp>

Map_Fixture::Map_Fixture():
	
	test_map_name("map" + RandomGenerator::instance().rndString()),
	test_location_name(init_locationnamevector_helper()),
	test_distance(init_distancevector_helper()),
	test_locations(init_locationvector_helper()),
	test_map(new Map(test_map_name, test_locations, init_pathlist_helper())),
	test_locationMap(init_locationmap_helper()),
	test_mapMap(init_mapmap_helper())
{ 
	CoreDirectories::initTemp("temp");

	MapStorage::instance(test_mapMap);	
}

Map_Fixture::~Map_Fixture() 
{ 
	CoreDirectories::initTemp("temp");

	MapStorage::clear();

	CoreDirectories::init();
}

const std::vector<std::string> Map_Fixture::init_locationnamevector_helper() {
	std::vector<std::string> locationNameVector = boost::assign::list_of("Location" + RandomGenerator::instance().rndString())("Location" + RandomGenerator::instance().rndString())("Location" + RandomGenerator::instance().rndString())("Location" + RandomGenerator::instance().rndString());
	return locationNameVector;
}

const std::vector<unsigned int> Map_Fixture::init_distancevector_helper() {
	std::vector<unsigned int> distanceVector = boost::assign::list_of(1100)(1200)(1300)(1400)(2400);
	return distanceVector;
}

const std::vector<boost::shared_ptr<Location> > Map_Fixture::init_locationvector_helper() {
	std::vector<boost::shared_ptr<Location> > locationVector;
	// don't use boost::assign::list_of, otherwise the locations are initialized in the wrong order!
		locationVector.push_back(boost::shared_ptr<Location>(new Location(test_location_name[0], 1, 1)));
		locationVector.push_back(boost::shared_ptr<Location>(new Location(test_location_name[1], 1000, 1)));
		locationVector.push_back(boost::shared_ptr<Location>(new Location(test_location_name[2], 2000, 1000)));
		locationVector.push_back(boost::shared_ptr<Location>(new Location(test_location_name[3], 1, 1000)));
	return locationVector;
}

const std::list<boost::shared_ptr<const Path> > Map_Fixture::init_pathlist_helper() {
	std::list<boost::shared_ptr<const Path> > pathList = boost::assign::list_of
		(boost::shared_ptr<Path>(new Path(test_locations[0]->getId(), test_locations[1]->getId(), test_distance[0])))
		(boost::shared_ptr<Path>(new Path(test_locations[1]->getId(), test_locations[2]->getId(), test_distance[1])))
		(boost::shared_ptr<Path>(new Path(test_locations[1]->getId(), test_locations[3]->getId(), test_distance[4])))
		(boost::shared_ptr<Path>(new Path(test_locations[2]->getId(), test_locations[3]->getId(), test_distance[2])))
		(boost::shared_ptr<Path>(new Path(test_locations[3]->getId(), test_locations[0]->getId(), test_distance[3])));
	return pathList;
}

const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Map> > Map_Fixture::init_mapmap_helper() {
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const Map> > mapMap;
	mapMap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const Map> >(test_map->getId(), test_map));
	return mapMap;
}

const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Location> > Map_Fixture::init_locationmap_helper() {
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const Location> > locationMap;
	for(std::vector<boost::shared_ptr<Location> >::const_iterator i = test_locations.begin(); i != test_locations.end(); i++) {
		locationMap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const Location> >((*i)->getId(), *i));
	}	
	return locationMap;
}