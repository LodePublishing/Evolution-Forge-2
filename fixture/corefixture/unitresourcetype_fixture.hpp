#ifndef _CORETEST_UNITRESOURCETYPEFIXTURE_HPP
#define _CORETEST_UNITRESOURCETYPEFIXTURE_HPP

#include <unitresourcetype.hpp>
#include <enums/unitresourcetypeenums.hpp>

struct UnitResourceType_Fixture
{
	UnitResourceType_Fixture();
	~UnitResourceType_Fixture();

	const eUnitResourceType test_unitResourceType;
	std::list<std::list<unsigned int> > test_unitTypeIDList;
	signed int test_amount;

	UnitResourceType* test_unitresourcetype;

	time_t seed;
};

#endif // _CORETEST_UNITRESOURCETYPEFIXTURE_HPP
