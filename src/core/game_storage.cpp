#include "game_storage.hpp"
#include "game.hpp"

#include <misc/io.hpp>

#include "rules_storage.hpp"
#include "map_storage.hpp"
#include "startcondition_storage.hpp"

template<> const std::string SingleStorage<Game>::DATA_FILE_NAME_BASE = IO::getDirectory(boost::assign::list_of("data")("storage")("core")) + "game.xml";
template<> const std::string SingleStorage<Game>::DATA_FILE_IDENTIFIER = "GameStorage";


template<> boost::shared_ptr<Game> NodeCreator<Game>::createObjectFromNode(const std::vector<Node>& node) {
	return boost::shared_ptr<Game>(new Game(Misc::uuid(node[0]), 
		node[1], 
		RulesStorage::instance().get(Misc::uuid(node[2])), 
		MapStorage::instance().get(Misc::uuid(node[3])), 
		StartConditionStorage::instance().get(Misc::uuid(node[4]))));
}

template<> Node NodeCreator<Game>::createNodeFromObject(const Game& t) {
	Node n("game");
	n.addChild(Node("id", boost::lexical_cast<std::string>(t.getId())));
	n.addChild(Node("name", t.getName()));
	n.addChild(Node("rulesID", boost::lexical_cast<std::string>(t.getRulesId())));
	n.addChild(Node("mapID", boost::lexical_cast<std::string>(t.getMapId())));
	n.addChild(Node("startConditionID", boost::lexical_cast<std::string>(t.getStartConditionId())));
	return n;
}