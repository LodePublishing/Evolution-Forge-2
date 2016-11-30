#pragma warning(push, 0)  
#include <boost/assign/list_of.hpp>
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include "unittype_fixture.hpp"
#include <random_fixture.hpp>

UnitType_Fixture::UnitType_Fixture():
	test_unitName1("Test Unit Name1"), 
	test_unitName2("Test Unit Name2"), 
	test_buildtime(Random_Fixture::instance().rnd()),
	test_maxcount(Random_Fixture::instance().rnd()),

	test_speed(Random_Fixture::instance().rnd()),
	test_default_speed(0), 
	test_unitMovementType(GROUND_MOVEMENT_TYPE), 
	test_default_movementType(NO_MOVEMENT_TYPE), 
	test_movementType(GROUND_MOVEMENT_TYPE),
	
	test_resourceType1(NORMAL_GLOBAL_RESOURCE), 
	test_resourceType2(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE), 
	test_resourceType3(GLOBAL_PREREQUISITE_RESOURCE),

	test_unitID1(Random_Fixture::instance().rnd()),
	test_unitID2(Random_Fixture::instance().rnd()),
	test_unitID3(Random_Fixture::instance().rnd()),
	test_unitID4(Random_Fixture::instance().rnd()),
	test_unitID5(Random_Fixture::instance().rnd()),

	test_amount1(Random_Fixture::instance().rnd()),
	test_amount2(Random_Fixture::instance().rnd()),
	test_amount3(Random_Fixture::instance().rnd()),

	test_resources(init_resourceslist_helper())
{ }

UnitType_Fixture::~UnitType_Fixture() 
{ }

const std::list<UnitResourceType> UnitType_Fixture::init_resourceslist_helper() {
	const std::list<UnitResourceType> resourcesList = boost::assign::list_of
		(UnitResourceType(test_resourceType1, test_amount1, boost::assign::list_of(boost::assign::list_of(test_unitID1))))
		(UnitResourceType(test_resourceType2, test_amount2, boost::assign::list_of(boost::assign::list_of(test_unitID2))(boost::assign::list_of(test_unitID3))))
		(UnitResourceType(test_resourceType3, test_amount3, boost::assign::list_of(boost::assign::list_of(test_unitID4)(test_unitID5))));
	return resourcesList;
}

// TODO vielleicht hier eine allgemeine Prüffunktion rein