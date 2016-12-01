#ifndef _GOALTEST_PROCESSEDGOALENTRYFIXTURE_HPP
#define _GOALTEST_PROCESSEDGOALENTRYFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <corefixture/player_fixture.hpp>
#include <corefixture/map_fixture.hpp>

#include <games/broodwar.hpp>

#include <goal/processedgoalentry.hpp>

 
struct ProcessedGoalEntry_Fixture
{
public:
	const Player_Fixture playerFixture;
	const Map_Fixture mapFixture;	
	const BroodWar broodwar;

	const boost::shared_ptr<Units> test_units;
	const boost::shared_ptr<Unit> test_unit1;
	const boost::shared_ptr<Unit> test_unit2;
	const boost::shared_ptr<Unit> test_unit3;
	const boost::shared_ptr<Unit> test_unit4;
	
	// we better use an own goal entry object in order to fill it not with random but with proper values for goals (e.g. 1 spacemarine with predictable buildable list as result)
	// we do not need to test random values for goalEntry, we did that already in the goalEntry_test
	const std::string test_goalentry_name;
	const std::list<std::list<std::list<GoalItem> > > test_goalentry_goalitemlist;	
	const boost::shared_ptr<const GoalEntry> test_goalentry;

	boost::shared_ptr<ProcessedGoalEntry> test_processedGoalEntry;

	ProcessedGoalEntry_Fixture();
	virtual ~ProcessedGoalEntry_Fixture();

private:
	const std::list<std::list<std::list<GoalItem> > > init_goalitemlist_helper();
};


#endif // _GOALTEST_PROCESSEDGOALENTRYFIXTURE_HPP
