#include "unittype_storage.hpp"
#include "unittype.hpp"
#include "unitresourcetype.hpp"

#include <misc/io.hpp>

#include "race_storage.hpp"
#include "unitresourcetype_creator.hpp"


template<> const std::string SingleStorage<UnitType>::DATA_FILE_NAME_BASE = IO::getDirectory(boost::assign::list_of("data")("storage")("core")) + "unittype.xml";
template<> const std::string SingleStorage<UnitType>::DATA_FILE_IDENTIFIER = "UnitTypeStorage";

template<> boost::shared_ptr<UnitType> NodeCreator<UnitType>::createObjectFromNode(const std::vector<Node>& node) {
	std::list<UnitResourceType> unitResourceTypeList;
	for(std::vector<Node>::const_iterator i = node[3].getChildren().begin(); i != node[3].getChildren().end(); i++) {
		boost::shared_ptr<UnitResourceType> unitResourceType = NodeCreator<UnitResourceType>::createObjectFromNode(i->getChildren());
		unitResourceTypeList.push_back(*unitResourceType);
	}
	return boost::shared_ptr<UnitType>(new UnitType(Misc::uuid(node[0]), 
		node[1], 
		RaceStorage::instance().get(Misc::uuid(node[2])), 
		unitResourceTypeList, 
		boost::lexical_cast<bool>(node[4].getValue()), 
		boost::lexical_cast<unsigned int>(node[5].getValue()), 
		boost::lexical_cast<unsigned int>(node[6].getValue()), 
		(eUnitMovementType)(boost::lexical_cast<unsigned int>(node[7].getValue())), 
		boost::lexical_cast<unsigned int>(node[8].getValue()), 
		boost::lexical_cast<unsigned int>(node[9].getValue())));
}

template<> Node NodeCreator<UnitType>::createNodeFromObject(const UnitType& t) {
	Node n("unittype");
	n.addChild(Node("id", boost::lexical_cast<std::string>(t.getId())));
	n.addChild(Node("name", t.getName()));
	n.addChild(Node("raceID", boost::lexical_cast<std::string>(t.getRaceId())));

	Node resourcesList("resources");
	for(std::list<UnitResourceType>::const_iterator i = t.getResources().begin(); i != t.getResources().end(); i++) {
		resourcesList.addChild(NodeCreator<UnitResourceType>::createNodeFromObject(*i));
	}
	n.addChild(resourcesList);

	n.addChild(Node("corporeal", boost::lexical_cast<std::string>(t.isCorporeal())));
	n.addChild(Node("maxCount", boost::lexical_cast<std::string>(t.getMaxCount())));
	n.addChild(Node("buildTime", boost::lexical_cast<std::string>(t.getBuildTime())));
	n.addChild(Node("movementType", boost::lexical_cast<std::string>(t.getMovementType())));
	n.addChild(Node("speed", boost::lexical_cast<std::string>(t.getSpeed())));
	n.addChild(Node("upgradedSpeed", boost::lexical_cast<std::string>(t.getUpgradedSpeed())));
	
	return n;
}
