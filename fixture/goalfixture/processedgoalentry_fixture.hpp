#ifndef _GOALTEST_PROCESSEDGOALENTRYFIXTURE_HPP
#define _GOALTEST_PROCESSEDGOALENTRYFIXTURE_HPP

#include <player_fixture.hpp>
#include <map_fixture.hpp>
#include <broodwar.hpp>

#include <boost/smart_ptr.hpp>

#include <random_fixture.hpp>

#include <processedgoalentry.hpp>
 
struct ProcessedGoalEntry_Fixture : public Random_Fixture
{
public:
	ProcessedGoalEntry_Fixture();
	~ProcessedGoalEntry_Fixture();
	
	const Player_Fixture playerFixture;
	const Map_Fixture mapFixture;
	
	const boost::shared_ptr<Broodwar> broodwar;

	// we better use an own goal entry object in order to fill it not with random but with proper values for goals (e.g. 1 spacemarine with predictable buildable list as result)
	// we do not need to test random values for goalEntry, we did that already in the goalEntry_test
	const std::string test_goalentry_name;
	const std::list<std::list<std::list<Goal> > > test_goalentry_goallist;	
	const boost::shared_ptr<const GoalEntry> test_goalentry;
	
	const boost::shared_ptr<Units> test_units;
	const boost::shared_ptr<Unit> test_unit1;
	const boost::shared_ptr<Unit> test_unit2;
	const boost::shared_ptr<Unit> test_unit3;
	const boost::shared_ptr<Unit> test_unit4;
	
	ProcessedGoalEntry* test_processedGoalEntry;

private:
	const std::list<std::list<std::list<Goal> > > init_goallist_helper();
};


#endif // _GOALTEST_PROCESSEDGOALENTRYFIXTURE_HPP
