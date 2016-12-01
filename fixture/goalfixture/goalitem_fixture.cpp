#pragma warning(push, 0)  
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include <misc/randomgenerator.hpp>

#include "goalitem_fixture.hpp"


GoalItem_Fixture::GoalItem_Fixture():
	test_unitTypeId(boost::uuids::random_generator()()),
	test_locationId(boost::uuids::random_generator()()),
	test_count(RandomGenerator::instance().rnd()),
	test_time(RandomGenerator::instance().rnd()),
	test_goalitem(boost::shared_ptr<const GoalItem>(new GoalItem(test_unitTypeId, test_locationId, test_count, test_time)))
{ }

GoalItem_Fixture::~GoalItem_Fixture() 
{ }
