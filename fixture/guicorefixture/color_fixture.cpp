#include <misc/randomgenerator.hpp>

#include "color_fixture.hpp"
#include <guicore/color_storage.hpp>
#include <guicore/guicore_directories.hpp>

Color_Fixture::Color_Fixture() :
	dcFixture(),
	test_sdlcolor(Color::toSDL_Color(static_cast<Uint8>(RandomGenerator::instance().rnd()), static_cast<Uint8>(RandomGenerator::instance().rnd()), static_cast<Uint8>(RandomGenerator::instance().rnd()), static_cast<Uint8>(RandomGenerator::instance().rnd()))),
	test_color(new Color(DC::instance().getSurface(), test_sdlcolor)),
	test_colorMap(init_colormap_helper())
{ 
	GuiCoreDirectories::initTemp("temp");	

	ColorStorage::instance(test_colorMap);
}

Color_Fixture::~Color_Fixture() 
{ 
	GuiCoreDirectories::initTemp("temp");

	ColorStorage::clear();
	
	GuiCoreDirectories::init();
}


const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Color> > Color_Fixture::init_colormap_helper() {
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const Color> > colorMap;
	colorMap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const Color> >(test_color->getId(), test_color));
	return colorMap;
}