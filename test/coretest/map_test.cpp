#pragma warning(push, 0) 
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <map_fixture.hpp>

BOOST_FIXTURE_TEST_SUITE( Map_test, Map_Fixture )

	BOOST_AUTO_TEST_CASE ( Map_constructor_test )
{
	BOOST_CHECK_EQUAL(test_map->getName(), test_map_name);
	BOOST_CHECK_EQUAL(test_map->getLocationVector().size(), 4);

	BOOST_CHECK_EQUAL(test_map->getLocationAt(1)->getAirDistance(test_map->getLocationAt(2)), 9);
	BOOST_CHECK_EQUAL(test_map->getLocationAt(1)->getAirDistance(test_map->getLocationAt(33)), 21);
	BOOST_CHECK_EQUAL(test_map->getLocationAt(1)->getAirDistance(test_map->getLocationAt(5)), 9);
	BOOST_CHECK_EQUAL(test_map->getLocationAt(2)->getAirDistance(test_map->getLocationAt(33)), 13);
	BOOST_CHECK_EQUAL(test_map->getLocationAt(2)->getAirDistance(test_map->getLocationAt(5)), 12);
	BOOST_CHECK_EQUAL(test_map->getLocationAt(33)->getAirDistance(test_map->getLocationAt(5)), 19);

	BOOST_CHECK_EQUAL(test_map->getLocationAt(1)->getGroundDistance(test_map->getLocationAt(2)), 11);
	BOOST_CHECK_EQUAL(test_map->getLocationAt(1)->getGroundDistance(test_map->getLocationAt(33)), 23);
	BOOST_CHECK_EQUAL(test_map->getLocationAt(1)->getGroundDistance(test_map->getLocationAt(5)), 14);
	BOOST_CHECK_EQUAL(test_map->getLocationAt(2)->getGroundDistance(test_map->getLocationAt(33)), 12);
	BOOST_CHECK_EQUAL(test_map->getLocationAt(2)->getGroundDistance(test_map->getLocationAt(5)), 24);
	BOOST_CHECK_EQUAL(test_map->getLocationAt(33)->getGroundDistance(test_map->getLocationAt(5)), 13);
}

BOOST_AUTO_TEST_CASE( Map_invalid_locations_test )
{
	const boost::shared_ptr<Location> ind_location(new Location("test", 99, 3, 3));
	bool exception = false;
	try {
		test_map->getLocationAt(1)->getGroundDistance(ind_location);
	} catch(...) {
		exception = true;
	}

	BOOST_CHECK_EQUAL(exception, true);
}

BOOST_AUTO_TEST_CASE( Map_no_location_position_test ) 
{
        bool exception = false;
        try {
                test_map->getLocationAt(99);
        } catch(...) {
                exception = true;
        }
        BOOST_CHECK_EQUAL(exception, true);
}

BOOST_AUTO_TEST_CASE( Map_location_index_test ) 
{
        bool exception = false;
        try {
                test_map->getLocationIndex(99);
        } catch(...) {
                exception = true;
        }
        BOOST_CHECK_EQUAL(exception, true);
}

