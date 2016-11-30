#ifndef _COREFIXTURE_GOALFIXTURE_HPP
#define _COREFIXTURE_GOALFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <goal.hpp>

#include <random_fixture.hpp>

struct Goal_Fixture : public Random_Fixture
{
	Goal_Fixture();
	~Goal_Fixture();

	unsigned int test_unitTypeId;
	unsigned int test_locationId;

	unsigned int test_count;
	unsigned int test_time;

	const boost::shared_ptr<const Goal> test_goal;
};

#endif // _COREFIXTURE_GOALFIXTURE_HPP
