#include "goalentry.hpp"

#include "globalstorage.hpp"

GoalEntry::GoalEntry(const boost::uuids::uuid id, const std::string& name, const std::list<std::list<std::list<Goal> > >& goalList):
	UUID<GoalEntry>(id), 
	name(name), 
	goalList(goalList) 
{
}

GoalEntry::GoalEntry(const std::string& name, const std::list<std::list<std::list<Goal> > >& goalList):
	name(name),
	goalList(goalList) 
{ }