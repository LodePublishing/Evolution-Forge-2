#include "rules_storage.hpp"
#include "rules.hpp"

#include <misc/io.hpp>

#include "race_storage.hpp"
#include "unittype_storage.hpp"


template<> const std::string SingleStorage<Rules>::DATA_FILE_NAME_BASE = IO::getDirectory(boost::assign::list_of("data")("storage")("core")) + "rules.xml";
template<> const std::string SingleStorage<Rules>::DATA_FILE_IDENTIFIER = "RulesStorage";

template<> boost::shared_ptr<Rules> NodeCreator<Rules>::createObjectFromNode(const std::vector<XmlNode>& node) {
	std::list<boost::shared_ptr<const Race> > raceList;
	std::list<boost::shared_ptr<const UnitType> > unitTypeList;
	
	for(std::vector<XmlNode>::const_iterator i = node[2].getChildren().begin(); i != node[2].getChildren().end(); i++) {
		raceList.push_back(RaceStorage::instance().get(i->getValue())); // TODO?
	}
	for(std::vector<XmlNode>::const_iterator i = node[3].getChildren().begin(); i != node[3].getChildren().end(); i++) {
		unitTypeList.push_back(UnitTypeStorage::instance().get(i->getValue())); // TODO?
	}

	return boost::shared_ptr<Rules>(new Rules(Misc::uuid(node[0]), node[1], raceList, unitTypeList));
}

template<> XmlNode NodeCreator<Rules>::createNodeFromObject(const Rules& t) {
	XmlNode n("rules");
	n.addChild(XmlNode("id", boost::lexical_cast<std::string>(t.getId())));
	n.addChild(XmlNode("name", t.getName()));
	XmlNode raceIdList("raceIDs");
	for(std::list<boost::uuids::uuid>::const_iterator i = t.getRaceIdList().begin(); i != t.getRaceIdList().end(); i++) {
		raceIdList.addChild(XmlNode("id", boost::lexical_cast<std::string>(*i)));
	}
	n.addChild(raceIdList);
	XmlNode unitTypeIdList("unitTypeIDs");
	for(std::list<boost::uuids::uuid>::const_iterator i = t.getUnitTypeIdList().begin(); i != t.getUnitTypeIdList().end(); i++) {
		unitTypeIdList.addChild(XmlNode("id", boost::lexical_cast<std::string>(*i)));
	}
	n.addChild(unitTypeIdList);
	return n;
}