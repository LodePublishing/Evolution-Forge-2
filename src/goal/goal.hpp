#ifndef _GOAL_GOAL_HPP
#define _GOAL_GOAL_HPP

#pragma warning(push, 0)  
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/assert.hpp>
#pragma warning(pop)

#include <uuid.hpp>

class Goal
{
	public:
		Goal(const boost::uuids::uuid unitTypeId, const boost::uuids::uuid locationId, const unsigned int count, const unsigned int time = GOAL_MAX_TIME);
		~Goal();
		bool operator<(const Goal& goal);
		Goal(const Goal& goal);
		bool operator==(const Goal& goal) const;

		boost::uuids::uuid getUnitTypeId() const;
		boost::uuids::uuid getLocationId() const;
		unsigned int getTime() const;
		unsigned int getCount() const;		

		static const unsigned int GOAL_MAX_TIME;

	private:
		friend class boost::serialization::access;

		template<class Archive> 
		void serialize(Archive &ar, const unsigned int version)
		{ }

		template<class Archive>
		friend inline void save_construct_data(Archive &ar, const Goal* goal, const unsigned int version) { 

			const boost::uuids::uuid& unitTypeId = goal->getUnitTypeId();
			const boost::uuids::uuid& locationId = goal->getLocationId();
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
			boost::uuids::uuid unitTypeId;
			boost::uuids::uuid locationId;
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
		boost::uuids::uuid unitTypeId;
		boost::uuids::uuid locationId;

		// count can be 0! Then it is a 'bonus'
		unsigned int count;
		unsigned int time;
};

inline boost::uuids::uuid Goal::getUnitTypeId() const {
	return unitTypeId;
}

inline boost::uuids::uuid Goal::getLocationId() const {
	return locationId;
}

inline unsigned int Goal::getTime() const {
	return time;
}

inline unsigned int Goal::getCount() const {
	return count;
}


#endif // _GOAL_GOAL_HPP