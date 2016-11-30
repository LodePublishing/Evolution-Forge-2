#ifndef _COREFIXTURE_GOALFIXTURE_HPP
#define _COREFIXTURE_GOALFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <goal.hpp>


struct Goal_Fixture
{
	const boost::uuids::uuid test_unitTypeId;
	const boost::uuids::uuid test_locationId;

	const unsigned int test_count;
	const unsigned int test_time;

	const boost::shared_ptr<const Goal> test_goal;
	
	Goal_Fixture();
	virtual ~Goal_Fixture();
};

#endif // _COREFIXTURE_GOALFIXTURE_HPP
