#include "processedgoalentry.hpp"

#include <sstream>

ProcessedGoalEntry::ProcessedGoalEntry(const boost::shared_ptr<const GoalEntry> goalEntry, const boost::shared_ptr<const Player> player, const boost::shared_ptr<const Map> map, const boost::shared_ptr<const Units> startingUnits, const boost::shared_ptr<const Rules> rules):
goalItemList(),
buildableUnits(),
processedGoalMap()
{
	for(std::list<std::list<std::list<GoalItem> > >::const_iterator i = goalEntry->getGoalItemList().begin(); i != goalEntry->getGoalItemList().end(); i++) {
		std::list<std::list<GoalItem> > new_goals_1;
		for(std::list<std::list<GoalItem> >::const_iterator j = i->begin(); j != i->end(); j++) {
			std::list<GoalItem> new_goals_2;
			for(std::list<GoalItem>::const_iterator k = j->begin(); k != j->end(); k++) {
				new_goals_2.push_back(GoalItem(*k));
			}
			new_goals_1.push_back(new_goals_2);
		}
		goalItemList.push_back(new_goals_1);
	}

	fillBuildableListAndAddGoals(rules, map, player, startingUnits);	
}

// fill processedGoalList and goalItemList
void ProcessedGoalEntry::fillBuildableListAndAddGoals(const boost::shared_ptr<const Rules> rules, const boost::shared_ptr<const Map> map, const boost::shared_ptr<const Player> player, const boost::shared_ptr<const Units> startingUnits)

//	TODO separates 'startingUnits' oder units schon an Player verteilt?

{
	// run through all unitTypeIds and set them to false at the beginning
	clearProcessedGoalMap(rules, map);

	// mark starting units
	initializeProcessedGoalMap(player, startingUnits);

	// now fill the reachableUnitTypeMap with all units that can be reached! (ignoring the goals)
	calculateReachableUnits(rules, map);

	// now we know for each location what buildings we can build there!
	// TODO movement buildings/orders!

	// first: check if all goals are haveable (if not then the goal is impossible! call an exception
	if(!checkIfGoalsHaveable()) {
		throw std::exception();
	}
	// second: remove unbuildable goals (only affects OR goals!), maybe move below?
	// remove goal branches that are not reachable with the current starting units
	eraseUnreachableORGoals();
	//eraseRedundantGoals();

	// now remove buildable, but unnecessary units from processedGoalMaps

	// third: create AND/OR goals on the base of all existing goals, only look at the haveable entities, start with the goals itself ("build" the prerequisites as goals)
	// loop through all goal elements

	// TODO: Now traverse back from the goal list
	// 1. alle processedmap felder unchecken
	uncheckProcessedGoalMap(rules, map);


	// 2. von goals ausgehen, felder checken
	checkGoalRelated(rules, map);

	removeProcessedGoalFromMapIfUnchecked(rules, map);

	fillBuildableUnits();


}


ProcessedGoalEntry::~ProcessedGoalEntry() {
	goalItemList.clear();
	processedGoalMap.clear();
}

void ProcessedGoalEntry::clearProcessedGoalMap(const boost::shared_ptr<const Rules> rules, const boost::shared_ptr<const Map> map) {
	for(std::vector<boost::shared_ptr<Location> >::const_iterator i = map->getLocationVector().begin(); i != map->getLocationVector().end(); i++) {
		for(std::list<boost::shared_ptr<const UnitType> >::const_iterator j = rules->getUnitTypeList().begin(); j != rules->getUnitTypeList().end(); j++) {
			processedGoalMap.insert(std::pair<UnitLocalNeutralKey, ProcessedGoal>(UnitLocalNeutralKey((*i)->getId(), (*j)->getId()), ProcessedGoal(false, false)));
		}
	}
}

void ProcessedGoalEntry::initializeProcessedGoalMap(const boost::shared_ptr<const Player> player, const boost::shared_ptr<const Units> startingUnits) {
	for(std::list<boost::shared_ptr<Unit> >::const_iterator i = startingUnits->getUnitList().begin(); i != startingUnits->getUnitList().end(); i++) {
		if((*i)->getPlayerId() == player->getId()) {
			processedGoalMap[UnitLocalNeutralKey((*i)->getLocationId(), (*i)->getUnitTypeId())].setHaveable(true);
		}
	}
}



