
#include <neededresource.hpp>

#include "simulator.hpp"

Simulator::Simulator(const Game* const game):
game(game),
	currentState(game->getStartingUnits())
{}

void Simulator::restart() {
	currentState = game->getStartingUnits();
	time = game->getStartingTime();
}

const bool Simulator::buildOrdersFinished() const {
	for(std::list<BuildOrder>::const_iterator i = buildOrderList.begin(); i != buildOrderList.end(); i++) {
		if(!i->isFinished()) {
			return false;
		}
	}
	return true;
}

const bool Simulator::isCalculationDone() const
{
	for(std::list<BuildOrder>::const_iterator i = buildOrderList.begin(); i != buildOrderList.end(); i++) {
		if(!i->isCalculationDone()) {
			return false;
		}
	}
	return true;
}


const bool Simulator::step() {
	// update "currentState" according to the rules defined in "constants"

	if(calculationDone()) {
		postProcessing();
		return true;
	}

	for(std::list<BuildOrder>::iterator i = buildOrderList.begin(); i != buildOrderList.end(); i++) {
		bool ok = true;
		while((ok)&&(!i->isFinished()))
		{
			bool ok = tryBuildGene(*i);
			// resetNeededResources();
			ok = executeNextInstruction();
			i->
				unsigned int command = getGoal()->toPhaeno(getCurrentCode());

			bool ok = buildGene(command);
			if((ok) || (isTimeOut()))
			{
				resetTimeOut();
				moveToNextInstruction();
			}
			return ok;

		}

		ready = calculateReady();
	}

	leapForwardInTime();
	processBuildingQueue();

	leapForwardInTime();

	currentState.process();

	get all next items from queue (can be in parallel, e.g. locations)

		choose random facility

		if item buildable -> add to queue

			TODO resources etc.

			return false;
}

void Simulator::initBuildOrders() {
	for(std::list<BuildOrder>::iterator i = buildOrderList.begin(); i != buildOrderList.end(); i++) {
		i->initialize();
	}
}

//neededResource brauchen wir nur für resourcen?
//	Wir nehmen einfach aus der priorityQueue den Kopf um die Zeit bis zum nächsten Ereignis zu bekommen?
//	Ist etwas genauer wenn man es über die komplette Abdekcung macht... jo, so lassen...

