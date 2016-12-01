#include <misc/randomgenerator.hpp>

#include "race_fixture.hpp"
#include <core/race_storage.hpp>
#include <core/core_directories.hpp>

Race_Fixture::Race_Fixture():
	test_race_name("my_race_Name" + RandomGenerator::instance().rndString()),
	test_race(new Race(test_race_name)),
	test_raceMap(init_racemap_helper())
{ 
	CoreDirectories::initTemp("temp");

	RaceStorage::instance(test_raceMap);	
}

Race_Fixture::~Race_Fixture() 
{ 
	CoreDirectories::initTemp("temp");

	RaceStorage::clear();

	CoreDirectories::init();
}


const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Race> > Race_Fixture::init_racemap_helper() {
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const Race> > raceMap;
	raceMap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const Race> >(test_race->getId(), test_race));
	return raceMap;
}