void ProcessedGoalEntry::calculateReachableUnits(const boost::shared_ptr<const Rules> rules, const boost::shared_ptr<const Map> map) {
	// repeat until there is no more change
	bool change = true;
	while(change) {
		change = false;
		for(std::list<boost::shared_ptr<const UnitType> >::const_iterator i = rules->getUnitTypeList().begin(); i != rules->getUnitTypeList().end(); i++) {
			const UnitType& unitType = **i;

			for(std::vector<boost::shared_ptr<Location> >::const_iterator location = map->getLocationVector().begin(); location != map->getLocationVector().end(); location++) {

				const UnitLocalNeutralKey unitLocalNeutralKey((*location)->getId(), (*i)->getId());

				// we have already checked this one
				if(processedGoalMap[unitLocalNeutralKey].wasChecked()) {
					continue;
				}


				bool buildable = true;
				bool isResource = false; // for RESOURCE_RESOURCES TODO, only allow haveable, not buildable
				// also add these unit types to the map if the current unit itself is buildable. Again, only add those units if th
				std::list<UnitLocalNeutralKey> alsoProduce; 


				for(std::list<UnitResourceType>::const_iterator j = unitType.getResources().begin(); j != unitType.getResources().end(); j++) {

					if(!buildable) {
						break;
					}

					switch(j->getResourceType()) {
					case NOT_BUILDABLE:buildable = false;break; // neutral units, global special units (supply, resources)

					case PRODUCE_SUPPLY_RESOURCE:
						for(std::vector<boost::shared_ptr<Location> >::const_iterator location2 = map->getLocationVector().begin(); location2 != map->getLocationVector().end(); location2++) {
							for(std::list<std::list<boost::uuids::uuid> >::const_iterator k = j->getUnitTypeIdList().begin(); k != j->getUnitTypeIdList().end(); k++) {
								for(std::list<boost::uuids::uuid>::const_iterator l = k->begin(); l != k->end(); l++) {
									alsoProduce.push_back(UnitLocalNeutralKey((*location2)->getId(), *l)); 
								}
							}
						}
						break;

						// ignore 
					case SUPPLY_PROVIDER:isResource = true;break;

					case ACCEPTER_RESOURCES:break;				
					case SOURCE_RESOURCES:break;

					case GATHERER_RESOURCES:
					case FACILITY_IS_LOST_RESOURCE:
					case NEUTRAL_FACILITY_IS_LOST_RESOURCE:
					case NEUTRAL_FACILITY_IS_NEEDED_ALWAYS_RESOURCE:
					case FACILITY_IS_MORPHING_RESOURCE:
					case FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE:
					case FACILITY_IS_NEEDED_ALWAYS_RESOURCE:
					case GLOBAL_FACILITY_IS_MORPHING_RESOURCE:
					case NORMAL_GLOBAL_RESOURCE:
					case NEED_GLOBAL_SUPPLY_RESOURCE:
					case GLOBAL_PREREQUISITE_RESOURCE:
					case LOCAL_PREREQUISITE_RESOURCE: // location is ignored, just see if we can build the unit at all
						{
							bool anyReachable = false;

							for(std::list<std::list<boost::uuids::uuid> >::const_iterator k = j->getUnitTypeIdList().begin(); k != j->getUnitTypeIdList().end(); k++) {
								bool allReachable = true;
								for(std::list<boost::uuids::uuid>::const_iterator l = k->begin(); l != k->end(); l++) {
									if(!processedGoalMap[UnitLocalNeutralKey((*location)->getId(), *l)].isHaveable()) {
										allReachable = false;
										break;
									}
								}
								if(allReachable) {
									anyReachable = true;
									break;
								}

							}

							if(!anyReachable) {
								buildable = false;
							} 
							break;
						}

					case RESOURCE_RESOURCES:
						{

							bool anyReachable = false;
							isResource = true;
							// any location! -> later: also allow local resources
							for(std::vector<boost::shared_ptr<Location> >::const_iterator location2 = map->getLocationVector().begin(); location2 != map->getLocationVector().end(); location2++) {
								for(std::list<std::list<boost::uuids::uuid> >::const_iterator k = j->getUnitTypeIdList().begin(); k != j->getUnitTypeIdList().end(); k++) {
									bool allReachable = true;
									for(std::list<boost::uuids::uuid>::const_iterator l = k->begin(); l != k->end(); l++) {
										if(!processedGoalMap[UnitLocalNeutralKey((*location2)->getId(), *l)].isHaveable()) {
											allReachable = false;
											break;
										}
									}
									if(allReachable) {
										anyReachable = true;
										break;
									}

								}
							}

							if(!anyReachable) {
								buildable = false;
							} 

							break;
						}



					case UNIT_CREATE_RESOURCE:
						for(std::list<std::list<boost::uuids::uuid> >::const_iterator k = j->getUnitTypeIdList().begin(); k != j->getUnitTypeIdList().end(); k++) {
							for(std::list<boost::uuids::uuid>::const_iterator l = k->begin(); l != k->end(); l++) {
								alsoProduce.push_back(UnitLocalNeutralKey((*location)->getId(), *l));
							}
						}
						break;

					case AFFECTS_RESOURCE_GATHERING_LOCALLY:break; // ignore
					case AFFECTS_RESOURCE_GATHERING_GLOBALLY:break; // ignore
					/*case IS_SPEED_UPGRADE:break; // ignore TODO connect units with possible speed upgrades with unittype
// most units
	NEED_GLOBAL_SUPPLY_RESOURCE,
	
	// supply depot, command center, overlord etc.
	PRODUCE_SUPPLY_RESOURCE,
	
	// for the supply resource
	SUPPLY_PROVIDER,

	// Mineral
	NORMAL_GLOBAL_RESOURCE,
	
	// for units of the whole resource gathering chain
	ACCEPTER_RESOURCES, // resource, source, gatherer
	GATHERER_RESOURCES, // resource, source, accepter
	SOURCE_RESOURCES,   // resource, gatherer, accepter
	RESOURCE_RESOURCES, // source, gatherer, accepter

	
	

// technology
	GLOBAL_PREREQUISITE_RESOURCE,
// e.g. a probe, needed only a short time
	LOCAL_PREREQUISITE_RESOURCE, 

// facility is lost immediately after construction is started
	FACILITY_IS_LOST_RESOURCE,
// neutral facility is lost immediately after construction is started TODO Example?
	NEUTRAL_FACILITY_IS_LOST_RESOURCE,
// neutral facility (e.g. vespene geysir, gold mine etc.) is needed as long as this building stands
	NEUTRAL_FACILITY_IS_NEEDED_ALWAYS_RESOURCE,
// facility continues to exist (i.e. provide technology, supply etc.) until construction is complete
	FACILITY_IS_MORPHING_RESOURCE,
// facility is used during the building but is not lost at the end
// TODO später: Mehrere alternative facilities erlauben
	FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE,
// facility can build only one item, stays unavailable even after construction is finished (e.g. silos, scarabs, interceptors)
	FACILITY_IS_NEEDED_ALWAYS_RESOURCE,
// global facility continues to exist until construction is complete (e.g. researches)
	GLOBAL_FACILITY_IS_MORPHING_RESOURCE,

	// this unit gets created when the construction is finished
	UNIT_CREATE_RESOURCE,

	// create one unit every X time units, e.g. larvae, but also resource points (CoH)
	UNIT_CREATE_REGULARLY_RESOURCE, 

	// e.g. new local harvesting technology
	AFFECTS_RESOURCE_GATHERING_LOCALLY,
	// e.g. new harvesting technology
	AFFECTS_RESOURCE_GATHERING_GLOBALLY,

	, // count = time (e.g. stim), 0 = permanent

	*/

					case MAX_GAME_RESOURCE_TYPES:
					default:BOOST_ASSERT(false);break;
					}
				}

				// no prerequisite failed -> allow build
				if(buildable) {
					processedGoalMap[unitLocalNeutralKey].setWasChecked(true);
					change = true;
					if(!isResource) {				
						// std::cout << "buildable " << unitLocalNeutralKey.locationId << " / " << unitLocalNeutralKey.unitTypeId << std::endl;
						processedGoalMap[unitLocalNeutralKey].setBuildable(true);
						for(std::list<UnitLocalNeutralKey>::const_iterator j = alsoProduce.begin(); j != alsoProduce.end(); j++) {
							processedGoalMap[*j].setHaveable(true);
						}
					} else {
						// std::cout << "haveable " << unitLocalNeutralKey.locationId << " / " << unitLocalNeutralKey.unitTypeId << std::endl;
						processedGoalMap[unitLocalNeutralKey].setHaveable(true);
					}

				}

			}
		}
	}
}



