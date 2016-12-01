#include "government_storage.hpp"
#include "government.hpp"

#include <misc/io.hpp>

template<> const std::string SingleStorage<Government>::DATA_FILE_NAME_BASE = IO::getDirectory(boost::assign::list_of("data")("storage")("core")) + "government.xml";
template<> const std::string SingleStorage<Government>::DATA_FILE_IDENTIFIER = "GovernmentStorage";

template<> boost::shared_ptr<Government> NodeCreator<Government>::createObjectFromNode(const std::vector<Node>& node) {
	return boost::shared_ptr<Government>(new Government(Misc::uuid(node[0]), node[1]));
}

template<> Node NodeCreator<Government>::createNodeFromObject(const Government& t) {
	Node n("government");
	n.addChild(Node("id", boost::lexical_cast<std::string>(t.getId())));
	n.addChild(Node("name", t.getName()));
	return n;
}