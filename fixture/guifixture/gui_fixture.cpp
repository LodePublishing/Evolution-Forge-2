#include <misc/randomgenerator.hpp>

#include "gui_fixture.hpp"
#include <misc/ids.hpp>
#include <gui/guiconfiguration_storage.hpp>
#include <gui/gui_directories.hpp>
#include <gui/gui_storage.hpp>

Gui_Fixture::Gui_Fixture():
	title("my gui"),
	iconTitle("my icon title"),
	test_screenshotFileName(IO::getDirectory(boost::assign::list_of("temp")) + "shot.png")
{ 
	
	GuiDirectories::init();
	test_gui = boost::shared_ptr<const Gui>(new Gui(title, iconTitle, GuiConfigurationStorage::instance().get(IDS::DEFAULT_GUI_CONFIGURATION_ID)));
	test_dc = test_gui->createScreen();
	GuiDirectories::initTemp("temp");

	GuiStorage::instance(init_guimap_helper());	
}

Gui_Fixture::~Gui_Fixture() 
{
	GuiDirectories::initTemp("temp");

	GuiStorage::clear();

	GuiDirectories::init();

	delete test_dc;
}

const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Gui> > Gui_Fixture::init_guimap_helper() const {
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const Gui> > guimap;
	guimap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const Gui> >(test_gui->getId(), test_gui));
	return guimap;
}