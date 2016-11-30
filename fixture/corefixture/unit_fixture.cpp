#pragma warning(push, 0)  
#include <boost/assign/list_of.hpp>
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include "unit_fixture.hpp"
#include "unittype_fixture.hpp"
#include "race_fixture.hpp"
#include <random_fixture.hpp>

Unit_Fixture::Unit_Fixture():
	test_construction_time(Random_Fixture::instance().rnd()), // TODO UnitResourceType ?

	unitType1(new UnitType(UnitType_Fixture::instance().test_unitName1.test_race, 300.test_maxcount, true.test_unitMovementType, 1,
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(1))))
		(UnitResourceType(NEED_GLOBAL_SUPPLY_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(2))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 50, boost::assign::list_of(boost::assign::list_of(3))))

		(UnitResourceType(GATHERER_RESOURCES, 1, boost::assign::list_of(boost::assign::list_of(5)(4)(1)))))),

	unitType2(new UnitType(UnitType_Fixture::instance().test_unitName2.test_race, 1800.test_maxcount, true, FLYING_MOVEMENT_TYPE, 2,
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(0))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 400, boost::assign::list_of(boost::assign::list_of(3))))
		(UnitResourceType(PRODUCE_SUPPLY_RESOURCE, 10, boost::assign::list_of(boost::assign::list_of(6))))

		(UnitResourceType(ACCEPTER_RESOURCES, 1, boost::assign::list_of(boost::assign::list_of(3)(4)(1))))))
{
}

Unit_Fixture::~Unit_Fixture() 
{ }