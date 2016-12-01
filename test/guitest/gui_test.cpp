#ifndef WIN32
#define BOOST_TEST_DYN_LINK
#endif
#define BOOST_TEST_MODULE GUI
#pragma warning(push, 0) 
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <guifixture/guiconfiguration_fixture.hpp>
#include <guifixture/gui_fixture.hpp>
#include <gui/guiconfiguration_storage.hpp>
#include <guicore/bitmap_storage.hpp>
#include <misc/ids.hpp>
#include <gui/gui_directories.hpp>
#include <gui/guiprocessor.hpp>

BOOST_FIXTURE_TEST_SUITE( GuiConfiguration_Test, GuiConfiguration_Fixture )

	BOOST_AUTO_TEST_CASE (GuiConfiguration_Constructor)
{

	BOOST_CHECK_EQUAL(test_guiConfiguration->getResolutionSize(), test_resolutionSize);
	BOOST_CHECK_EQUAL(test_guiConfiguration->getBitDepth(), test_bitDepth);
	BOOST_CHECK_EQUAL(test_guiConfiguration->isFullScreen(), test_fullScreen);
	BOOST_CHECK_EQUAL(test_guiConfiguration->getDesiredFramerate(), test_desiredFramerate);
	BOOST_CHECK_EQUAL(test_guiConfiguration->getDesiredCPU(), test_desiredCPU);
	BOOST_CHECK_EQUAL(test_guiConfiguration->isUnloadGraphics(), test_unloadGraphics);
	BOOST_CHECK_EQUAL(test_guiConfiguration->isSmoothMovements(), test_smoothMovements);
	BOOST_CHECK_EQUAL(test_guiConfiguration->isTransparency(), test_transparency);
	BOOST_CHECK_EQUAL(test_guiConfiguration->isSoftwareMouse(), test_softwareMouse);
	BOOST_CHECK_EQUAL(test_guiConfiguration->isGlowingButtons(), test_glowingButtons);
	BOOST_CHECK_EQUAL(test_guiConfiguration->isToolTips(), test_toolTips);
}

BOOST_AUTO_TEST_CASE(GuiConfiguration_Storage)
{
	BOOST_CHECK_EQUAL(GuiConfigurationStorage::instance().get(test_guiConfiguration->getId())->getResolutionSize(), test_resolutionSize);
	BOOST_CHECK_EQUAL(GuiConfigurationStorage::instance().get(test_guiConfiguration->getId())->getBitDepth(), test_bitDepth);
	BOOST_CHECK_EQUAL(GuiConfigurationStorage::instance().get(test_guiConfiguration->getId())->isFullScreen(), test_fullScreen);
	BOOST_CHECK_EQUAL(GuiConfigurationStorage::instance().get(test_guiConfiguration->getId())->getDesiredFramerate(), test_desiredFramerate);
	BOOST_CHECK_EQUAL(GuiConfigurationStorage::instance().get(test_guiConfiguration->getId())->getDesiredCPU(), test_desiredCPU);
	BOOST_CHECK_EQUAL(GuiConfigurationStorage::instance().get(test_guiConfiguration->getId())->isUnloadGraphics(), test_unloadGraphics);
	BOOST_CHECK_EQUAL(GuiConfigurationStorage::instance().get(test_guiConfiguration->getId())->isSmoothMovements(), test_smoothMovements);
	BOOST_CHECK_EQUAL(GuiConfigurationStorage::instance().get(test_guiConfiguration->getId())->isTransparency(), test_transparency);
	BOOST_CHECK_EQUAL(GuiConfigurationStorage::instance().get(test_guiConfiguration->getId())->isSoftwareMouse(), test_softwareMouse);
	BOOST_CHECK_EQUAL(GuiConfigurationStorage::instance().get(test_guiConfiguration->getId())->isGlowingButtons(), test_glowingButtons);
	BOOST_CHECK_EQUAL(GuiConfigurationStorage::instance().get(test_guiConfiguration->getId())->isToolTips(), test_toolTips);

	GuiConfigurationStorage::saveToXML();
	GuiConfigurationStorage::reset();

	BOOST_CHECK_EQUAL(GuiConfigurationStorage::instance().get(test_guiConfiguration->getId())->getResolutionSize(), test_resolutionSize);
	BOOST_CHECK_EQUAL(GuiConfigurationStorage::instance().get(test_guiConfiguration->getId())->getBitDepth(), test_bitDepth);
	BOOST_CHECK_EQUAL(GuiConfigurationStorage::instance().get(test_guiConfiguration->getId())->isFullScreen(), test_fullScreen);
	BOOST_CHECK_EQUAL(GuiConfigurationStorage::instance().get(test_guiConfiguration->getId())->getDesiredFramerate(), test_desiredFramerate);
	BOOST_CHECK_EQUAL(GuiConfigurationStorage::instance().get(test_guiConfiguration->getId())->getDesiredCPU(), test_desiredCPU);
	BOOST_CHECK_EQUAL(GuiConfigurationStorage::instance().get(test_guiConfiguration->getId())->isUnloadGraphics(), test_unloadGraphics);
	BOOST_CHECK_EQUAL(GuiConfigurationStorage::instance().get(test_guiConfiguration->getId())->isSmoothMovements(), test_smoothMovements);
	BOOST_CHECK_EQUAL(GuiConfigurationStorage::instance().get(test_guiConfiguration->getId())->isTransparency(), test_transparency);
	BOOST_CHECK_EQUAL(GuiConfigurationStorage::instance().get(test_guiConfiguration->getId())->isSoftwareMouse(), test_softwareMouse);
	BOOST_CHECK_EQUAL(GuiConfigurationStorage::instance().get(test_guiConfiguration->getId())->isGlowingButtons(), test_glowingButtons);
	BOOST_CHECK_EQUAL(GuiConfigurationStorage::instance().get(test_guiConfiguration->getId())->isToolTips(), test_toolTips);
}

BOOST_AUTO_TEST_SUITE_END( )



	BOOST_FIXTURE_TEST_SUITE( Gui_Test, Gui_Fixture )

	BOOST_AUTO_TEST_CASE (Gui_constructor)
{
	GuiDirectories::init();
	BitmapStorage::reset();
	BitmapObject* object = new BitmapObject(NULL, Rect(), Size(), BitmapStorage::instance().get(IDS::BACKGROUND_SC_BITMAP));

	GuiProcessor t;

	t.process(test_dc);

	if(!IO::fileExists(test_screenshotFileName)) {
		test_dc->saveBMP(test_screenshotFileName);
	}
	SDL_Surface* surface = test_dc->loadBMP(test_screenshotFileName);
	BOOST_CHECK(BitmapStorage::instance().get(IDS::BACKGROUND_SC_BITMAP)->equals(surface));
	SDL_FreeSurface(surface);
	delete object;


}

BOOST_AUTO_TEST_SUITE_END( )

