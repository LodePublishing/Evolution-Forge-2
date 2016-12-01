#include "buildorder.hpp"

BuildOrder::BuildOrder(int locationCount):
	goalsReached(false)
{
	for(int i = 0; i < locationCount; i++) {
		code[i] = Code();
	}
}

BuildOrder::~BuildOrder()
{ }

// TODO if a code has finished 0 is returned...
const std::vector<unsigned int> BuildOrder::getCurrentCode() const {
	std::vector<unsigned int> currentCodeList;
	for(int i = 0; i < code.size(); i++) {
		currentCodeList.push_back(code[i].getCurrentCode());
	}
	return currentCodeList;
}

void BuildOrder::initialize() {
	
}

const bool BuildOrder::isFinished() const {
	for(int i = 0; i < code.size(); i++) {
		if(!code[i].isCodeFinished()) {
			return false;
		}
	}
	return true;
}

bool BuildOrder::isCalculationDone() const {

	if((goalsReached) || (!getTimer()) || (isFinished() && (buildingQueue.empty() || (!getTimeOut()))))
	{
//		eraseRemainingCode();
		if(!ready) 
		{
			ready = calculateReady();
			if(!ready) {
				setTimer(0);
			}
		}		
		return true;
	}
	return false;

}
