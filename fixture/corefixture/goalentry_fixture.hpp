#ifndef _CORETEST_GOALENTRYFIXTURE_HPP
#define _CORETEST_GOALENTRYFIXTURE_HPP

#include <string>

#include <goalentry.hpp>

struct GoalEntry_Fixture
{
	GoalEntry_Fixture();
	~GoalEntry_Fixture();
	const std::string test_goalentry_name;
	std::list<std::list<std::list<Goal> > > test_goalentry_goallist;
	GoalEntry* test_goalentry;
	time_t seed;
};



#endif // _CORETEST_PLAYERFIXTURE_HPP
