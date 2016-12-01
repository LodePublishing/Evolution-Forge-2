#include "pen_storage.hpp"
#include "pen.hpp"

#include <misc/miscellaneous.hpp>
#include <misc/io.hpp>

#include "color_storage.hpp"

template<> const std::string SingleStorage<Pen>::DATA_FILE_NAME_BASE = IO::getDirectory(boost::assign::list_of("data")("storage")("guicore")) + "pen.xml";
template<> const std::string SingleStorage<Pen>::DATA_FILE_IDENTIFIER = "PenStorage";

template<> boost::shared_ptr<Pen> NodeCreator<Pen>::createObjectFromNode(const std::vector<Node>& node) {
	return boost::shared_ptr<Pen>(new Pen(Misc::uuid(node[0]), ColorStorage::instance().get(node[1]), boost::lexical_cast<Uint16>(node[2].getValue()), static_cast<ePenStyle>(boost::lexical_cast<unsigned int>(node[3].getValue()))));
}

template<> Node NodeCreator<Pen>::createNodeFromObject(const Pen& t) {
	Node n("pen");
	n.addChild(Node("id", boost::lexical_cast<std::string>(t.getId())));
	n.addChild(Node("colorID", boost::lexical_cast<std::string>(t.getColor()->getId())));
	n.addChild(Node("width", boost::lexical_cast<std::string>(t.getWidth())));
	n.addChild(Node("style", boost::lexical_cast<std::string>(t.getStyle())));
	return n;
}