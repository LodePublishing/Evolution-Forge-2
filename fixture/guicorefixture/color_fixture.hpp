#ifndef _GUICORE_FIXTURE_COLORFIXTURE_HPP
#define _GUICORE_FIXTURE_COLORFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/shared_ptr.hpp>
#pragma warning(pop)

#include <guicore/color.hpp>
#include <map>
#include <sdlwrapfixture/dc_fixture.hpp>

struct Color_Fixture
{
	DC_Fixture dcFixture;
	
	SDL_Color test_sdlcolor;
	// TODO test others, init function etc.
	boost::shared_ptr<const Color> test_color;

	Color_Fixture();	
	~Color_Fixture();

private:
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Color> > test_colorMap;
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Color> > init_colormap_helper();
};

#endif // _GUICORE_FIXTURE_COLORFIXTURE_HPP
