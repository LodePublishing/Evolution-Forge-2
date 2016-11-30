#ifndef _CORETEST_LOCATIONFIXTURE_HPP
#define _CORETEST_LOCATIONFIXTURE_HPP

#include <location.hpp>
#include <units.hpp>

struct Location_Fixture
{
	Location_Fixture();
	~Location_Fixture();

	unsigned int test_position;
	const std::string test_name;
	Coordinate* test_coordinate;
	Units* test_units;

	Location* test_location;

	time_t seed;
};

#endif // _CORETEST_LOCATIONFIXTURE_HPP