#pragma warning(push, 0)  
#include <boost/assign/list_of.hpp>
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include "unitresourcetype_fixture.hpp"
#include <random_fixture.hpp>

UnitResourceType_Fixture::UnitResourceType_Fixture():
	test_eUnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE),
	test_amount(Random_Fixture::instance().rnd()),
	test_unitTypeIdList(init_unittypeidlist_helper()),
	test_unitResourceType(boost::shared_ptr<UnitResourceType>(new UnitResourceType(test_eUnitResourceType, test_amount, test_unitTypeIdList)))
{
}

UnitResourceType_Fixture::~UnitResourceType_Fixture() 
{
}

const std::list<std::list<unsigned int> > UnitResourceType_Fixture::init_unittypeidlist_helper() {
	const std::list<std::list<unsigned int> > unitTypeIdList = boost::assign::list_of
			(boost::assign::list_of(Random_Fixture::instance().rnd())(Random_Fixture::instance().rnd()))
			(boost::assign::list_of(Random_Fixture::instance().rnd()));
	return unitTypeIdList;
}