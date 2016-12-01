#include "unit.hpp"
#include "unit_creator.hpp"

#include "player_storage.hpp"
#include "unittype_storage.hpp"
#include "location_storage.hpp"

template<> boost::shared_ptr<Unit> NodeCreator<Unit>::createObjectFromNode(const std::vector<XmlNode>& node) {

	std::list<boost::uuids::uuid> occupiedFacilityIdList;
	std::list<boost::uuids::uuid> constructingUnitIdList;
	for(std::vector<XmlNode>::const_iterator i = node[8].getChildren().begin(); i != node[8].getChildren().end(); i++) {
		occupiedFacilityIdList.push_back(Misc::uuid(i->getValue()));
	}
	for(std::vector<XmlNode>::const_iterator i = node[9].getChildren().begin(); i != node[9].getChildren().end(); i++) {
		constructingUnitIdList.push_back(Misc::uuid(i->getValue()));
	}

	return boost::shared_ptr<Unit>(new Unit(Misc::uuid(node[0]), 
		PlayerStorage::instance().get(Misc::uuid(node[1])), 
		UnitTypeStorage::instance().get(Misc::uuid(node[2])), 			
		LocationStorage::instance().get(Misc::uuid(node[3])), 
		LocationStorage::instance().get(Misc::uuid(node[4])),
		boost::lexical_cast<unsigned int>(node[5].getValue()),
		boost::lexical_cast<unsigned int>(node[6].getValue()),
		boost::lexical_cast<unsigned int>(node[7].getValue()),
		occupiedFacilityIdList,
		constructingUnitIdList));
}

template<> XmlNode NodeCreator<Unit>::createNodeFromObject(const Unit& t) {
	XmlNode n("unit");
	n.addChild(XmlNode("id", boost::lexical_cast<std::string>(t.getId())));
	n.addChild(XmlNode("playerID", boost::lexical_cast<std::string>(t.getPlayerId())));
	n.addChild(XmlNode("unitTypeID", boost::lexical_cast<std::string>(t.getUnitTypeId())));
	n.addChild(XmlNode("locationID", boost::lexical_cast<std::string>(t.getLocationId())));
	n.addChild(XmlNode("goalLocationID", boost::lexical_cast<std::string>(t.getGoalLocationId())));
	n.addChild(XmlNode("count", boost::lexical_cast<std::string>(t.getCount())));
	n.addChild(XmlNode("remainingMovementTime", boost::lexical_cast<std::string>(t.getRemainingMovementTime())));
	n.addChild(XmlNode("remainingConstructionTime", boost::lexical_cast<std::string>(t.getRemainingConstructionTime())));
	XmlNode occupiedFacilityList("occupiedFacilityIDs");
	for(std::list<boost::uuids::uuid>::const_iterator i = t.getOccupiedFacilityIdList().begin(); i != t.getOccupiedFacilityIdList().end(); i++) {
		occupiedFacilityList.addChild(XmlNode("id", boost::lexical_cast<std::string>(*i)));
	}
	n.addChild(occupiedFacilityList);
	XmlNode constructingUnitList("constructingUnitIDs");
	for(std::list<boost::uuids::uuid>::const_iterator i = t.getConstructingUnitIdList().begin(); i != t.getConstructingUnitIdList().end(); i++) {
		constructingUnitList.addChild(XmlNode("id", boost::lexical_cast<std::string>(*i)));
	}	
	n.addChild(constructingUnitList);
	return n;
}

