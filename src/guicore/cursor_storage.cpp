#include "cursor_storage.hpp"
#include "cursor.hpp"

#include <misc/miscellaneous.hpp>
#include <misc/io.hpp>

template<> const std::string SingleStorage<Cursor>::DATA_FILE_NAME_BASE = IO::getDirectory(boost::assign::list_of("data")("storage")("guicore")) + "cursor.xml";
template<> const std::string SingleStorage<Cursor>::DATA_FILE_IDENTIFIER = "CursorStorage";

template<> boost::shared_ptr<Cursor> NodeCreator<Cursor>::createObjectFromNode(const std::vector<Node>& node) {
	return boost::shared_ptr<Cursor>(new Cursor(Misc::uuid(node[0]), node[1]));
}

template<> Node NodeCreator<Cursor>::createNodeFromObject(const Cursor& t) {
	Node n("cursor");
	n.addChild(Node("id", boost::lexical_cast<std::string>(t.getId())));
	n.addChild(Node("fileName", t.getFileName()));
	return n;
}