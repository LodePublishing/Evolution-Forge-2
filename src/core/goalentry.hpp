#ifndef _CORE_GOALENTRY_HPP
#define _CORE_GOALENTRY_HPP

#include <string>
#include <vector>
#include <list>

#pragma warning(push, 0)  
#include <boost/serialization/base_object.hpp>
#include <boost/config.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/nvp.hpp>
#pragma warning(pop)

#include "goal.hpp"
#include "id.hpp"


class GoalEntry : public ID<GoalEntry>
{
public:
	GoalEntry(const std::string& goal_name, const std::list<std::list<std::list<Goal> > >& goalList):name(goal_name),goalList(goalList) {}
	~GoalEntry() {}

	const std::string& getName() const;
	// AND list ... OR list :)
	const std::list<std::list<std::list<Goal> > >& getGoalList() const;


	static const char* const Name_tag_string;
	static const char* const GoalList_tag_string;

private:
	friend class boost::serialization::access;

	template<class Archive> void serialize(Archive &ar, const unsigned int version)
	{
		ar & boost::serialization::make_nvp(ID_tag_string, id);
		ar & boost::serialization::make_nvp(Name_tag_string, name);
		ar & boost::serialization::make_nvp(GoalList_tag_string, goalList);
		if(version > 0) {
		}
	}
	GoalEntry() {}

	std::string name;
	std::list<std::list<std::list<Goal> > > goalList;
};

inline const std::list<std::list<std::list<Goal> > >& GoalEntry::getGoalList() const {
	return goalList;
}

inline const std::string& GoalEntry::getName() const {
	return name;
}


#endif // _CORE_GOALENTRY_HPP

