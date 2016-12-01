#ifndef _COREFIXTURE_GOALENTRYFIXTURE_HPP
#define _COREFIXTURE_GOALENTRYFIXTURE_HPP

#include <string>

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <goal/goalentry.hpp>

struct GoalEntry_Fixture
{
	const std::string test_goalentry_name;

	const std::list<std::list<std::list<GoalItem> > > test_goalentry_goalitemlist;
	
	const boost::shared_ptr<const GoalEntry> test_goalentry;
	
	GoalEntry_Fixture();
	virtual ~GoalEntry_Fixture();

private:
	const std::list<std::list<std::list<GoalItem> > > init_goalitemlist_helper();	
};

#endif // _COREFIXTURE_PLAYERFIXTURE_HPP
