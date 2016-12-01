#include <misc/randomgenerator.hpp>

#include <core/location.hpp>

#include "path_fixture.hpp"


Path_Fixture::Path_Fixture():
	test_source_location_id(boost::uuids::random_generator()()),
	test_target_location_id(boost::uuids::random_generator()()),
	test_distance(RandomGenerator::instance().rnd()),
	test_path(new Path(test_source_location_id, test_target_location_id, test_distance))
{ }

Path_Fixture::~Path_Fixture() 
{ }