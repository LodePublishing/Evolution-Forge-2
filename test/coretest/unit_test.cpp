#pragma warning(push, 0) 
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <unit_fixture.hpp>

// TODO aufteilen
BOOST_FIXTURE_TEST_SUITE( Unit_test, Unit_Fixture )

	BOOST_AUTO_TEST_CASE (Unit_constructor)
{
	// facility
	Unit* test_unit1 = new Unit(unitType1,  test_player, mapFixture.locations[0]);
	BOOST_CHECK_EQUAL(test_unit1->isConstructing(), false);
	
	std::list<Unit*> unit_list;
	unit_list.push_back(test_unit1);

	// unit to build
	Unit* test_unit2 = new Unit(unitType2,  test_player, mapFixture.locations[0], test_construction_time, unit_list);

	BOOST_CHECK_EQUAL(test_unit2->getLocation()->getName(), mapFixture.locations[0]->getName());
	BOOST_CHECK_EQUAL(test_unit2->getPlayer()->getName(), playerFixture.test_player_name);
	BOOST_CHECK_EQUAL(test_unit2->getRemainingConstructionTime(), test_construction_time);
	BOOST_CHECK_EQUAL(test_unit2->getRemainingMovementTime(), 0);
	BOOST_CHECK_EQUAL(test_unit2->isUnderConstruction(), true);
	BOOST_CHECK_EQUAL(test_unit1->isConstructing(), true);
	
	for(unsigned int i = 0; i < test_construction_time; i++) {
		mapFixture.test_units->process();
	}
	BOOST_CHECK_EQUAL(test_unit2->isUnderConstruction(), false);
	BOOST_CHECK_EQUAL(test_unit1->isConstructing(), false);

	test_unit1->setGoalLocation(mapFixture.locations[0]);
	test_unit2->setGoalLocation(mapFixture.locations[0]);
	BOOST_CHECK_EQUAL(test_unit1->getRemainingMovementTime(), 0);
	BOOST_CHECK_EQUAL(test_unit2->getRemainingMovementTime(), 0);

	test_unit1->setGoalLocation(mapFixture.locations[1]);
	test_unit2->setGoalLocation(mapFixture.locations[2]);
	unsigned int distance1 = mapFixture.test_map->getLocationAt(1)->getGroundDistance(mapFixture.test_map->getLocationAt(2));
	unsigned int distance2 = mapFixture.test_map->getLocationAt(1)->getAirDistance(mapFixture.test_map->getLocationAt(33));
	unsigned int time1 = distance1 / test_unit1->getUnitType()->getSpeed();
	unsigned int time2 = distance2 / test_unit2->getUnitType()->getSpeed();

	for(unsigned int i = 0; i < time1; i++) {
		test_unit1->process();
	}
	BOOST_CHECK_EQUAL(test_unit1->getLocation()->getName(), mapFixture.locations[1]->getName());

	for(unsigned int i = 0; i < time2; i++) {
		test_unit2->process();
	}
	BOOST_CHECK_EQUAL(test_unit2->getLocation()->getName(), mapFixture.locations[2]->getName());

			

// unit to build and then cancel
	/*Unit* test_unit3 = new Unit(unitType2,  test_player, mapFixture.locations[1], test_construction_time, unit_list);

	Location* temp_location = test_unit3->getLocation();
	UnitLocalKey localKey = test_unit3->getLocalKey();

	BOOST_CHECK_EQUAL(temp_location->getGlobalUnits()->getLocalTotal(localKey), 1);
	BOOST_CHECK_EQUAL(test_unit1->isConstructing(), true);
	delete test_unit3; // calls cancelConstruction
	//BOOST_CHECK_EQUAL(temp_location->getGlobalUnits()->getLocalTotal(localKey), 0);
	BOOST_CHECK_EQUAL(test_unit1->isConstructing(), false);*/
	// TODO
}

BOOST_AUTO_TEST_SUITE_END( )