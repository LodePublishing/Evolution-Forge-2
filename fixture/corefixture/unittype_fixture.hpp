#ifndef _CORETEST_UNITTYPEFIXTURE_HPP
#define _CORETEST_UNITTYPEFIXTURE_HPP

#include <string>

#include <unittype.hpp>

#include "race_fixture.hpp"

struct UnitType_Fixture
{
	UnitType_Fixture();
	~UnitType_Fixture();

	const Race_Fixture raceFixture;

	const std::string test_unitName1;
	const std::string test_unitName2;
	
	unsigned int test_buildtime;
	unsigned int test_maxcount;
	const eUnitMovementType test_unitMovementType;
	unsigned int test_speed;

	const eUnitMovementType test_default_movementType;
	unsigned int test_default_speed;
	const eUnitMovementType test_movementType;

	const eUnitResourceType test_resourceType1;
	const eUnitResourceType test_resourceType2;
	const eUnitResourceType test_resourceType3;

	unsigned int test_unitID1;
	unsigned int test_unitID2;
	unsigned int test_unitID3;
	unsigned int test_unitID4;
	unsigned int test_unitID5;

	signed int test_amount1;
	signed int test_amount2;
	signed int test_amount3;


	std::list<UnitResourceType> test_resources;

	time_t seed;
};

#endif // _CORETEST_UNITTYPEFIXTURE_HPP