void ProcessedGoalEntry::eraseUnreachableORGoals() {

	for(std::list<std::list<std::list<GoalItem> > >::iterator i = goalItemList.begin(); i != goalItemList.end(); ) {

		// loop through all OR goals
		for(std::list<std::list<GoalItem> >::iterator j = i->begin(); j != i->end(); ) {
			bool all_fulfilled = true;
			for(std::list<GoalItem>::const_iterator k = j->begin(); k != j->end(); k++) {
				if(!processedGoalMap[UnitLocalNeutralKey(k->getLocationId(), k->getUnitTypeId())].isHaveable()) {
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
			i = goalItemList.erase(i);
		} else {
			i++;
		}
	}// TODO optimize


}


void ProcessedGoalEntry::eraseRedundantGoals() {

	for(std::list<std::list<std::list<GoalItem> > >::iterator i = goalItemList.begin(); i != goalItemList.end(); ) {

		// loop through all OR goals
		for(std::list<std::list<GoalItem> >::iterator j = i->begin(); j != i->end(); ) {
			bool all_fulfilled = true;
			for(std::list<GoalItem>::const_iterator k = j->begin(); k != j->end(); k++) {
				if(!processedGoalMap[UnitLocalNeutralKey(k->getLocationId(), k->getUnitTypeId())].isHaveable()) {
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
			i = goalItemList.erase(i);
		} else {
			i++;
		}
	}// TODO optimize


}


void ProcessedGoalEntry::uncheckProcessedGoalMap(const boost::shared_ptr<const Rules> rules, const boost::shared_ptr<const Map> map) {
	for(std::vector<boost::shared_ptr<Location> >::const_iterator i = map->getLocationVector().begin(); i != map->getLocationVector().end(); i++) {
		for(std::list<boost::shared_ptr<const UnitType> >::const_iterator j = rules->getUnitTypeList().begin(); j != rules->getUnitTypeList().end(); j++) {
			processedGoalMap[UnitLocalNeutralKey((*i)->getId(), (*j)->getId())].setWasChecked(false);
		}
	}
}

// TODO UUID List statt tatsaechliche Objecte?

void ProcessedGoalEntry::removeProcessedGoalFromMapIfUnchecked(const boost::shared_ptr<const Rules> rules, const boost::shared_ptr<const Map> map) {
	for(std::vector<boost::shared_ptr<Location> >::const_iterator i = map->getLocationVector().begin(); i != map->getLocationVector().end(); i++) {
		for(std::list<boost::shared_ptr<const UnitType> >::const_iterator j = rules->getUnitTypeList().begin(); j != rules->getUnitTypeList().end(); j++) {
			if(!processedGoalMap[UnitLocalNeutralKey((*i)->getId(), (*j)->getId())].wasChecked()) {
				// std::cout << "remove UUID : Location " << (*i)->getId() << " -> " << j->first << std::endl;
				processedGoalMap[UnitLocalNeutralKey((*i)->getId(), (*j)->getId())].setBuildable(false);
			}
		}
	}
}


void ProcessedGoalEntry::fillBuildableUnits() 
{
	for(std::map<UnitLocalNeutralKey, ProcessedGoal>::const_iterator i = processedGoalMap.begin(); i != processedGoalMap.end(); i++) {
		if(i->second.isBuildable()) {
			buildableUnits[i->first.locationId].push_back(i->first.unitTypeId);
		}
	}

}


/**
 * Use goals as starting point and traverse through all buildable units (defined by starting units) 
 */
void ProcessedGoalEntry::checkGoalRelated(const boost::shared_ptr<const Rules> rules, const boost::shared_ptr<const Map> map) {




	// initial filling
	// loop through all goal elements
	for(std::list<std::list<std::list<GoalItem> > >::iterator i = goalItemList.begin(); i != goalItemList.end(); i++) {
		// loop through all OR goals (we [now!] know all OR goals can be fully fulfilled!)
		for(std::list<std::list<GoalItem> >::const_iterator j = i->begin(); j != i->end(); j++) {
			// finally loop through all AND goals
			for(std::list<GoalItem>::const_iterator k = j->begin(); k != j->end(); k++) {
				processedGoalMap[UnitLocalNeutralKey(k->getLocationId(), k->getUnitTypeId())].setWasChecked(true);
			}
		}
	}

	bool change = true;

	while(change) {
		change = false;

		for(std::map<UnitLocalNeutralKey, ProcessedGoal>::const_iterator i = processedGoalMap.begin(); i != processedGoalMap.end(); i++) {
			if(i->second.wasChecked()) {

				const UnitType& unitType = *(rules->getUnitType(i->first.unitTypeId));

				for(std::list<UnitResourceType>::const_iterator l = unitType.getResources().begin(); l != unitType.getResources().end(); l++) {

					switch(l->getResourceType()) {
					case NOT_BUILDABLE:break; // ignore, can't have any prerequisites, they must be given (e.g. neutral units, starting units)

						
					case PRODUCE_SUPPLY_RESOURCE:break; // ignore, is a property, no prerequisite (what units does this produce when created?)
					case ACCEPTER_RESOURCES:break; // ignore, is a property, no prerequisite (what units can use this as an accepter?)
					case SOURCE_RESOURCES:break; // ignore, is a property, no prerequisite (what units can gather this item?)
					case NEUTRAL_FACILITY_IS_LOST_RESOURCE:
					case NEUTRAL_FACILITY_IS_NEEDED_ALWAYS_RESOURCE:break;  // ignore, neutral units cannot be build



// we need to have this facility as a goal
					case FACILITY_IS_LOST_RESOURCE:
					case FACILITY_IS_MORPHING_RESOURCE:
						{								
							for(std::list<std::list<boost::uuids::uuid> >::const_iterator m = l->getUnitTypeIdList().begin(); m != l->getUnitTypeIdList().end(); m++) {
								for(std::list<boost::uuids::uuid>::const_iterator n = m->begin(); n != m->end(); n++) {
									// this is a bonus Unit, TODO?
									if(processedGoalMap[UnitLocalNeutralKey(i->first.locationId, *n)].setWasChecked(true)) {
										change = true;
									}
								}
							}
						}
						break;


						// OR goal bonus auf alle locations
					case GLOBAL_FACILITY_IS_MORPHING_RESOURCE:
						{
							for(std::list<std::list<boost::uuids::uuid> >::const_iterator m = l->getUnitTypeIdList().begin(); m != l->getUnitTypeIdList().end(); m++) {
								for(std::vector<boost::shared_ptr<Location> >::const_iterator j = map->getLocationVector().begin(); j != map->getLocationVector().end(); j++) {
									for(std::list<boost::uuids::uuid>::const_iterator n = m->begin(); n != m->end(); n++) {
										// this is a bonus Unit, TODO?
										if(processedGoalMap[UnitLocalNeutralKey((*j)->getId(), *n)].setWasChecked(true)) {
											change = true;
										}
										// std::cout << "checked " << (*j)->getId() << " / " << *n << std::endl;
									}
								}
							}
						}
						break;						

					case LOCAL_PREREQUISITE_RESOURCE:
					case GATHERER_RESOURCES:
					case RESOURCE_RESOURCES:
					case FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE:
					case FACILITY_IS_NEEDED_ALWAYS_RESOURCE:	
						{
							for(std::list<std::list<boost::uuids::uuid> >::const_iterator m = l->getUnitTypeIdList().begin(); m != l->getUnitTypeIdList().end(); m++) {
								for(std::list<boost::uuids::uuid>::const_iterator n = m->begin(); n != m->end(); n++) {
									if(processedGoalMap[UnitLocalNeutralKey(i->first.locationId, *n)].setWasChecked(true)) {
										change = true;
									}
									// std::cout << "checked " << i->first.locationId << " / " << *n << std::endl;
								}
							}
						}
						break;

					case SUPPLY_PROVIDER:
					case NEED_GLOBAL_SUPPLY_RESOURCE: 			
					case NORMAL_GLOBAL_RESOURCE: // global resource
					case GLOBAL_PREREQUISITE_RESOURCE: // global resource, look anywhere
						{
							for(std::list<std::list<boost::uuids::uuid> >::const_iterator m = l->getUnitTypeIdList().begin(); m != l->getUnitTypeIdList().end(); m++) {
								for(std::vector<boost::shared_ptr<Location> >::const_iterator i = map->getLocationVector().begin(); i != map->getLocationVector().end(); i++) {
									for(std::list<boost::uuids::uuid>::const_iterator n = m->begin(); n != m->end(); n++) {
										if(processedGoalMap[UnitLocalNeutralKey((*i)->getId(), *n)].setWasChecked(true)) {
											change = true;
										}
										// std::cout << "checked " << (*i)->getId() << " / " << *n << std::endl;
									}
								}
							}
						}
						break;				


					case UNIT_CREATE_RESOURCE:break; // ignore
					case AFFECTS_RESOURCE_GATHERING_LOCALLY:break; // ignore
					case AFFECTS_RESOURCE_GATHERING_GLOBALLY:break; // ignore
					case MAX_GAME_RESOURCE_TYPES:
					default:BOOST_ASSERT(false);break;
					}
				}

			}}
	}
}

bool ProcessedGoalEntry::checkIfGoalsHaveable() const {
	for(std::list<std::list<std::list<GoalItem> > >::const_iterator i = goalItemList.begin(); i != goalItemList.end(); i++) {
		bool any_fulfilled = false;
		for(std::list<std::list<GoalItem> >::const_iterator j = i->begin(); j != i->end(); j++) {
			bool all_fulfilled = true;
			for(std::list<GoalItem>::const_iterator k = j->begin(); k != j->end(); k++) {
				std::map<UnitLocalNeutralKey, ProcessedGoal>::const_iterator i = processedGoalMap.find(UnitLocalNeutralKey(k->getLocationId(), k->getUnitTypeId()));
				BOOST_ASSERT(i != processedGoalMap.end());
				if(!i->second.isHaveable()) {
					all_fulfilled = false;
				}
			}
			if(all_fulfilled) {
				any_fulfilled = true;
			}
		}
		if(!any_fulfilled) {
			// not buildable! error!
			return false;
		}
	}
	return true;
}


std::string ProcessedGoalEntry::getGoalString() const {
	std::ostringstream os;
	for(std::list<std::list<std::list<GoalItem> > >::const_iterator i = goalItemList.begin(); i != goalItemList.end(); i++) {
		for(std::list<std::list<GoalItem> >::const_iterator j = i->begin(); j != i->end(); j++) {
			if(j != i->begin()) {
				os << " OR ";
			}
			for(std::list<GoalItem>::const_iterator k = j->begin(); k != j->end(); k++) {
				if(k != j->begin()) {
					os << " AND ";
				}
				os << k->getUnitTypeId() << "/" << k->getLocationId() << "/" << k->getCount();
			}
			os << "   ";
		}
	}
	return os.str();
}


void ProcessedGoalEntry::addGoalItem(std::list<std::list<GoalItem> >& goal)
{
	goalItemList.push_back(goal);
}




// was checkGoalRelated:




	/*bool change = true;

	while(change) {
	change = false;

	std::list<std::list<std::list<GoalItem> > > newGoalList;

	// loop through all goal elements
	for(std::list<std::list<std::list<GoalItem> > >::iterator i = goalItemList.begin(); i != goalItemList.end(); i++) {

	std::list<std::list<std::list<std::list<GoalItem> > > > newOrGoalList;
	// loop through all OR goals (we [now!] know all OR goals are fully fulfilled!)
	for(std::list<std::list<GoalItem> >::const_iterator j = i->begin(); j != i->end(); j++) {



	// finally loop through all AND goals
	for(std::list<GoalItem>::const_iterator k = j->begin(); k != j->end(); k++) {
	// loop through all prerequisites, add OR goals if necessary

	const UnitType& unitType = *(rules->getUnitType(k->getUnitTypeId()));
	std::cout << " Add for unit type " << unitType.getName() << std::endl;
	std::list<std::list<std::list<GoalItem> > > thisGoalList;

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
	std::list<std::list<GoalItem> > orGoal;
	for(std::list<std::list<unsigned int> >::const_iterator m = l->getUnitTypeIdList().begin(); m != l->getUnitTypeIdList().end(); m++) {
	std::list<GoalItem> andGoal;
	for(std::list<unsigned int>::const_iterator n = m->begin(); n != m->end(); n++) {
	andGoal.push_back(Goal(*n, k->getLocationId(), 0)); // 0 = bonus
	}
	orGoal.push_back(andGoal);
	}
	newGoalList.push_back(orGoal);
	thisGoalList.push_back(orGoal);
	}
	break;


	// OR goal bonus auf alle locations
	case GLOBAL_FACILITY_IS_MORPHING_RESOURCE:
	{
	std::list<std::list<GoalItem> > orGoal;
	for(std::list<std::list<unsigned int> >::const_iterator m = l->getUnitTypeIdList().begin(); m != l->getUnitTypeIdList().end(); m++) {
	for(std::vector<Location*>::const_iterator i = map.getLocations().begin(); i != map.getLocations().end(); i++) {
	std::list<GoalItem> andGoal;
	for(std::list<unsigned int>::const_iterator n = m->begin(); n != m->end(); n++) {
	andGoal.push_back(Goal(*n, (*i)->getId(), 0)); // 0 = bonus
	}
	orGoal.push_back(andGoal);
	}
	}
	newGoalList.push_back(orGoal);
	thisGoalList.push_back(orGoal);
	}
	break;						

	case LOCAL_PREREQUISITE_RESOURCE:
	case RESOURCE_RESOURCES:
	case FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE:
	case FACILITY_IS_NEEDED_ALWAYS_RESOURCE:	
	{
	std::list<std::list<GoalItem> > orGoal;
	for(std::list<std::list<unsigned int> >::const_iterator m = l->getUnitTypeIdList().begin(); m != l->getUnitTypeIdList().end(); m++) {
	std::list<GoalItem> andGoal;
	for(std::list<unsigned int>::const_iterator n = m->begin(); n != m->end(); n++) {
	andGoal.push_back(Goal(*n, k->getLocationId(), 1)); // 1 = goal
	}
	orGoal.push_back(andGoal);
	}
	newGoalList.push_back(orGoal);
	thisGoalList.push_back(orGoal);
	}
	break;

	case NEED_GLOBAL_SUPPLY_RESOURCE: 			
	case NORMAL_GLOBAL_RESOURCE: // global resource
	case GLOBAL_PREREQUISITE_RESOURCE: // global resource, look anywhere
	{
	std::list<std::list<GoalItem> > orGoal;
	for(std::list<std::list<unsigned int> >::const_iterator m = l->getUnitTypeIdList().begin(); m != l->getUnitTypeIdList().end(); m++) {
	for(std::vector<Location*>::const_iterator i = map.getLocations().begin(); i != map.getLocations().end(); i++) {
	std::list<GoalItem> andGoal;
	for(std::list<unsigned int>::const_iterator n = m->begin(); n != m->end(); n++) {
	andGoal.push_back(Goal(*n, (*i)->getId(), 1)); // 1 = goal
	}
	orGoal.push_back(andGoal);
	}
	}
	newGoalList.push_back(orGoal);
	thisGoalList.push_back(orGoal);
	}
	break;				


	case UNIT_CREATE_RESOURCE:break; // ignore
	case AFFECTS_RESOURCE_GATHERING_LOCALLY:break; // ignore
	case AFFECTS_RESOURCE_GATHERING_GLOBALLY:break; // ignore
	case MAX_GAME_RESOURCE_TYPES:
	default:BOOST_ASSERT(false);break;
	}
	}

	for(std::list<std::list<std::list<GoalItem> > >::const_iterator i = thisGoalList.begin(); i != thisGoalList.end(); i++) {
	for(std::list<std::list<GoalItem> >::const_iterator j = i->begin(); j != i->end(); j++) {
	if(j != i->begin()) {
	std::cout << " OR ";
	}
	for(std::list<GoalItem>::const_iterator k = j->begin(); k != j->end(); k++) {
	if(k != j->begin()) {
	std::cout << " AND ";
	}
	std::cout << k->getUnitTypeId() << "/" << k->getLocationId() << "/" << k->getCount();
	}
	std::cout << "   ";
	}
	std::cout << std::endl;
	}

	}
	}
	//			thisGoalList ORen und dann erst in newGoalList eintragen!
	}
	}
	*/


// FROM: fillBuildableListAndGoals

	// check for doubles (in any order!)

	// prerequisite: same number of items

	/*std::cout << "CHECK FOR DOUBLES" << std::endl;
	// loop through all goal elements
	for(std::list<std::list<std::list<GoalItem> > >::iterator i = newGoalList.begin(); i != newGoalList.end(); ) {
	bool identical = false; // assume that this entry does not occur in the goalItemList and try to disprove it

	for(std::list<std::list<std::list<GoalItem> > >::const_iterator old_i = goalItemList.begin(); old_i != goalItemList.end(); old_i++) {
	if(i->size() != old_i->size()) {
	continue;
	}

	unsigned int equals = 0;
	// search for an equal
	for(std::list<std::list<GoalItem> >::const_iterator old_j = old_i->begin(); old_j != old_i->end(); old_j++) {
	for(std::list<std::list<GoalItem> >::const_iterator j = i->begin(); j != i->end(); j++) {

	if(j->size() != old_j->size()) {
	continue;
	}
	unsigned int equals2 = 0;
	for(std::list<GoalItem>::const_iterator old_k = old_j->begin(); old_k != old_j->end(); old_k++) {
	for(std::list<GoalItem>::const_iterator k = j->begin(); k != j->end(); k++) {
	//std::cout << "Compare GOAL " << k->getUnitTypeId() << "/" << k->getLocationId() << "/" << k->getCount() << " with " << old_k->getUnitTypeId() << "/" << old_k->getLocationId() << "/" << old_k->getCount();
	if(*k == *old_k) {
	//std::cout << " OK" << std::endl;
	equals2++;
	break;
	}
	//std::cout << std::endl;
	}
	}
	if(equals2 == j->size()) {
	//std::cout << "EQUALS" << std::endl;
	equals++;
	break;
	}
	}
	}
	if(equals == i->size()) {
	//std::cout << "IDENTICAL" << std::endl;
	identical = true;
	break;
	}
	}



	if(identical) {
	std::cout << "--REMOVE-- ";
	for(std::list<std::list<GoalItem> >::const_iterator j = i->begin(); j != i->end(); j++) {
	if(j != i->begin()) {
	std::cout << " OR ";
	}
	for(std::list<GoalItem>::const_iterator k = j->begin(); k != j->end(); k++) {
	if(k != j->begin()) {
	std::cout << " AND ";
	}
	std::cout << k->getUnitTypeId() << "/" << k->getLocationId() << "/" << k->getCount();
	}
	}
	std::cout << "----" << std::endl;
	// ignore
	} else {
	goalItemList.push_back(*i);
	change = true;
	std::cout << "--ADDING-- ";
	for(std::list<std::list<GoalItem> >::const_iterator j = i->begin(); j != i->end(); j++) {
	if(j != i->begin()) {
	std::cout << " OR ";
	}
	for(std::list<GoalItem>::const_iterator k = j->begin(); k != j->end(); k++) {
	if(k != j->begin()) {
	std::cout << " AND ";
	}
	std::cout << k->getUnitTypeId() << "/" << k->getLocationId() << "/" << k->getCount();
	}					
	}
	std::cout << " ----" << std::endl;
	}
	i = newGoalList.erase(i);
	}

	}*/
