#pragma warning(push, 0) 
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <unitresourcetype_fixture.hpp>


BOOST_FIXTURE_TEST_SUITE( UnitResourceType_test, UnitResourceType_Fixture )
	
BOOST_AUTO_TEST_CASE (UnitResourceType_constructor)
{
	BOOST_CHECK_EQUAL(test_unitResourceType->getResourceType(), test_eUnitResourceType);
	BOOST_CHECK_EQUAL(test_unitResourceType->getAmount(), test_amount);
	BOOST_CHECK_EQUAL(test_unitResourceType->getUnitTypeIDList().front().front(), test_unitTypeIdList.front().front());
	BOOST_CHECK_EQUAL(test_unitResourceType->getUnitTypeIDList().front().back(), test_unitTypeIdList.front().back());
	BOOST_CHECK_EQUAL(test_unitResourceType->getUnitTypeIDList().back().front(), test_unitTypeIdList.back().front());
}


BOOST_AUTO_TEST_SUITE_END( )
