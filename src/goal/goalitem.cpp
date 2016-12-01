#include "goalitem.hpp"

GoalItem::GoalItem(const boost::uuids::uuid unitTypeId, const boost::uuids::uuid locationId, const unsigned int count, const unsigned int time) :
	unitTypeId(unitTypeId),
	locationId(locationId),
	count(count),
	time(time)
{ }
	
GoalItem::~GoalItem()
{ }

GoalItem::GoalItem(const GoalItem& object) :
	unitTypeId(object.unitTypeId),
	locationId(object.locationId),
	count(object.count),
	time(object.time)
{ }


bool GoalItem::operator<(const GoalItem& goal)
{
	return getLocationId() < goal.getLocationId();
}

bool GoalItem::operator==(const GoalItem& goal) const {
	return unitTypeId == goal.unitTypeId && time == goal.time && count == goal.count && locationId == goal.locationId;
}

// TODO in CoreConfiguration rein!?
// CoreConfiguration an Player/AI binden!
const unsigned int GoalItem::GOAL_MAX_TIME = 1800;
