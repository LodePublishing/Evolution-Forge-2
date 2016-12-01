#ifndef _GOAL_GOALENTRY_HPP
#define _GOAL_GOALENTRY_HPP

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

#include <misc/uuid.hpp>

#include "goalitem.hpp"

class GoalEntry : public UUID<GoalEntry>
{
public:
	GoalEntry(const boost::uuids::uuid id, const std::string& name, const std::list<std::list<std::list<GoalItem> > >& goalItemList);
	GoalEntry(const std::string& name, const std::list<std::list<std::list<GoalItem> > >& goalItemList);
	~GoalEntry() {}

	const std::string& getName() const;

	// ALL [std::list<std::list<GoalItem> >]s in the std::list<[std::list<std::list<GoalItem> >] > list have to be fulfilled (AND)
	// ANY [std::list<GoalItem>]s in the std::list<[std::list<GoalItem>] > list have to be fulfilled (OR)
	// ALL [Goal]s in the std::list<GoalItem> have to be fulfilled (AND)
	const std::list<std::list<std::list<GoalItem> > >& getGoalItemList() const;

private:
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{ }

	template<class Archive>
	inline friend void save_construct_data(Archive &ar, GoalEntry* goalEntry, const unsigned int version) { 

		const boost::uuids::uuid& id = goalEntry->getId();
		const std::string& name = goalEntry->getName();
		const std::list<std::list<std::list<GoalItem> > >& goalItemList = goalEntry->getGoalItemList();

		if(version > 0) {
		}

		ar & BOOST_SERIALIZATION_NVP(id)
		   & BOOST_SERIALIZATION_NVP(name)
		   & BOOST_SERIALIZATION_NVP(goalItemList);
	} 

	template<class Archive> 
	inline friend void load_construct_data(Archive& ar, GoalEntry*& goalEntry, const unsigned int version)
	{
		boost::uuids::uuid id;
		std::string name;
		std::list<std::list<std::list<GoalItem> > > goalItemList;

		ar & BOOST_SERIALIZATION_NVP(id)
		   & BOOST_SERIALIZATION_NVP(name)
		   & BOOST_SERIALIZATION_NVP(goalItemList);

		::new(goalEntry)GoalEntry(id, name, goalItemList);
	}

	const std::string name;
	const std::list<std::list<std::list<GoalItem> > > goalItemList;

	GoalEntry& operator=(const GoalEntry& other);
};

inline const std::list<std::list<std::list<GoalItem> > >& GoalEntry::getGoalItemList() const {
	return goalItemList;
}

inline const std::string& GoalEntry::getName() const {
	return name;
}


#endif // _GOAL_GOALENTRY_HPP

