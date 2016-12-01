#include "units_storage.hpp"
#include "units.hpp"

#include <misc/io.hpp>

template<> const std::string SingleStorage<Units>::DATA_FILE_NAME_BASE = IO::getDirectory(boost::assign::list_of("data")("storage")("core")) + "units.xml";
template<> const std::string SingleStorage<Units>::DATA_FILE_IDENTIFIER = "UnitsStorage";

template<> boost::shared_ptr<Units> NodeCreator<Units>::createObjectFromNode(const std::vector<Node>& node) {
	std::list<boost::shared_ptr<Unit> > unitList;
	for(std::vector<Node>::const_iterator i = node[1].getChildren().begin(); i != node[1].getChildren().end(); i++) {
		unitList.push_back(boost::shared_ptr<Unit>(NodeCreator<Unit>::createObjectFromNode(i->getChildren())));
	}
	boost::shared_ptr<Units> temp = boost::shared_ptr<Units>(new Units(Misc::uuid(node[0]), unitList));
	temp->initializeUnitList();
	return temp;
}

template<> Node NodeCreator<Units>::createNodeFromObject(const Units& t) {
	Node n("units");
	n.addChild(Node("id", boost::lexical_cast<std::string>(t.getId())));
	Node unitIdList("units");
	for(std::list<boost::shared_ptr<Unit> >::const_iterator i = t.getUnitList().begin(); i != t.getUnitList().end(); i++) {
		unitIdList.addChild(NodeCreator<Unit>::createNodeFromObject(**i));
	}
	n.addChild(unitIdList);
	return n;
}

