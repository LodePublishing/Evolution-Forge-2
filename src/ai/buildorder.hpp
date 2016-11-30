#ifndef _AI_BUILDORDER_HPP
#define _AI_BUILDORDER_HPP

#include <vector>
#include "code.hpp"


class BuildOrder 
{
public:
	BuildOrder(int locationCount);
	const Code& getCode(int location) const;
	const std::vector<unsigned int> getCurrentCode() const;
	const unsigned int getPlayerId() const;
	const bool isFinished() const;
	const bool isCalculationDone() const;
	// later: make this abstract
	void initialize();

	void setTimeOfLastCodeExecution(const unsigned int timeOfLastCodeExecution);
	const unsigned int getTimeOfLastCodeExecution() const;

private:
	unsigned int playerId;
	std::vector<Code> code;
	bool goalsReached;
	// temporary variable
	unsigned int timeOfLastCodeExecution; // is set to the current time whenever a building is built
};

inline const unsigned int BuildOrder::getTimeOfLastCodeExecution() const {
	return timeOfLastCodeExecution;
}

inline void BuildOrder::setTimeOfLastCodeExecution(const unsigned int timeOfLastCodeExecution) {
	this->timeOfLastCodeExecution = timeOfLastCodeExecution;
}


inline const Code& BuildOrder::getCode(int location) const {
	return code[location];
}

