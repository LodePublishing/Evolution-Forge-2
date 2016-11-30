#include <iostream>
#include <time.h>

#pragma warning(push, 0)  
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include "map_fixture.hpp"

Map_Fixture::Map_Fixture():
test_map_name("map"),
	test_file_name("Map1"),
	test_filename_xml("demofile.xml"),
	test_filename_raw("demofile.txt"),
	seed(time(0))
{
	boost::mt19937 generator(static_cast<boost::uint32_t>(seed));
	boost::uniform_int<> distribution(1, 100);
	boost::variate_generator<boost::mt19937&, boost::uniform_int<> > rnd(generator,  distribution); 
	std::cout << "Setting up map fixture (seed " << seed << ")" << std::endl;

	test_position.push_back(1);
	test_position.push_back(2);
	test_position.push_back(33);
	test_position.push_back(5);

	test_location_name.push_back("Location1"); 
	test_location_name.push_back("Location2"); 
	test_location_name.push_back("Location3");
	test_location_name.push_back("Location4");

	test_coordinate.push_back(Coordinate(1,1));
	test_coordinate.push_back(Coordinate(10,1));
	test_coordinate.push_back(Coordinate(20,10));
	test_coordinate.push_back(Coordinate(1,10));

	test_distance.push_back(11); 
	test_distance.push_back(12); 
	test_distance.push_back(13); 
	test_distance.push_back(14); 
	test_distance.push_back(24);

	test_map = new Map(test_map_name);
	test_units = new Units();


	for(int i = 0; i < 4; i++) {
		locations.push_back(new Location(test_location_name[i], test_position[i], test_coordinate[i], test_units));
		test_map->addLocation(locations[i]);
	}

	paths.push_back(new Path(locations[0]->getPosition(), locations[1]->getPosition(), test_distance[0]));
	test_map->addPath(paths[0]);
	paths.push_back(new Path(locations[1]->getPosition(), locations[2]->getPosition(), test_distance[1]));
	test_map->addPath(paths[1]);
	paths.push_back(new Path(locations[1]->getPosition(), locations[3]->getPosition(), test_distance[4]));
	test_map->addPath(paths[2]);
	paths.push_back(new Path(locations[2]->getPosition(), locations[3]->getPosition(), test_distance[2]));
	test_map->addPath(paths[3]);
	paths.push_back(new Path(locations[3]->getPosition(), locations[0]->getPosition(), test_distance[3]));
	test_map->addPath(paths[4]);
	test_map->addPathsFromLocations();
	// TODO sorting map needs entries in orderly fashion (first all paths from location index 0, then index 1, etc.pp.

	test_map->calculateDistanceMap();
}

Map_Fixture::~Map_Fixture() 
{
	delete test_map;
	delete test_units;

	Map::resetCounter();
	Location::resetCounter();
	Path::resetCounter();
}