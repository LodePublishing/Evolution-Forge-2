#pragma warning(push, 0) 
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <map_fixture.hpp>

BOOST_FIXTURE_TEST_SUITE( Map_test, Map_Fixture )

	BOOST_AUTO_TEST_CASE ( Map_constructor_test )
{
	BOOST_CHECK_EQUAL(test_map->getName(), test_map_name);
	BOOST_CHECK_EQUAL(locations.size(), 4);

	BOOST_CHECK_EQUAL(test_map->getLocationAt(1)->getAirDistance(test_map->getLocationAt(2)), 9);
	BOOST_CHECK_EQUAL(test_map->getLocationAt(1)->getAirDistance(test_map->getLocationAt(33)), 21);
	BOOST_CHECK_EQUAL(test_map->getLocationAt(1)->getAirDistance(test_map->getLocationAt(5)), 9);
	BOOST_CHECK_EQUAL(test_map->getLocationAt(2)->getAirDistance(test_map->getLocationAt(33)), 13);
	BOOST_CHECK_EQUAL(test_map->getLocationAt(2)->getAirDistance(test_map->getLocationAt(5)), 12);
	BOOST_CHECK_EQUAL(test_map->getLocationAt(33)->getAirDistance(test_map->getLocationAt(5)), 19);

	// TODO ground distance?
}

	BOOST_AUTO_TEST_CASE ( Map_reload_test )
{
	// remove previously written files
	std::remove(test_filename_xml.c_str());
	std::remove(test_filename_raw.c_str());
	// save the map
	Map::saveToXML(*test_map, test_filename_xml, test_file_name);
	Map::saveToRAW(*test_map, test_filename_raw);

	// reload the map
	Map* new_map_xml = new Map("");
	Map* new_map_raw = new Map("");
	Map::loadFromXML(*new_map_xml, test_filename_xml, test_file_name);
	Map::loadFromRAW(*new_map_raw, test_filename_raw);
	std::remove(test_filename_xml.c_str());
	std::remove(test_filename_raw.c_str());

	new_map_xml->initialize();
	new_map_raw->initialize();

	// should be the same as the old one. (except for the pointer values)
	std::vector<Location*> locations_xml = new_map_xml->getLocations();
	std::vector<Location*> locations_raw = new_map_raw->getLocations();

	BOOST_CHECK_EQUAL(new_map_xml->getName(), test_map_name);
	BOOST_CHECK_EQUAL(new_map_raw->getName(), test_map_name);

	BOOST_CHECK_EQUAL(locations_xml.size(), 4);
	BOOST_CHECK_EQUAL(locations_raw.size(), 4);

	for(int i = 0; i < 4; i++) {
		BOOST_CHECK_EQUAL(locations_xml[i]->getName(), test_location_name[i]);
		BOOST_CHECK_EQUAL(locations_xml[i]->getPaths().front()->getTargetLocationPosition(), locations[(i+1)%4]->getPosition());
		BOOST_CHECK_EQUAL(locations_xml[i]->getPaths().front()->getDistance(), test_distance[i]);
		BOOST_CHECK_EQUAL(locations_raw[i]->getName(), test_location_name[i]);
		BOOST_CHECK_EQUAL(locations_raw[i]->getPaths().front()->getTargetLocationPosition(), locations[(i+1)%4]->getPosition());
		BOOST_CHECK_EQUAL(locations_raw[i]->getPaths().front()->getDistance(), test_distance[i]);
	}

	BOOST_CHECK_EQUAL(locations_xml[1]->getPaths().back()->getTargetLocationPosition(), locations[3]->getPosition());
	BOOST_CHECK_EQUAL(locations_xml[1]->getPaths().back()->getDistance(), test_distance[4]);
	BOOST_CHECK_EQUAL(locations_raw[1]->getPaths().back()->getTargetLocationPosition(), locations[3]->getPosition());
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

	delete new_map_xml;
	delete new_map_raw;
}


BOOST_AUTO_TEST_SUITE_END( )
