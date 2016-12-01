#include "unittype_storage.hpp"
#include "unittype.hpp"
#include "unitresourcetype.hpp"

#include <misc/io.hpp>

#include "race_storage.hpp"
#include "unitresourcetype_creator.hpp"


template<> const std::string SingleStorage<UnitType>::DATA_FILE_NAME_BASE = IO::getDirectory(boost::assign::list_of("data")("storage")("core")) + "unittype.xml";
template<> const std::string SingleStorage<UnitType>::DATA_FILE_IDENTIFIER = "UnitTypeStorage";

template<> boost::shared_ptr<UnitType> NodeCreator<UnitType>::createObjectFromNode(const std::vector<XmlNode>& node) {
	std::list<UnitResourceType> unitResourceTypeList;
	for(std::vector<XmlNode>::const_iterator i = node[3].getChildren().begin(); i != node[3].getChildren().end(); i++) {
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

template<> XmlNode NodeCreator<UnitType>::createNodeFromObject(const UnitType& t) {
	XmlNode n("unittype");
	n.addChild(XmlNode("id", boost::lexical_cast<std::string>(t.getId())));
	n.addChild(XmlNode("name", t.getName()));
	n.addChild(XmlNode("raceID", boost::lexical_cast<std::string>(t.getRaceId())));

	XmlNode resourcesList("resources");
	for(std::list<UnitResourceType>::const_iterator i = t.getResources().begin(); i != t.getResources().end(); i++) {
		resourcesList.addChild(NodeCreator<UnitResourceType>::createNodeFromObject(*i));
	}
	n.addChild(resourcesList);

	n.addChild(XmlNode("corporeal", boost::lexical_cast<std::string>(t.isCorporeal())));
	n.addChild(XmlNode("maxCount", boost::lexical_cast<std::string>(t.getMaxCount())));
	n.addChild(XmlNode("buildTime", boost::lexical_cast<std::string>(t.getBuildTime())));
	n.addChild(XmlNode("movementType", boost::lexical_cast<std::string>(t.getMovementType())));
	n.addChild(XmlNode("speed", boost::lexical_cast<std::string>(t.getSpeed())));
	n.addChild(XmlNode("upgradedSpeed", boost::lexical_cast<std::string>(t.getUpgradedSpeed())));
	
	return n;
}
