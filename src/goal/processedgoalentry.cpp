#include "processedgoalentry.hpp"


ProcessedGoalEntry::ProcessedGoalEntry(const GoalEntry* const goalEntry, const Player* const player, const Map& map, const Units& startingUnits, const Rules* const rules)
{
	for(std::list<std::list<std::list<Goal> > >::const_iterator i = goalEntry->getGoalList().begin(); i != goalEntry->getGoalList().end(); i++) {
		std::list<std::list<Goal> > new_goals_1;
		for(std::list<std::list<Goal> >::const_iterator j = i->begin(); j != i->end(); j++) {
			std::list<Goal> new_goals_2;
			for(std::list<Goal>::const_iterator k = j->begin(); k != j->end(); k++) {
				new_goals_2.push_back(Goal(*k));
			}
			new_goals_1.push_back(new_goals_2);
		}
		goalList.push_back(new_goals_1);
	}

	fillBuildableListAndAddGoals(rules, map, player, startingUnits);	
}

ProcessedGoalEntry::~ProcessedGoalEntry() {
	goalList.clear();
	processedGoalMap.clear();
}

// fill processedGoalList and goalList
void ProcessedGoalEntry::fillBuildableListAndAddGoals(const Rules* const rules, const Map& map, const Player* const player, const Units& startingUnits)
{

	// run through all unitTypeIDs and set them to false at the beginning

	for(std::vector<Location*>::const_iterator i = map.getLocations().begin(); i != map.getLocations().end(); i++) {
		for(std::map<unsigned int, UnitType>::const_iterator j = rules->getUnitTypeMap().begin(); j != rules->getUnitTypeMap().end(); j++) {
			processedGoalMap.insert(std::pair<UnitLocalNeutralKey, ProcessedGoal>(UnitLocalNeutralKey((*i)->getID(), j->first), ProcessedGoal(false, false, false)));
		}
	}

	for(std::list<Unit*>::const_iterator i = startingUnits.getUnitList().begin(); i != startingUnits.getUnitList().end(); i++) {
		if((*i)->getPlayerId() == player->getID()) {
			processedGoalMap[UnitLocalNeutralKey((*i)->getLocationId(), (*i)->getUnitTypeId())].setHaveable(true);
		}
	}

	// fill the reachableUnitTypeMap with all units that can be reached! (ignoring the goals)

	// repeat until there is no more change
	bool change = true;
	while(change) {
		change = false;
		for(std::vector<Location*>::const_iterator location = map.getLocations().begin(); location != map.getLocations().end(); location++) {
			for(std::map<unsigned int, UnitType>::const_iterator i = rules->getUnitTypeMap().begin(); i != rules->getUnitTypeMap().end(); i++) {

				UnitLocalNeutralKey unitLocalNeutralKey((*location)->getID(), i->first);

				// we have already checked this one
				if(processedGoalMap[unitLocalNeutralKey].isBuildable()) {
					continue;
				}

				const UnitType& unitType = rules->getUnitType(i->first);

				bool buildable = true;

				// also add these unit types to the map if the current unit itself is buildable. Again, only add those units if th
				std::list<UnitLocalNeutralKey> alsoProduce; 


				for(std::list<UnitResourceType>::const_iterator j = unitType.getResources().begin(); j != unitType.getResources().end(); j++) {

					if(!buildable) {
						break;
					}

					switch(j->getResourceType()) {
					case NOT_BUILDABLE:buildable = false;break; // neutral units

						// ignore
					case PRODUCE_SUPPLY_RESOURCE:break;
					case SUPPLY_PROVIDER:break;
					case ACCEPTER_RESOURCES:break;
					case GATHERER_RESOURCES:break;
					case SOURCE_RESOURCES:break;

					case FACILITY_IS_LOST_RESOURCE:
					case NEUTRAL_FACILITY_IS_LOST_RESOURCE:
					case FACILITY_IS_MORPHING_RESOURCE:
					case FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE:
					case FACILITY_IS_NEEDED_ALWAYS_RESOURCE:
					case GLOBAL_FACILITY_IS_MORPHING_RESOURCE:
					case NORMAL_GLOBAL_RESOURCE:
					case NEED_GLOBAL_SUPPLY_RESOURCE:
					case GLOBAL_PREREQUISITE_RESOURCE:
					case LOCAL_PREREQUISITE_RESOURCE: // location is ignored, just see if we can build the unit at all
					case RESOURCE_RESOURCES:
						{
							bool anyReachable = false;

							for(std::list<std::list<unsigned int> >::const_iterator k = j->getUnitTypeIDList().begin(); k != j->getUnitTypeIDList().end(); k++) {
								bool allReachable = true;
								for(std::list<unsigned int>::const_iterator l = k->begin(); l != k->end(); l++) {
									if(!processedGoalMap[UnitLocalNeutralKey((*location)->getID(), *l)].isHaveable()) {
										allReachable = false;
										break;
									}
								}
							}

							if(!anyReachable) {
								buildable = false;
							} 
						}
						break;


					case UNIT_CREATE_RESOURCE:
						for(std::list<std::list<unsigned int> >::const_iterator k = j->getUnitTypeIDList().begin(); k != j->getUnitTypeIDList().end(); k++) {
							for(std::list<unsigned int>::const_iterator l = k->begin(); l != k->end(); l++) {
								alsoProduce.push_back(UnitLocalNeutralKey((*location)->getID(), *l));
							}
						}
						break;

					case AFFECTS_RESOURCE_GATHERING_LOCALLY:break; // ignore
					case AFFECTS_RESOURCE_GATHERING_GLOBALLY:break; // ignore

					default:assert(false);break;
					}
				}

				// no prerequisite failed -> allow build
				if(buildable) {

					processedGoalMap[UnitLocalNeutralKey((*location)->getID(), i->second.getID())].setBuildable(true);

					for(std::list<UnitLocalNeutralKey>::const_iterator j = alsoProduce.begin(); j != alsoProduce.end(); j++) {
						processedGoalMap[*j].setHaveable(true);
					}

					change = true;
				}
			}
		}
	}

	// now we know for each location what buildings we can build there!
	// TODO movement buildings/orders!

	// first: check if all goals are haveable (if not then the goal is impossible! call an exception

	for(std::list<std::list<std::list<Goal> > >::const_iterator i = goalList.begin(); i != goalList.end(); i++) {
		bool any_fulfilled = false;
		for(std::list<std::list<Goal> >::const_iterator j = i->begin(); j != i->end(); j++) {
			bool all_fulfilled = true;
			for(std::list<Goal>::const_iterator k = j->begin(); k != j->end(); k++) {
				if(!processedGoalMap[UnitLocalNeutralKey(k->getLocationID(), k->getUnitTypeID())].isHaveable()) {
					all_fulfilled = false;
				}
			}
			if(all_fulfilled) {
				any_fulfilled = true;
			}
		}
		if(!any_fulfilled) {
			assert(false);
			//throw std::exception("Goal is not buildable!");
		}
	}


	eraseUnreachableORGoals();

	// third: create AND/OR goals on the base of all existing goals, only look at the haveable entities, start with the goals itself ("build" the prerequisites as goals)
	// loop through all goal elements

	change = true;

	while(change) {
		change = false;

		// second: remove unbuildable goals (only affects OR goals!), maybe move below?

		std::list<std::list<std::list<Goal> > > newGoalList;

		// loop through all goal elements
		for(std::list<std::list<std::list<Goal> > >::iterator i = goalList.begin(); i != goalList.end(); ) {
			// loop through all OR goals (we [now!] know all OR goals are fully fulfilled!)
			for(std::list<std::list<Goal> >::const_iterator j = i->begin(); j != i->end(); ) {
				for(std::list<Goal>::const_iterator k = j->begin(); k != j->end(); k++) {
					// loop through all prerequisites, add OR goals if necessary

					const UnitType& unitType = rules->getUnitType(k->getUnitTypeID());
					for(std::list<UnitResourceType>::const_iterator l = unitType.getResources().begin(); l != unitType.getResources().end(); l++) {

						switch(l->getResourceType()) {
						case NOT_BUILDABLE:break; // neutral units

							// ignore
						case PRODUCE_SUPPLY_RESOURCE:break;
						case SUPPLY_PROVIDER:break;
						case ACCEPTER_RESOURCES:break;
						case GATHERER_RESOURCES:break;
						case SOURCE_RESOURCES:break;

						case NEUTRAL_FACILITY_IS_LOST_RESOURCE:break; // ignore




						case FACILITY_IS_LOST_RESOURCE:
						case FACILITY_IS_MORPHING_RESOURCE:
							{
								std::list<std::list<Goal> > orGoal;
								for(std::list<std::list<unsigned int> >::const_iterator m = l->getUnitTypeIDList().begin(); m != l->getUnitTypeIDList().end(); m++) {
									std::list<Goal> andGoal;
									for(std::list<unsigned int>::const_iterator n = m->begin(); n != m->end(); n++) {
										andGoal.push_back(Goal(*n, k->getLocationID(), 0)); // 0 = bonus
									}
									orGoal.push_back(andGoal);
								}
								newGoalList.push_back(orGoal);
							}
							break;


							// OR goal bonus auf alle locations
						case GLOBAL_FACILITY_IS_MORPHING_RESOURCE:
							{
								std::list<std::list<Goal> > orGoal;
								for(std::list<std::list<unsigned int> >::const_iterator m = l->getUnitTypeIDList().begin(); m != l->getUnitTypeIDList().end(); m++) {
									for(std::vector<Location*>::const_iterator i = map.getLocations().begin(); i != map.getLocations().end(); i++) {
										std::list<Goal> andGoal;
										for(std::list<unsigned int>::const_iterator n = m->begin(); n != m->end(); n++) {
											andGoal.push_back(Goal(*n, (*i)->getID(), 0)); // 0 = bonus
										}
										orGoal.push_back(andGoal);
									}
								}
								newGoalList.push_back(orGoal);
							}
							break;						

						case LOCAL_PREREQUISITE_RESOURCE:
						case RESOURCE_RESOURCES:
						case FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE:
						case FACILITY_IS_NEEDED_ALWAYS_RESOURCE:	
							{
								std::list<std::list<Goal> > orGoal;
								for(std::list<std::list<unsigned int> >::const_iterator m = l->getUnitTypeIDList().begin(); m != l->getUnitTypeIDList().end(); m++) {
									std::list<Goal> andGoal;
									for(std::list<unsigned int>::const_iterator n = m->begin(); n != m->end(); n++) {
										andGoal.push_back(Goal(*n, k->getLocationID(), 1)); // 1 = goal
									}
									orGoal.push_back(andGoal);
								}
								newGoalList.push_back(orGoal);
							}
							break;

						case NEED_GLOBAL_SUPPLY_RESOURCE: 			
						case NORMAL_GLOBAL_RESOURCE: // global resource
						case GLOBAL_PREREQUISITE_RESOURCE: // global resource, look anywhere
							{
								std::list<std::list<Goal> > orGoal;
								for(std::list<std::list<unsigned int> >::const_iterator m = l->getUnitTypeIDList().begin(); m != l->getUnitTypeIDList().end(); m++) {
									for(std::vector<Location*>::const_iterator i = map.getLocations().begin(); i != map.getLocations().end(); i++) {
										std::list<Goal> andGoal;
										for(std::list<unsigned int>::const_iterator n = m->begin(); n != m->end(); n++) {
											andGoal.push_back(Goal(*n, (*i)->getID(), 1)); // 1 = goal
										}
										orGoal.push_back(andGoal);
									}
								}
								newGoalList.push_back(orGoal);
							}
							break;				


						case UNIT_CREATE_RESOURCE:break; // ignore
						case AFFECTS_RESOURCE_GATHERING_LOCALLY:break; // ignore
						case AFFECTS_RESOURCE_GATHERING_GLOBALLY:break; // ignore

						default:assert(false);break;
						}
					}

				}
			}
		}

		goalList.splice(goalList.end(), newGoalList);

		// remove double entries TODO later... test and see how many doubles we have

		eraseUnreachableORGoals();
	}
}

// TODO remove double goals?

void ProcessedGoalEntry::eraseUnreachableORGoals() {
	for(std::list<std::list<std::list<Goal> > >::iterator i = goalList.begin(); i != goalList.end(); ) {

		// loop through all OR goals
		for(std::list<std::list<Goal> >::iterator j = i->begin(); j != i->end(); ) {
			bool all_fulfilled = true;
			for(std::list<Goal>::const_iterator k = j->begin(); k != j->end(); k++) {
				if(!processedGoalMap[UnitLocalNeutralKey(k->getLocationID(), k->getUnitTypeID())].isHaveable()) {
					all_fulfilled = false;
				}
			}
			if(!all_fulfilled) {
				// if an OR goal is not fully buildable then remove it from the goal
				j = i->erase(j);
			} else {
				j++;
			}
		}
		if(i->empty()) {
			i = goalList.erase(i);
		} else {
			i++;
		}
	}// TODO optimize


}

const std::list<std::list<std::list<Goal> > >& ProcessedGoalEntry::getGoalList() const {
	return goalList;
}

const std::list<std::list<std::list<Goal> > >& ProcessedGoalEntry::getBonusList() const {
	return bonusList;
}
