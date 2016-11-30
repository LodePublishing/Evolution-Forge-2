#pragma warning(push, 0) 
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <rules_fixture.hpp>
#include <unittype_fixture.hpp>

BOOST_FIXTURE_TEST_SUITE( Rules_test, Rules_Fixture )

	BOOST_AUTO_TEST_CASE (Rules_constructor)
{
	BOOST_CHECK_EQUAL(test_rules->getName(), test_rules_name);
	BOOST_CHECK_EQUAL(test_rules->getUnitType(unitTypeFixture.test_unittype->getId())->getName(), unitTypeFixture.test_unittype->getName());
	BOOST_CHECK_EQUAL(test_rules->getUnitType(unitTypeFixture.test_unittype_noncorporeal->getId())->getName(), unitTypeFixture.test_unittype_noncorporeal->getName());
}

	BOOST_AUTO_TEST_CASE (Rules_reload)
{
	// remove previously written files
	std::remove(test_filename_xml.c_str());
	// save the map
	Rules::saveToXML(test_rules.get(), test_filename_xml, test_file_name);

	// reload the map
	Rules* new_rules_xml2 = NULL;	
	Rules::loadFromXML(new_rules_xml2, test_filename_xml, test_file_name);
	boost::shared_ptr<Rules> new_rules_xml(new_rules_xml2);

	std::remove(test_filename_xml.c_str());
		
	BOOST_CHECK_EQUAL(new_rules_xml->getName(), test_rules_name);
	BOOST_CHECK_EQUAL(new_rules_xml->getUnitType(unitTypeFixture.test_unittype->getId())->getName(), unitTypeFixture.test_unittype->getName());
	BOOST_CHECK_EQUAL(new_rules_xml->getUnitType(unitTypeFixture.test_unittype_noncorporeal->getId())->getName(), unitTypeFixture.test_unittype_noncorporeal->getName());
}

BOOST_AUTO_TEST_SUITE_END( )
