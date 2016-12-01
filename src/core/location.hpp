#ifndef _CORE_LOCATION_HPP
#define _CORE_LOCATION_HPP

#include <string>
#include <list>
#include <map>

#include <misc/uuid.hpp>

#include <geometry/coordinate.hpp>

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
	const std::string name;

	std::list<boost::shared_ptr<const Path> > paths;
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

