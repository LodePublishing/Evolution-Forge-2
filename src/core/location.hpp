#ifndef _CORE_LOCATION_HPP
#define _CORE_LOCATION_HPP

#include <string>
#include <list>
#include <map>

#pragma warning(push, 0)  
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/list.hpp>
#pragma warning(pop)

#include "id.hpp"
#include "coordinate.hpp"

class Units;
class Path;

class Location : public ID<Location>
{
public:
	Location(const std::string& name, const unsigned int position, const Coordinate& coordinate, Units* globalUnits);
	~Location();

	void addPath(const Path* const path);

	unsigned int getAirDistance(const Location* const targetLocation) const;
	unsigned int getGroundDistance(const Location* const targetLocation) const;

	unsigned int getPosition() const;
	Coordinate* getCoordinate() const; // TODO const operators required?!
	const std::string& getName() const;
	const std::string toString() const;
	const std::list<const Path*>& getPaths() const;
	
	void setDistanceMap(std::map<unsigned int, unsigned int> distanceMap);

	Units* getGlobalUnits() const;

	static const unsigned int MAX_DISTANCE;
private:
	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive &ar, const unsigned int version)
	{
		ar & boost::serialization::make_nvp(ID_tag_string, id);
		ar & boost::serialization::make_nvp(Position_tag_string, position);
		ar & boost::serialization::make_nvp(Coordinate_tag_string, coordinate);
		ar & boost::serialization::make_nvp(Name_tag_string, name);
		// paths are saved in the map! Need to be reassigned!
		if(version > 0) {
		}
	}
	// only use for serialization / deserialization
	Location():coordinate(NULL),globalUnits(NULL) {}

	std::string name;
	unsigned int position;
	Coordinate* coordinate;
	
	// TODO add Units for testing of process in Unit test
	// temp variables
	Units* globalUnits;

	std::list<const Path*> paths;	
	// key is the location position
	std::map<unsigned int, unsigned int> distanceMap;

	static const char* const Position_tag_string;
	static const char* const Coordinate_tag_string;
	static const char* const Name_tag_string;
};


inline unsigned int Location::getPosition() const {
	return position;
}

inline const std::string& Location::getName() const {
	return name;
}

inline const std::list<const Path*>& Location::getPaths() const {
	return paths;
}

inline Coordinate* Location::getCoordinate() const {
	return coordinate;
}


inline void Location::setDistanceMap(std::map<unsigned int, unsigned int> distanceMap) {
	this->distanceMap = distanceMap;
}

inline Units* Location::getGlobalUnits() const {
	return globalUnits;
}


#endif // _CORE_LOCATION_HPP

