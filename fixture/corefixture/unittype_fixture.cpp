#include <iostream>
#include <time.h>

#pragma warning(push, 0)  
#include <boost/assign/list_of.hpp>
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include "unittype_fixture.hpp"

UnitType_Fixture::UnitType_Fixture():
	raceFixture(),
	test_unitName1("Test Unit Name1"), 
	test_unitName2("Test Unit Name2"), 
	
	test_unitMovementType(GROUND_MOVEMENT_TYPE), 
	test_resourceType1(NORMAL_GLOBAL_RESOURCE), 
	test_resourceType2(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE), 
	test_resourceType3(GLOBAL_PREREQUISITE_RESOURCE),

	test_default_movementType(NO_MOVEMENT_TYPE), 
	test_default_speed(0), 
	test_movementType(GROUND_MOVEMENT_TYPE),

	seed(time(0))
{
	boost::mt19937 generator(static_cast<boost::uint32_t>(seed));
	boost::uniform_int<> distribution(1, 100);
	boost::variate_generator<boost::mt19937&, boost::uniform_int<> > rnd(generator,  distribution); 
	std::cout << "Setting up unit type fixture (seed " << seed << ")" << std::endl;

	test_buildtime = rnd();
	test_maxcount = rnd();
	test_unitID1 = rnd();
	test_unitID2 = rnd();
	test_unitID3 = rnd();
	test_unitID4 = rnd();
	test_unitID5 = rnd();
	test_amount1 = rnd();
	test_amount2 = rnd();
	test_amount3 = rnd();
	test_speed = rnd();

	test_resources.push_back(UnitResourceType(test_resourceType1, boost::assign::list_of(boost::assign::list_of(test_unitID1)), test_amount1));
	test_resources.push_back(UnitResourceType(test_resourceType2, boost::assign::list_of(boost::assign::list_of(test_unitID2))(boost::assign::list_of(test_unitID3)), test_amount2));
	test_resources.push_back(UnitResourceType(test_resourceType3, boost::assign::list_of(boost::assign::list_of(test_unitID4)(test_unitID5)), test_amount3));
}

UnitType_Fixture::~UnitType_Fixture() 
{
	UnitType::resetCounter();
}

// TODO vielleicht hier eine allgemeine Prüffunktion rein