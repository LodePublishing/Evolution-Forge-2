#pragma warning(push, 0) 
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <unit_fixture.hpp>
#include <map_fixture.hpp>
#include <player_fixture.hpp>

// TODO aufteilen
BOOST_FIXTURE_TEST_SUITE( Unit_test, Unit_Fixture )

	BOOST_AUTO_TEST_CASE (Unit_constructor )
{
	const boost::shared_ptr<Units> test_units(new Units());
	// facility
	boost::shared_ptr<Unit> test_unit1(new Unit(Player_Fixture::instance().test_player, unitType1.test_map->getLocation(0), test_units));
	test_units->addUnit(test_unit1);

	BOOST_CHECK_EQUAL(test_unit1->isConstructing(), false);
	
	std::list<boost::shared_ptr<Unit> > unit_list;
	unit_list.push_back(test_unit1);

	// unit to build
	boost::shared_ptr<Unit> test_unit2(new Unit(Player_Fixture::instance().test_player, unitType2.test_map->getLocation(0), test_units, 1, test_construction_time, unit_list));
	test_units->addUnit(test_unit2);
	
	BOOST_CHECK_EQUAL(test_unit2->getLocation()->getName().test_map->getLocation(0)->getName());
	BOOST_CHECK_EQUAL(test_unit2->getPlayerId().test_player->getId());
	BOOST_CHECK_EQUAL(test_unit2->getRemainingConstructionTime(), test_construction_time);
	BOOST_CHECK_EQUAL(test_unit2->getRemainingMovementTime(), 0);
	BOOST_CHECK_EQUAL(test_unit2->isUnderConstruction(), true);
	BOOST_CHECK_EQUAL(test_unit1->isConstructing(), true);
	
	for(unsigned int i = 0; i < test_construction_time; i++) {
		test_units->process();
	}
	BOOST_CHECK_EQUAL(test_unit2->isUnderConstruction(), false);
	BOOST_CHECK_EQUAL(test_unit1->isConstructing(), false);

	test_unit1->setGoalLocation(Map_Fixture::instance().test_map->getLocation(0));
	test_unit2->setGoalLocation(Map_Fixture::instance().test_map->getLocation(0));
	BOOST_CHECK_EQUAL(test_unit1->getRemainingMovementTime(), 0);
	BOOST_CHECK_EQUAL(test_unit2->getRemainingMovementTime(), 0);

	test_unit1->setGoalLocation(Map_Fixture::instance().test_map->getLocation(1));
	test_unit2->setGoalLocation(Map_Fixture::instance().test_map->getLocation(2));
	unsigned int distance1 = Map_Fixture::instance().test_map->getLocationAt(1)->getGroundDistance(Map_Fixture::instance().test_map->getLocationAt(2));
	unsigned int distance2 = Map_Fixture::instance().test_map->getLocationAt(1)->getAirDistance(Map_Fixture::instance().test_map->getLocationAt(33));
	unsigned int time1 = distance1 / test_unit1->getUnitType()->getSpeed();
	unsigned int time2 = distance2 / test_unit2->getUnitType()->getSpeed();

	for(unsigned int i = 0; i < time1; i++) {
		test_unit1->process();
	}
	BOOST_CHECK_EQUAL(test_unit1->getLocation()->getName().test_map->getLocation(1)->getName());

	for(unsigned int i = 0; i < time2; i++) {
		test_unit2->process();
	}
	BOOST_CHECK_EQUAL(test_unit2->getLocation()->getName().test_map->getLocation(2)->getName());

			
	/*
// unit to build and then cancel
	Unit* test_unit3 = new Unit(unitType2,  test_player, mapFixture.locations[1], test_construction_time, unit_list);

	Location* temp_location = test_unit3->getLocation();
	UnitLocalKey localKey = test_unit3->getLocalKey();

	BOOST_CHECK_EQUAL(temp_location->getGlobalUnits()->getLocalTotal(localKey), 1);
	BOOST_CHECK_EQUAL(test_unit1->isConstructing(), true);
	delete test_unit3; // calls cancelConstruction
	BOOST_CHECK_EQUAL(temp_location->getGlobalUnits()->getLocalTotal(localKey), 0);
	BOOST_CHECK_EQUAL(test_unit1->isConstructing(), false);*/
	// TODO
}

BOOST_AUTO_TEST_SUITE_END( )
