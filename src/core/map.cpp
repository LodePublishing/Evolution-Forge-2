#include <sstream>
#include <iomanip>

#pragma warning(push, 0)  
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/johnson_all_pairs_shortest.hpp>
#pragma warning(pop)

#include "map.hpp"

Map::Map(const std::string& name, const std::vector<boost::shared_ptr<Location> > locationVector, const std::list<boost::shared_ptr<const Path> > pathList):
	name(name),
	locationVector(locationVector),
	pathList(pathList),
	locationMap(),
	idIndexMap(),
	indexIdMap(),
	minDistance()
{
	processLocations();
	// TODO sorting map needs entries in orderly fashion (first all paths from location index 0, then index 1, etc.pp.
	calculateDistanceMap();

}

Map::Map(const boost::uuids::uuid id, const std::string& name, const std::vector<boost::shared_ptr<Location> > locationVector, const std::list<boost::shared_ptr<const Path> > pathList):
	UUID<Map>(id),
	name(name),
	locationVector(locationVector),
	pathList(pathList),
	locationMap(),
	idIndexMap(),
	indexIdMap(),
	minDistance()
{
	processLocations();
	// TODO sorting map needs entries in orderly fashion (first all paths from location index 0, then index 1, etc.pp.
	calculateDistanceMap();

}

Map::~Map()
{}

void Map::processLocations() {
	int index = 0;
	for(std::vector<boost::shared_ptr<Location> >::const_iterator i = locationVector.begin(); i != locationVector.end(); i++) {
		idIndexMap.insert(std::pair<const boost::uuids::uuid, const unsigned int>((*i)->getId(), index));
		indexIdMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(index, (*i)->getId()));
		locationMap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<Location> >((*i)->getId(), *i));
		index++;
	}
}

// needs to be called after deserialization
void Map::initialize() {
	processLocations();

	for(std::list<boost::shared_ptr<const Path> >::const_iterator i = pathList.begin(); i != pathList.end(); i++) {
		const boost::shared_ptr<Location> source_location = getLocation((*i)->getSourceLocationId());
		source_location->addPath(*i);
	}
}



void Map::processPaths() {
	for(std::list<boost::shared_ptr<const Path> >::const_iterator i = pathList.begin(); i != pathList.end(); i++) {
		// TODO Test for multiple paths for the same source&target?
		getLocation((*i)->getSourceLocationId())->addPath(*i);
	}

	// "paths" are initialized at the end of the initialization process (see "initialize", they need to be in the correct sequence, first all paths from locations 0, then from location 1 etc.
}

const std::string Map::toString() const {
	std::ostringstream os;
	os << std::endl << "Map Name: " << name << std::endl << std::endl << "Locations:" << std::endl;
	for(std::vector<boost::shared_ptr<Location> >::const_iterator i = locationVector.begin(); i != locationVector.end(); i++) {
		os << (*i)->toString() << std::endl;
	}
	return os.str();
}

void Map::calculateDistanceMap() {

	using namespace boost;
	typedef adjacency_list<vecS, vecS, undirectedS, no_property,
		property< edge_weight_t, unsigned int, property< edge_weight2_t, unsigned int > > > Graph;
	typedef std::pair <unsigned int, unsigned int> Edge;
	std::vector<unsigned int> weights;
	const unsigned int V = locationVector.size();
	Graph g(V);

	for(std::list<boost::shared_ptr<const Path> >::const_iterator j = pathList.begin(); j != pathList.end(); j++) {
		weights.push_back((*j)->getDistance());
		add_edge(getLocationIndex((*j)->getSourceLocationId()), getLocationIndex((*j)->getTargetLocationId()), g);

		//std::cout << getLocationIndex((*j)->getSourceLocationPosition()) << " -> " << getLocationIndex((*j)->getTargetLocationPosition()) << " = " << (*j)->getDistance() << std::endl;
	}

	property_map < Graph, edge_weight_t >::type w = get(edge_weight, g);
	std::vector<unsigned int>::const_iterator wp = weights.begin();
	graph_traits < Graph >::edge_iterator e, e_end;
	for (boost::tie(e, e_end) = edges(g); e != e_end; ++e) {
		w[*e] = *wp++;
	}
	std::vector<unsigned int> d(V, (std::numeric_limits<unsigned int>::max)());
	minDistance = std::vector<std::vector<unsigned int> >(V,std::vector<unsigned int>(V));
	johnson_all_pairs_shortest_paths(g, minDistance, distance_map(&d[0]));

	unsigned int j = 0;
	for(std::vector<boost::shared_ptr<Location> >::const_iterator location = locationVector.begin(); location != locationVector.end(); location++) {
		std::map<const boost::uuids::uuid, const unsigned int> distancemap;
		unsigned int i = 0;
		for(std::vector<boost::shared_ptr<Location> >::const_iterator target_location = locationVector.begin(); target_location != locationVector.end(); target_location++) {
			distancemap.insert(std::pair<const boost::uuids::uuid, const unsigned int>(getLocationId(i), minDistance[j][i]));
			i++;
		}
		(*location)->setDistanceMap(distancemap);
		j++;
	}

}

unsigned int Map::getLocationIndex(const boost::uuids::uuid locationId) const {
	std::map<const boost::uuids::uuid, const unsigned int>::const_iterator indexentry = idIndexMap.find(locationId);
	if(indexentry == idIndexMap.end()) {
		throw std::exception();
	}
	return indexentry->second;
}

const boost::shared_ptr<Location> Map::getLocation(const boost::uuids::uuid locationId) const {
	std::map<const boost::uuids::uuid, const boost::shared_ptr<Location> >::const_iterator locationentry = locationMap.find(locationId);
		if(locationentry == locationMap.end()) {
		throw std::exception();
	}
	return locationentry->second;
}

const boost::uuids::uuid Map::getLocationId(const unsigned int index) const {
	std::map<const unsigned int, const boost::uuids::uuid>::const_iterator identry = indexIdMap.find(index);
	if(identry == indexIdMap.end()) {
		throw std::exception();
	}
	return identry->second;
}