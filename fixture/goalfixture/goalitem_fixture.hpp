#ifndef _COREFIXTURE_GOALITEMFIXTURE_HPP
#define _COREFIXTURE_GOALITEMFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <goal/goalitem.hpp>


struct GoalItem_Fixture
{
	const boost::uuids::uuid test_unitTypeId;
	const boost::uuids::uuid test_locationId;

	const unsigned int test_count;
	const unsigned int test_time;

	const boost::shared_ptr<const GoalItem> test_goalitem;

	GoalItem_Fixture();
	virtual ~GoalItem_Fixture();
};

#endif // _COREFIXTURE_GOALITEMFIXTURE_HPP
