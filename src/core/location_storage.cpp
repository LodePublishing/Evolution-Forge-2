#include "location_storage.hpp"
#include "location.hpp"
#include "path.hpp"

#include <misc/io.hpp>


template<> const std::string SingleStorage<Location>::DATA_FILE_NAME_BASE = IO::getDirectory(boost::assign::list_of("data")("storage")("core")) + "location.xml";
template<> const std::string SingleStorage<Location>::DATA_FILE_IDENTIFIER = "LocationStorage";

template<> boost::shared_ptr<Location> NodeCreator<Location>::createObjectFromNode(const std::vector<Node>& node) {
	boost::shared_ptr<Location> location = boost::shared_ptr<Location>(new Location(Misc::uuid(node[0]), node[1], boost::lexical_cast<signed int>(node[2].getValue()), boost::lexical_cast<signed int>(node[3].getValue())));
	for(std::vector<Node>::const_iterator i = node[4].getChildren().begin(); i != node[4].getChildren().end(); i++) {
		location->addPath(boost::shared_ptr<const Path>(NodeCreator<Path>::createObjectFromNode(i->getChildren())));
	}	
	return location;	
}

template<> Node NodeCreator<Location>::createNodeFromObject(const Location& t) {
	Node n("location");
	n.addChild(Node("id", boost::lexical_cast<std::string>(t.getId())));
	n.addChild(Node("name", t.getName()));
	n.addChild(Node("x", boost::lexical_cast<std::string>(t.getX())));
	n.addChild(Node("y", boost::lexical_cast<std::string>(t.getY())));

	Node pathList("paths");
	for(std::list<boost::shared_ptr<const Path> >::const_iterator i = t.getPaths().begin(); i != t.getPaths().end(); i++) {
		pathList.addChild(NodeCreator<Path>::createNodeFromObject(**i));
	}
	n.addChild(pathList);

	return n;
}
