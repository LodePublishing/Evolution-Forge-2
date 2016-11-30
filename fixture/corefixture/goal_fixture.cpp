#pragma warning(push, 0)  
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include "goal_fixture.hpp"

Goal_Fixture::Goal_Fixture():
	Random_Fixture(),
	test_unitTypeId(rnd()),
	test_locationId(rnd()),
	test_count(rnd()),
	test_time(rnd()),
	test_goal(boost::shared_ptr<const Goal>(new Goal(test_unitTypeId, test_locationId, test_count, test_time)))
{
}

Goal_Fixture::~Goal_Fixture() 
{
}
