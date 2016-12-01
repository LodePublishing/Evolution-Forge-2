#include "mainconfiguration_storage.hpp"
#include "mainconfiguration.hpp"

#include <misc/io.hpp>

#include <guicore/bitmap_storage.hpp>

template<> const std::string SingleStorage<MainConfiguration>::DATA_FILE_NAME_BASE = IO::getDirectory(boost::assign::list_of("data")("storage")("main")) + "mainconfiguration.xml";
template<> const std::string SingleStorage<MainConfiguration>::DATA_FILE_IDENTIFIER = "MainConfigurationStorage";

template<> boost::shared_ptr<MainConfiguration> NodeCreator<MainConfiguration>::createObjectFromNode(const std::vector<Node>& node) {
	return boost::shared_ptr<MainConfiguration>(new MainConfiguration(
		Misc::uuid(node[0]), 
		Misc::uuid(node[1]), 
		Misc::uuid(node[2]), 
		BitmapStorage::instance().get(Misc::uuid(node[3])), 
		boost::lexical_cast<bool>(node[4].getValue())
		));
}

template<> Node NodeCreator<MainConfiguration>::createNodeFromObject(const MainConfiguration& t) {
	Node n("mainconfiguration");
	n.addChild(Node("id", boost::lexical_cast<std::string>(t.getId())));
	n.addChild(Node("LanguageID", boost::lexical_cast<std::string>(t.getLanguageId())));	
	n.addChild(Node("GuiID", boost::lexical_cast<std::string>(t.getGuiId())));	
	n.addChild(Node("BackgroundBitmapID", boost::lexical_cast<std::string>(t.getBackgroundBitmap()->getId())));	
	n.addChild(Node("DnaSpiral", boost::lexical_cast<std::string>(t.isDnaSpiral())));	
	return n;
}