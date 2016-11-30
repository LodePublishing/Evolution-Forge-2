#ifndef _AI_NEEDEDRESOURCE_HPP
#define _AI_NEEDEDRESOURCE_HPP


#include <map>
#include <unit.hpp>

class NeededResource
{
public:
	NeededResource() {}
	~NeededResource() {}

	void resetNeededResources();

	// temporary variables holding the needed resources
	// together with TimeChange a time can be calculated how long this build order has to wait until a new unit can be built
	std::map<UnitGlobalKey, unsigned int> neededGlobalResources; // playerId -> unitTypeId -> amount
	std::map<UnitLocalKey, unsigned int> neededLocalResources; // locationId -> playerId -> unitTypeId -> amount
	std::map<UnitLocalNeutralKey, unsigned int> neededLocalNeutralResources; // locationId -> unitTypeId -> amount

private:

};

#endif // _AI_NEEDEDRESOURCE_HPP