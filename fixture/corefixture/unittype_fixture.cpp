#pragma warning(push, 0)  
#include <boost/assign/list_of.hpp>
#pragma warning(pop)

#include <random_fixture.hpp>
#include <globalstorage.hpp>

#include "unittype_fixture.hpp"


UnitType_Fixture::UnitType_Fixture():
	raceFixture(),

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

	test_unitID1(boost::uuids::random_generator()()),
	test_unitID2(boost::uuids::random_generator()()),
	test_unitID3(boost::uuids::random_generator()()),
	test_unitID4(boost::uuids::random_generator()()),
	test_unitID5(boost::uuids::random_generator()()),

	test_amount1(Random_Fixture::instance().rnd()),
	test_amount2(Random_Fixture::instance().rnd()),
	test_amount3(Random_Fixture::instance().rnd()),

	test_resources(init_resourceslist_helper()),

	test_unittype(boost::shared_ptr<UnitType>(new UnitType(test_unitName1, raceFixture.test_race, test_buildtime, test_maxcount, true, test_unitMovementType, test_speed, test_resources))),
	test_unittype_noncorporeal(boost::shared_ptr<UnitType>(new UnitType(test_unitName2, raceFixture.test_race, test_buildtime, test_maxcount, false, NO_MOVEMENT_TYPE, 0, test_resources)))
{ 
	GlobalStorage::instance().addUnitType(test_unittype);
	GlobalStorage::instance().addUnitType(test_unittype_noncorporeal);
}

UnitType_Fixture::~UnitType_Fixture() 
{
	GlobalStorage::instance().removeUnitType(test_unittype->getId());
	GlobalStorage::instance().removeUnitType(test_unittype_noncorporeal->getId());
}

const std::list<UnitResourceType> UnitType_Fixture::init_resourceslist_helper() {
	const std::list<UnitResourceType> resourcesList = boost::assign::list_of
		(UnitResourceType(test_resourceType1, test_amount1, boost::assign::list_of(boost::assign::list_of(test_unitID1))))
		(UnitResourceType(test_resourceType2, test_amount2, boost::assign::list_of(boost::assign::list_of(test_unitID2))(boost::assign::list_of(test_unitID3))))
		(UnitResourceType(test_resourceType3, test_amount3, boost::assign::list_of(boost::assign::list_of(test_unitID4)(test_unitID5))));
	return resourcesList;
}

// TODO vielleicht hier eine allgemeine Prüffunktion rein