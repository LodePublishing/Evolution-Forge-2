#pragma warning(push, 0) 
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <unittype_fixture.hpp>


BOOST_FIXTURE_TEST_SUITE( UnitType_test, UnitType_Fixture )

	BOOST_AUTO_TEST_CASE (UnitType_constructor )
{
	BOOST_CHECK_EQUAL(test_unittype->getMovementType(), test_unitMovementType);
	BOOST_CHECK_EQUAL(test_unittype->getSpeed(), test_speed);
	BOOST_CHECK_EQUAL(test_unittype->isCorporeal(), true);
	BOOST_CHECK_EQUAL(test_unittype->getMaxCount(), test_maxcount);
	BOOST_CHECK_EQUAL(test_unittype->getName(), test_unitName1);
	BOOST_CHECK_EQUAL(test_unittype->getRace()->getName(), raceFixture.test_race_name);

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
}

	BOOST_AUTO_TEST_CASE (UnitType_notcorporeal_constructor )
{
	BOOST_CHECK_EQUAL(test_unittype_noncorporeal->getMaxCount(), test_maxcount);
	BOOST_CHECK_EQUAL(test_unittype_noncorporeal->getName(), test_unitName2);
	BOOST_CHECK_EQUAL(test_unittype_noncorporeal->getRace()->getName(), raceFixture.test_race_name);
	BOOST_CHECK_EQUAL(test_unittype_noncorporeal->isCorporeal(), false);

	std::list<UnitResourceType> unitResourceType = test_unittype_noncorporeal->getResources();
	
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
}


BOOST_AUTO_TEST_SUITE_END( )