inline const unsigned int BuildOrder::getPlayerId() const {
	return playerId;
}
/*


#include "start.hpp"

#include <functional>
#include <queue>

class PREBUILDORDER
{
	public:
// ------ INITIALIZATION ------
		void assignStartGoal(const GOAL_ENTRY* goal);		
// assigns player data from start (start minerals, supply etc.) and sets the appropriate optimized pointers (global, location, pMap etc.) CALL IT AFTER EACH MAP CHANGE AND PLAYER CHANGE!!

// ------ CALCULATION ------
		virtual void prepareForNewGeneration();
		virtual void postProcessing();

		
// ------ STATISTICS ------
		const bool haveConditionsChanged() const;
		
		GOAL_ENTRY* getGoal() const;

		const unsigned int getHarvestedResource(const unsigned int resource_type) const;
		const unsigned int getResource(const unsigned int resource_type) const;
	
		const unsigned int getPlayerNumber() const;
		const unsigned int getNeedSupply() const;
		const unsigned int getHaveSupply() const;
		void setTimer(const unsigned int time);
		const unsigned int getTimer() const;
		const unsigned int getRealTimer() const;
		const unsigned int getLength() const;
		const unsigned int getLocationTotal(const unsigned int location_number, const unsigned int unit_type) const;
		const unsigned int getLocationAvailable(const unsigned int location_number, const unsigned int unit_type) const;

		const unsigned int getRace() const;
		const START_CONDITION* const* getStartCondition() const; //pointer to player in start
		void setConditionsChanged(const bool conditions_changed = true);

		std::priority_queue<Building, std::vector<Building> > buildingQueue;

// ------ CODE CONTROL ------
		void eraseIllegalCode();
		void mutateGeneCode();//const bool* fixed_list);
		void resetGeneCode();//resets either to a pre-processed buildorder or a completely random one
		void assignCode(const PREBUILDORDER& player);
		void assignCode(const std::list<unsigned int>& src);
		void copyCode(std::list<unsigned int>& dst) const;
		const std::list<unsigned int>& getCode() const;
		const bool isDifferent(const std::list<unsigned int>& code) const;
		
		START* getpStart() const;

	protected:
		PREBUILDORDER(unsigned int player_number, START* start, Units (&units)[MAX_PLAYER][MAX_LOCATIONS]);
		virtual ~PREBUILDORDER();

		const bool calculationDone();
		void resetNeededResources();
		const bool executeAlwaysBuildInstructions();
		const bool executeNextInstruction();
		void processBuildingQueue();
		void eraseRemainingCode();
		void resetTimeOut();
		void leapForwardInTime();
		const bool calculateReady() const;
		const unsigned int calculatePrimaryFitness(const bool ready);
	
		virtual void resetData();
		void resetSpecial();


// HACK for anarace:
		eErrorMessages successType;
		UnitStatistics& successUnit;

		UnitStatistics& anaraceBuildFacility;
		MapLocation* anaraceBuildLocation;
		unsigned int anaraceBuildTotalTime;
		UnitStatistics& anaraceBuildUnit;
		unsigned int anaraceBuildFinishedTime;

		const std::vector<UnitStatistics>* getpStats() const;
		Units& getUnit(const unsigned int player_number, const unsigned int location_number) const;
		bool ready;

	private:
	
		void modifyLocationAvailable(const unsigned int location_number, const unsigned int unit_type, const signed int available);
		void modifyLocationTotal(const unsigned int location_number, const unsigned int unit_type, const signed int total);
		void addOneLocationAvailable(const unsigned int location_number, const unsigned int unit_type);
		void addOneLocationTotal(const unsigned int location_number, const unsigned int unit_type);
		void removeLocationAvailable(const unsigned int location_number, const unsigned int unit_type, const unsigned int available);
		void removeLocationTotal(const unsigned int location_number, const unsigned int unit_type, const unsigned int total);

		void removeOneLocationAvailable(const unsigned int location_number, const unsigned int unit_type);
		void removeOneLocationTotal(const unsigned int location_number, const unsigned int unit_type);

		void removeOneLocationTotalAllPlayers(const unsigned int location_number, const unsigned int unit_type);
		void removeOneLocationAvailableAllPlayers(const unsigned int location_number, const unsigned int unit_type);

		void removeOneTotalEverywhere(const unsigned int unit_type);
		void removeOneAvailableEverywhere(const unsigned int unit_type);

	

//		void setResourceHarvestPerFrame(const unsigned int resource_type, const unsigned int location_number, const unsigned int worker, const unsigned int harvest_speed);
		const unsigned int getResourceHarvestPerFrame(const unsigned int resource_type, const unsigned int location_number, const unsigned int worker) const;
		void setHarvestedResource(const unsigned int resource_type, const unsigned int harvested_resource);

		const unsigned int harvestResource(const unsigned int resource_type) const;

//		void adjustHarvest(const unsigned int resource_type, const unsigned int location_number);
//		void adjustHarvestAllLocations(const unsigned int resource_type);

		void adjustAccepterDistance(const unsigned int resource_type, const unsigned int location_number);
		void adjustAccepterDistanceAllLocations(const unsigned int resource_type);
			
		//Units (&unit)[MAX_PLAYER][MAX_LOCATIONS];
		
		void setTimeOut(const unsigned int time);
		const unsigned int getTimeOut() const;
		
		const unsigned int calculateIdleTime() const; // calculate the next time something significant will happen, CONST MACHEN
		const bool buildGene(const unsigned int build_unit);
		const bool putInBuildingQueue(const unsigned int build_unit);
		
		void adjustLocationUnitsAfterCompletion(const unsigned int location_number, const eFacilityType facility_type, const unsigned int facility, const unsigned int facility2, const unsigned int count);
		void adjustAvailability(const unsigned int location, const eFacilityType facility_type, const unsigned int facility, const unsigned int facility2, signed int count);
		void cancelBuilding(const Building& build);

		void createSpecial();
		const bool checkForLarva(const unsigned int current_location_window);
		const bool isTimeOut() const;
		void addLarvaToQueue(const unsigned int location_number);
		void removeLarvaFromQueue(const unsigned int location_number);

		void setNeedSupply(const unsigned int need_supply);
		void setHaveSupply(const unsigned int have_supply);

		void setResource(const unsigned int resource_type, const unsigned int have_resource);

		unsigned int larvaInProduction[MAX_LOCATIONS]; // well... one of that ugly race-specific variables saves a lot of trouble...
		
		START* pStart;

		bool conditionsChanged;
		bool alwaysBuildWorkers;
		bool onlySwapOrders;

		unsigned int playerNum;
		unsigned int timer;

		std::vector<unsigned int> resource;
		std::vector<unsigned int> neededResource;
		std::vector<unsigned int> accepterDistance[MAX_LOCATIONS];
//		std::vector< std::vector< unsigned int > > resourceHarvestPerFrame[MAX_LOCATIONS];
		std::vector<unsigned int> harvestedResource;
		
		unsigned int needSupply;		// free supply
		unsigned int haveSupply; // total supply
		unsigned int timeout;

//		bool playerNumInitialized;
//		bool unitsInitialized;
//		bool pStartInitialized;

		
inline START* PREBUILDORDER::getpStart() const {
	return(pStart);
}

inline const unsigned int PREBUILDORDER::getPlayerNumber() const {
	return(playerNum);
}

inline const bool PREBUILDORDER::haveConditionsChanged() const {
	return(conditionsChanged);
}

inline const unsigned int PREBUILDORDER::getRace() const {
	return(pStart->getPlayerRace());
}

inline const BASIC_MAP* const* PREBUILDORDER::getMap() const {
	return(pStart->getMap());
}

inline GOAL_ENTRY* PREBUILDORDER::getGoal() const 
{
/*#ifdef _SCC_DEBUG
	if(!goalInitialized) {
		toErrorLog("DEBUG (PREBUILDORDER::getGoal()()): Variable pGoal was not initialized.");
	}
#endif
	return(pGoal);*/
