#pragma warning(push, 0)  
#include <boost/assign/list_of.hpp>
#pragma warning(pop)

#include <random_fixture.hpp>

#include "unitresourcetype_fixture.hpp"


UnitResourceType_Fixture::UnitResourceType_Fixture():
	test_eUnitResourceType((eUnitResourceType)Random_Fixture::instance().rnd()),
	test_amount(Random_Fixture::instance().rnd()),
	test_unitTypeIdList(init_unittypeidlist_helper()),
	test_unitResourceType(boost::shared_ptr<UnitResourceType>(new UnitResourceType(test_eUnitResourceType, test_amount, test_unitTypeIdList)))
{ }

UnitResourceType_Fixture::~UnitResourceType_Fixture() 
{ }

const std::list<std::list<boost::uuids::uuid> > UnitResourceType_Fixture::init_unittypeidlist_helper() {
	const std::list<std::list<boost::uuids::uuid> > unitTypeIdList = boost::assign::list_of
			(boost::assign::list_of(boost::uuids::random_generator()())(boost::uuids::random_generator()()))
			(boost::assign::list_of(boost::uuids::random_generator()()));
	return unitTypeIdList;
}