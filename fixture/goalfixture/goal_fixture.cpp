#pragma warning(push, 0)  
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include <random_fixture.hpp>

#include "goal_fixture.hpp"

Goal_Fixture::Goal_Fixture():
	test_unitTypeId(boost::uuids::random_generator()()),
	test_locationId(boost::uuids::random_generator()()),
	test_count(Random_Fixture::instance().rnd()),
	test_time(Random_Fixture::instance().rnd()),
	test_goal(boost::shared_ptr<const Goal>(new Goal(test_unitTypeId, test_locationId, test_count, test_time)))
{
}

Goal_Fixture::~Goal_Fixture() 
{
}