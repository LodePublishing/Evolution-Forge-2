#include "gui_storage.hpp"
#include "guiinstance.hpp"

#include <misc/io.hpp>

#include "guiconfiguration_storage.hpp"

template<> const std::string SingleStorage<Gui>::DATA_FILE_NAME_BASE = IO::getDirectory(boost::assign::list_of("data")("storage")("gui")) + "gui.xml";
template<> const std::string SingleStorage<Gui>::DATA_FILE_IDENTIFIER = "GuiStorage";

template<> boost::shared_ptr<Gui> NodeCreator<Gui>::createObjectFromNode(const std::vector<Node>& node) {
	return boost::shared_ptr<Gui>(new Gui(
		Misc::uuid(node[0]),
		node[1],
		GuiConfigurationStorage::instance().get(Misc::uuid(node[2]))));
}

template<> Node NodeCreator<Gui>::createNodeFromObject(const Gui& t) {
	Node n("gui");
	n.addChild(Node("id", boost::lexical_cast<std::string>(t.getId())));
	n.addChild(Node("configurationID", boost::lexical_cast<std::string>(t.getGuiConfigurationId())));
	n.addChild(Node("WindowTitle", boost::lexical_cast<std::string>(t.getTitle())));	
	return n;
}
