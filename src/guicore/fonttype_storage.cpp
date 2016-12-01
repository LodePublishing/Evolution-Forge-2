#include "fonttype_storage.hpp"
#include "fonttype.hpp"

#include <misc/miscellaneous.hpp>
#include <misc/io.hpp>

#include "font_storage.hpp"

template<> const std::string SingleStorage<FontType>::DATA_FILE_NAME_BASE = IO::getDirectory(boost::assign::list_of("data")("storage")("guicore")) + "fonttype.xml";
template<> const std::string SingleStorage<FontType>::DATA_FILE_IDENTIFIER = "FontTypeStorage";

template<> boost::shared_ptr<FontType> NodeCreator<FontType>::createObjectFromNode(const std::vector<Node>& node) {
	return boost::shared_ptr<FontType>(new FontType(Misc::uuid(node[0]), 
		FontStorage::instance().get(node[1]), 
		FontStorage::instance().get(node[2]), 
		FontStorage::instance().get(node[3]), 
		FontStorage::instance().get(node[4]), 
		FontStorage::instance().get(node[5]), 
		FontStorage::instance().get(node[6]), 
		FontStorage::instance().get(node[7]), 
		FontStorage::instance().get(node[8])));
}

template<> Node NodeCreator<FontType>::createNodeFromObject(const FontType& t) {
	Node n("fontType");
	n.addChild(Node("id", boost::lexical_cast<std::string>(t.getId())));
	n.addChild(Node("fontID", boost::lexical_cast<std::string>(t.getNormalFont()->getId())));
	n.addChild(Node("boldFontID", boost::lexical_cast<std::string>(t.getBoldFont()->getId())));
	n.addChild(Node("shadowFontID", boost::lexical_cast<std::string>(t.getShadowFont()->getId())));
	n.addChild(Node("underlinedFontID", boost::lexical_cast<std::string>(t.getUnderlinedFont()->getId())));
	n.addChild(Node("shadowBoldFontID", boost::lexical_cast<std::string>(t.getShadowBoldFont()->getId())));
	n.addChild(Node("shadowUnderlinedFontID", boost::lexical_cast<std::string>(t.getShadowUnderlinedFont()->getId())));
	n.addChild(Node("underlinedBoldFontID", boost::lexical_cast<std::string>(t.getUnderlinedBoldFont()->getId())));
	n.addChild(Node("shadowUnderlinedBoldFontID", boost::lexical_cast<std::string>(t.getShadowUnderlinedBoldFont()->getId())));
	return n;
}