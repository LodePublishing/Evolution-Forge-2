#pragma warning(push, 0) 
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <location_fixture.hpp>
#include <path_fixture.hpp>

BOOST_FIXTURE_TEST_SUITE( Location_test, Location_Fixture )

	BOOST_AUTO_TEST_CASE (Location_constructor)
	{	
		BOOST_CHECK_EQUAL(test_location->getName(), test_name);		
		BOOST_CHECK_EQUAL(test_location->getX(), test_x);
		BOOST_CHECK_EQUAL(test_location->getY(), test_y);
		BOOST_CHECK_EQUAL(test_location->getPaths().front()->getSourceLocationId(), test_location->getId());
		BOOST_CHECK_EQUAL(test_location->getPaths().front()->getTargetLocationId(), test_target_location->getId());
		BOOST_CHECK_EQUAL(test_location->getPaths().front()->getDistance(), test_path->getDistance());
	}

	BOOST_AUTO_TEST_CASE (Location_toString)
	{
		std::ostringstream os;
		os << "Location Name: " << test_name << std::endl << "Distances: ";
		for(std::list<boost::shared_ptr<const Path> >::const_iterator i = test_location->getPaths().begin(); i != test_location->getPaths().end(); i++) {
			os << (*i)->toString() << ", ";
		}
   		os << std::endl;	
		BOOST_CHECK_EQUAL(test_location->toString(), os.str());
	}

	
BOOST_AUTO_TEST_SUITE_END( )