/*
	return(pStart->getCurrentGoal());
}

inline void PREBUILDORDER::setStartPosition(const unsigned int start_position) 
{
	if(pStart->setStartPosition(start_position))
		setConditionsChanged();
}

inline void PREBUILDORDER::setStartRace(const unsigned int start_race) // => gleichzeitig wird harvestspeed geaendert und condition und goal muessen u.U. neugewaehlt werden!
{
	if(pStart->setPlayerRace(start_race))
		setConditionsChanged();
}

inline void PREBUILDORDER::assignStartGoal(const GOAL_ENTRY* start_goal) {
	if(pStart->assignGoal(start_goal))
		setConditionsChanged();
}



// ------ Units ------

inline Units& PREBUILDORDER::getUnit(const unsigned int player_number, const unsigned int location_number) const {
	assert(player_number < (*getMap())->getMaxPlayer());
	assert(location_number < (*getMap())->getMaxLocations());

	return(unit[player_number][location_number]);
}

inline const unsigned int PREBUILDORDER::getLocationTotal(const unsigned int location_number, const unsigned int unit_type) const {
	return(getUnit(playerNum, location_number).getTotal(unit_type));
}

inline const unsigned int PREBUILDORDER::getLocationAvailable(const unsigned int location_number, const unsigned int unit_type) const {
	return(getUnit(playerNum, location_number).getAvailable(unit_type));
}

inline void PREBUILDORDER::modifyLocationAvailable(const unsigned int location_number, const unsigned int unit_type, const signed int available)
{
	getUnit(getPlayerNumber(), location_number).modifyAvailable(unit_type, available);
	if(location_number!=GLOBAL) //sonst waers ja doppelt...
		getUnit(getPlayerNumber(), GLOBAL).modifyAvailable(unit_type, available);
}

inline void PREBUILDORDER::modifyLocationTotal(const unsigned int location_number, const unsigned int unit_type, const signed int total)
{
	getUnit(getPlayerNumber(), location_number).modifyTotal( unit_type, total );
	if(location_number!=GLOBAL) // sonst waers ja doppelt wenn location = 0
		getUnit(getPlayerNumber(), GLOBAL).modifyTotal(unit_type, total);
}

inline void PREBUILDORDER::addOneLocationAvailable(const unsigned int location_number, const unsigned int unit_type)
{
	getUnit(getPlayerNumber(), location_number).addOneAvailable( unit_type );
// also add one unit to the global location if global location was not already specified
	if(location_number!=GLOBAL) 
		getUnit(getPlayerNumber(), GLOBAL).addOneAvailable( unit_type );
}

inline void PREBUILDORDER::addOneLocationTotal(const unsigned int location_number, const unsigned int unit_type)
{
	getUnit(getPlayerNumber(), location_number).addOneTotal( unit_type );
	if(location_number!=GLOBAL) // sonst waers ja doppelt wenn location = 0
		getUnit(getPlayerNumber(), GLOBAL).addOneTotal( unit_type );
}

inline void PREBUILDORDER::removeOneLocationAvailable(const unsigned int location_number, const unsigned int unit_type)
{
	getUnit(getPlayerNumber(), location_number).removeOneAvailable( unit_type );
// also add one unit to the global location if global location was not already specified
	if(location_number!=GLOBAL)
		getUnit(getPlayerNumber(), GLOBAL).removeOneAvailable( unit_type );
}

inline void PREBUILDORDER::removeOneLocationTotal(const unsigned int location_number, const unsigned int unit_type)
{
	getUnit(getPlayerNumber(), location_number).removeOneTotal( unit_type );
	if(location_number!=GLOBAL) 
		getUnit(getPlayerNumber(), GLOBAL).removeOneTotal( unit_type );
}


inline void PREBUILDORDER::removeOneLocationTotalAllPlayers(const unsigned int location_number, const unsigned int unit_type)
{
	for(unsigned int i = (*getMap())->getMaxPlayer(); i--;)
		getUnit(i, location_number).removeOneTotal( unit_type );
}

inline void PREBUILDORDER::removeOneLocationAvailableAllPlayers(const unsigned int location_number, const unsigned int unit_type)
{
	for(unsigned int i = (*getMap())->getMaxPlayer(); i--;)
		getUnit(i, location_number).removeOneAvailable( unit_type );
}

inline void PREBUILDORDER::removeOneTotalEverywhere(const unsigned int unit_type) // for researchs
{
	for(unsigned int i = (*getMap())->getMaxLocations(); i--;)
		getUnit(getPlayerNumber(), i).removeOneTotal( unit_type );
}

inline void PREBUILDORDER::removeOneAvailableEverywhere(const unsigned int unit_type) // for researchs
{
	for(unsigned int i = (*getMap())->getMaxLocations(); i--;)
		getUnit(getPlayerNumber(), i).removeOneAvailable( unit_type );
}

// ------ END Units -----


// ----- SUPPLY ------
inline void PREBUILDORDER::setNeedSupply(const unsigned int need_supply) {
	assert(need_supply <= 2*GAME::MAX_SUPPLY);

	needSupply = need_supply;
}

inline const unsigned int PREBUILDORDER::getNeedSupply() const {
	assert(needSupply <= 2*GAME::MAX_SUPPLY);

	return(needSupply);
}

inline void PREBUILDORDER::setHaveSupply(const unsigned int have_supply) {
	assert(have_supply <= 2*GAME::MAX_SUPPLY);

	haveSupply = have_supply;
}

inline const unsigned int PREBUILDORDER::getHaveSupply() const {
	assert(haveSupply <= 2*GAME::MAX_SUPPLY);

	return(haveSupply);
}
// ----- END SUPPLY ------

// ----- HARVEST ------

inline void PREBUILDORDER::setResource(const unsigned int resource_type, const unsigned int have_resource) {
	assert(resource_type < GameRace::MAX_RESOURCE_TYPES);
	assert(have_resource <= GAME::MAX_RESOURCES);

	resource[resource_type] = have_resource;
}

inline const unsigned int PREBUILDORDER::getResource(const unsigned int resource_type) const {
	assert(resource_type < GameRace::MAX_RESOURCE_TYPES);
	assert(resource[resource_type] <= GAME::MAX_RESOURCES);

	return(resource[resource_type]);
}
/*
inline void PREBUILDORDER::setResourceHarvestPerFrame( const unsigned int resource_type, const unsigned int location_number, const unsigned int worker, const unsigned int resource_harvest_per_frame ) {
#ifdef _SCC_DEBUG
	if(resource_type >= GameRace::MAX_RESOURCE_TYPES) {
		toErrorLog("DEBUG (PREBUILDORDER::setResourceHarvestPerFrame()): Value resource_type out of range.");return;
	}
	if(resource_harvest_per_frame >= GAME::MAX_RESOURCES) {
		toErrorLog("DEBUG (PREBUILDORDER::setResourceHarvestPerFrame()): Value resource_harvest_per_frame out of range.");return;
	}
	if((location_number >= (*getMap())->getMaxLocations())) {
		toErrorLog("DEBUG (PREBUILDORDER::setResourceHarvestPerFrame()): Value location_number out of range.");return;
	}
	if(worker>=45) { // TODO
		toErrorLog("DEBUG (PREBUILDORDER::setResourceHarvestPerFrame()): Value worker out of range.");return;
	}
#endif
	resourceHarvestPerFrame[location_number][resource_type][worker] = resource_harvest_per_frame;
}*/

