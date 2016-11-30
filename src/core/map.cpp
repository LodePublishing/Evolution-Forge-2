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
	positionIndexMap(),
	indexPositionMap(),
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
	positionIndexMap(),
	indexPositionMap(),
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
		positionIndexMap.insert(std::pair<const unsigned int, const unsigned int>((*i)->getPosition(), index));
		indexPositionMap.insert(std::pair<const unsigned int, const unsigned int>(index, (*i)->getPosition()));
		locationMap.insert(std::pair<const unsigned int, const boost::shared_ptr<Location> >((*i)->getPosition(), *i));
		index++;
	}
}

void Map::processPaths() {
	for(std::list<boost::shared_ptr<const Path> >::const_iterator i = pathList.begin(); i != pathList.end(); i++) {
		// TODO Test for multiple paths for the same source&target?
		getLocationAt((*i)->getSourceLocationPosition())->addPath(*i);
	}

	// "paths" are initialized at the end of the initialization process (see "initialize", they need to be in the correct sequence, first all paths from locations 0, then from location 1 etc.
}

const boost::shared_ptr<Location> Map::getLocationAt(const unsigned int position) const {
	std::map<const unsigned int, const boost::shared_ptr<Location> >::const_iterator locmapentry = locationMap.find(position);
	if(locmapentry == locationMap.end()) {
		throw "No location found at that position";
	}
	return locmapentry->second;
}

unsigned int Map::getLocationIndex(const unsigned int position) const {
	std::map<const unsigned int, const unsigned int>::const_iterator indexentry = positionIndexMap.find(position);
	if(indexentry == positionIndexMap.end()) {
		throw "No index found at that position";
	}
	return indexentry->second;
}

unsigned int Map::getLocationPosition(const unsigned int index) const {
	std::map<const unsigned int, const unsigned int>::const_iterator positionentry = indexPositionMap.find(index);
	if(positionentry == indexPositionMap.end()) {
		throw "No index found at that position";
	}
	return positionentry->second;
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
		add_edge(getLocationIndex((*j)->getSourceLocationPosition()), getLocationIndex((*j)->getTargetLocationPosition()), g);

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
	
/*	for (int k = 0; k < V; ++k)
		std::cout << std::setw(5) << k;
	std::cout << std::endl;

	for (int i = 0; i < V; ++i) {
		std::cout << std::setw(6) << i << " (" << getLocationPosition(i) << ") -> ";
		for (int j = 0; j < V; ++j) {
			if (minDistance[i][j] == (std::numeric_limits<int>::max)())
				std::cout << std::setw(5) << "inf";
			else
				std::cout << std::setw(5) << minDistance[i][j];
		}
		std::cout << std::endl;
	}
	*/
	unsigned int j = 0;
	for(std::vector<boost::shared_ptr<Location> >::const_iterator location = locationVector.begin(); location != locationVector.end(); location++) {
		std::map<unsigned int, unsigned int> distancemap;
		unsigned int i = 0;
		for(std::vector<boost::shared_ptr<Location> >::const_iterator target_location = locationVector.begin(); target_location != locationVector.end(); target_location++) {
			distancemap[getLocationPosition(i)] = minDistance[j][i];
			i++;
		}
		(*location)->setDistanceMap(distancemap);
		j++;
	}

}

// needs to be called after deserialization
void Map::initialize() {
	int index = 0;

	for(std::vector<boost::shared_ptr<Location> >::const_iterator i = locationVector.begin(); i != locationVector.end(); i++) {
		locationMap.insert(std::pair<unsigned int, boost::shared_ptr<Location> >((*i)->getPosition(), *i));
		positionIndexMap.insert(std::pair<unsigned int, unsigned int>((*i)->getPosition(), index));
		indexPositionMap.insert(std::pair<unsigned int, unsigned int>(index, (*i)->getPosition()));
		index++;
	}

	for(std::list<boost::shared_ptr<const Path> >::const_iterator i = pathList.begin(); i != pathList.end(); i++) {
		const boost::shared_ptr<Location> source_location = getLocationAt((*i)->getSourceLocationPosition());
		source_location->addPath(*i);
	}
}