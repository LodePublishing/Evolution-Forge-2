#pragma warning(push, 0) 
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <rules_fixture.hpp>

BOOST_FIXTURE_TEST_SUITE( Rules_test, Rules_Fixture )

	BOOST_AUTO_TEST_CASE (Rules_constructor)
{
	BOOST_CHECK_EQUAL(test_rules->getName(), test_rules_name);
	BOOST_CHECK_EQUAL(test_rules->getRaceList().back().getName(), unitTypeFixture.raceFixture.test_race_name);
	BOOST_CHECK_EQUAL(test_rules->getUnitType(unitType1->getID()).getName(), unitTypeFixture.test_unitName1);
	BOOST_CHECK_EQUAL(test_rules->getUnitType(unitType2->getID()).getName(), unitTypeFixture.test_unitName2);
}

	BOOST_AUTO_TEST_CASE (Rules_reload)
{


	// remove previously written files
	std::remove(test_filename_xml.c_str());
	// save the map
	Rules::saveToXML(*test_rules, test_filename_xml, test_file_name);

	// reload the map
	Rules* new_rules_xml = new Rules("");
	
	Rules::loadFromXML(*new_rules_xml, test_filename_xml, test_file_name);

	std::remove(test_filename_xml.c_str());
	
	new_rules_xml->initializeRaces();
	
	BOOST_CHECK_EQUAL(new_rules_xml->getName(), test_rules_name);
	BOOST_CHECK_EQUAL(new_rules_xml->getRaceList().back().getName(), unitTypeFixture.raceFixture.test_race_name);
	BOOST_CHECK_EQUAL(new_rules_xml->getUnitType(unitType1->getID()).getName(), unitTypeFixture.test_unitName1);
	BOOST_CHECK_EQUAL(new_rules_xml->getUnitType(unitType2->getID()).getName(), unitTypeFixture.test_unitName2);

	delete new_rules_xml;
}

BOOST_AUTO_TEST_SUITE_END( )
