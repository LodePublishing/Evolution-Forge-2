#pragma warning(push, 0) 
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <units_fixture.hpp>
#include <player_fixture.hpp>
#include <unit_fixture.hpp>
#include <map_fixture.hpp>

BOOST_FIXTURE_TEST_SUITE( Units_test, Units_Fixture )

	BOOST_AUTO_TEST_CASE (Units_constructor )
{
	//TODO evtl UNITs einzeln direkt nur intern in 'units' erstellen...
	
	Units my_units;

	const UnitLocalKey localKey1 = test_unit1->getLocalKey();
	const UnitLocalKey localKey2 = test_unit2->getLocalKey();
	const UnitLocalKey localKey3 = test_unit3->getLocalKey();

	const UnitGlobalKey globalKey1 = test_unit1->getGlobalKey();
	const UnitGlobalKey globalKey2 = test_unit2->getGlobalKey();
	const UnitGlobalKey globalKey3 = test_unit3->getGlobalKey();

	BOOST_CHECK_EQUAL(my_units.getLocalAvailable(localKey1), 2);
	BOOST_CHECK_EQUAL(my_units.getLocalAvailable(localKey2), 2);
	BOOST_CHECK_EQUAL(my_units.getLocalAvailable(localKey3), 1);

	BOOST_CHECK_EQUAL(my_units.getLocalTotal(localKey1), 2);
	BOOST_CHECK_EQUAL(my_units.getLocalTotal(localKey2), 2);
	BOOST_CHECK_EQUAL(my_units.getLocalTotal(localKey3), 1);

	BOOST_CHECK_EQUAL(my_units.getGlobalAvailable(globalKey1), 2);
	BOOST_CHECK_EQUAL(my_units.getGlobalAvailable(globalKey2), 2);
	BOOST_CHECK_EQUAL(my_units.getGlobalAvailable(globalKey3), 1);

	BOOST_CHECK_EQUAL(my_units.getGlobalTotal(globalKey1), 2);
	BOOST_CHECK_EQUAL(my_units.getGlobalTotal(globalKey2), 2);
	BOOST_CHECK_EQUAL(my_units.getGlobalTotal(globalKey3), 1);

	test_unit2->removeUnit();
	test_unit3->removeUnit();

	BOOST_CHECK_EQUAL(my_units.getLocalAvailable(localKey1), 1);
	BOOST_CHECK_EQUAL(my_units.getLocalAvailable(localKey2), 1);
	BOOST_CHECK_EQUAL(my_units.getLocalAvailable(localKey3), 0);

	BOOST_CHECK_EQUAL(my_units.getLocalTotal(localKey1), 1);
	BOOST_CHECK_EQUAL(my_units.getLocalTotal(localKey2), 1);
	BOOST_CHECK_EQUAL(my_units.getLocalTotal(localKey3), 0);

	BOOST_CHECK_EQUAL(my_units.getGlobalAvailable(globalKey1), 1);
	BOOST_CHECK_EQUAL(my_units.getGlobalAvailable(globalKey2), 1);
	BOOST_CHECK_EQUAL(my_units.getGlobalAvailable(globalKey3), 0);

	BOOST_CHECK_EQUAL(my_units.getGlobalTotal(globalKey1), 1);
	BOOST_CHECK_EQUAL(my_units.getGlobalTotal(globalKey2), 1);
	BOOST_CHECK_EQUAL(my_units.getGlobalTotal(globalKey3), 0);

	// start building unit 4 at facility unit 1

	std::list<boost::shared_ptr<Unit> > unit_list;
	unit_list.push_back(test_unit1);

	// unit to build
	boost::shared_ptr<Unit> test_unit4(new Unit(Player_Fixture::instance().test_player.unitType2.test_map->getLocation(1), test_units, 1, test_construction_time, unit_list));
	test_units->addUnit(test_unit4);
	
	BOOST_CHECK_EQUAL(my_units.getLocalAvailable(test_unit1->getLocalKey()), 0);
	BOOST_CHECK_EQUAL(my_units.getLocalAvailable(test_unit4->getLocalKey()), 0);

	BOOST_CHECK_EQUAL(my_units.getLocalTotal(test_unit1->getLocalKey()), 1);
	BOOST_CHECK_EQUAL(my_units.getLocalTotal(test_unit4->getLocalKey()), 1);

	BOOST_CHECK_EQUAL(my_units.getGlobalAvailable(test_unit1->getGlobalKey()), 0);
	BOOST_CHECK_EQUAL(my_units.getGlobalAvailable(test_unit4->getGlobalKey()), 0);

	BOOST_CHECK_EQUAL(my_units.getGlobalTotal(test_unit1->getGlobalKey()), 1);
	BOOST_CHECK_EQUAL(my_units.getGlobalTotal(test_unit4->getGlobalKey()), 1);
	// todo neutral
	// TODO test removing facility where units currently build
	// TODO test removing units that are currently being built
	
	TODO clean up
}

BOOST_AUTO_TEST_SUITE_END( )
