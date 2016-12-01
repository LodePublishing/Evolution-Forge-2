#ifndef WIN32
#define BOOST_TEST_DYN_LINK
#endif
#define BOOST_TEST_MODULE MAIN
#pragma warning(push, 0) 
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <mainfixture/mainconfiguration_fixture.hpp>
#include <main/mainconfiguration_storage.hpp>
#include <guicore/bitmap_storage.hpp>
#include <misc/ids.hpp>
#include <main/main_directories.hpp>

BOOST_FIXTURE_TEST_SUITE( MainConfiguration_Test, MainConfiguration_Fixture )

	BOOST_AUTO_TEST_CASE (MainConfiguration_Constructor)
{
	BOOST_CHECK_EQUAL(test_mainConfiguration->getLanguageId(), IDS::ENGLISH_LANGUAGE_ID);
	BOOST_CHECK_EQUAL((*test_mainConfiguration->getBackgroundBitmap())->w, (*bitmapFixture.test_bitmap1)->w);
	BOOST_CHECK_EQUAL((*test_mainConfiguration->getBackgroundBitmap())->h, (*bitmapFixture.test_bitmap1)->h);
	BOOST_CHECK_EQUAL(test_mainConfiguration->getBackgroundBitmap()->getId(), bitmapFixture.test_bitmap1->getId());
	BOOST_CHECK_EQUAL(test_mainConfiguration->isDnaSpiral(), test_dnaSpiral);
}

BOOST_AUTO_TEST_CASE(MainConfiguration_Storage)
{
	BOOST_CHECK_EQUAL(MainConfigurationStorage::instance().get(test_mainConfiguration->getId())->getLanguageId(), IDS::ENGLISH_LANGUAGE_ID);
	BOOST_CHECK_EQUAL((*MainConfigurationStorage::instance().get(test_mainConfiguration->getId())->getBackgroundBitmap())->w, (*bitmapFixture.test_bitmap1)->w);
	BOOST_CHECK_EQUAL((*MainConfigurationStorage::instance().get(test_mainConfiguration->getId())->getBackgroundBitmap())->h, (*bitmapFixture.test_bitmap1)->h);
	BOOST_CHECK_EQUAL(MainConfigurationStorage::instance().get(test_mainConfiguration->getId())->getBackgroundBitmap()->getId(), bitmapFixture.test_bitmap1->getId());
	BOOST_CHECK_EQUAL(MainConfigurationStorage::instance().get(test_mainConfiguration->getId())->isDnaSpiral(), test_dnaSpiral);

	MainConfigurationStorage::saveToXML();
	MainConfigurationStorage::reset();

	BOOST_CHECK_EQUAL(MainConfigurationStorage::instance().get(test_mainConfiguration->getId())->getLanguageId(), IDS::ENGLISH_LANGUAGE_ID);
	BOOST_CHECK_EQUAL((*MainConfigurationStorage::instance().get(test_mainConfiguration->getId())->getBackgroundBitmap())->w, (*bitmapFixture.test_bitmap1)->w);
	BOOST_CHECK_EQUAL((*MainConfigurationStorage::instance().get(test_mainConfiguration->getId())->getBackgroundBitmap())->h, (*bitmapFixture.test_bitmap1)->h);
	BOOST_CHECK_EQUAL(MainConfigurationStorage::instance().get(test_mainConfiguration->getId())->getBackgroundBitmap()->getId(), bitmapFixture.test_bitmap1->getId());
	BOOST_CHECK_EQUAL(MainConfigurationStorage::instance().get(test_mainConfiguration->getId())->isDnaSpiral(), test_dnaSpiral);
}

BOOST_AUTO_TEST_SUITE_END( )



