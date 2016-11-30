#ifndef _COREFIXTURE_DISTANCEFIXTURE_HPP
#define _COREFIXTURE_DISTANCEFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <distance.hpp>

struct Distance_Fixture
{
	const unsigned int test_width;
	const unsigned int test_height;

	const boost::shared_ptr<const Distance> test_distance;

	~Distance_Fixture();
	Distance_Fixture();
};

#endif // _COREFIXTURE_DISTANCEFIXTURE_HPP