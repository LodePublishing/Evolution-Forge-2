#include "guiconfiguration_storage.hpp"
#include "guiconfiguration.hpp"

#include <misc/io.hpp>

#include <guicore/bitmap_storage.hpp>

template<> const std::string SingleStorage<GuiConfiguration>::DATA_FILE_NAME_BASE = IO::getDirectory(boost::assign::list_of("data")("storage")("gui")) + "guiconfiguration.xml";
template<> const std::string SingleStorage<GuiConfiguration>::DATA_FILE_IDENTIFIER = "GuiConfigurationStorage";

template<> boost::shared_ptr<GuiConfiguration> NodeCreator<GuiConfiguration>::createObjectFromNode(const std::vector<XmlNode>& node) {
	return boost::shared_ptr<GuiConfiguration>(new GuiConfiguration(
		Misc::uuid(node[0]), 
		*NodeCreator<Size>::createObjectFromNode(node[1].getChildren()),
		(eBitDepth)(boost::lexical_cast<unsigned int>(node[2].getValue())), 
		boost::lexical_cast<bool>(node[3].getValue()), 
		boost::lexical_cast<unsigned int>(node[4].getValue()),
		boost::lexical_cast<unsigned int>(node[5].getValue()),
		boost::lexical_cast<bool>(node[6].getValue()), 
		boost::lexical_cast<bool>(node[7].getValue()), 
		boost::lexical_cast<bool>(node[8].getValue()), 
		boost::lexical_cast<bool>(node[9].getValue()), 
		boost::lexical_cast<bool>(node[10].getValue()), 
		boost::lexical_cast<bool>(node[11].getValue())
		));
}

template<> XmlNode NodeCreator<GuiConfiguration>::createNodeFromObject(const GuiConfiguration& t) {
	XmlNode n("guiconfiguration");
	n.addChild(XmlNode("id", boost::lexical_cast<std::string>(t.getId())));
	n.addChild(NodeCreator<Size>::createNodeFromObject(t.getResolutionSize()));
	n.addChild(XmlNode("BitDepth", boost::lexical_cast<std::string>(t.getBitDepth())));	
	n.addChild(XmlNode("FullScreen", boost::lexical_cast<std::string>(t.isFullScreen())));	
	n.addChild(XmlNode("DesiredFramerate", boost::lexical_cast<std::string>(t.getDesiredFramerate())));	
	n.addChild(XmlNode("DesiredCPU", boost::lexical_cast<std::string>(t.getDesiredCPU())));	
	n.addChild(XmlNode("UnloadGraphics", boost::lexical_cast<std::string>(t.isUnloadGraphics())));	
	n.addChild(XmlNode("SmoothMovements", boost::lexical_cast<std::string>(t.isSmoothMovements())));	
	n.addChild(XmlNode("Transparency", boost::lexical_cast<std::string>(t.isTransparency())));
	n.addChild(XmlNode("SoftwareMouse", boost::lexical_cast<std::string>(t.isSoftwareMouse())));	
	n.addChild(XmlNode("GlowingButtons", boost::lexical_cast<std::string>(t.isGlowingButtons())));	
	n.addChild(XmlNode("ToolTips", boost::lexical_cast<std::string>(t.isToolTips())));
	return n;
}