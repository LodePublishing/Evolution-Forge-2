#pragma warning(push, 0) 
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <unitresourcetype_fixture.hpp>


BOOST_FIXTURE_TEST_SUITE( UnitResourceType_test, UnitResourceType_Fixture )

BOOST_AUTO_TEST_CASE (UnitResourceType_constructor)
{
	BOOST_CHECK_EQUAL(test_unitresourcetype->getResourceType(), test_unitResourceType);
	BOOST_CHECK_EQUAL(test_unitresourcetype->getAmount(), test_amount);
	BOOST_CHECK_EQUAL(test_unitresourcetype->getUnitTypeIDList().front().front(), test_unitTypeIDList.front().front());
	BOOST_CHECK_EQUAL(test_unitresourcetype->getUnitTypeIDList().front().back(), test_unitTypeIDList.front().back());
	BOOST_CHECK_EQUAL(test_unitresourcetype->getUnitTypeIDList().back().front(), test_unitTypeIDList.back().front());
}


BOOST_AUTO_TEST_SUITE_END( )
