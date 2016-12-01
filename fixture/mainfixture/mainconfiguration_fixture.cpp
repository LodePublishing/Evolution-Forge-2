#include <misc/randomgenerator.hpp>
#include <main/main_directories.hpp>

#include "mainconfiguration_fixture.hpp"
#include <main/mainconfiguration_storage.hpp>
#include <misc/ids.hpp>

MainConfiguration_Fixture::MainConfiguration_Fixture():
	guiFixture(),
	bitmapFixture(),
    test_dnaSpiral(RandomGenerator::instance().rndBool()),
	test_mainConfiguration(new MainConfiguration(IDS::ENGLISH_LANGUAGE_ID, guiFixture.test_gui->getId(), bitmapFixture.test_bitmap1, test_dnaSpiral)),
	test_mainConfigurationMap(init_mainconfigurationmap_helper())
{
	MainDirectories::initTemp("temp");
	MainConfigurationStorage::instance(test_mainConfigurationMap);
}

MainConfiguration_Fixture::~MainConfiguration_Fixture() 
{ 
	MainDirectories::initTemp("temp");

	MainConfigurationStorage::clear();

	MainDirectories::init();
}


const std::map<const boost::uuids::uuid, const boost::shared_ptr<const MainConfiguration> > MainConfiguration_Fixture::init_mainconfigurationmap_helper() const {
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const MainConfiguration> > mainconfigurationmap;
	mainconfigurationmap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const MainConfiguration> >(test_mainConfiguration->getId(), test_mainConfiguration));
	return mainconfigurationmap;
}