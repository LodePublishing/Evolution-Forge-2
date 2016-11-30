#pragma warning(push, 0)  
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include "path_fixture.hpp"
#include <random_fixture.hpp>

Path_Fixture::Path_Fixture():
	test_source_position(Random_Fixture::instance().rnd()),
	test_target_position(Random_Fixture::instance().rnd()),
	test_distance(Random_Fixture::instance().rnd()),
	test_path(new Path(test_source_position, test_target_position, test_distance))
{}

Path_Fixture::~Path_Fixture() 
{ }