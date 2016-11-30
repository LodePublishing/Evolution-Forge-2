#ifndef _COREFIXTURE_LOCATIONFIXTURE_HPP
#define _COREFIXTURE_LOCATIONFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <location.hpp>
#include <path.hpp>

struct Location_Fixture
{
	const std::string test_name;
	const signed int test_x;
	const signed int test_y;

	const boost::shared_ptr<Location> test_location;
	
	const boost::shared_ptr<Location> test_target_location;
	const unsigned int test_distance;

	const boost::shared_ptr<const Path> test_path;

	Location_Fixture();	
	virtual ~Location_Fixture();	
};

#endif // _COREFIXTURE_LOCATIONFIXTURE_HPP