/*

inline void PREBUILDORDER::setHarvestedResource( const unsigned int resource_type, const unsigned int harvested_resource ) {
	assert(resource_type < GameRace::MAX_RESOURCE_TYPES);
	assert(harvested_resource < GAME::MAX_RESOURCES);

	harvestedResource[resource_type] = harvested_resource;
}

inline const unsigned int PREBUILDORDER::getHarvestedResource( const unsigned int resource_type ) const {
	assert(resource_type < GameRace::MAX_RESOURCE_TYPES);
	assert(harvestedResource[resource_type] <= GAME::MAX_RESOURCES);

	return(harvestedResource[resource_type]);
}

// ----- END HARVEST -----


inline const START_CONDITION* const* PREBUILDORDER::getStartCondition() const {
	return(pStart->getStartCondition());
}


inline void PREBUILDORDER::setTimer(const unsigned int time) {
	assert(time <= coreConfiguration.getMaxTime());

	timer = time;
}

inline const unsigned int PREBUILDORDER::getTimer() const {
	assert(timer <= coreConfiguration.getMaxTime());

	return(timer);
}

inline const unsigned int PREBUILDORDER::getRealTimer() const {
	assert(timer <= coreConfiguration.getMaxTime());

	return(coreConfiguration.getMaxTime()-timer);
	// TODO auf > checken
}

inline const std::vector<UnitStatistics>* PREBUILDORDER::getpStats() const {
/*#ifdef _SCC_DEBUG
	if(!pStatsInitialized)	{
		toErrorLog("DEBUG (PREBUILDORDER::getpStats()()): Variable pStats not initialized.");return(0);
	}
#endif
	return(pStats);*/
	/*return(pStart->getpStats());
}


inline void PREBUILDORDER::resetTimeOut() {
	timeout = coreConfiguration.getMaxTimeOut();
}

inline void PREBUILDORDER::setTimeOut(const unsigned int time_out) {
	if(timeout == time_out)
		return;	
	assert(time_out <= coreConfiguration.getMaxTimeOut());

	timeout = time_out;
}

inline const bool PREBUILDORDER::isTimeOut() const {
	assert(timeout <= coreConfiguration.getMaxTimeOut());

	return(timeout==0);
}

inline const unsigned int PREBUILDORDER::getTimeOut() const {
	assert(timeout <= coreConfiguration.getMaxTimeOut());

	return(timeout);
}


// --------------------------------------
// ------ END OF GET/SET FUNCTIONS ------
// --------------------------------------

inline void PREBUILDORDER::removeLarvaFromQueue(const unsigned int location_number) {
	assert(location_number > 0 && location_number < (*getMap())->getMaxLocations());
	assert(larvaInProduction[location_number]>0 && larvaInProduction[location_number] < GAME::MAX_SUPPLY);

	--larvaInProduction[location_number];
}

inline void PREBUILDORDER::addLarvaToQueue(const unsigned int location_number) {
	assert(location_number > 0 && location_number < (*getMap())->getMaxLocations());
	assert(larvaInProduction[location_number] < GAME::MAX_SUPPLY);

	++larvaInProduction[location_number];
}


inline const bool PREBUILDORDER::isAlwaysBuildWorkers() const {
	return(alwaysBuildWorkers);
}

inline const bool PREBUILDORDER::isOnlySwapOrders() const {
	return(onlySwapOrders);
}

inline void PREBUILDORDER::assignCode(const PREBUILDORDER& player) {
	Code = player.Code;
}

inline void PREBUILDORDER::assignCode(const std::list<unsigned int>& src) {
	Code = src;
}

inline void PREBUILDORDER::copyCode(std::list<unsigned int>& dst) const {
	dst = Code;
}

inline const bool PREBUILDORDER::isDifferent(const std::list<unsigned int>& code) const {
	return(Code != code);
}


#endif // __PREBUILDORDER_H

*/



#endif // _AI_BUILDORDER_HPP
