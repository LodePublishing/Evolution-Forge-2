#pragma warning(push, 0)
#include <boost/assign/list_of.hpp>
#pragma warning(pop)

#include <random_fixture.hpp>
#include <globalstorage.hpp>

#include "map_fixture.hpp"


Map_Fixture::Map_Fixture():
	test_map_name("map"),
	test_file_name("Map1"),
	test_filename_xml("demofile.xml"),
	test_filename_raw("demofile.txt"),
	test_position(init_positionvector_helper()),
	test_location_name(init_locationnamevector_helper()),
	test_distance(init_distancevector_helper()),
	test_locations(init_locationvector_helper()),
	test_map(boost::shared_ptr<Map>(new Map(test_map_name, test_locations, init_pathlist_helper())))
{ 
	GlobalStorage::instance().addMap(test_map);

	for(std::vector<boost::shared_ptr<Location> >::const_iterator i = test_locations.begin(); i != test_locations.end(); i++) {
		GlobalStorage::instance().addLocation(*i);
	}
}

Map_Fixture::~Map_Fixture() 
{ 
	GlobalStorage::instance().removeMap(test_map->getId());

	for(std::vector<boost::shared_ptr<Location> >::const_iterator i = test_locations.begin(); i != test_locations.end(); i++) {
		GlobalStorage::instance().removeLocation((*i)->getId());
	}
}

const std::vector<unsigned int> Map_Fixture::init_positionvector_helper() {
	std::vector<unsigned int> positionVector = boost::assign::list_of(1)(2)(33)(5);
	return positionVector;
}

const std::vector<std::string> Map_Fixture::init_locationnamevector_helper() {
	std::vector<std::string> locationNameVector = boost::assign::list_of("Location1")("Location2")("Location3")("Location4");
	return locationNameVector;
}

const std::vector<unsigned int> Map_Fixture::init_distancevector_helper() {
	std::vector<unsigned int> distanceVector = boost::assign::list_of(11)(12)(13)(14)(24);
	return distanceVector;
}

const std::vector<boost::shared_ptr<Location> > Map_Fixture::init_locationvector_helper() {
	std::vector<boost::shared_ptr<Location> > locationVector;
	// don't use boost::assign::list_of, otherwise the locations are initialized in the wrong order!
		locationVector.push_back(boost::shared_ptr<Location>(new Location(test_location_name[0], 1, 1)));
		locationVector.push_back(boost::shared_ptr<Location>(new Location(test_location_name[1], 10, 1)));
		locationVector.push_back(boost::shared_ptr<Location>(new Location(test_location_name[2], 20, 10)));
		locationVector.push_back(boost::shared_ptr<Location>(new Location(test_location_name[3], 1, 10)));
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