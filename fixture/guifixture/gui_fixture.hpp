#ifndef _GUI_FIXTURE_GUIFIXTURE_HPP
#define _GUI_FIXTURE_GUIFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)
#include "guiconfiguration_fixture.hpp"
#include <gui/guiinstance.hpp>

struct Gui_Fixture
{
	GuiConfiguration_Fixture guiConfigurationFixture;

	const std::string title;
	const boost::shared_ptr<const Gui> gui;

	Gui_Fixture();	
	~Gui_Fixture();
};

#endif // _GUI_FIXTURE_GUIFIXTURE_HPP
