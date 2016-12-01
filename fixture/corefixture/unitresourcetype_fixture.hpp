#ifndef _CORE_FIXTURE_UNITRESOURCETYPEFIXTURE_HPP
#define _CORE_FIXTURE_UNITRESOURCETYPEFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <core/unitresourcetype.hpp>

#include <core/enums/unitresourcetype.hpp>

struct UnitResourceType_Fixture
{
	const eUnitResourceType test_eUnitResourceType;
	const signed int test_amount;
	const std::list<std::list<boost::uuids::uuid> > test_unitTypeIdList;
	const boost::shared_ptr<const UnitResourceType> test_unitResourceType;

	UnitResourceType_Fixture();
	virtual ~UnitResourceType_Fixture();

private:
	const std::list<std::list<boost::uuids::uuid> > init_unittypeidlist_helper();
};

#endif // _CORE_FIXTURE_UNITRESOURCETYPEFIXTURE_HPP
