#ifndef _CORETEST_MAPFIXTURE_HPP
#define _CORETEST_MAPFIXTURE_HPP

#include <vector>
#include <string>
#include <coordinate.hpp>
#include <map.hpp>
#include <units.hpp>

struct Map_Fixture
{
	Map_Fixture();
	~Map_Fixture();

	const std::string test_map_name;	
	const std::string test_file_name;
	const std::string test_filename_xml;
	const std::string test_filename_raw;

	std::vector<unsigned int> test_position;
	std::vector<std::string> test_location_name;
	std::vector<unsigned int> test_distance;
	std::vector<Coordinate> test_coordinate;

	Map* test_map;
	Units* test_units;
	std::vector<Location*> locations;
	std::vector<Path*> paths;

	time_t seed;
};

#endif // _CORETEST_MAPFIXTURE_HPP