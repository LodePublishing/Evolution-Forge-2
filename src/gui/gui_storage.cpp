#include "gui_storage.hpp"
#include "guiinstance.hpp"

#include <misc/io.hpp>

#include "guiconfiguration_storage.hpp"

template<> const std::string SingleStorage<Gui>::DATA_FILE_NAME_BASE = IO::getDirectory(boost::assign::list_of("data")("storage")("gui")) + "gui.xml";
template<> const std::string SingleStorage<Gui>::DATA_FILE_IDENTIFIER = "GuiStorage";

template<> boost::shared_ptr<Gui> NodeCreator<Gui>::createObjectFromNode(const std::vector<XmlNode>& node) {
	return boost::shared_ptr<Gui>(new Gui(
		Misc::uuid(node[0]),
		node[1],
		node[2],
		GuiConfigurationStorage::instance().get(Misc::uuid(node[3]))));
}

template<> XmlNode NodeCreator<Gui>::createNodeFromObject(const Gui& t) {
	XmlNode n("gui");
	n.addChild(XmlNode("id", boost::lexical_cast<std::string>(t.getId())));
	n.addChild(XmlNode("WindowTitle", boost::lexical_cast<std::string>(t.getTitle())));	
	n.addChild(XmlNode("IconWindowTitle", boost::lexical_cast<std::string>(t.getIconTitle())));	
	n.addChild(XmlNode("configurationID", boost::lexical_cast<std::string>(t.getGuiConfigurationId())));
	return n;
}