BOOST_AUTO_TEST_CASE( Map_location_position_test ) 
{
        bool exception = false;
        try {
                test_map->getLocationPosition(5);
        } catch(...) {
                exception = true;
        }
        BOOST_CHECK_EQUAL(exception, true);
}


	BOOST_AUTO_TEST_CASE ( Map_reload_test )
{
	// remove previously written files
	std::remove(test_filename_xml.c_str());
	std::remove(test_filename_raw.c_str());
	// save the map
	Map::saveToXML(test_map.get(), test_filename_xml, test_file_name);
	Map::saveToRAW(test_map.get(), test_filename_raw);

	// reload the map
	Map* new_map_xml2 = NULL;
	Map* new_map_raw2 = NULL;

	Map::loadFromXML(new_map_xml2, test_filename_xml, test_file_name);
	Map::loadFromRAW(new_map_raw2, test_filename_raw);
	boost::shared_ptr<Map> new_map_xml(new_map_xml2);
	boost::shared_ptr<Map> new_map_raw(new_map_raw2);

	std::remove(test_filename_xml.c_str());
	std::remove(test_filename_raw.c_str());

	new_map_xml->initialize();
	new_map_raw->initialize();

	// should be the same as the old one. (except for the pointer values)
	const std::vector<boost::shared_ptr<Location> > locations_xml = new_map_xml->getLocationVector();
	const std::vector<boost::shared_ptr<Location> > locations_raw = new_map_raw->getLocationVector();

	BOOST_CHECK_EQUAL(new_map_xml->getName(), test_map_name);
	BOOST_CHECK_EQUAL(new_map_raw->getName(), test_map_name);

	BOOST_CHECK_EQUAL(locations_xml.size(), 4);
	BOOST_CHECK_EQUAL(locations_raw.size(), 4);

	for(int i = 0; i < 4; i++) {
		BOOST_CHECK_EQUAL(locations_xml[i]->getName(), test_location_name[i]);
		BOOST_CHECK_EQUAL(locations_xml[i]->getPaths().front()->getTargetLocationPosition(), test_map->getLocation((i+1)%4)->getPosition());
		BOOST_CHECK_EQUAL(locations_xml[i]->getPaths().front()->getDistance(), test_distance[i]);
		BOOST_CHECK_EQUAL(locations_raw[i]->getName(), test_location_name[i]);
		BOOST_CHECK_EQUAL(locations_raw[i]->getPaths().front()->getTargetLocationPosition(), test_map->getLocation((i+1)%4)->getPosition());
		BOOST_CHECK_EQUAL(locations_raw[i]->getPaths().front()->getDistance(), test_distance[i]);
	}

	BOOST_CHECK_EQUAL(locations_xml[1]->getPaths().back()->getTargetLocationPosition(), test_map->getLocation(3)->getPosition());
	BOOST_CHECK_EQUAL(locations_xml[1]->getPaths().back()->getDistance(), test_distance[4]);
	BOOST_CHECK_EQUAL(locations_raw[1]->getPaths().back()->getTargetLocationPosition(), test_map->getLocation(3)->getPosition());
	BOOST_CHECK_EQUAL(locations_raw[1]->getPaths().back()->getDistance(), test_distance[4]);

	new_map_raw->calculateDistanceMap();
	new_map_xml->calculateDistanceMap();

	BOOST_CHECK_EQUAL(new_map_raw->getLocationAt(1)->getAirDistance(new_map_raw->getLocationAt(2)), 9);
	BOOST_CHECK_EQUAL(new_map_raw->getLocationAt(1)->getAirDistance(new_map_raw->getLocationAt(33)), 21);
	BOOST_CHECK_EQUAL(new_map_raw->getLocationAt(1)->getAirDistance(new_map_raw->getLocationAt(5)), 9);
	BOOST_CHECK_EQUAL(new_map_raw->getLocationAt(2)->getAirDistance(new_map_raw->getLocationAt(33)), 13);
	BOOST_CHECK_EQUAL(new_map_raw->getLocationAt(2)->getAirDistance(new_map_raw->getLocationAt(5)), 12);
	BOOST_CHECK_EQUAL(new_map_raw->getLocationAt(33)->getAirDistance(new_map_raw->getLocationAt(5)), 19);

	BOOST_CHECK_EQUAL(new_map_xml->getLocationAt(1)->getAirDistance(new_map_raw->getLocationAt(2)), 9);
	BOOST_CHECK_EQUAL(new_map_xml->getLocationAt(1)->getAirDistance(new_map_raw->getLocationAt(33)), 21);
	BOOST_CHECK_EQUAL(new_map_xml->getLocationAt(1)->getAirDistance(new_map_raw->getLocationAt(5)), 9);
	BOOST_CHECK_EQUAL(new_map_xml->getLocationAt(2)->getAirDistance(new_map_raw->getLocationAt(33)), 13);
	BOOST_CHECK_EQUAL(new_map_xml->getLocationAt(2)->getAirDistance(new_map_raw->getLocationAt(5)), 12);
	BOOST_CHECK_EQUAL(new_map_xml->getLocationAt(33)->getAirDistance(new_map_raw->getLocationAt(5)), 19);
}
	
BOOST_AUTO_TEST_SUITE_END( )
