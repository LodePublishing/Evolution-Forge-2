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
	BOOST_CHECK_EQUAL((*test_guiConfiguration->getBackgroundBitmap())->w, (*bitmapFixture.test_bitmap1)->w);
	BOOST_CHECK_EQUAL((*test_guiConfiguration->getBackgroundBitmap())->h, (*bitmapFixture.test_bitmap1)->h);
	BOOST_CHECK_EQUAL(test_guiConfiguration->getBackgroundBitmap()->getId(), bitmapFixture.test_bitmap1->getId());
	BOOST_CHECK_EQUAL(test_guiConfiguration->isSoftwareMouse(), test_softwareMouse);
	BOOST_CHECK_EQUAL(test_guiConfiguration->isGlowingButtons(), test_glowingButtons);
	BOOST_CHECK_EQUAL(test_guiConfiguration->isToolTips(), test_toolTips);
	BOOST_CHECK_EQUAL(test_guiConfiguration->isDnaSpiral(), test_dnaSpiral);
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
	BOOST_CHECK_EQUAL((*GuiConfigurationStorage::instance().get(test_guiConfiguration->getId())->getBackgroundBitmap())->w, (*bitmapFixture.test_bitmap1)->w);
	BOOST_CHECK_EQUAL((*GuiConfigurationStorage::instance().get(test_guiConfiguration->getId())->getBackgroundBitmap())->h, (*bitmapFixture.test_bitmap1)->h);
	BOOST_CHECK_EQUAL(GuiConfigurationStorage::instance().get(test_guiConfiguration->getId())->getBackgroundBitmap()->getId(), bitmapFixture.test_bitmap1->getId());
	BOOST_CHECK_EQUAL(GuiConfigurationStorage::instance().get(test_guiConfiguration->getId())->isSoftwareMouse(), test_softwareMouse);
	BOOST_CHECK_EQUAL(GuiConfigurationStorage::instance().get(test_guiConfiguration->getId())->isGlowingButtons(), test_glowingButtons);
	BOOST_CHECK_EQUAL(GuiConfigurationStorage::instance().get(test_guiConfiguration->getId())->isToolTips(), test_toolTips);
	BOOST_CHECK_EQUAL(GuiConfigurationStorage::instance().get(test_guiConfiguration->getId())->isDnaSpiral(), test_dnaSpiral);

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
	BOOST_CHECK_EQUAL((*GuiConfigurationStorage::instance().get(test_guiConfiguration->getId())->getBackgroundBitmap())->w, (*bitmapFixture.test_bitmap1)->w);
	BOOST_CHECK_EQUAL((*GuiConfigurationStorage::instance().get(test_guiConfiguration->getId())->getBackgroundBitmap())->h, (*bitmapFixture.test_bitmap1)->h);
	BOOST_CHECK_EQUAL(GuiConfigurationStorage::instance().get(test_guiConfiguration->getId())->getBackgroundBitmap()->getId(), bitmapFixture.test_bitmap1->getId());
	BOOST_CHECK_EQUAL(GuiConfigurationStorage::instance().get(test_guiConfiguration->getId())->isSoftwareMouse(), test_softwareMouse);
	BOOST_CHECK_EQUAL(GuiConfigurationStorage::instance().get(test_guiConfiguration->getId())->isGlowingButtons(), test_glowingButtons);
	BOOST_CHECK_EQUAL(GuiConfigurationStorage::instance().get(test_guiConfiguration->getId())->isToolTips(), test_toolTips);
	BOOST_CHECK_EQUAL(GuiConfigurationStorage::instance().get(test_guiConfiguration->getId())->isDnaSpiral(), test_dnaSpiral);
}

BOOST_AUTO_TEST_SUITE_END( )



	BOOST_FIXTURE_TEST_SUITE( Gui_Test, Gui_Fixture )

	BOOST_AUTO_TEST_CASE (Gui_constructor)
{

	BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END( )

