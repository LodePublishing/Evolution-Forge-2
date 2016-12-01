#include "objectsize_storage.hpp"
#include "objectsize.hpp"

#include <misc/miscellaneous.hpp>
#include <misc/io.hpp>

template<> const std::string SingleStorage<ObjectSize>::DATA_FILE_NAME_BASE = IO::getDirectory(boost::assign::list_of("data")("storage")("guicore")) + "objectsize.xml";
template<> const std::string SingleStorage<ObjectSize>::DATA_FILE_IDENTIFIER = "ObjectSizeStorage";

template<> boost::shared_ptr<ObjectSize> NodeCreator<ObjectSize>::createObjectFromNode(const std::vector<Node>& node) {
	return boost::shared_ptr<ObjectSize>(new ObjectSize(Misc::uuid(node[0]), static_cast<Uint16>(boost::lexical_cast<unsigned int>(node[1].getValue())), static_cast<Uint16>(boost::lexical_cast<unsigned int>(node[2].getValue()))));
}

template<> Node NodeCreator<ObjectSize>::createNodeFromObject(const ObjectSize& t) {
	Node n("objectsize");
	n.addChild(Node("id", boost::lexical_cast<std::string>(t.getId())));
	n.addChild(Node("width", boost::lexical_cast<std::string>(t.getWidth())));
	n.addChild(Node("height", boost::lexical_cast<std::string>(t.getHeight())));
	return n;
}