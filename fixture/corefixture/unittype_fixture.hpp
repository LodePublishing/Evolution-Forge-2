#ifndef _COREFIXTURE_UNITTYPEFIXTURE_HPP
#define _COREFIXTURE_UNITTYPEFIXTURE_HPP

#include <string>

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <unittype.hpp>

#include <random_fixture.hpp>

#include "race_fixture.hpp"

struct UnitType_Fixture : public Random_Fixture
{
public:
	UnitType_Fixture();
	~UnitType_Fixture();

	const Race_Fixture raceFixture;

	const std::string test_unitName1;
	const std::string test_unitName2;
	
	const unsigned int test_buildtime;
	const unsigned int test_maxcount;

	const unsigned int test_speed;
	const unsigned int test_default_speed;
	const eUnitMovementType test_unitMovementType;
	const eUnitMovementType test_default_movementType;	
	const eUnitMovementType test_movementType;

	const eUnitResourceType test_resourceType1;
	const eUnitResourceType test_resourceType2;
	const eUnitResourceType test_resourceType3;

	const unsigned int test_unitID1;
	const unsigned int test_unitID2;
	const unsigned int test_unitID3;
	const unsigned int test_unitID4;
	const unsigned int test_unitID5;

	const signed int test_amount1;
	const signed int test_amount2;
	const signed int test_amount3;

	const std::list<UnitResourceType> test_resources;

private:
	const std::list<UnitResourceType> init_resourceslist_helper();
};

#endif // _COREFIXTURE_UNITTYPEFIXTURE_HPP
