#include <sstream>

#include "location.hpp"
#include "path.hpp"
#include "units.hpp"

Location::Location(const std::string& name, const unsigned int position, const Coordinate& coordinate, Units* globalUnits) :
	name(name),
	position(position),
	coordinate(new Coordinate(coordinate)),
	globalUnits(globalUnits)
{
	// TODO local units?!
	// the paths are loaded later when all locations are initialized!
}

// this is executed by the map automatically whenever a path is added
void Location::addPath(const Path* const path) {
	paths.push_back(path);
}


Location::~Location()
{ 
	delete coordinate;
}


// just calculate the direct distance
unsigned int Location::getAirDistance(const Location* const targetLocation) const {
	return (*targetLocation->getCoordinate() - *coordinate).getLength();
}

unsigned int Location::getGroundDistance(const Location* const targetLocation) const {
	std::map<unsigned int, unsigned int>::const_iterator i = distanceMap.find(targetLocation->getPosition());

	if(i == distanceMap.end()) {
		throw "Could not find location index";
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
	for(std::list<const Path*>::const_iterator i = paths.begin(); i != paths.end(); i++) {
		os << (*i)->toString() << ", ";
	}
	os << std::endl;
    return os.str();
}



const unsigned int Location::MAX_DISTANCE = 999;

const char* const Location::Position_tag_string = "position";
const char* const Location::Name_tag_string = "name";
const char* const Location::Coordinate_tag_string = "coordinate";