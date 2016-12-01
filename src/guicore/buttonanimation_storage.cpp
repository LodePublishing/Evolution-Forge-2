#include "buttonanimation_storage.hpp"
#include "buttonanimation.hpp"

#include <misc/miscellaneous.hpp>
#include <misc/io.hpp>

#include "brush_storage.hpp"
#include "color_storage.hpp"
#include "pen_storage.hpp"
#include "bitmap_storage.hpp"

template<> const std::string SingleStorage<ButtonAnimation>::DATA_FILE_NAME_BASE = IO::getDirectory(boost::assign::list_of("data")("storage")("guicore")) + "buttonanimation.xml";
template<> const std::string SingleStorage<ButtonAnimation>::DATA_FILE_IDENTIFIER = "ButtonAnimationStorage";

template<> boost::shared_ptr<ButtonAnimation> NodeCreator<ButtonAnimation>::createObjectFromNode(const std::vector<XmlNode>& node) {
	return boost::shared_ptr<ButtonAnimation>(new ButtonAnimation(Misc::uuid(node[0]),
		BrushStorage::instance().get(node[1]),
		BrushStorage::instance().get(node[2]),
		ColorStorage::instance().get(node[3]),
		ColorStorage::instance().get(node[4]),
		PenStorage::instance().get(node[5]),
		PenStorage::instance().get(node[6]),
		BitmapStorage::instance().get(node[7])));
}

template<> XmlNode NodeCreator<ButtonAnimation>::createNodeFromObject(const ButtonAnimation& t) {
	XmlNode n("buttonAnimation");
	n.addChild(XmlNode("id", boost::lexical_cast<std::string>(t.getId())));
	n.addChild(XmlNode("startBrushID", boost::lexical_cast<std::string>(t.getStartBrush()->getId())));
	n.addChild(XmlNode("endBrushID", boost::lexical_cast<std::string>(t.getEndBrush()->getId())));
	n.addChild(XmlNode("startTextColorID", boost::lexical_cast<std::string>(t.getStartTextColor()->getId())));
	n.addChild(XmlNode("endTextColorID", boost::lexical_cast<std::string>(t.getEndTextColor()->getId())));
	n.addChild(XmlNode("startBorderPenID", boost::lexical_cast<std::string>(t.getStartBorderPen()->getId())));
	n.addChild(XmlNode("endBorderPenID", boost::lexical_cast<std::string>(t.getEndBorderPen()->getId())));
	n.addChild(XmlNode("bitmapID", boost::lexical_cast<std::string>(t.getBitmap()->getId())));
	return n;
}