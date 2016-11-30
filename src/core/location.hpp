#ifndef _CORE_LOCATION_HPP
#define _CORE_LOCATION_HPP

#include <string>
#include <list>
#include <map>

#pragma warning(push, 0)  
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/list.hpp>
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <uuid.hpp>

#include "coordinate.hpp"

class Path;

class Location : public UUID<Location>, public Coordinate
{
public:
	Location(const boost::uuids::uuid id, const std::string& name, const signed int x, const signed int y);
	Location(const std::string& name, const signed int x, const signed int y);
	~Location();

	void addPath(const boost::shared_ptr<const Path> path);

	unsigned int getAirDistance(const boost::shared_ptr<const Location> targetLocation) const;
	unsigned int getGroundDistance(const boost::shared_ptr<const Location> targetLocation) const;

	const std::string& getName() const;
	const std::string toString() const;
	const std::list<boost::shared_ptr<const Path> >& getPaths() const;
	
	void setDistanceMap(const std::map<const boost::uuids::uuid, const unsigned int> distanceMap);

	static const unsigned int MAX_DISTANCE;

	Location(const Location& object);

private:
	friend class boost::serialization::access;

	template<class Archive> 
	void serialize(Archive &ar, const unsigned int version)
	{ }

	template<class Archive>
	friend inline void save_construct_data(Archive &ar, const Location* location, const unsigned int version) { 

		const boost::uuids::uuid& id = location->getId();
		const std::string& name = location->getName();
		const signed int& x = location->getX();
		const signed int& y = location->getY();

		if(version > 0) {
		}

		ar & BOOST_SERIALIZATION_NVP(id)
		   & BOOST_SERIALIZATION_NVP(name)
		   & BOOST_SERIALIZATION_NVP(x)
		   & BOOST_SERIALIZATION_NVP(y);
	}

	template<class Archive> 
	friend inline void load_construct_data(Archive& ar, Location*& location, const unsigned int version)
	{
		boost::uuids::uuid id;
		std::string name;
		signed int x;
		signed int y;

		ar & BOOST_SERIALIZATION_NVP(id)
		   & BOOST_SERIALIZATION_NVP(name)
		   & BOOST_SERIALIZATION_NVP(x)
		   & BOOST_SERIALIZATION_NVP(y);

		if(version > 0) {
		}

		::new(location)Location(id, name, x, y);
	}

	const std::string name;

	std::list<boost::shared_ptr<const Path> > paths;	
	// key is the location position
	std::map<const boost::uuids::uuid, const unsigned int> distanceMap;

	Location& operator=(const Location& object);
};

inline const std::string& Location::getName() const {
	return name;
}

inline const std::list<boost::shared_ptr<const Path> >& Location::getPaths() const {
	return paths;
}

inline void Location::setDistanceMap(const std::map<const boost::uuids::uuid, const unsigned int> distanceMap) {
	this->distanceMap = distanceMap;
}

#endif // _CORE_LOCATION_HPP

