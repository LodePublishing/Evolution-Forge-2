#ifndef _CORE_MAP_HPP
#define _CORE_MAP_HPP

#include <string>
#include <vector>
#include <map>

#pragma warning(push, 0)  
#include <boost/config.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/vector.hpp>
#pragma warning(pop)

#include <loadsave.hpp>

#include "location.hpp"
#include "path.hpp"
#include "id.hpp"

// pointer nur bei mehrfach genutzten Objekten (z.B. Units, locations)

class Map : public LoadSave<Map>, public ID<Map>
{
public:		
	Map(const std::string& name);
	~Map();

	void addLocation(Location* location);
	void addPath(Path* path);

	void setName(const std::string& name);


	const std::string& getName() const;
	const std::string toString() const;
	const std::vector<Location*>& getLocations() const;
	const std::list<const Path*>& getPaths() const;

	void calculateDistanceMap();

	Location* getLocationAt(const unsigned int position) const;
	unsigned int getLocationIndex(const unsigned int position) const;
	unsigned int getLocationPosition(const unsigned int index) const;

	// initialize after raw data was filled (by e.g. serialization)
	void initialize();	
	void addPathsFromLocations();

	static const char* const Name_tag_string;
	static const char* const Locations_tag_string;
	static const char* const Paths_tag_string;
	// units are administered in a higher class, like game.hpp or something like that

	// needs to be public to allow deserialization (loading)
	Map(){}

private:
	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive &ar, const unsigned int version)
	{
		ar & boost::serialization::make_nvp(ID_tag_string, id);
		ar & boost::serialization::make_nvp(Name_tag_string, name);
		ar & boost::serialization::make_nvp(Locations_tag_string, locations);
		ar & boost::serialization::make_nvp(Paths_tag_string, paths);
		// distance map is recalculated! location pointers have to be reassigned!
		if(version > 0) {
		}
	}


	std::string name;

	std::map<unsigned int, Location*> locationMap;
	std::map<unsigned int, unsigned int> positionIndexMap;
	std::map<unsigned int, unsigned int> indexPositionMap;

	std::vector<Location*> locations;
	std::list<const Path*> paths;

	//cached entries:
	std::vector<std::vector<unsigned int> > minDistance;

	Map& operator=(const Map& other);
	Map(const Map& other);
};

inline void Map::setName(const std::string& name) {
	this->name = name;
}

inline const std::string& Map::getName() const 
{
	return name;
}

inline const std::vector<Location*>& Map::getLocations() const
{
	return locations;
}

inline const std::list<const Path*>& Map::getPaths() const
{
	return paths;
}


#endif // _CORE_MAP_HPP

