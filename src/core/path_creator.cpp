#include "path_creator.hpp"
#include "path.hpp"

#include <misc/miscellaneous.hpp>


template<> boost::shared_ptr<Path> NodeCreator<Path>::createObjectFromNode(const std::vector<Node>& node) {
	return boost::shared_ptr<Path>(new Path(Misc::uuid(node[0]), Misc::uuid(node[1]), Misc::uuid(node[2]), boost::lexical_cast<unsigned int>(node[3].getValue())));
}

template<> Node NodeCreator<Path>::createNodeFromObject(const Path& t) {
	Node n("path");
	n.addChild(Node("id", boost::lexical_cast<std::string>(t.getId())));
	n.addChild(Node("sourceID", boost::lexical_cast<std::string>(t.getSourceLocationId())));
	n.addChild(Node("targetID", boost::lexical_cast<std::string>(t.getTargetLocationId())));
	n.addChild(Node("distance", boost::lexical_cast<std::string>(t.getDistance())));
	return n;
}