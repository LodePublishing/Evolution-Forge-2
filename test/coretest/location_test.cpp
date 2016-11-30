#pragma warning(push, 0) 
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <location_fixture.hpp>

BOOST_FIXTURE_TEST_SUITE( Location_test, Location_Fixture )

	BOOST_AUTO_TEST_CASE (Location_constructor)
	{	
		BOOST_CHECK_EQUAL(test_location->getPosition(), test_position);
		BOOST_CHECK_EQUAL(test_location->getName(), test_name);		
		BOOST_CHECK_EQUAL(test_location->getCoordinate()->getX(), test_coordinate->getX());
		BOOST_CHECK_EQUAL(test_location->getCoordinate()->getY(), test_coordinate->getY());
	}
	
BOOST_AUTO_TEST_SUITE_END( )
