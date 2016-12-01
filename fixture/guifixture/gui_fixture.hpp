#ifndef _GUI_FIXTURE_GUIFIXTURE_HPP
#define _GUI_FIXTURE_GUIFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)
#include <gui/guiinstance.hpp>

struct Gui_Fixture
{
	const std::string title;
	const std::string iconTitle;
	const std::string test_screenshotFileName;
	boost::shared_ptr<const Gui> test_gui;
	DC* test_dc;

	Gui_Fixture();	
	~Gui_Fixture();

private:
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Gui> > init_guimap_helper() const;
};

#endif // _GUI_FIXTURE_GUIFIXTURE_HPP
