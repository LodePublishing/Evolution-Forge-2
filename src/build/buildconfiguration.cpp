#include "buildconfiguration.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

BuildConfiguration::BuildConfiguration(const boost::uuids::uuid id,
		const unsigned int crossingOver, 
		const unsigned int breedFactor, 
		const unsigned int mutationFactor,
		const unsigned int maxTime, 
		const unsigned int maxTimeOut, 
		const unsigned int maxLength, 
		const unsigned int maxRuns,
		const unsigned int maxGenerations, 
		const unsigned int noise,
		const bool preprocessBuildOrder, 
		const bool allowGoalAdaption, 
		const bool alwaysBuildWorker, 
		const bool onlySwapOrders):
UUID<BuildConfiguration>(id),
		crossingOver(crossingOver), 
		breedFactor(breedFactor), 
		mutationFactor(mutationFactor),
		maxTime(maxTime), 
		maxTimeOut(maxTimeOut), 
		maxLength(maxLength), 
		maxRuns(maxRuns),
		maxGenerations(maxGenerations), 
		noise(noise),
		preprocessBuildOrder(preprocessBuildOrder), 
		allowGoalAdaption(allowGoalAdaption), 
		alwaysBuildWorker(alwaysBuildWorker), 
		onlySwapOrders(onlySwapOrders)
{ }

BuildConfiguration::BuildConfiguration(
		const unsigned int crossingOver, 
		const unsigned int breedFactor, 
		const unsigned int mutationFactor,
		const unsigned int maxTime, 
		const unsigned int maxTimeOut, 
		const unsigned int maxLength, 
		const unsigned int maxRuns,
		const unsigned int maxGenerations, 
		const unsigned int noise,
		const bool preprocessBuildOrder, 
		const bool allowGoalAdaption, 
		const bool alwaysBuildWorker, 
		const bool onlySwapOrders):
UUID<BuildConfiguration>(),
		crossingOver(crossingOver), 
		breedFactor(breedFactor), 
		mutationFactor(mutationFactor),
		maxTime(maxTime), 
		maxTimeOut(maxTimeOut), 
		maxLength(maxLength), 
		maxRuns(maxRuns),
		maxGenerations(maxGenerations), 
		noise(noise),
		preprocessBuildOrder(preprocessBuildOrder), 
		allowGoalAdaption(allowGoalAdaption), 
		alwaysBuildWorker(alwaysBuildWorker), 
		onlySwapOrders(onlySwapOrders)
{ }

BuildConfiguration::~BuildConfiguration()
{ }

/*
BuildConfiguration::BuildConfiguration(): 
	crossingOver(MIN_CROSSING_OVER),
	breedFactor(20),
	mutationFactor(200),
	maxTime(MAX_TIME),
	maxTimeOut(MAX_TIMEOUT),
	maxLength(MAX_LENGTH),
	maxRuns(MAX_RUNS),
	maxGenerations(200),
	noise(0),
	preprocessBuildOrder(false),
	allowGoalAdaption(true),
	alwaysBuildWorker(false),
	onlySwapOrders(false),
	configurationFile("settings/core.cfg")
{ }

void BuildConfiguration::initDefaults()
{
	setCrossingOver(MIN_CROSSING_OVER);
	setBreedFactor(20);
	setMutationFactor(200);
	setMaxTime(MAX_TIME-1);
	setMaxTimeOut(MAX_TIMEOUT-1);
	setMaxLength(MAX_LENGTH-1);
	setMaxRuns(MAX_RUNS-1);
	setMaxGenerations(MAX_GENERATIONS-1);
	setNoise(0);
	setPreprocessBuildOrder(false);
	setAllowGoalAdaption(true);
	setAlwaysBuildWorker(false);
	setOnlySwapOrders(false);
	configurationFile = "settings/core.cfg";
}*/

/*

const unsigned int MAX_MUTATION_FACTOR = 400;
const unsigned int MIN_MUTATION_FACTOR = 1;

const unsigned int MAX_BREED_FACTOR = 40;
const unsigned int MIN_BREED_FACTOR = 0;

const unsigned int MIN_NOISE = 0;
const unsigned int MAX_NOISE = 100;

const unsigned int MAX_CROSSING_OVER = 40;
const unsigned int MIN_CROSSING_OVER = 0;

*/