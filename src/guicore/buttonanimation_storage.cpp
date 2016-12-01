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

template<> boost::shared_ptr<ButtonAnimation> NodeCreator<ButtonAnimation>::createObjectFromNode(const std::vector<Node>& node) {
	return boost::shared_ptr<ButtonAnimation>(new ButtonAnimation(Misc::uuid(node[0]),
		BrushStorage::instance().get(node[1]),
		BrushStorage::instance().get(node[2]),
		ColorStorage::instance().get(node[3]),
		ColorStorage::instance().get(node[4]),
		PenStorage::instance().get(node[5]),
		PenStorage::instance().get(node[6]),
		BitmapStorage::instance().get(node[7])));
}

template<> Node NodeCreator<ButtonAnimation>::createNodeFromObject(const ButtonAnimation& t) {
	Node n("buttonAnimation");
	n.addChild(Node("id", boost::lexical_cast<std::string>(t.getId())));
	n.addChild(Node("startBrushID", boost::lexical_cast<std::string>(t.getStartBrush()->getId())));
	n.addChild(Node("endBrushID", boost::lexical_cast<std::string>(t.getEndBrush()->getId())));
	n.addChild(Node("startTextColorID", boost::lexical_cast<std::string>(t.getStartTextColor()->getId())));
	n.addChild(Node("endTextColorID", boost::lexical_cast<std::string>(t.getEndTextColor()->getId())));
	n.addChild(Node("startBorderPenID", boost::lexical_cast<std::string>(t.getStartBorderPen()->getId())));
	n.addChild(Node("endBorderPenID", boost::lexical_cast<std::string>(t.getEndBorderPen()->getId())));
	n.addChild(Node("bitmapID", boost::lexical_cast<std::string>(t.getBitmap()->getId())));
	return n;
}