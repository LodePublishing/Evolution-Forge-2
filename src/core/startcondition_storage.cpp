#include "startcondition_storage.hpp"
#include "startcondition.hpp"

#include <misc/io.hpp>

#include "player_storage.hpp"
#include "units_storage.hpp"

template<> const std::string SingleStorage<StartCondition>::DATA_FILE_NAME_BASE = IO::getDirectory(boost::assign::list_of("data")("storage")("core")) + "startcondition.xml";
template<> const std::string SingleStorage<StartCondition>::DATA_FILE_IDENTIFIER = "StartConditionStorage";

template<> boost::shared_ptr<StartCondition> NodeCreator<StartCondition>::createObjectFromNode(const std::vector<Node>& node) {

	std::list<boost::shared_ptr<const Player> > playerList;
	for(std::vector<Node>::const_iterator i = node[4].getChildren().begin(); i != node[4].getChildren().end(); i++) {
		playerList.push_back(PlayerStorage::instance().get(i->getValue())); // TODO?
	}

	return boost::shared_ptr<StartCondition>(new StartCondition(Misc::uuid(node[0]), node[1], boost::lexical_cast<unsigned int>(node[2].getValue()), UnitsStorage::instance().get(node[3]), playerList));
}

template<> Node NodeCreator<StartCondition>::createNodeFromObject(const StartCondition& t) {
	Node n("startcondition");
	n.addChild(Node("id", boost::lexical_cast<std::string>(t.getId())));
	n.addChild(Node("name", t.getName()));
	n.addChild(Node("time", boost::lexical_cast<std::string>(t.getStartingTime())));
	n.addChild(Node("unitsID", boost::lexical_cast<std::string>(t.getUnitsId())));
	Node playerIdList("playerIDs");
	for(std::list<boost::uuids::uuid>::const_iterator i = t.getPlayerIdList().begin(); i != t.getPlayerIdList().end(); i++) {
		playerIdList.addChild(Node("id", boost::lexical_cast<std::string>(*i)));
	}
	n.addChild(playerIdList);

	return n;
}