#include "guiconfiguration_storage.hpp"
#include "guiconfiguration.hpp"

#include <misc/io.hpp>

#include <guicore/bitmap_storage.hpp>

template<> const std::string SingleStorage<GuiConfiguration>::DATA_FILE_NAME_BASE = IO::getDirectory(boost::assign::list_of("data")("storage")("gui")) + "guiconfiguration.xml";
template<> const std::string SingleStorage<GuiConfiguration>::DATA_FILE_IDENTIFIER = "GuiConfigurationStorage";

template<> boost::shared_ptr<GuiConfiguration> NodeCreator<GuiConfiguration>::createObjectFromNode(const std::vector<Node>& node) {
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
		BitmapStorage::instance().get(Misc::uuid(node[9])), 
		boost::lexical_cast<bool>(node[10].getValue()), 
		boost::lexical_cast<bool>(node[11].getValue()), 
		boost::lexical_cast<bool>(node[12].getValue()), 
		boost::lexical_cast<bool>(node[13].getValue())
		));
}

template<> Node NodeCreator<GuiConfiguration>::createNodeFromObject(const GuiConfiguration& t) {
	Node n("guiconfiguration");
	n.addChild(Node("id", boost::lexical_cast<std::string>(t.getId())));
	n.addChild(NodeCreator<Size>::createNodeFromObject(t.getResolutionSize()));
	n.addChild(Node("BitDepth", boost::lexical_cast<std::string>(t.getBitDepth())));	
	n.addChild(Node("FullScreen", boost::lexical_cast<std::string>(t.isFullScreen())));	
	n.addChild(Node("DesiredFramerate", boost::lexical_cast<std::string>(t.getDesiredFramerate())));	
	n.addChild(Node("DesiredCPU", boost::lexical_cast<std::string>(t.getDesiredCPU())));	
	n.addChild(Node("UnloadGraphics", boost::lexical_cast<std::string>(t.isUnloadGraphics())));	
	n.addChild(Node("SmoothMovements", boost::lexical_cast<std::string>(t.isSmoothMovements())));	
	n.addChild(Node("Transparency", boost::lexical_cast<std::string>(t.isTransparency())));	
	n.addChild(Node("BackgroundBitmapID", boost::lexical_cast<std::string>(t.getBackgroundBitmap()->getId())));	
	n.addChild(Node("SoftwareMouse", boost::lexical_cast<std::string>(t.isSoftwareMouse())));	
	n.addChild(Node("GlowingButtons", boost::lexical_cast<std::string>(t.isGlowingButtons())));	
	n.addChild(Node("ToolTips", boost::lexical_cast<std::string>(t.isToolTips())));	
	n.addChild(Node("DnaSpiral", boost::lexical_cast<std::string>(t.isDnaSpiral())));	
	return n;
}