#include "goal.hpp"


Goal::Goal(const unsigned int unitTypeID, const unsigned int locationID, const unsigned int count, const unsigned int time) :
	unitTypeID(unitTypeID),
	locationID(locationID),
	count(count),
	time(time)
{}
	
Goal::~Goal()
{ 
}

Goal::Goal(const Goal& object) :
	unitTypeID(object.unitTypeID),
	locationID(object.locationID),
	count(object.count),
	time(object.time)
{ }

Goal& Goal::operator=(const Goal& object)
{
	unitTypeID = object.unitTypeID;
	time = object.time;
	count = object.count;
	locationID = object.locationID;
	return(*this);
}

bool Goal::operator<(const Goal& goal)
{
	return(getLocationID() < goal.getLocationID());
}

// TODO in CoreConfiguration rein!
// CoreConfiguration an Player/AI binden!
const unsigned int Goal::GOAL_MAX_TIME = 1800;

const char* const Goal::unitTypeID_tag_string = "unitTypeID";
const char* const Goal::locationID_tag_string = "locationID";
const char* const Goal::count_tag_string = "count";
const char* const Goal::time_tag_string = "time";
