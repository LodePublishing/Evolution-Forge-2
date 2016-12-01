#include "windowlayout_storage.hpp"
#include "windowlayout.hpp"

#include <misc/miscellaneous.hpp>
#include <misc/io.hpp>
#include <misc/exceptions.hpp>

template<> const std::string SingleStorage<WindowLayout>::DATA_FILE_NAME_BASE = IO::getDirectory(boost::assign::list_of("data")("storage")("geometry")) + "windowlayout.xml";
template<> const std::string SingleStorage<WindowLayout>::DATA_FILE_IDENTIFIER = "WindowLayoutStorage";

std::string getDockType(eDockType dockType) {
	std::string dockTypeName = "";
switch(dockType) {
	case NO_DOCKTYPE:dockTypeName = "NO_DOCKTYPE";break;
	case ABSOLUTE_COORDINATE_DOCKTYPE:dockTypeName = "ABSOLUTE_COORDINATE_DOCKTYPE";break;
	case DOCK_WITH_BEGINNING_BORDER_OF_DOCKTYPE:dockTypeName = "DOCK_WITH_BEGINNING_BORDER_OF_DOCKTYPE";break;
	case DOCK_WITH_ENDING_BORDER_OF_DOCKTYPE:dockTypeName = "DOCK_WITH_ENDING_BORDER_OF_DOCKTYPE";break;
	case DOCK_WITH_BEGINNING_INSIDE_OF_DOCKTYPE:dockTypeName = "DOCK_WITH_BEGINNING_INSIDE_OF_DOCKTYPE";break;
	case DOCK_WITH_ENDING_INSIDE_OF_DOCKTYPE:dockTypeName = "DOCK_WITH_ENDING_INSIDE_OF_DOCKTYPE";break;
	case DOCK_WITH_CENTER_INSIDE_OF_DOCKTYPE:dockTypeName = "DOCK_WITH_CENTER_INSIDE_OF_DOCKTYPE";break;
	
	default:break;
	}
	return dockTypeName;
}


eDockType getDockType(std::string dockTypeValue)
{
	eDockType dockType;

	if(dockTypeValue == "NO_DOCKTYPE") {
		dockType = NO_DOCKTYPE;
	} else 
	if(dockTypeValue == "ABSOLUTE_COORDINATE_DOCKTYPE") {
		dockType = ABSOLUTE_COORDINATE_DOCKTYPE;
	} else 
	if(dockTypeValue == "DOCK_WITH_BEGINNING_BORDER_OF_DOCKTYPE") {
		dockType = DOCK_WITH_BEGINNING_BORDER_OF_DOCKTYPE;
	} else 
	if(dockTypeValue == "DOCK_WITH_ENDING_BORDER_OF_DOCKTYPE") {
		dockType = DOCK_WITH_ENDING_BORDER_OF_DOCKTYPE;
	} else 
	if(dockTypeValue == "DOCK_WITH_BEGINNING_INSIDE_OF_DOCKTYPE") {
		dockType = DOCK_WITH_BEGINNING_INSIDE_OF_DOCKTYPE;
	} else 
	if(dockTypeValue == "DOCK_WITH_ENDING_INSIDE_OF_DOCKTYPE") {
		dockType = DOCK_WITH_ENDING_INSIDE_OF_DOCKTYPE;
	} else 
	if(dockTypeValue == "DOCK_WITH_CENTER_INSIDE_OF_DOCKTYPE") {
		dockType = DOCK_WITH_CENTER_INSIDE_OF_DOCKTYPE;
	} else {
		throw FileException("Error creating window layout from node (" + dockTypeValue + " is unknown dock type, see " + SingleStorage<WindowLayout>::DATA_FILE_NAME_BASE + ")");
	}

	return dockType;
}

template<> boost::shared_ptr<WindowLayout> NodeCreator<WindowLayout>::createObjectFromNode(const std::vector<XmlNode>& node) {
	

	std::string dockTypeHorizontalValue = node[5].getValue();
	std::string dockTypeVerticalValue = node[6].getValue();
	eDockType dockTypeHorizontal = getDockType(dockTypeHorizontalValue);
	eDockType dockTypeVertical = getDockType(dockTypeVerticalValue);

	return boost::shared_ptr<WindowLayout>(new WindowLayout(
		Misc::uuid(node[0]), 
		Size(static_cast<Uint16>(boost::lexical_cast<unsigned int>(node[1].getValue())),
		static_cast<Uint16>(boost::lexical_cast<unsigned int>(node[2].getValue()))),
		
		Size(static_cast<Uint16>(boost::lexical_cast<unsigned int>(node[3].getValue())), 
		static_cast<Uint16>(boost::lexical_cast<unsigned int>(node[4].getValue()))),

		dockTypeHorizontal, dockTypeVertical,
		Point(static_cast<Sint16>(boost::lexical_cast<unsigned int>(node[7].getValue())), 
		static_cast<Sint16>(boost::lexical_cast<unsigned int>(node[8].getValue()))),		
		Misc::uuid(node[9])));
}

template<> XmlNode NodeCreator<WindowLayout>::createNodeFromObject(const WindowLayout& t) {

	std::string dockTypeHorizontalName = getDockType(t.getDockTypeHorizontal());
	std::string dockTypeVerticalName = getDockType(t.getDockTypeVertical());

	XmlNode n("windowlayout");
	n.addChild(XmlNode("id", boost::lexical_cast<std::string>(t.getId())));
	n.addChild(XmlNode("width", boost::lexical_cast<std::string>(t.getWidth())));
	n.addChild(XmlNode("height", boost::lexical_cast<std::string>(t.getHeight())));
	n.addChild(XmlNode("maxwidth", boost::lexical_cast<std::string>(t.getMaxWidth())));
	n.addChild(XmlNode("maxheight", boost::lexical_cast<std::string>(t.getMaxHeight())));
	n.addChild(XmlNode("dockTypeHorizontal", dockTypeHorizontalName));
	n.addChild(XmlNode("dockTypeVertical", dockTypeVerticalName));
	n.addChild(XmlNode("x", boost::lexical_cast<std::string>(t.getPosition().getX())));
	n.addChild(XmlNode("y", boost::lexical_cast<std::string>(t.getPosition().getY())));
	n.addChild(XmlNode("windowLayoutHorizontalID", boost::lexical_cast<std::string>(t.getWindowLayoutHorizontalId())));
	n.addChild(XmlNode("windowLayoutVerticalID", boost::lexical_cast<std::string>(t.getWindowLayoutVerticalId())));

	// TODO percent!

	return n;
}