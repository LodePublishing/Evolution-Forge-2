#ifndef _GOAL_PROCESSEDGOALENTRY_HPP
#define _GOAL_PROCESSEDGOALENTRY_HPP

#include <map>

#include <core/units.hpp>
#include <core/rules.hpp>
#include <core/map.hpp>
#include <core/player.hpp>

#include "goalentry.hpp"
#include "processedgoal.hpp"


class ProcessedGoalEntry
{
public:
	ProcessedGoalEntry(const boost::shared_ptr<const GoalEntry> goalEntry, const boost::shared_ptr<const Player> player, const boost::shared_ptr<const Map> map, const boost::shared_ptr<const Units> startingUnits, const boost::shared_ptr<const Rules> rules);
	~ProcessedGoalEntry();

	const std::list<std::list<std::list<GoalItem> > >& getGoalList() const;
	const std::map<UnitLocalNeutralKey, ProcessedGoal>& getProcessedGoalMap() const;
	const std::list<boost::uuids::uuid>& getBuildableUnits(const boost::uuids::uuid locationId) const;

	std::string getGoalString() const;
	void addGoalItem(std::list<std::list<GoalItem> >& goalItem);

	void fillBuildableListAndAddGoals(const boost::shared_ptr<const Rules> rules, const boost::shared_ptr<const Map> map, const boost::shared_ptr<const Player> player, const boost::shared_ptr<const Units> startingUnits); 

private:
	void eraseRedundantGoals();
	// call as soon as all goals were added
	// recalculate whenever goalentry has changed

	void eraseUnreachableORGoals();
	// fill this list with all goals from goalEntry
	// then add all steps in between as a goal (for fitness calculation)
	std::list<std::list<std::list<GoalItem> > > goalItemList;
	std::map<const boost::uuids::uuid, std::list<boost::uuids::uuid> > buildableUnits; // location -> unitTypeList

	// TODO Buildable at start
	//TODO once buildableUnits are calculated make a tree, starting with the start units -> this when processing the build order!


	// all units that could theoretically be build based on the startingUnits
	std::map<UnitLocalNeutralKey, ProcessedGoal> processedGoalMap; // unitTypeId -> location -> buildable/isgoal etc.

	void clearProcessedGoalMap(const boost::shared_ptr<const Rules> rules, const boost::shared_ptr<const Map> map);
	void initializeProcessedGoalMap(const boost::shared_ptr<const Player> player, const boost::shared_ptr<const Units> startingUnits);
	void calculateReachableUnits(const boost::shared_ptr<const Rules> rules, const boost::shared_ptr<const Map> map);
	bool checkIfGoalsHaveable() const;

	void uncheckProcessedGoalMap(const boost::shared_ptr<const Rules> rules, const boost::shared_ptr<const Map> map);
	void removeProcessedGoalFromMapIfUnchecked(const boost::shared_ptr<const Rules> rules, const boost::shared_ptr<const Map> map);
	void checkGoalRelated(const boost::shared_ptr<const Rules> rules, const boost::shared_ptr<const Map> map);
	void fillBuildableUnits();

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

inline const std::list<boost::uuids::uuid>& ProcessedGoalEntry::getBuildableUnits(const boost::uuids::uuid locationId) const {
	const std::map<const boost::uuids::uuid, std::list<boost::uuids::uuid> >::const_iterator i = buildableUnits.find(locationId);
	if(i == buildableUnits.end()) {
		throw std::exception();
	}
	return i->second;
}

inline const std::map<UnitLocalNeutralKey, ProcessedGoal>& ProcessedGoalEntry::getProcessedGoalMap() const {
	return processedGoalMap;
}

inline const std::list<std::list<std::list<GoalItem> > >& ProcessedGoalEntry::getGoalList() const {
	return goalItemList;
}


#endif // _GOAL_PROCESSEDGOALENTRY_HPP
