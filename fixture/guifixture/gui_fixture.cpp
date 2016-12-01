#include <misc/randomgenerator.hpp>

#include "gui_fixture.hpp"

Gui_Fixture::Gui_Fixture():
	guiConfigurationFixture(),
	title("my gui"),
	gui(new Gui(title, guiConfigurationFixture.test_guiConfiguration))
{ }

Gui_Fixture::~Gui_Fixture() 
{ }
