#pragma warning(push, 0) 
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <path_fixture.hpp>

BOOST_FIXTURE_TEST_SUITE( Path_test, Path_Fixture )

	BOOST_AUTO_TEST_CASE (Path_constructor )
	{
		BOOST_CHECK_EQUAL(test_path->getDistance(), test_distance);
		BOOST_CHECK_EQUAL(test_path->getSourceLocationId(), test_source_location_id);
		BOOST_CHECK_EQUAL(test_path->getTargetLocationId(), test_target_location_id);
	}

	BOOST_AUTO_TEST_CASE (Path_toString )
	{
		std::ostringstream os;
		os << test_source_location_id << " -> " << test_target_location_id << " [" << test_distance << "km]";

		BOOST_CHECK_EQUAL(test_path->toString(), os.str());
	}

BOOST_AUTO_TEST_SUITE_END( )
