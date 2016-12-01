#pragma warning(push, 0)  
#include <boost/assign/list_of.hpp>
#pragma warning(pop)

#include <misc/randomgenerator.hpp>

#include "unitresourcetype_fixture.hpp"

UnitResourceType_Fixture::UnitResourceType_Fixture():
	test_eUnitResourceType(static_cast<eUnitResourceType>(RandomGenerator::instance().rnd())),
	test_amount(RandomGenerator::instance().rnd()),
	test_unitTypeIdList(init_unittypeidlist_helper()),
	test_unitResourceType(new UnitResourceType(test_eUnitResourceType, test_amount, test_unitTypeIdList))
{ }

UnitResourceType_Fixture::~UnitResourceType_Fixture() 
{ }

const std::list<std::list<boost::uuids::uuid> > UnitResourceType_Fixture::init_unittypeidlist_helper() {
	const std::list<std::list<boost::uuids::uuid> > unitTypeIdList = boost::assign::list_of
			(boost::assign::list_of(boost::uuids::random_generator()())(boost::uuids::random_generator()()))
			(boost::assign::list_of(boost::uuids::random_generator()()));
	return unitTypeIdList;
}
