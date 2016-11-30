#ifndef _COREFIXTURE_MAPFIXTURE_HPP
#define _COREFIXTURE_MAPFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <vector>
#include <string>
#include <map.hpp>
#include <units.hpp>

struct Map_Fixture
{
	const std::string test_map_name;	
	const std::string test_file_name;
	const std::string test_filename_xml;
	const std::string test_filename_raw;

	const std::vector<unsigned int> test_position;
	const std::vector<std::string> test_location_name;
	const std::vector<unsigned int> test_distance;
	const std::vector<boost::shared_ptr<Location> > test_locations;

	const boost::shared_ptr<Map> test_map;

	Map_Fixture();
	virtual ~Map_Fixture();

private:
	const std::vector<boost::shared_ptr<Location> > init_locationvector_helper();
	const std::list<boost::shared_ptr<const Path> > init_pathlist_helper();
	const std::vector<unsigned int> init_positionvector_helper();
	const std::vector<std::string> init_locationnamevector_helper();
	const std::vector<unsigned int> init_distancevector_helper();
};

#endif // _COREFIXTURE_MAPFIXTURE_HPP