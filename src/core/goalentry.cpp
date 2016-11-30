#include "goalentry.hpp"

GoalEntry::GoalEntry(const unsigned int id, const std::string& name, const std::list<std::list<std::list<Goal> > >& goalList):
	ID<GoalEntry>(id), 
	name(name), 
	goalList(goalList) 
{ }

GoalEntry::GoalEntry(const std::string& name, const std::list<std::list<std::list<Goal> > >& goalList):
	name(name),
	goalList(goalList) 
{ }