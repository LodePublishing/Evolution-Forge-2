#include "race_storage.hpp"
#include "race.hpp"

#include <misc/io.hpp>

template<> const std::string SingleStorage<Race>::DATA_FILE_NAME_BASE = IO::getDirectory(boost::assign::list_of("data")("storage")("core")) + "race.xml";
template<> const std::string SingleStorage<Race>::DATA_FILE_IDENTIFIER = "RaceStorage";

template<> boost::shared_ptr<Race> NodeCreator<Race>::createObjectFromNode(const std::vector<Node>& node) {
	return boost::shared_ptr<Race>(new Race(Misc::uuid(node[0]), node[1]));
}

template<> Node NodeCreator<Race>::createNodeFromObject(const Race& t) {
	Node n("race");
	n.addChild(Node("id", boost::lexical_cast<std::string>(t.getId())));
	n.addChild(Node("name", t.getName()));
	return n;
}