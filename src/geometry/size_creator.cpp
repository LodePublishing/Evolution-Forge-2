#include "size_creator.hpp"
#include "size.hpp"

#include <misc/miscellaneous.hpp>
#include <misc/uuid.hpp>

template<> boost::shared_ptr<Size> NodeCreator<Size>::createObjectFromNode(const std::vector<Node>& node) {
	return boost::shared_ptr<Size>(new Size(boost::lexical_cast<unsigned int>(node[0].getValue()), boost::lexical_cast<unsigned int>(node[1].getValue())));
}

template<> Node NodeCreator<Size>::createNodeFromObject(const Size& t) {
	Node n("size");
	n.addChild(Node("w", boost::lexical_cast<std::string>(t.getWidth())));
	n.addChild(Node("h", boost::lexical_cast<std::string>(t.getHeight())));
	return n;
}