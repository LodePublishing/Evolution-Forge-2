#include "brush_storage.hpp"
#include "brush.hpp"

#include <misc/miscellaneous.hpp>
#include <misc/io.hpp>

#include "color_storage.hpp"

template<> const std::string SingleStorage<Brush>::DATA_FILE_NAME_BASE = IO::getDirectory(boost::assign::list_of("data")("storage")("guicore")) + "brush.xml";
template<> const std::string SingleStorage<Brush>::DATA_FILE_IDENTIFIER = "BrushStorage";

template<> boost::shared_ptr<Brush> NodeCreator<Brush>::createObjectFromNode(const std::vector<Node>& node) {
	return boost::shared_ptr<Brush>(new Brush(Misc::uuid(node[0]), ColorStorage::instance().get(node[1]), static_cast<eBrushStyle>(boost::lexical_cast<unsigned int>(node[2].getValue()))));
}

template<> Node NodeCreator<Brush>::createNodeFromObject(const Brush& t) {
	Node n("brush");
	n.addChild(Node("id", boost::lexical_cast<std::string>(t.getId())));
	n.addChild(Node("colorID", boost::lexical_cast<std::string>(t.getColor()->getId())));
	n.addChild(Node("style", boost::lexical_cast<std::string>(t.getStyle())));
	return n;
}