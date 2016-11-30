#include <random_fixture.hpp>

#include "distance_fixture.hpp"


Distance_Fixture::Distance_Fixture() :
	test_width(Random_Fixture::instance().rnd()),
	test_height(Random_Fixture::instance().rnd()),
	test_distance(boost::shared_ptr<const Distance>(new Distance(test_width, test_height)))
{ }

Distance_Fixture::~Distance_Fixture() 
{ }