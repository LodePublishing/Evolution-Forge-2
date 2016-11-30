#include "goal.hpp"

Goal::Goal(const boost::uuids::uuid unitTypeId, const boost::uuids::uuid locationId, const unsigned int count, const unsigned int time) :
	unitTypeId(unitTypeId),
	locationId(locationId),
	count(count),
	time(time)
{ }
	
Goal::~Goal()
{ }

Goal::Goal(const Goal& object) :
	unitTypeId(object.unitTypeId),
	locationId(object.locationId),
	count(object.count),
	time(object.time)
{ }


bool Goal::operator<(const Goal& goal)
{
	return(getLocationId() < goal.getLocationId());
}

bool Goal::operator==(const Goal& goal) const {
	return unitTypeId == goal.unitTypeId && time == goal.time && count == goal.count && locationId == goal.locationId;
}

// TODO in CoreConfiguration rein!?
// CoreConfiguration an Player/AI binden!
const unsigned int Goal::GOAL_MAX_TIME = 1800;
