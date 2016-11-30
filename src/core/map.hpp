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
#include <boost/serialization/shared_ptr.hpp>
#pragma warning(pop)

#include <loadsave.hpp>
#include <uuid.hpp>

#include "location.hpp"
#include "path.hpp"

// pointer nur bei mehrfach genutzten Objekten (z.B. Units, locations)


class Map : public LoadSave<Map>, public UUID<Map>
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
	const boost::shared_ptr<Location> getLocation(const unsigned index) const;
	const boost::shared_ptr<Location> getLocationAt(const unsigned int position) const;
	unsigned int getLocationIndex(const unsigned int position) const;
	unsigned int getLocationPosition(const unsigned int index) const;
	
private:
	friend class boost::serialization::access;

	template<class Archive> 
	void serialize(Archive &ar, const unsigned int version)
	{ }

	template<class Archive>
	friend inline void save_construct_data(Archive &ar, const Map* map, const unsigned int version) { 

		const boost::uuids::uuid& id = map->getId();
		const std::string& name = map->getName();
		const std::vector<boost::shared_ptr<Location> >& locationVector = map->getLocationVector();
		const std::list<boost::shared_ptr<const Path> >& pathList = map->getPathList();

		if(version > 0) {
		}

		ar & BOOST_SERIALIZATION_NVP(id)
		   & BOOST_SERIALIZATION_NVP(name)
		   & BOOST_SERIALIZATION_NVP(locationVector)
		   & BOOST_SERIALIZATION_NVP(pathList);
	}
	// TODO write test for locations?
	template<class Archive>
	inline friend void load_construct_data(Archive& ar, Map*& map, const unsigned int version)
	{
		boost::uuids::uuid id;
		std::string name;
		std::vector<boost::shared_ptr<Location> > locationVector;
		std::list<boost::shared_ptr<const Path> > pathList;

		ar & BOOST_SERIALIZATION_NVP(id)
		   & BOOST_SERIALIZATION_NVP(name)
		   & BOOST_SERIALIZATION_NVP(locationVector)
		   & BOOST_SERIALIZATION_NVP(pathList);
			
		if(version > 0) {
		}

		::new(map)Map(id, name, locationVector, pathList);
	}

	const std::string name;
	const std::vector<boost::shared_ptr<Location> > locationVector;
	const std::list<boost::shared_ptr<const Path> > pathList;
	
	std::map<const unsigned int, const boost::shared_ptr<Location> > locationMap; // position -> location
	std::map<const unsigned int, const unsigned int> positionIndexMap; // position -> index
	std::map<const unsigned int, const unsigned int> indexPositionMap; // index -> position

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

inline const boost::shared_ptr<Location> Map::getLocation(const unsigned index) const {
	return locationVector[index];
}

#endif // _CORE_MAP_HPP

