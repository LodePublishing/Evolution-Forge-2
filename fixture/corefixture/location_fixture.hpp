#ifndef _COREFIXTURE_LOCATIONFIXTURE_HPP
#define _COREFIXTURE_LOCATIONFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <location.hpp>

#include <random_fixture.hpp>

#include "path_fixture.hpp"


struct Location_Fixture : public Random_Fixture
{
	Location_Fixture();
	~Location_Fixture();

	const Path_Fixture path_fixture;

	const std::string test_name;
	const unsigned int test_position;	
	const signed int test_x;
	const signed int test_y;

	const boost::shared_ptr<Location> test_location;

	
};

#endif // _COREFIXTURE_LOCATIONFIXTURE_HPP
