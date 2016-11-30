#pragma warning(push, 0)  
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include "path_fixture.hpp"

Path_Fixture::Path_Fixture():
	Random_Fixture(),
	test_source_position(rnd()),
	test_target_position(rnd()),
	test_distance(rnd()),
	test_path(new Path(test_source_position, test_target_position, test_distance))
{}

Path_Fixture::~Path_Fixture() 
{
	Path::resetCounter();
}