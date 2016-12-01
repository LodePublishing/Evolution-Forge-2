#ifndef _BUILD_CONFIGURATION_HPP
#define _BUILD_CONFIGURATION_HPP

#pragma warning(push, 0)  
#include <boost/uuid/uuid.hpp>
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <misc/uuid.hpp>



class BuildConfiguration : public UUID<BuildConfiguration>
{
public:
	BuildConfiguration(const boost::uuids::uuid id,
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
		const bool onlySwapOrders);

	BuildConfiguration(
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
		const bool onlySwapOrders);
	
	~BuildConfiguration();

	unsigned int getCrossingOver() const;
	unsigned int getBreedFactor() const;
	unsigned int getMutationFactor() const;
	unsigned int getMaxTime() const;
	unsigned int getMaxTimeOut() const;
	unsigned int getMaxLength() const;
	unsigned int getMaxRuns() const;
	unsigned int getMaxGenerations() const;
	unsigned int getNoise() const;
	
	bool isPreprocessBuildOrder() const;
	bool isAllowGoalAdaption() const;
	bool isAlwaysBuildWorker() const;
	bool isOnlySwapOrders() const;

private:
	const unsigned int crossingOver;			// percentage of population that should exchange their genetic informations with each other
	const unsigned int breedFactor;		// percentage of population that should copy 1:1 their genetic informations 
	const unsigned int mutationFactor;
	const unsigned int maxTime;			// border of global searchspace in seconds (the lower the faster but needs longer to get a valid solution at the first place)
	const unsigned int maxTimeOut;			// border of local searchspace in seconds (how long the program should be allowed to wait until prerequisites of an item are fulfilled)
	const unsigned int maxLength;			// max length of individual (as maxTime)
	const unsigned int maxRuns;			// how many different solutions should be searched
	const unsigned int maxGenerations;		// how many unchanged generations shall occur until the run is terminated
	const unsigned int noise; //in %
	
	const bool preprocessBuildOrder; // should the program create a basic valid solution? TODO: IMPLEMENT IT!
	const bool allowGoalAdaption;
	const bool alwaysBuildWorker;
	const bool onlySwapOrders;
	
	BuildConfiguration();
};

inline unsigned int BuildConfiguration::getCrossingOver() const {
	return crossingOver;
}

inline unsigned int BuildConfiguration::getBreedFactor() const {
	return breedFactor;
}

inline unsigned int BuildConfiguration::getMutationFactor() const {
	return mutationFactor;
}

inline unsigned int BuildConfiguration::getMaxTime() const {
	return maxTime;
}

inline unsigned int BuildConfiguration::getMaxTimeOut() const {
	return maxTimeOut;
}

inline unsigned int BuildConfiguration::getMaxLength() const {
	return maxLength;
}

inline unsigned int BuildConfiguration::getMaxRuns() const {
	return maxRuns;
}

inline unsigned int BuildConfiguration::getMaxGenerations() const {
	return maxGenerations;
}

inline unsigned int BuildConfiguration::getNoise() const {
	return noise;
}

inline bool BuildConfiguration::isPreprocessBuildOrder() const {
	return preprocessBuildOrder;
}

inline bool BuildConfiguration::isAllowGoalAdaption() const {
	return allowGoalAdaption;
}

inline bool BuildConfiguration::isAlwaysBuildWorker() const {
	return alwaysBuildWorker;
}

inline bool BuildConfiguration::isOnlySwapOrders() const {
	return onlySwapOrders;
}


#endif // _BUILD_CONFIGURATION_HPP



