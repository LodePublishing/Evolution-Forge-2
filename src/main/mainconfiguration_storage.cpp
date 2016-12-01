#include "mainconfiguration_storage.hpp"
#include "mainconfiguration.hpp"

#include <misc/io.hpp>

#include <guicore/bitmap_storage.hpp>

template<> const std::string SingleStorage<MainConfiguration>::DATA_FILE_NAME_BASE = IO::getDirectory(boost::assign::list_of("data")("storage")("main")) + "mainconfiguration.xml";
template<> const std::string SingleStorage<MainConfiguration>::DATA_FILE_IDENTIFIER = "MainConfigurationStorage";

template<> boost::shared_ptr<MainConfiguration> NodeCreator<MainConfiguration>::createObjectFromNode(const std::vector<XmlNode>& node) {
	return boost::shared_ptr<MainConfiguration>(new MainConfiguration(
		Misc::uuid(node[0]), 
		Misc::uuid(node[1]), 
		Misc::uuid(node[2]), 
		Misc::uuid(node[3]), 
		boost::lexical_cast<bool>(node[4].getValue()),
		BitmapStorage::instance().get(Misc::uuid(node[5])), 
		boost::lexical_cast<bool>(node[6].getValue())
		));
}

template<> XmlNode NodeCreator<MainConfiguration>::createNodeFromObject(const MainConfiguration& t) {
	XmlNode n("mainconfiguration");
	n.addChild(XmlNode("id", boost::lexical_cast<std::string>(t.getId())));
	n.addChild(XmlNode("LanguageID", boost::lexical_cast<std::string>(t.getLanguageId())));	
	n.addChild(XmlNode("GuiID", boost::lexical_cast<std::string>(t.getGuiId())));
	n.addChild(XmlNode("SoundConfigurationID", boost::lexical_cast<std::string>(t.getGuiId())));
	n.addChild(XmlNode("FirstStart", boost::lexical_cast<std::string>(t.isFirstStart())));	
	n.addChild(XmlNode("BackgroundBitmapID", boost::lexical_cast<std::string>(t.getBackgroundBitmap()->getId())));	
	n.addChild(XmlNode("DnaSpiral", boost::lexical_cast<std::string>(t.isDnaSpiral())));	
	return n;
}