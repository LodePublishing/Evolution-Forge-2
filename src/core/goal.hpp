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
		Goal(const unsigned int unitTypeId, const unsigned int locationId, const unsigned int count, const unsigned int time = GOAL_MAX_TIME);
		~Goal();
		bool operator<(const Goal& goal);
		Goal(const Goal& goal);
		bool operator==(const Goal& goal) const;

		unsigned int getUnitTypeId() const;
		unsigned int getTime() const;
		unsigned int getCount() const;
		unsigned int getLocationId() const;

		static const unsigned int GOAL_MAX_TIME;

	private:
		friend class boost::serialization::access;

		template<class Archive> 
		void serialize(Archive &ar, const unsigned int version)
		{ }

		template<class Archive>
		friend inline void save_construct_data(Archive &ar, const Goal* goal, const unsigned int version) { 

			const unsigned int& unitTypeId = goal->getUnitTypeId();
			const unsigned int& locationId = goal->getLocationId();
			const unsigned int& count = goal->getCount();
			const unsigned int& time = goal->getTime();

			if(version > 0) {
			}

			ar & BOOST_SERIALIZATION_NVP(unitTypeId)
			   & BOOST_SERIALIZATION_NVP(locationId)
			   & BOOST_SERIALIZATION_NVP(count)
			   & BOOST_SERIALIZATION_NVP(time);
		} 

		template<class Archive> 
		friend inline void load_construct_data(Archive& ar, Goal*& goal, const unsigned int version)
		{
			unsigned int unitTypeId;
			unsigned int locationId;
			unsigned int count;
			unsigned int time;

			ar & BOOST_SERIALIZATION_NVP(unitTypeId)
			   & BOOST_SERIALIZATION_NVP(locationId)
			   & BOOST_SERIALIZATION_NVP(count)
			   & BOOST_SERIALIZATION_NVP(time);

			if(version > 0) {
			}

			::new(goal)Goal(unitTypeId, locationId, count, time);
		}

		// TODO actual pointers?
		unsigned int unitTypeId;
		unsigned int locationId;

		// count can be 0! Then it is a 'bonus'
		unsigned int count;
		unsigned int time;
};

inline unsigned int Goal::getUnitTypeId() const {
	return unitTypeId;
}

inline unsigned int Goal::getTime() const {
	return time;
}

inline unsigned int Goal::getCount() const {
	return count;
}

inline unsigned int Goal::getLocationId() const {
	return locationId;
}


#endif // _CORE_GOAL_HPP