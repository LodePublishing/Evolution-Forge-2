#include "color_storage.hpp"
#include "color.hpp"

#include <misc/miscellaneous.hpp>
#include <misc/io.hpp>

template<> const std::string SingleStorage<Color>::DATA_FILE_NAME_BASE = IO::getDirectory(boost::assign::list_of("data")("storage")("guicore")) + "color.xml";
template<> const std::string SingleStorage<Color>::DATA_FILE_IDENTIFIER = "ColorStorage";

template<> boost::shared_ptr<Color> NodeCreator<Color>::createObjectFromNode(const std::vector<XmlNode>& node) {
	return boost::shared_ptr<Color>(new Color(Misc::uuid(node[0]), 
		atoi(node[1].getValue().c_str()), 
		atoi(node[2].getValue().c_str()), 
		atoi(node[3].getValue().c_str()), 
		atoi(node[4].getValue().c_str())));
}

template<> XmlNode NodeCreator<Color>::createNodeFromObject(const Color& t) {
	XmlNode n("color");
	n.addChild(XmlNode("id", boost::lexical_cast<std::string>(t.getId())));
	n.addChild(XmlNode("r", boost::lexical_cast<std::string>((int)(t.r()))));
	n.addChild(XmlNode("g", boost::lexical_cast<std::string>((int)(t.g()))));
	n.addChild(XmlNode("b", boost::lexical_cast<std::string>((int)(t.b()))));
	n.addChild(XmlNode("a", boost::lexical_cast<std::string>((int)(t.a()))));
	return n;
}