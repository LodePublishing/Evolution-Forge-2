#ifndef WIN32
#define BOOST_TEST_NO_MAIN
#define BOOST_TEST_DYN_LINK
#else
#undef main
#endif

#define BOOST_TEST_MAIN

#pragma warning(push, 0) 
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <sdlwrapfixture/dc_fixture.hpp>
#include "SDL.h"
#include <iostream>

BOOST_FIXTURE_TEST_SUITE( dc_test, DC_Fixture )

	BOOST_AUTO_TEST_CASE (dc_constructor)
    {
		BOOST_REQUIRE(DC::instance().valid());
		BOOST_CHECK_EQUAL(DC::instance().getBitDepth(), depth);
		BOOST_CHECK_EQUAL(DC::instance().getBits(), (depth+1)*8);
		BOOST_CHECK_EQUAL(DC::instance().getSize().getWidth(), 640);
		BOOST_CHECK_EQUAL(DC::instance().getSize().getHeight(), 480);
		BOOST_CHECK_EQUAL(DC::instance().w(), 640);
		BOOST_CHECK_EQUAL(DC::instance().h(), 480);
		BOOST_CHECK_EQUAL(DC::instance().getMaxX(), 640);
		BOOST_CHECK_EQUAL(DC::instance().getMaxY(), 480);
		BOOST_CHECK_EQUAL(DC::instance().isFullScreen(), false);
    }

#ifdef WIN32
	BOOST_AUTO_TEST_CASE (dc_fullscreen)
    {
		BOOST_REQUIRE(DC::instance().valid());
		DC::instance().setFullScreen(true);
		SDL_Delay(1000);
		//BOOST_CHECK_EQUAL(DC::instance().isFullScreen(), true);

		DC::instance().setFullScreen(false);
		BOOST_CHECK_EQUAL(DC::instance().isFullScreen(), false);

		DC::instance().setFullScreen(true);
		BOOST_CHECK_EQUAL(DC::instance().isFullScreen(), true);
    }
#endif

	BOOST_AUTO_TEST_CASE (dc_bitdepth)
    {
		BOOST_REQUIRE(DC::instance().valid());
		BOOST_CHECK_EQUAL(DC::instance().getBitDepth(), depth);
		DC::instance().setBitDepth(DEPTH_16BIT);
		BOOST_CHECK_EQUAL(DC::instance().getBitDepth(), DEPTH_16BIT);
		DC::instance().setBitDepth(DEPTH_24BIT);
		BOOST_CHECK_EQUAL(DC::instance().getBitDepth(), DEPTH_24BIT);
		DC::instance().setBitDepth(DEPTH_32BIT);
		BOOST_CHECK_EQUAL(DC::instance().getBitDepth(), DEPTH_32BIT);
    }

	BOOST_AUTO_TEST_CASE (dc_size)
    {
		BOOST_REQUIRE(DC::instance().valid());
		BOOST_CHECK_EQUAL(DC::instance().w(), 640);
		BOOST_CHECK_EQUAL(DC::instance().h(), 480);
		DC::instance().setResolution(Size(800,600));
		BOOST_CHECK_EQUAL(DC::instance().w(), 800);
		BOOST_CHECK_EQUAL(DC::instance().h(), 600);
		DC::instance().setResolution(Size(1024,768));
		BOOST_CHECK_EQUAL(DC::instance().w(), 1024);
		BOOST_CHECK_EQUAL(DC::instance().h(), 768);
		DC::instance().setResolution(Size(1280,1024));
		BOOST_CHECK_EQUAL(DC::instance().w(), 1280);
		BOOST_CHECK_EQUAL(DC::instance().h(), 1024);
		DC::instance().setResolution(Size(1920,1080));
		BOOST_CHECK_EQUAL(DC::instance().w(), 1920);
		BOOST_CHECK_EQUAL(DC::instance().h(), 1080);
    }


BOOST_AUTO_TEST_SUITE_END()

// required because of SDL
int main( int argc, char* argv[] )
{
#ifdef WIN32
	return ::boost::unit_test::unit_test_main(&init_unit_test_suite, argc, argv); 
#else
	return ::boost::unit_test::unit_test_main(&init_unit_test, argc, argv); 
#endif
}
