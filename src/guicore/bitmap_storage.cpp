#include "bitmap_storage.hpp"
#include "bitmap.hpp"

#include <misc/miscellaneous.hpp>
#include <misc/io.hpp>

template<> const std::string SingleStorage<Bitmap>::DATA_FILE_NAME_BASE = IO::getDirectory(boost::assign::list_of("data")("storage")("guicore")) + "bitmap.xml";
template<> const std::string SingleStorage<Bitmap>::DATA_FILE_IDENTIFIER = "BitmapStorage";

template<> boost::shared_ptr<Bitmap> NodeCreator<Bitmap>::createObjectFromNode(const std::vector<Node>& node) {
	return boost::shared_ptr<Bitmap>(new Bitmap(Misc::uuid(node[0]), node[1]));
}

template<> Node NodeCreator<Bitmap>::createNodeFromObject(const Bitmap& t) {
	Node n("rules");
	n.addChild(Node("id", boost::lexical_cast<std::string>(t.getId())));
	n.addChild(Node("fileName", t.getFileName()));
	return n;
}