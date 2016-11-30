#pragma warning(push, 0)  
#include <boost/assign/list_of.hpp>
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include "unitresourcetype_fixture.hpp"

UnitResourceType_Fixture::UnitResourceType_Fixture():
	Random_Fixture(),
	test_unitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE),
	test_amount(rnd()),
	test_unitTypeIdList(init_unittypeidlist_helper()),
	test_unitresourcetype(boost::shared_ptr<UnitResourceType>(new UnitResourceType(test_unitResourceType, test_amount, test_unitTypeIdList)))
{
}

UnitResourceType_Fixture::~UnitResourceType_Fixture() 
{
}

const std::list<std::list<unsigned int> > UnitResourceType_Fixture::init_unittypeidlist_helper() {
	const std::list<std::list<unsigned int> > unitTypeIdList = boost::assign::list_of
			(boost::assign::list_of(rnd())(rnd()))
			(boost::assign::list_of(rnd()));
	return unitTypeIdList;
}