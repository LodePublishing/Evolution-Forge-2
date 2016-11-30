#include <sstream>
#include <iomanip>

#pragma warning(push, 0)  
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/johnson_all_pairs_shortest.hpp>
#pragma warning(pop)

#include "map.hpp"

Map::Map(const std::string& name):
name(name),
	locations(),
	paths()
{
}

Map::~Map()
{
	for(std::list<const Path*>::iterator i = paths.begin(); i != paths.end(); i++) {
		delete *i;
	}

	for(std::vector<Location*>::iterator i = locations.begin(); i != locations.end(); i++) {
		delete *i;
	}

	locations.clear();
	paths.clear();
}


void Map::addLocation(Location* location) {
	// test if position is already taken
	for(std::vector<Location*>::const_iterator i = locations.begin(); i != locations.end(); i++) {
		if(location->getPosition() == (*i)->getPosition()) {
			throw "Location with that position was already added";
		}
	}

	positionIndexMap.insert(std::pair<unsigned int, unsigned int>(location->getPosition(), locations.size()));
	indexPositionMap.insert(std::pair<unsigned int, unsigned int>(locations.size(), location->getPosition()));
	locations.push_back(location);
	locationMap.insert(std::pair<unsigned int, Location*>(location->getPosition(), location));
}

void Map::addPath(Path* path) {
	// TODO Test for multiple paths for the same source&target?
	getLocationAt(path->getSourceLocationPosition())->addPath(path);

	// "paths" are initialized at the end of the initialization process (see "initialize", they need to be in the correct sequence, first all paths from locations 0, then from location 1 etc.
}



Location* Map::getLocationAt(const unsigned int position) const {
	std::map<unsigned int, Location*>::const_iterator locmapentry = locationMap.find(position);
	if(locmapentry == locationMap.end()) {
		throw "No location found at that position";
	}
	return locmapentry->second;
}

unsigned int Map::getLocationIndex(const unsigned int position) const {
	std::map<unsigned int, unsigned int>::const_iterator indexentry = positionIndexMap.find(position);
	if(indexentry == positionIndexMap.end()) {
		throw "No index found at that position";
	}
	return indexentry->second;
}

unsigned int Map::getLocationPosition(const unsigned int index) const {
	std::map<unsigned int, unsigned int>::const_iterator positionentry = indexPositionMap.find(index);
	if(positionentry == indexPositionMap.end()) {
		throw "No index found at that position";
	}
	return positionentry->second;
}


Map& Map::operator=(const Map& other) {
	name = other.name;
	locations = other.locations;
	paths = other.paths;

	return *this;
}

Map::Map(const Map& other):
	ID<Map>(other.getID()),
	name(other.name),
	locations(other.locations),
	paths(other.paths)
{}

const std::string Map::toString() const {
	std::ostringstream os;
	os << std::endl << "Map Name: " << name << std::endl << std::endl << "Locations:" << std::endl;
	for(std::vector<Location*>::const_iterator i = locations.begin(); i != locations.end(); i++) {
		os << (*i)->toString() << std::endl;
	}
	return os.str();
}

void Map::calculateDistanceMap() {

	using namespace boost;
	typedef adjacency_list<vecS, vecS, undirectedS, no_property,
		property< edge_weight_t, unsigned int, property< edge_weight2_t, unsigned int > > > Graph;

	typedef std::pair < unsigned int, unsigned int >Edge;

	std::vector<unsigned int> weights;

	const unsigned int V = locations.size();
	Graph g(V);

	for(std::list<const Path*>::const_iterator j = paths.begin(); j != paths.end(); j++) {
		weights.push_back((*j)->getDistance());
		add_edge(getLocationIndex((*j)->getSourceLocationPosition()), getLocationIndex((*j)->getTargetLocationPosition()), g);

//		std::cout << getLocationIndex((*j)->getSourceLocationPosition()) << " -> " << getLocationIndex((*j)->getTargetLocationPosition()) << " = " << (*j)->getDistance() << std::endl;
	}

	property_map < Graph, edge_weight_t >::type w = get(edge_weight, g);
	std::vector<unsigned int>::const_iterator wp = weights.begin();
	graph_traits < Graph >::edge_iterator e, e_end;
	for (boost::tie(e, e_end) = edges(g); e != e_end; ++e)
		w[*e] = *wp++;
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
	for(std::vector<Location*>::iterator location = locations.begin(); location != locations.end(); location++) {
		std::map<unsigned int, unsigned int> distancemap;
		unsigned int i = 0;
		for(std::vector<Location*>::iterator target_location = locations.begin(); target_location != locations.end(); target_location++) {
			distancemap[getLocationPosition(i)] = minDistance[j][i];
			i++;
		}
		(*location)->setDistanceMap(distancemap);
		j++;
	}

}

// helper function for proper sequence of paths (first all paths from first location etc.)
void Map::addPathsFromLocations() {
	for(std::vector<Location*>::iterator i = locations.begin(); i != locations.end(); i++) {
		paths.insert(paths.end(), (*i)->getPaths().begin(), (*i)->getPaths().end());
	}
}

// needs to be called after deserialization
void Map::initialize() {
	int j = 0;

	for(std::vector<Location*>::iterator i = locations.begin(); i != locations.end(); i++) {
		locationMap.insert(std::pair<unsigned int, Location*>((*i)->getPosition(), *i));
		positionIndexMap.insert(std::pair<unsigned int, unsigned int>((*i)->getPosition(), j));
		indexPositionMap.insert(std::pair<unsigned int, unsigned int>(j, (*i)->getPosition()));
		j++;
	}

	for(std::list<const Path*>::iterator i = paths.begin(); i != paths.end(); i++) {
		Location* source_location = getLocationAt((*i)->getSourceLocationPosition());
		source_location->addPath(*i);
	}
}

const char* const Map::Name_tag_string = "name";
const char* const Map::Locations_tag_string = "locations";
const char* const Map::Paths_tag_string = "paths";