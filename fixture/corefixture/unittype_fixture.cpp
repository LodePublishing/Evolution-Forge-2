#pragma warning(push, 0)  
#include <boost/assign/list_of.hpp>
#pragma warning(pop)

#include <misc/randomgenerator.hpp>

#include "unittype_fixture.hpp"
#include <core/unittype_storage.hpp>
#include <core/core_directories.hpp>

UnitType_Fixture::UnitType_Fixture():
	raceFixture(),

	test_unitName1("Test Unit Name" + RandomGenerator::instance().rndString()), 
	test_unitName2("Test Unit Name" + RandomGenerator::instance().rndString()), 
	test_buildtime(RandomGenerator::instance().rnd()),
	test_maxcount(RandomGenerator::instance().rnd()),

	test_speed(RandomGenerator::instance().rnd()),
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

	test_amount1(RandomGenerator::instance().rnd()),
	test_amount2(RandomGenerator::instance().rnd()),
	test_amount3(RandomGenerator::instance().rnd()),

	test_resources(init_resourceslist_helper()),

	test_unittype(new UnitType(test_unitName1, raceFixture.test_race, test_resources, true, test_maxcount, test_buildtime, test_unitMovementType, test_speed)),
	test_unittype_noncorporeal(new UnitType(test_unitName2, raceFixture.test_race, test_resources, false, test_maxcount, test_buildtime, NO_MOVEMENT_TYPE, 0)),
	test_unitTypeMap(init_unittypemap_helper())
{
	CoreDirectories::initTemp("temp");

	UnitTypeStorage::instance(test_unitTypeMap);	
}

UnitType_Fixture::~UnitType_Fixture() 
{ 
	CoreDirectories::initTemp("temp");

	UnitTypeStorage::clear();

	CoreDirectories::init();
}

const std::list<UnitResourceType> UnitType_Fixture::init_resourceslist_helper() {
	const std::list<UnitResourceType> resourcesList = boost::assign::list_of
		(UnitResourceType(test_resourceType1, test_amount1, boost::assign::list_of(boost::assign::list_of(test_unitID1))))
		(UnitResourceType(test_resourceType2, test_amount2, boost::assign::list_of(boost::assign::list_of(test_unitID2))(boost::assign::list_of(test_unitID3))))
		(UnitResourceType(test_resourceType3, test_amount3, boost::assign::list_of(boost::assign::list_of(test_unitID4)(test_unitID5))));
	return resourcesList;
}

// TODO vielleicht hier eine allgemeine Prüffunktion rein


const std::map<const boost::uuids::uuid, const boost::shared_ptr<const UnitType> > UnitType_Fixture::init_unittypemap_helper() {
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const UnitType> > unitTypeMap;
	unitTypeMap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const UnitType> >(test_unittype->getId(), test_unittype));
	unitTypeMap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const UnitType> >(test_unittype_noncorporeal->getId(), test_unittype_noncorporeal));
	return unitTypeMap;
}