#ifndef _MAIN_FIXTURE_MAINCONFIGURATIONFIXTURE_HPP
#define _MAIN_FIXTURE_MAINCONFIGURATIONFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <main/mainconfiguration.hpp>
#include <guicorefixture/bitmap_fixture.hpp>
#include <guifixture/gui_fixture.hpp>

struct MainConfiguration_Fixture
{
	const Gui_Fixture guiFixture;
	const Bitmap_Fixture bitmapFixture;
	
	const bool test_firstStart;
    const bool test_dnaSpiral;

	const boost::shared_ptr<const MainConfiguration> test_mainConfiguration;

	MainConfiguration_Fixture();	
	~MainConfiguration_Fixture();

private:
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const MainConfiguration> > test_mainConfigurationMap;
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const MainConfiguration> > init_mainconfigurationmap_helper() const;
};

#endif // _MAIN_FIXTURE_MAINCONFIGURATIONFIXTURE_HPP