const bool Simulator::tryBuildGene(const BuildOrder& buildOrder)
{
	// TODO if a code has finished then 0 is returned... maybe ignore it or something.
	const std::list<unsigned int> orderList = buildOrder.getCurrentCode();

	const unsigned int playerId = buildOrder.getPlayerId();
	const Player& player = game->getPlayer(playerId);
	unsigned int location = 0;


	for(std::list<unsigned int>::const_iterator i = orderList.begin(); i != orderList.end(); i++) {
		const unsigned int build_unit = *i;
		const UnitType& unitType = constants->getRules()->getUnitType(build_unit);

		// test if this unit is buildable
		BOOST_ASSERT(unitType.getMaxCount() > 0);

		bool notBuildable = false;

		for(std::list<UnitResourceType>::const_iterator j = unitType.getResources().begin(); j != unitType.getResources().end(); j++) {
			if(notBuildable) {
				break;
			}

			const UnitLocalKey localKey(location, playerId, j->getUnitTypeId());
			const UnitLocalNeutralKey localNeutralKey(location, j->getUnitTypeId());
			const UnitGlobalKey globalKey(playerId, j->getUnitTypeId());

			const unsigned int amount = j->getAmount();
			// TODO a real neutral player? What about neutral units in building queues?
			const unsigned int localNeutralAvailable = currentState.getUnits().getLocalNeutralAvailable(localNeutralKey);
			const unsigned int localAvailable = currentState.getUnits().getLocalAvailable(localKey);
			const unsigned int localTotal = currentState.getUnits().getLocalTotal(localKey);
			const unsigned int globalTotal = currentState.getUnits().getGlobalTotal(globalKey);
			const unsigned int globalAvailable = currentState.getUnits().getGlobalAvailable(globalKey); 




			switch(j->getResourceType()) {

				// minerals, gas etc.
			case NORMAL_RESOURCE:
			case NEEDED_SUPPLY_RESOURCE:
				// technology
			case GLOBAL_PREREQUISITE_RESOURCE:
				if(amount > globalTotal) {
					// neededResourceTotal[location].neededGlobalResources[globalKey] = globalTotal - amount;
					notBuildable = true;
				}	
				break;
			case PRODUCED_SUPPLY_RESOURCE:break; // no constraint

				// a unit without a time resource is an order! TODO
			case TIME_RESOURCE:break;

				// e.g. a probe, needed only a short time
			case LOCAL_PREREQUISITE_RESOURCE:
				if(amount > localTotal) {
					// neededResourceTotal[location].neededLocalResources[localKey] = localTotal - amount;
					notBuildable = true;
				}
				break;

				// facility can build only one item, stays unavailable even after construction is finished (e.g. silos, scarabs, interceptors)
			case FACILITY_IS_NEEDED_ALWAYS_RESOURCE:
				// facility is used during the building but is not lost at the end
			case FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE:
				// facility continues to exist (i.e. provide technology, supply etc.) until construction is complete (then it's lost)
			case FACILITY_IS_MORPHING_RESOURCE:
				// facility is lost immediately after construction is started
			case FACILITY_IS_LOST_RESOURCE:
				if(amount > localAvailable) {
					// neededResourceAvailable[location].neededLocalResources[localKey] = localAvailable - amount;
					notBuildable = true;
				}
				break;
				// neutral facility (e.g. vespene geysir, gold mine etc.) is lost immediately after construction is started
			case NEUTRAL_FACILITY_IS_LOST_RESOURCE:
				if(amount > localNeutralAvailable) {
					// neededResourceAvailable[location].neededLocalNeutralResources[localKey] = localNeutralAvailable - amount;
					notBuildable = true;
				}		
				break;

				// global facility continues to exist until construction is complete (e.g. researches)  TODO replace with maxCount? mmmh... Not with upgrades!
			case GLOBAL_FACILITY_IS_MORPHING_RESOURCE:break;
				if(amount > globalAvailable) {
					// neededResourceAvailable[location].neededGlobalResources[localKey] = globalAvailable - amount;
					notBuildable = true;
				}

				// this unit gets created when the construction is finished
			case UNIT_CREATE_RESOURCE:break; // ignore

				// e.g. new gathering building near the gather place, TimeChange has to be recalculated locally
			case AFFECTS_RESOURCE_GATHERING_LOCALLY:break; // ignore
				// e.g. new harvesting technology, TimeChange has to be recalculated globally 
			case AFFECTS_RESOURCE_GATHERING_GLOBALLY:break; // ignore

				// this is a global resource, not 
				//case IS_GLOBAL_RESOURCE:break;  TODO!? Spätestens wenn wir das Spiel konfigurieren kehren wir hier zurück :)



			} // end of switch
		} // end of resources loop
		if(!notBuildable) {
			//protocol as being built!
			//buildOrder.setTimeOfLastCodeExecution(time);
			putInBuildingQueue(location, build_unit);

			// build unit return putInBuildingQueue(build_unit);
		} else {
			//TODO protocol needeResources
			// 
		}
		location++; // next order / location
	} // end of loop of order list
}

/*
void Simulator::resetNeededResource() {
neededResourceAvailable.clear();
neededResourceTotal.clear();
}*/
/* 1. get UnitType from rules
2. check all prerequisites from the units-list
3. insert new units (with remainingbuildingtime > 0) into the units list, remove resource units

if no unit can be build: determine time until units prerequisites are met ( use timechange class !)

maybe put timechange into Units? TimeChange needs to be updated whenever units change...
*/


//Idee: wenn an einem Ort eine Einheit nicht gebaut werden kann, weil z.B. das Baugebäude fehlt, wird es einfach in die Queue woanders eingeschoben!
//  braucht constants und rules... alles i
