#ifndef _COREFIXTURE_UNITRESOURCETYPEFIXTURE_HPP
#define _COREFIXTURE_UNITRESOURCETYPEFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <unitresourcetype.hpp>
#include <enums/unitresourcetypeenums.hpp>

struct UnitResourceType_Fixture
{
	const eUnitResourceType test_eUnitResourceType;
	const signed int test_amount;
	const std::list<std::list<boost::uuids::uuid> > test_unitTypeIdList;
	const boost::shared_ptr<const UnitResourceType> test_unitResourceType;

	UnitResourceType_Fixture();
	~UnitResourceType_Fixture();

private:
	const std::list<std::list<boost::uuids::uuid> > init_unittypeidlist_helper();
};

#endif // _COREFIXTURE_UNITRESOURCETYPEFIXTURE_HPP
