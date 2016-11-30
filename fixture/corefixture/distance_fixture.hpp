#ifndef _COREFIXTURE_DISTANCEFIXTURE_HPP
#define _COREFIXTURE_DISTANCEFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <distance.hpp>

#include <random_fixture.hpp>

struct Distance_Fixture : public Random_Fixture
{
	Distance_Fixture();
	~Distance_Fixture();

	unsigned int test_width;
	unsigned int test_height;

	const boost::shared_ptr<const Distance> test_distance;
};

#endif // _COREFIXTURE_DISTANCEFIXTURE_HPP