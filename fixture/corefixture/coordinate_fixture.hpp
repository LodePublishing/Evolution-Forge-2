#ifndef _COREFIXTURE_COORDINATEFIXTURE_HPP
#define _COREFIXTURE_COORDINATEFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <coordinate.hpp>
#include <random_fixture.hpp>

struct Coordinate_Fixture : public Random_Fixture
{
	Coordinate_Fixture();
	~Coordinate_Fixture();

	unsigned int test_x;
	unsigned int test_y;

	const boost::shared_ptr<const Coordinate> test_coordinate;
};

#endif // _COREFIXTURE_COORDINATEFIXTURE_HPP