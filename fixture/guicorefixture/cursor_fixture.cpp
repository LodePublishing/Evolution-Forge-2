#include <misc/randomgenerator.hpp>

#include "cursor_fixture.hpp"

#include <misc/miscellaneous.hpp>
#include <misc/io.hpp>
#include <guicore/cursor_storage.hpp>
#include <guicore/guicore_directories.hpp>

#pragma warning(push, 0) 
#include <boost/assign/list_of.hpp>
#pragma warning(pop)

Cursor_Fixture::Cursor_Fixture() :
	test_arrowFileName(IO::getDirectory(boost::assign::list_of("fixture")("guicorefixture")("unittestdata")) + "arrow.png"),
	test_handFileName(IO::getDirectory(boost::assign::list_of("fixture")("guicorefixture")("unittestdata")) + "hand.png"),
	test_clock1FileName(IO::getDirectory(boost::assign::list_of("fixture")("guicorefixture")("unittestdata")) + "clock1.png"),
	test_clock2FileName(IO::getDirectory(boost::assign::list_of("fixture")("guicorefixture")("unittestdata")) + "clock2.png"),
	test_arrowCursor(new Cursor(test_arrowFileName)),
	test_handCursor(new Cursor(test_handFileName)),
	test_clock1Cursor(new Cursor(test_clock1FileName)),
	test_clock2Cursor(new Cursor(test_clock2FileName)),
	test_cursorMap(init_cursormap_helper())
{ 
	GuiCoreDirectories::initTemp("temp");	

	CursorStorage::instance(test_cursorMap);
}

Cursor_Fixture::~Cursor_Fixture() 
{ 
	GuiCoreDirectories::initTemp("temp");

	CursorStorage::clear();
	
	GuiCoreDirectories::init();
}

const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Cursor> > Cursor_Fixture::init_cursormap_helper() {
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const Cursor> > cursorMap;
	cursorMap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const Cursor> >(test_arrowCursor->getId(), test_arrowCursor));
	cursorMap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const Cursor> >(test_handCursor->getId(), test_handCursor));
	cursorMap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const Cursor> >(test_clock1Cursor->getId(), test_clock1Cursor));
	cursorMap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const Cursor> >(test_clock2Cursor->getId(), test_clock2Cursor));
	return cursorMap;
}