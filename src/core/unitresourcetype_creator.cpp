#include "unitresourcetype_creator.hpp"
#include "unitresourcetype.hpp"

#include <list>
#include <vector>
#include <misc/miscellaneous.hpp>
#include <misc/uuid.hpp>

template<> boost::shared_ptr<UnitResourceType> NodeCreator<UnitResourceType>::createObjectFromNode(const std::vector<XmlNode>& node) {
	std::list<std::list<boost::uuids::uuid> > unitTypeIdList;
	for(std::vector<XmlNode>::const_iterator i = node[2].getChildren().begin(); i != node[2].getChildren().end(); i++) {
		std::list<boost::uuids::uuid> unitTypeIdList2;
		for(std::vector<XmlNode>::const_iterator j = i->getChildren().begin(); j != i->getChildren().end(); j++) {
			unitTypeIdList2.push_back(Misc::uuid(*j));
		}
		unitTypeIdList.push_back(unitTypeIdList2);
	}

	return boost::shared_ptr<UnitResourceType>(new UnitResourceType((eUnitResourceType)(boost::lexical_cast<unsigned int>((std::string)(node[0]))), boost::lexical_cast<signed int>(node[1].getValue()), unitTypeIdList));
}

template<> XmlNode NodeCreator<UnitResourceType>::createNodeFromObject(const UnitResourceType& t) {
	XmlNode n("unitresourcetype");
	n.addChild(XmlNode("resourceType", boost::lexical_cast<std::string>(t.getResourceType())));
	n.addChild(XmlNode("amount", boost::lexical_cast<std::string>(t.getAmount())));
	XmlNode unitTypeList("unitTypeIDs");
	for(std::list<std::list<boost::uuids::uuid> >::const_iterator i = t.getUnitTypeIdList().begin(); i != t.getUnitTypeIdList().end(); i++) {
		XmlNode unitTypeList2("list");
		for(std::list<boost::uuids::uuid>::const_iterator j = i->begin(); j != i->end(); j++) {
			unitTypeList2.addChild(XmlNode("id", boost::lexical_cast<std::string>(*j)));
		}
		unitTypeList.addChild(unitTypeList2);
	}
	n.addChild(unitTypeList);
	return n;
}




