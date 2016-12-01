#ifndef _CORE_FIXTURE_LOCATIONFIXTURE_HPP
#define _CORE_FIXTURE_LOCATIONFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <core/location.hpp>
#include <core/path.hpp>
#include <map>

struct Location_Fixture
{
	const std::string test_name;
	const signed int test_x;
	const signed int test_y;
	const boost::shared_ptr<Location> test_location;	

	const std::string test_target_name;
	const signed int test_target_x;
	const signed int test_target_y;
	const boost::shared_ptr<Location> test_target_location;
	const unsigned int test_distance;

	const boost::shared_ptr<const Path> test_path;
	const boost::shared_ptr<const Path> test_target_path;

	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Location> > test_locationMap;

	Location_Fixture();	
	virtual ~Location_Fixture();	

private:
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Location> > init_locationmap_helper();

};

#endif // _CORE_FIXTURE_LOCATIONFIXTURE_HPP
