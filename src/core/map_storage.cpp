#include "map_storage.hpp"
#include "map.hpp"


#include <misc/io.hpp>


template<> const std::string SingleStorage<Map>::DATA_FILE_NAME_BASE = IO::getDirectory(boost::assign::list_of("data")("storage")("core")) + "map.xml";
template<> const std::string SingleStorage<Map>::DATA_FILE_IDENTIFIER = "MapStorage";

template<> boost::shared_ptr<Map> NodeCreator<Map>::createObjectFromNode(const std::vector<XmlNode>& node) {

	std::vector<boost::shared_ptr<Location> > locationVector;
	std::list<boost::shared_ptr<const Path> > pathList;

	for(std::vector<XmlNode>::const_iterator i = node[2].getChildren().begin(); i != node[2].getChildren().end(); i++) {
		locationVector.push_back(boost::shared_ptr<Location>(SingleStorage<Location>::createObjectFromNode(i->getChildren())));
	}
	for(std::vector<XmlNode>::const_iterator i = node[3].getChildren().begin(); i != node[3].getChildren().end(); i++) {
		pathList.push_back(boost::shared_ptr<const Path>(SingleStorage<Path>::createObjectFromNode(i->getChildren())));
	}

	return boost::shared_ptr<Map>(new Map(Misc::uuid(node[0]), node[1], locationVector, pathList));
}

template<> XmlNode NodeCreator<Map>::createNodeFromObject(const Map& t) {
	XmlNode n("map");
	n.addChild(XmlNode("id", boost::lexical_cast<std::string>(t.getId())));
	n.addChild(XmlNode("name", t.getName()));

	XmlNode locationVector("locations");
	XmlNode pathList("paths");
	for(std::vector<boost::shared_ptr<Location> >::const_iterator i = t.getLocationVector().begin(); i != t.getLocationVector().end(); i++) {
		locationVector.addChild(SingleStorage<Location>::createNodeFromObject(**i));
	}
	for(std::list<boost::shared_ptr<const Path> >::const_iterator i = t.getPathList().begin(); i != t.getPathList().end(); i++) {
		pathList.addChild(SingleStorage<Path>::createNodeFromObject(**i));
	}
	n.addChild(locationVector);
	n.addChild(pathList);
	return n;
}