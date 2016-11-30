#ifndef _CORE_PROCESSEDGOALENTRY_HPP
#define _CORE_PROCESSEDGOALENTRY_HPP

#include <map>

#include <goalentry.hpp>
#include <units.hpp>
#include <rules.hpp>
#include <map.hpp>
#include <player.hpp>

#include "processedgoal.hpp"

class ProcessedGoalEntry
{
public:
	ProcessedGoalEntry(const GoalEntry* const goalEntry, const Player* const player, const Map& map, const Units& startingUnits, const Rules* const rules);
	~ProcessedGoalEntry();

	const std::list<std::list<std::list<Goal> > >& getGoalList() const;
	const std::list<std::list<std::list<Goal> > >& getBonusList() const;
private:
	
	// call as soon as all goals were added
	// recalculate whenever goalentry has changed

	void fillBuildableListAndAddGoals(const Rules* const rules, const Map& map, const Player* const player, const Units& startingUnits); 
	void eraseUnreachableORGoals();
	// fill this list with all goals from goalEntry
	// then add all steps in between as a goal (for fitness calculation)
	std::list<std::list<std::list<Goal> > > goalList;
	std::list<std::list<std::list<Goal> > > bonusList;

	// all unitTypeIDs which buildings are buildable
	std::list<unsigned int> buildableList;

	// all units that could theoretically be build based on the startingUnits
	std::map<UnitLocalNeutralKey, ProcessedGoal> processedGoalMap; // unitTypeID -> location -> buildable/isgoal etc.
	
//		void addSpecialUnitsToBuildableList(); TODO?
//		void recheckTooManyGoals(); for special things like building addons
//		std::vector<unsigned int> phaenoToGenotype;
//		std::vector<unsigned int> genoToPhaenotype;
//		unsigned int maxBuildTypes;
//		unsigned int maxBuildTypesAtStart;

//		std::vector<unsigned int> genoAtStart;
//		std::vector<FacilityNeed> needsAtStart;  TODO
		
// um auch Zwischenziele (z.B. Hydralisks beim morphen oder untere Techstufen (z.B. Infantry Lvl1) zu belohnen!
//		std::vector<unsigned int> bonusTable;

//		void fillBonusTable();
//		void giveBonusTo(const unsigned int unit, unsigned int caller, std::vector< std::vector<bool> >& checked);
//		const bool isError(const unsigned int j, const unsigned int unit) const;
};

#endif
