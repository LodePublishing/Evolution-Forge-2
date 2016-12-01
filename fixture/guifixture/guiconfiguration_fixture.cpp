#include <misc/randomgenerator.hpp>
#include <gui/gui_directories.hpp>

#include "guiconfiguration_fixture.hpp"
#include <gui/guiconfiguration_storage.hpp>

GuiConfiguration_Fixture::GuiConfiguration_Fixture():
	bitmapFixture(),

	test_resolutionSize(RandomGenerator::instance().rnd(), RandomGenerator::instance().rnd()),
    test_bitDepth((eBitDepth)(RandomGenerator::instance().rnd()%MAX_BITDEPTHS)),
	test_fullScreen(RandomGenerator::instance().rndBool()),
    test_desiredFramerate(RandomGenerator::instance().rnd()),
    test_desiredCPU(RandomGenerator::instance().rnd()),
    test_unloadGraphics(RandomGenerator::instance().rndBool()),
    test_smoothMovements(RandomGenerator::instance().rndBool()),
    test_transparency(RandomGenerator::instance().rndBool()),
    test_softwareMouse(RandomGenerator::instance().rndBool()),
    test_glowingButtons(RandomGenerator::instance().rndBool()),
    test_toolTips(RandomGenerator::instance().rndBool()),
    test_dnaSpiral(RandomGenerator::instance().rndBool()),

	test_guiConfiguration(new GuiConfiguration(test_resolutionSize, test_bitDepth, test_fullScreen, test_desiredFramerate, test_desiredCPU, test_unloadGraphics, test_smoothMovements, test_transparency, bitmapFixture.test_bitmap1, test_softwareMouse, test_glowingButtons, test_toolTips, test_dnaSpiral)),
	test_guiConfigurationMap(init_guiconfigurationmap_helper())
{
	GuiDirectories::initTemp("temp");

	GuiConfigurationStorage::instance(test_guiConfigurationMap);
}

GuiConfiguration_Fixture::~GuiConfiguration_Fixture() 
{ 
	GuiDirectories::initTemp("temp");

	GuiConfigurationStorage::clear();

	GuiDirectories::init();
}


const std::map<const boost::uuids::uuid, const boost::shared_ptr<const GuiConfiguration> > GuiConfiguration_Fixture::init_guiconfigurationmap_helper() const {
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const GuiConfiguration> > guiconfigurationmap;
	guiconfigurationmap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const GuiConfiguration> >(test_guiConfiguration->getId(), test_guiConfiguration));
	return guiconfigurationmap;
}