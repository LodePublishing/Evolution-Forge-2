#include "bitmap_storage.hpp"
#include "bitmap.hpp"

#include <misc/miscellaneous.hpp>
#include <misc/io.hpp>

template<> const std::string SingleStorage<Bitmap>::DATA_FILE_NAME_BASE = IO::getDirectory(boost::assign::list_of("data")("storage")("guicore")) + "bitmap.xml";
template<> const std::string SingleStorage<Bitmap>::DATA_FILE_IDENTIFIER = "BitmapStorage";

template<> boost::shared_ptr<Bitmap> NodeCreator<Bitmap>::createObjectFromNode(const std::vector<XmlNode>& node) {
	std::string transparency = node[2].getValue();
	bool transparent = (transparency == "TRANSPARENT");
	return boost::shared_ptr<Bitmap>(new Bitmap(Misc::uuid(node[0]), node[1], transparent));
}

template<> XmlNode NodeCreator<Bitmap>::createNodeFromObject(const Bitmap& t) {
	XmlNode n("bitmap");
	n.addChild(XmlNode("id", boost::lexical_cast<std::string>(t.getId())));
	n.addChild(XmlNode("fileName", t.getFileName()));
	n.addChild(XmlNode("transparent", t.isTransparent()?"TRANSPARENT":"SOLID"));
	return n;
}