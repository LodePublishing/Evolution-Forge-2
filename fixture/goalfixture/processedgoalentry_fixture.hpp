#ifndef _GOALTEST_PROCESSEDGOALENTRYFIXTURE_HPP
#define _GOALTEST_PROCESSEDGOALENTRYFIXTURE_HPP

#include <processedgoalentry.hpp>

#include <goalentry_fixture.hpp>
#include <player_fixture.hpp>
#include <map_fixture.hpp>
#include <broodwar.hpp>

struct ProcessedGoalEntry_Fixture
{
	ProcessedGoalEntry_Fixture();
	~ProcessedGoalEntry_Fixture();

	const std::string test_filename_xml;
	const std::string test_file_name;

	const GoalEntry_Fixture goalEntry_Fixture;
	const Player_Fixture player_Fixture;
	const Map_Fixture map_Fixture;
	
	Broodwar* broodwar;

	ProcessedGoalEntry* test_processedGoalEntry;

	time_t seed;
};


#endif // _GOALTEST_PROCESSEDGOALENTRYFIXTURE_HPP
