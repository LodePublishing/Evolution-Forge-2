#include "player_storage.hpp"
#include "player.hpp"

#include <misc/io.hpp>

#include "government_storage.hpp"


template<> const std::string SingleStorage<Player>::DATA_FILE_NAME_BASE = IO::getDirectory(boost::assign::list_of("data")("storage")("core")) + "player.xml";
template<> const std::string SingleStorage<Player>::DATA_FILE_IDENTIFIER = "PlayerStorage";

template<> boost::shared_ptr<Player> NodeCreator<Player>::createObjectFromNode(const std::vector<XmlNode>& node) {
	return boost::shared_ptr<Player>(new Player(Misc::uuid(node[0]), node[1], GovernmentStorage::instance().get(node[2])));
}

template<> XmlNode NodeCreator<Player>::createNodeFromObject(const Player& t) {
	XmlNode n("player");
	n.addChild(XmlNode("id", boost::lexical_cast<std::string>(t.getId())));
	n.addChild(XmlNode("name", t.getName()));
	n.addChild(XmlNode("governmentID", boost::lexical_cast<std::string>(t.getGovernmentId())));
	return n;
}