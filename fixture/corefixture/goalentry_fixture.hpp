#ifndef _COREFIXTURE_GOALENTRYFIXTURE_HPP
#define _COREFIXTURE_GOALENTRYFIXTURE_HPP

#include <string>

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <goalentry.hpp>

struct GoalEntry_Fixture
{
	const std::string test_goalentry_name;

	const std::list<std::list<std::list<Goal> > > test_goalentry_goallist;
	
	const boost::shared_ptr<const GoalEntry> test_goalentry;
	
	GoalEntry_Fixture();
	~GoalEntry_Fixture();

private:
	const std::list<std::list<std::list<Goal> > > init_goallist_helper();	
};

#endif // _COREFIXTURE_PLAYERFIXTURE_HPP
