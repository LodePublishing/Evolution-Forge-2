#include <random_fixture.hpp>

#include "coordinate_fixture.hpp"


Coordinate_Fixture::Coordinate_Fixture():
	test_x(Random_Fixture::instance().rnd()),
	test_y(Random_Fixture::instance().rnd()),
	test_coordinate(boost::shared_ptr<const Coordinate>(new Coordinate(test_x, test_y)))
{ }

Coordinate_Fixture::~Coordinate_Fixture() 
{ }