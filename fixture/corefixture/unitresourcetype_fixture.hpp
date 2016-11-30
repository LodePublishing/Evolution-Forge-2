#ifndef _COREFIXTURE_UNITRESOURCETYPEFIXTURE_HPP
#define _COREFIXTURE_UNITRESOURCETYPEFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <unitresourcetype.hpp>
#include <enums/unitresourcetypeenums.hpp>

#include <random_fixture.hpp>

struct UnitResourceType_Fixture : public Random_Fixture
{
public:
	UnitResourceType_Fixture();
	~UnitResourceType_Fixture();

	const eUnitResourceType test_unitResourceType;
	signed int test_amount;
	const std::list<std::list<unsigned int> > test_unitTypeIdList;	

	const boost::shared_ptr<const UnitResourceType> test_unitresourcetype;

private:
	const std::list<std::list<unsigned int> > init_unittypeidlist_helper();
};

#endif // _COREFIXTURE_UNITRESOURCETYPEFIXTURE_HPP
