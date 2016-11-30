#ifndef _COREFIXTURE_LOCATIONFIXTURE_HPP
#define _COREFIXTURE_LOCATIONFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <location.hpp>

struct Location_Fixture
{
	const std::string test_name;
	const unsigned int test_position;	
	const signed int test_x;
	const signed int test_y;

	const boost::shared_ptr<Location> test_location;

	Location_Fixture();	
	~Location_Fixture();	
};

#endif // _COREFIXTURE_LOCATIONFIXTURE_HPP
