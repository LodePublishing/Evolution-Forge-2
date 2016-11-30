#pragma warning(push, 0)  
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include "coordinate_fixture.hpp"
#include <random_fixture.hpp>

Coordinate_Fixture::Coordinate_Fixture():
	test_x(Random_Fixture::instance().rnd()),
	test_y(Random_Fixture::instance().rnd()),
	test_coordinate(boost::shared_ptr<const Coordinate>(new Coordinate(test_x, test_y)))
{}

Coordinate_Fixture::~Coordinate_Fixture() 
{
}