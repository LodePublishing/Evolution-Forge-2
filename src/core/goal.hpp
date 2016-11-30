#ifndef _CORE_GOAL_HPP
#define _CORE_GOAL_HPP

#pragma warning(push, 0)  
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/assert.hpp>
#pragma warning(pop)

class Goal
{
	public:
		Goal(const unsigned int unitTypeID, const unsigned int locationID, const unsigned int count, const unsigned int time = GOAL_MAX_TIME);
		~Goal();
		bool operator<(const Goal& goal);
		Goal(const Goal& goal);
		Goal& operator=(const Goal& goal);

		unsigned int getUnitTypeID() const;
		unsigned int getTime() const;
		unsigned int getCount() const;
		unsigned int getLocationID() const;

		static const unsigned int GOAL_MAX_TIME;

		static const char* const unitTypeID_tag_string;
		static const char* const locationID_tag_string;
		static const char* const count_tag_string;
		static const char* const time_tag_string;

	private:
		friend class boost::serialization::access;
		template<class Archive> void serialize(Archive &ar, const unsigned int version)
		{
			ar & boost::serialization::make_nvp(unitTypeID_tag_string, unitTypeID);
			ar & boost::serialization::make_nvp(locationID_tag_string, locationID);
			ar & boost::serialization::make_nvp(count_tag_string, count);
			ar & boost::serialization::make_nvp(time_tag_string, time);
			if(version > 0) {
			}
		}
		Goal() {}

		unsigned int unitTypeID;
		unsigned int locationID;

		// count can be 0! Then it is a 'bonus'
		unsigned int count;
		unsigned int time;
};


inline unsigned int Goal::getUnitTypeID() const
{
	return unitTypeID;
}

inline unsigned int Goal::getTime() const
{
	return time;
}

inline unsigned int Goal::getCount() const
{
	return count;
}

inline unsigned int Goal::getLocationID() const
{
	return locationID;
}


#endif // _CORE_GOAL_HPP