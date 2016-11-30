#pragma warning(push, 0)  
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include "distance_fixture.hpp"

Distance_Fixture::Distance_Fixture() :
	test_width(rnd()),
	test_height(rnd()),
	test_distance(boost::shared_ptr<const Distance>(new Distance(test_width, test_height)))
{}

Distance_Fixture::~Distance_Fixture() 
{
}
