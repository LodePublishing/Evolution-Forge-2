#include "unit.hpp"
#include "unit_creator.hpp"

#include "player_storage.hpp"
#include "unittype_storage.hpp"
#include "location_storage.hpp"

template<> boost::shared_ptr<Unit> NodeCreator<Unit>::createObjectFromNode(const std::vector<Node>& node) {

	std::list<boost::uuids::uuid> occupiedFacilityIdList;
	std::list<boost::uuids::uuid> constructingUnitIdList;
	for(std::vector<Node>::const_iterator i = node[8].getChildren().begin(); i != node[8].getChildren().end(); i++) {
		occupiedFacilityIdList.push_back(Misc::uuid(i->getValue()));
	}
	for(std::vector<Node>::const_iterator i = node[9].getChildren().begin(); i != node[9].getChildren().end(); i++) {
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

template<> Node NodeCreator<Unit>::createNodeFromObject(const Unit& t) {
	Node n("unit");
	n.addChild(Node("id", boost::lexical_cast<std::string>(t.getId())));
	n.addChild(Node("playerID", boost::lexical_cast<std::string>(t.getPlayerId())));
	n.addChild(Node("unitTypeID", boost::lexical_cast<std::string>(t.getUnitTypeId())));
	n.addChild(Node("locationID", boost::lexical_cast<std::string>(t.getLocationId())));
	n.addChild(Node("goalLocationID", boost::lexical_cast<std::string>(t.getGoalLocationId())));
	n.addChild(Node("count", boost::lexical_cast<std::string>(t.getCount())));
	n.addChild(Node("remainingMovementTime", boost::lexical_cast<std::string>(t.getRemainingMovementTime())));
	n.addChild(Node("remainingConstructionTime", boost::lexical_cast<std::string>(t.getRemainingConstructionTime())));
	Node occupiedFacilityList("occupiedFacilityIDs");
	for(std::list<boost::uuids::uuid>::const_iterator i = t.getOccupiedFacilityIdList().begin(); i != t.getOccupiedFacilityIdList().end(); i++) {
		occupiedFacilityList.addChild(Node("id", boost::lexical_cast<std::string>(*i)));
	}
	n.addChild(occupiedFacilityList);
	Node constructingUnitList("constructingUnitIDs");
	for(std::list<boost::uuids::uuid>::const_iterator i = t.getConstructingUnitIdList().begin(); i != t.getConstructingUnitIdList().end(); i++) {
		constructingUnitList.addChild(Node("id", boost::lexical_cast<std::string>(*i)));
	}	
	n.addChild(constructingUnitList);
	return n;
}

