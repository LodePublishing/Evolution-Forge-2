#include <sstream>

#include "location.hpp"
#include "path.hpp"
#include "units.hpp"

Location::Location(const std::string& name, const unsigned int position, const signed int x, const signed int y) :
	Coordinate(x, y),
	name(name),
	position(position),
	paths(),
	distanceMap()
{
	// the paths are loaded later when all locations are initialized!
}

Location::Location(const unsigned int id, const std::string& name, const unsigned int position, const signed int x, const signed int y) :
	ID<Location>(id),
	Coordinate(x, y),
	name(name),
	position(position),
	paths(),
	distanceMap()
{
	// the paths are loaded later when all locations are initialized!
}

Location::Location(const Location& object):
	ID<Location>(object),
	Coordinate(object),
	name(object.name),
	position(object.position),
	paths(object.paths),
	distanceMap(object.distanceMap)
{ }
	
Location::~Location()
{ }

// this is executed by the map automatically whenever a path is added
void Location::addPath(const boost::shared_ptr<const Path> path) {
	paths.push_back(path);
}

// just calculate the direct distance
unsigned int Location::getAirDistance(const boost::shared_ptr<const Location> targetLocation) const {
	return (*targetLocation - *this).getLength();
}

unsigned int Location::getGroundDistance(const boost::shared_ptr<const Location> targetLocation) const {
	std::map<unsigned int, unsigned int>::const_iterator i = distanceMap.find(targetLocation->getPosition());

	if(i == distanceMap.end()) {
		throw "Invalid location index or no path between both locations.";
	}
	
	return i->second;
}


const std::string Location::toString() const
{
	std::ostringstream os;
	os << "Location Name: " << name << std::endl;
	os << "Position: " << position << std::endl;
//	os << "Coordinate: " << coordinate.toString() << std::endl;
	os << "Distances: ";
	for(std::list<boost::shared_ptr<const Path> >::const_iterator i = paths.begin(); i != paths.end(); i++) {
		os << (*i)->toString() << ", ";
	}
	os << std::endl;
    return os.str();
}

const unsigned int Location::MAX_DISTANCE = 999;