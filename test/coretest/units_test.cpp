#pragma warning(push, 0) 
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <units_fixture.hpp>
#include <player_fixture.hpp>
#include <unit_fixture.hpp>
#include <map_fixture.hpp>
#include <random_fixture.hpp>

BOOST_FIXTURE_TEST_SUITE( Units_test, Units_Fixture )

	BOOST_AUTO_TEST_CASE (Units_constructor )
{
	//TODO evtl UNITs einzeln direkt nur intern in 'units' erstellen...
	
	const UnitLocalKey localKey1 = test_unit1->getLocalKey();
	const UnitLocalKey localKey2 = test_unit2->getLocalKey();
	const UnitLocalKey localKey3 = test_unit3->getLocalKey();

	const UnitGlobalKey globalKey1 = test_unit1->getGlobalKey();
	const UnitGlobalKey globalKey2 = test_unit2->getGlobalKey();
	const UnitGlobalKey globalKey3 = test_unit3->getGlobalKey();

	BOOST_CHECK_EQUAL(test_units->getLocalAvailable(localKey1), 2);
	BOOST_CHECK_EQUAL(test_units->getLocalAvailable(localKey2), 2);
	BOOST_CHECK_EQUAL(test_units->getLocalAvailable(localKey3), 1);

	BOOST_CHECK_EQUAL(test_units->getLocalTotal(localKey1), 2);
	BOOST_CHECK_EQUAL(test_units->getLocalTotal(localKey2), 2);
	BOOST_CHECK_EQUAL(test_units->getLocalTotal(localKey3), 1);

	BOOST_CHECK_EQUAL(test_units->getGlobalAvailable(globalKey1), 2);
	BOOST_CHECK_EQUAL(test_units->getGlobalAvailable(globalKey2), 2);
	BOOST_CHECK_EQUAL(test_units->getGlobalAvailable(globalKey3), 1);

	BOOST_CHECK_EQUAL(test_units->getGlobalTotal(globalKey1), 2);
	BOOST_CHECK_EQUAL(test_units->getGlobalTotal(globalKey2), 2);
	BOOST_CHECK_EQUAL(test_units->getGlobalTotal(globalKey3), 1);

	test_units->removeUnit(test_unit2);
	test_units->removeUnit(test_unit3);

	BOOST_CHECK_EQUAL(test_units->getLocalAvailable(localKey1), 1);
	BOOST_CHECK_EQUAL(test_units->getLocalAvailable(localKey2), 1);
	BOOST_CHECK_EQUAL(test_units->getLocalAvailable(localKey3), 0);

	BOOST_CHECK_EQUAL(test_units->getLocalTotal(localKey1), 1);
	BOOST_CHECK_EQUAL(test_units->getLocalTotal(localKey2), 1);
	BOOST_CHECK_EQUAL(test_units->getLocalTotal(localKey3), 0);

	BOOST_CHECK_EQUAL(test_units->getGlobalAvailable(globalKey1), 1);
	BOOST_CHECK_EQUAL(test_units->getGlobalAvailable(globalKey2), 1);
	BOOST_CHECK_EQUAL(test_units->getGlobalAvailable(globalKey3), 0);

	BOOST_CHECK_EQUAL(test_units->getGlobalTotal(globalKey1), 1);
	BOOST_CHECK_EQUAL(test_units->getGlobalTotal(globalKey2), 1);
	BOOST_CHECK_EQUAL(test_units->getGlobalTotal(globalKey3), 0);

	// start building unit 4 at facility unit 1

	std::list<boost::shared_ptr<Unit> > unit_list;
	unit_list.push_back(test_unit1);

	// unit to build
	boost::shared_ptr<Unit> test_unit4(boost::shared_ptr<Unit>(new Unit(playerFixture.test_player, broodwar.getRules()->getUnitType(broodwar.unit_id_map.find(Broodwar::SPACE_MARINE)->second), locationFixture.test_location, test_units, 1, test_construction_time, unit_list)));
	test_units->addUnit(test_unit4);
	
	BOOST_CHECK_EQUAL(test_units->getLocalAvailable(test_unit1->getLocalKey()), 0);
	BOOST_CHECK_EQUAL(test_units->getLocalAvailable(test_unit4->getLocalKey()), 0);

	BOOST_CHECK_EQUAL(test_units->getLocalTotal(test_unit1->getLocalKey()), 1);
	BOOST_CHECK_EQUAL(test_units->getLocalTotal(test_unit4->getLocalKey()), 0);

	BOOST_CHECK_EQUAL(test_units->getGlobalAvailable(test_unit1->getGlobalKey()), 0);
	BOOST_CHECK_EQUAL(test_units->getGlobalAvailable(test_unit4->getGlobalKey()), 0);

	BOOST_CHECK_EQUAL(test_units->getGlobalTotal(test_unit1->getGlobalKey()), 1);
	BOOST_CHECK_EQUAL(test_units->getGlobalTotal(test_unit4->getGlobalKey()), 0);
	// todo neutral
	// TODO test removing facility where units currently build
	// TODO test removing units that are currently being built
}

BOOST_AUTO_TEST_CASE (Units_add_units ) 
{
	boost::shared_ptr<Units> test_units2(boost::shared_ptr<Units>(new Units()));
		// unit to build
	boost::shared_ptr<Unit> test_unit5(boost::shared_ptr<Unit>(new Unit(playerFixture.test_player, broodwar.getRules()->getUnitType(broodwar.unit_id_map.find(Broodwar::SCV)->second), locationFixture.test_location, test_units2)));
	test_units2->addUnit(test_unit5);
		// unit to build
	boost::shared_ptr<Unit> test_unit6(boost::shared_ptr<Unit>(new Unit(playerFixture.test_player, broodwar.getRules()->getUnitType(broodwar.unit_id_map.find(Broodwar::SPACE_MARINE)->second), locationFixture.test_location, test_units2)));
	test_units2->addUnit(test_unit6);
	
	test_units->addUnits(test_units2->getUnitList());

	const UnitLocalKey localKey = test_unit5->getLocalKey();
	const UnitGlobalKey globalKey = test_unit5->getGlobalKey();
	
	BOOST_CHECK_EQUAL(test_units->getLocalAvailable(localKey), 3);
	BOOST_CHECK_EQUAL(test_units->getLocalTotal(localKey), 3);
	BOOST_CHECK_EQUAL(test_units->getGlobalAvailable(globalKey), 3);
	BOOST_CHECK_EQUAL(test_units->getGlobalTotal(globalKey), 3);
}

BOOST_AUTO_TEST_SUITE_END( )
