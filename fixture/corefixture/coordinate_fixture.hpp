#ifndef _COREFIXTURE_COORDINATEFIXTURE_HPP
#define _COREFIXTURE_COORDINATEFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <coordinate.hpp>

struct Coordinate_Fixture
{
	const unsigned int test_x;
	const unsigned int test_y;

	const boost::shared_ptr<const Coordinate> test_coordinate;

	Coordinate_Fixture();
	virtual ~Coordinate_Fixture();
};

#endif // _COREFIXTURE_COORDINATEFIXTURE_HPP