#ifndef _COREFIXTURE_UNITTYPEFIXTURE_HPP
#define _COREFIXTURE_UNITTYPEFIXTURE_HPP

#include <string>

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <unittype.hpp>

struct UnitType_Fixture
{
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

	const boost::uuids::uuid test_unitID1;
	const boost::uuids::uuid test_unitID2;
	const boost::uuids::uuid test_unitID3;
	const boost::uuids::uuid test_unitID4;
	const boost::uuids::uuid test_unitID5;

	const signed int test_amount1;
	const signed int test_amount2;
	const signed int test_amount3;

	const std::list<UnitResourceType> test_resources;

	UnitType_Fixture();
	~UnitType_Fixture();
	
private:
	const std::list<UnitResourceType> init_resourceslist_helper();

};

#endif // _COREFIXTURE_UNITTYPEFIXTURE_HPP
