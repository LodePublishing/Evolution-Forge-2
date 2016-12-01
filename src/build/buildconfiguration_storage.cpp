#include "buildconfiguration_storage.hpp"

#include "buildconfiguration.hpp"

#include <misc/io.hpp>

template<> const std::string SingleStorage<BuildConfiguration>::DATA_FILE_NAME_BASE = IO::getDirectory(boost::assign::list_of("data")("storage")("build")) + "buildconfiguration.xml";
template<> const std::string SingleStorage<BuildConfiguration>::DATA_FILE_IDENTIFIER = "BuildConfigurationStorage";

template<> boost::shared_ptr<BuildConfiguration> NodeCreator<BuildConfiguration>::createObjectFromNode(const std::vector<XmlNode>& node) {
	return boost::shared_ptr<BuildConfiguration>(new BuildConfiguration(
		Misc::uuid(node[0]), 
		boost::lexical_cast<unsigned int>(node[1].getValue()),
		boost::lexical_cast<unsigned int>(node[2].getValue()),
		boost::lexical_cast<unsigned int>(node[3].getValue()),
		boost::lexical_cast<unsigned int>(node[4].getValue()),
		boost::lexical_cast<unsigned int>(node[5].getValue()),
		boost::lexical_cast<unsigned int>(node[6].getValue()),
		boost::lexical_cast<unsigned int>(node[7].getValue()),
		boost::lexical_cast<unsigned int>(node[8].getValue()),
		boost::lexical_cast<unsigned int>(node[9].getValue()),
		boost::lexical_cast<bool>(node[10].getValue()), 
		boost::lexical_cast<bool>(node[11].getValue()), 
		boost::lexical_cast<bool>(node[12].getValue()), 
		boost::lexical_cast<bool>(node[13].getValue())
		));


}

template<> XmlNode NodeCreator<BuildConfiguration>::createNodeFromObject(const BuildConfiguration& t) {
	XmlNode n("buildconfiguration");
	n.addChild(XmlNode("id", boost::lexical_cast<std::string>(t.getId())));
	n.addChild(XmlNode("CrossingOver", boost::lexical_cast<std::string>(t.getCrossingOver())));	
	n.addChild(XmlNode("BreedFactor", boost::lexical_cast<std::string>(t.getBreedFactor())));	
	n.addChild(XmlNode("MutationFactor", boost::lexical_cast<std::string>(t.getMutationFactor())));	
	n.addChild(XmlNode("MaxTime", boost::lexical_cast<std::string>(t.getMaxTime())));	
	n.addChild(XmlNode("MaxTimeOut", boost::lexical_cast<std::string>(t.getMaxTimeOut())));	
	n.addChild(XmlNode("MaxLength", boost::lexical_cast<std::string>(t.getMaxLength())));	
	n.addChild(XmlNode("MaxRuns", boost::lexical_cast<std::string>(t.getMaxRuns())));
	n.addChild(XmlNode("MaxGenerations", boost::lexical_cast<std::string>(t.getMaxGenerations())));	
	n.addChild(XmlNode("Noise", boost::lexical_cast<std::string>(t.getNoise())));	
	n.addChild(XmlNode("PreprocessBuildOrder", boost::lexical_cast<std::string>(t.isPreprocessBuildOrder())));
	n.addChild(XmlNode("AllowGoalAdaption", boost::lexical_cast<std::string>(t.isAllowGoalAdaption())));
	n.addChild(XmlNode("AlwaysBuildWorker", boost::lexical_cast<std::string>(t.isAlwaysBuildWorker())));
	n.addChild(XmlNode("OnlySwapOrders", boost::lexical_cast<std::string>(t.isOnlySwapOrders())));
	return n;
}




#if 0
inline void BuildConfiguration::setCrossingOver(const unsigned int crossing_over) 
{
#ifdef _SCC_DEBUG
	if((crossing_over<MIN_CROSSING_OVER)||(crossing_over>MAX_CROSSING_OVER)) {
		toLog("WARNING: (BuildConfiguration::setCrossingOver): Value out of range.");return;
	}
#endif
	crossingOver = crossing_over;
}

inline void BuildConfiguration::setBreedFactor(const unsigned int breed_factor) 
{
#ifdef _SCC_DEBUG
	if((breed_factor<MIN_BREED_FACTOR)||(breed_factor>MAX_BREED_FACTOR)) {
		toLog("WARNING: (BuildConfiguration::setBreedFactor): Value out of range.");return;
	}
#endif
	breedFactor = breed_factor;
}
inline void BuildConfiguration::setMutationFactor(const unsigned int mutation_factor) 
{
#ifdef _SCC_DEBUG
	if((mutation_factor<MIN_MUTATION_FACTOR)||(mutation_factor>MAX_MUTATION_FACTOR)) {
		toLog("WARNING: (BuildConfiguration::setMutationFactor): Value out of range.");return;
	}
#endif
	mutationFactor = mutation_factor;
}

inline void BuildConfiguration::setMaxTime(const unsigned int max_time) 
{
#ifdef _SCC_DEBUG
	if((max_time<MIN_TIME)||(max_time>MAX_TIME)) {
		toLog("WARNING: (BuildConfiguration::setMaxTime): Value out of range.");return;
	}
#endif
	maxTime = max_time;
}

inline void BuildConfiguration::setMaxTimeOut(const unsigned int time_out) 
{
#ifdef _SCC_DEBUG
	if((time_out<MIN_TIMEOUT)||(time_out>MAX_TIMEOUT)) {
		toLog("WARNING: (BuildConfiguration::setMaxTimeOut): Value out of range.");return;
	}
#endif
	maxTimeOut = time_out;
}

inline void BuildConfiguration::setMaxLength(const unsigned int max_length) 
{
#ifdef _SCC_DEBUG
	if((max_length<MIN_LENGTH)||(max_length>MAX_LENGTH)) {
		toLog("WARNING: (BuildConfiguration::setMaxLength): Value out of range.");return;
	}
#endif
	maxLength = max_length;
}

inline void BuildConfiguration::setMaxRuns(const unsigned int max_runs) 
{
#ifdef _SCC_DEBUG
	if((max_runs<MIN_RUNS)||(max_runs>MAX_RUNS)) {
		toLog("WARNING: (BuildConfiguration::setMaxRuns): Value out of range.");return;
	}
#endif
	maxRuns = max_runs;
}

inline void BuildConfiguration::setMaxGenerations(const unsigned int max_generations) 
{
#ifdef _SCC_DEBUG
	if((max_generations<MIN_GENERATIONS)||(max_generations>MAX_GENERATIONS)) {
		toLog("WARNING: (BuildConfiguration::setMaxGenerations): Value out of range.");return;
	}
#endif
	maxGenerations = max_generations;
}

inline void BuildConfiguration::setNoise(const unsigned int desired_noise)
{
#ifdef _SCC_DEBUG
	if((desired_noise < MIN_NOISE)||(desired_noise > MAX_NOISE)) {
		toLog("WARNING: (BuildConfiguration::setNoise): Value out of range.");return;
	}
#endif
	noise = desired_noise;
}

#endif