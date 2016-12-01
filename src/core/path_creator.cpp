#include "path_creator.hpp"
#include "path.hpp"

#include <misc/miscellaneous.hpp>


template<> boost::shared_ptr<Path> NodeCreator<Path>::createObjectFromNode(const std::vector<XmlNode>& node) {
	return boost::shared_ptr<Path>(new Path(Misc::uuid(node[0]), Misc::uuid(node[1]), Misc::uuid(node[2]), boost::lexical_cast<unsigned int>(node[3].getValue())));
}

template<> XmlNode NodeCreator<Path>::createNodeFromObject(const Path& t) {
	XmlNode n("path");
	n.addChild(XmlNode("id", boost::lexical_cast<std::string>(t.getId())));
	n.addChild(XmlNode("sourceID", boost::lexical_cast<std::string>(t.getSourceLocationId())));
	n.addChild(XmlNode("targetID", boost::lexical_cast<std::string>(t.getTargetLocationId())));
	n.addChild(XmlNode("distance", boost::lexical_cast<std::string>(t.getDistance())));
	return n;
}