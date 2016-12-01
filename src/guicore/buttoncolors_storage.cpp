#include "buttoncolors_storage.hpp"
#include "buttoncolors.hpp"

#include <misc/io.hpp>

#include "buttonanimation_storage.hpp"

template<> const std::string SingleStorage<ButtonColors>::DATA_FILE_NAME_BASE = IO::getDirectory(boost::assign::list_of("data")("storage")("guicore")) + "buttoncolors.xml";
template<> const std::string SingleStorage<ButtonColors>::DATA_FILE_IDENTIFIER = "ButtonColorsStorage";

template<> boost::shared_ptr<ButtonColors> NodeCreator<ButtonColors>::createObjectFromNode(const std::vector<Node>& node) {
	std::vector<boost::shared_ptr<const ButtonAnimation> > buttonAnimationVector;
	for(std::vector<Node>::const_iterator i = node[3].getChildren().begin(); i != node[3].getChildren().end(); i++) {
		buttonAnimationVector.push_back(ButtonAnimationStorage::instance().get(i->getValue())); // TODO?
	}
	return boost::shared_ptr<ButtonColors>(new ButtonColors(Misc::uuid(node[0]), boost::lexical_cast<unsigned int>(node[1].getValue()), static_cast<eButtonAnimationType>(boost::lexical_cast<unsigned int>(node[2].getValue())), buttonAnimationVector));
}

template<> Node NodeCreator<ButtonColors>::createNodeFromObject(const ButtonColors& t) {
	Node n("buttonColors");
	n.addChild(Node("id", boost::lexical_cast<std::string>(t.getId())));
	n.addChild(Node("speed", boost::lexical_cast<std::string>(t.getSpeed())));
	n.addChild(Node("animationType",  boost::lexical_cast<std::string>(t.getAnimationType())));
	Node buttonAnimationIdList("buttonAnimationIDs");
	for(std::vector<boost::shared_ptr<const ButtonAnimation> >::const_iterator i = t.getButtonAnimationVector().begin(); i != t.getButtonAnimationVector().end(); i++) {
		buttonAnimationIdList.addChild(Node("id", boost::lexical_cast<std::string>((*i)->getId())));
	}
	n.addChild(buttonAnimationIdList);
	return n;
}