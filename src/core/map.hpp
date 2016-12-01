#ifndef _CORE_MAP_HPP
#define _CORE_MAP_HPP

#include <string>
#include <vector>
#include <map>

#include <misc/uuid.hpp>

#include "location.hpp"
#include "path.hpp"

// pointer nur bei mehrfach genutzten Objekten (z.B. Units, locations)


class Map : public UUID<Map>
{
public:		
	Map(const boost::uuids::uuid id, const std::string& name, const std::vector<boost::shared_ptr<Location> > locationVector, const std::list<boost::shared_ptr<const Path> > pathList);
	Map(const std::string& name, const std::vector<boost::shared_ptr<Location> > locationVector, const std::list<boost::shared_ptr<const Path> > pathList);
	~Map();

	void processLocations();
	void processPaths();
	void calculateDistanceMap();
	// initialize after raw data was filled (by e.g. serialization)
	void initialize();	
	void addPathsFromLocations();

	const std::string& getName() const;
	const std::string toString() const;
	const std::vector<boost::shared_ptr<Location> >& getLocationVector() const;
	const std::list<boost::shared_ptr<const Path> >& getPathList() const;

	const boost::shared_ptr<Location> getLocationByIndex(const unsigned index) const;
	const boost::shared_ptr<Location> getLocation(const boost::uuids::uuid locationId) const;
	unsigned int getLocationIndex(const boost::uuids::uuid locationId) const;
	const boost::uuids::uuid getLocationId(const unsigned int index) const;


private:
	const std::string name;
	const std::vector<boost::shared_ptr<Location> > locationVector;
	const std::list<boost::shared_ptr<const Path> > pathList;

	std::map<const boost::uuids::uuid, const boost::shared_ptr<Location> > locationMap; // uuid -> location
	std::map<const boost::uuids::uuid, const unsigned int> idIndexMap; // uuid -> index
	std::map<const unsigned int, const boost::uuids::uuid> indexIdMap; // index -> uuid

	//cached entries:
	std::vector<std::vector<unsigned int> > minDistance;
	
	Map(const Map& other);
	Map& operator=(const Map& other);
};

inline const std::string& Map::getName() const {
	return name;
}

inline const std::vector<boost::shared_ptr<Location> >& Map::getLocationVector() const {
	return locationVector;
}

inline const std::list<boost::shared_ptr<const Path> >& Map::getPathList() const {
	return pathList;
}

inline const boost::shared_ptr<Location> Map::getLocationByIndex(const unsigned index) const {
	return locationVector[index];
}


#endif // _CORE_MAP_HPP

