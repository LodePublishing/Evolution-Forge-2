#include "goalentry.hpp"

GoalEntry::GoalEntry(const boost::uuids::uuid id, const std::string& name, const std::list<std::list<std::list<GoalItem> > >& goalItemList):
	UUID<GoalEntry>(id), 
	name(name), 
	goalItemList(goalItemList) 
{
}

GoalEntry::GoalEntry(const std::string& name, const std::list<std::list<std::list<GoalItem> > >& goalItemList):
	name(name),
	goalItemList(goalItemList) 
{ }
