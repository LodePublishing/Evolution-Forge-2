#include <random_fixture.hpp>

#include "path_fixture.hpp"

#include <location.hpp>

Path_Fixture::Path_Fixture():
	test_source_location_id(boost::uuids::random_generator()()),
	test_target_location_id(boost::uuids::random_generator()()),
	test_distance(Random_Fixture::instance().rnd()),
	test_path(boost::shared_ptr<Path>(new Path(test_source_location_id, test_target_location_id, test_distance)))
{ }

Path_Fixture::~Path_Fixture() 
{ }