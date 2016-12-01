#ifndef _GUICORE_FIXTURE_CURSORFIXTURE_HPP
#define _GUICORE_FIXTURE_CURSORFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/shared_ptr.hpp>
#pragma warning(pop)

#include <guicore/cursor.hpp>
#include <map>

struct Cursor_Fixture
{
	const std::string test_arrowFileName;
	const std::string test_handFileName;
	const std::string test_clock1FileName;
	const std::string test_clock2FileName;
	const boost::shared_ptr<const Cursor> test_arrowCursor;
	const boost::shared_ptr<const Cursor> test_handCursor;
	const boost::shared_ptr<const Cursor> test_clock1Cursor;
	const boost::shared_ptr<const Cursor> test_clock2Cursor;

	Cursor_Fixture();	
	~Cursor_Fixture();
private:
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Cursor> > test_cursorMap;
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Cursor> > init_cursormap_helper();
};

#endif // _GUICORE_FIXTURE_CURSORFIXTURE_HPP
