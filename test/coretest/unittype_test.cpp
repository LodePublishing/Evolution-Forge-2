#pragma warning(push, 0) 
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <unittype_fixture.hpp>
#include <race_fixture.hpp>

// TODO vielleicht hier eine allgemeine Prüffunktion rein


BOOST_FIXTURE_TEST_SUITE( UnitType_test, UnitType_Fixture )

	BOOST_AUTO_TEST_CASE (UnitType_constructor )
{
	UnitType* test_unittype = new UnitType(test_unitName1.test_race, test_buildtime, test_maxcount, true, test_unitMovementType, test_speed, test_resources);

	BOOST_CHECK_EQUAL(test_unittype->getMovementType(), test_unitMovementType);
	BOOST_CHECK_EQUAL(test_unittype->getSpeed(), test_speed);
	BOOST_CHECK_EQUAL(test_unittype->isCorporeal(), true);
	BOOST_CHECK_EQUAL(test_unittype->getMaxCount(), test_maxcount);
	BOOST_CHECK_EQUAL(test_unittype->getName(), test_unitName1);
	BOOST_CHECK_EQUAL(test_unittype->getRace()->getName().test_race_name);

	BOOST_CHECK_EQUAL(test_unittype->getResources().front().getAmount(), test_amount1);
	BOOST_CHECK_EQUAL(test_unittype->getResources().back().getAmount(), test_amount3);

	std::list<UnitResourceType> unitResourceType = test_unittype->getResources();

	BOOST_CHECK_EQUAL(unitResourceType.front().getResourceType(), test_resourceType1);

	BOOST_CHECK_EQUAL(unitResourceType.front().getUnitTypeIDList().front().front(), test_unitID1);
	unitResourceType.pop_front();

	BOOST_CHECK_EQUAL(unitResourceType.front().getResourceType(), test_resourceType2);
	BOOST_CHECK_EQUAL(unitResourceType.front().getUnitTypeIDList().front().front(), test_unitID2);
	BOOST_CHECK_EQUAL(unitResourceType.front().getUnitTypeIDList().back().front(), test_unitID3);
	unitResourceType.pop_front();

	BOOST_CHECK_EQUAL(unitResourceType.front().getResourceType(), test_resourceType3);
	BOOST_CHECK_EQUAL(unitResourceType.front().getUnitTypeIDList().front().front(), test_unitID4);
	BOOST_CHECK_EQUAL(unitResourceType.front().getUnitTypeIDList().front().back(), test_unitID5);

	delete test_unittype;
}

	BOOST_AUTO_TEST_CASE (UnitType_notcorporeal_constructor )
{
	UnitType* test_unittype = new UnitType(test_unitName2.test_race, test_buildtime, test_maxcount, false, NO_MOVEMENT_TYPE, 0, test_resources);

	BOOST_CHECK_EQUAL(test_unittype->getMaxCount(), test_maxcount);
	BOOST_CHECK_EQUAL(test_unittype->getName(), test_unitName2);
	BOOST_CHECK_EQUAL(test_unittype->getRace()->getName().test_race_name);

	std::list<UnitResourceType> unitResourceType = test_unittype->getResources();

	
	BOOST_CHECK_EQUAL(unitResourceType.front().getAmount(), test_amount1);
	BOOST_CHECK_EQUAL(unitResourceType.front().getResourceType(), test_resourceType1);
	BOOST_CHECK_EQUAL(unitResourceType.front().getUnitTypeIDList().front().front(), test_unitID1);
	unitResourceType.pop_front();

	BOOST_CHECK_EQUAL(unitResourceType.front().getAmount(), test_amount2);
	BOOST_CHECK_EQUAL(unitResourceType.front().getResourceType(), test_resourceType2);
	BOOST_CHECK_EQUAL(unitResourceType.front().getUnitTypeIDList().front().front(), test_unitID2);
	BOOST_CHECK_EQUAL(unitResourceType.front().getUnitTypeIDList().back().front(), test_unitID3);
	unitResourceType.pop_front();

	BOOST_CHECK_EQUAL(unitResourceType.front().getAmount(), test_amount3);
	BOOST_CHECK_EQUAL(unitResourceType.front().getResourceType(), test_resourceType3);
	BOOST_CHECK_EQUAL(unitResourceType.front().getUnitTypeIDList().front().front(), test_unitID4);
	BOOST_CHECK_EQUAL(unitResourceType.front().getUnitTypeIDList().front().back(), test_unitID5);

	BOOST_CHECK_EQUAL(test_unittype->isCorporeal(), false);

	delete test_unittype;
}


BOOST_AUTO_TEST_SUITE_END( )
