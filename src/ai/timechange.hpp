#ifndef _AI_TIMECHANGE_HPP
#define _AI_TIMECHANGE_HPP

// class that holds the changes of resources per time tick

#include <unitresourcetype.hpp>
#include <units.hpp>
#include <rules.hpp>

class TimeChange
{
public:
	// calculate the change of global resources according to the list of units 
	TimeChange(const Player& player, const Units* const units, const Rules& rules);
	~TimeChange();

	const std::map<unsigned int, UnitResourceType> getChangeResource() const;

private:
	std::map<unsigned int, UnitResourceType> changeResource; // unitTypeID -> resourceType, need to be in a map in order to swiftly gather identical resource increases together.
};

inline const std::map<unsigned int, UnitResourceType> TimeChange::getChangeResource() const {
	return changeResource;
}

#endif // _AI_TIMECHANGE_HPP