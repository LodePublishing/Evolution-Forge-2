#include <random_fixture.hpp>
#include <globalstorage.hpp>

#include "race_fixture.hpp"


Race_Fixture::Race_Fixture():
	test_race_name("my_race_Name"),
	test_race(boost::shared_ptr<Race>(new Race(test_race_name)))
{ 
	GlobalStorage::instance().addRace(test_race);	
}

Race_Fixture::~Race_Fixture() 
{ 
	GlobalStorage::instance().removeRace(test_race->getId());
}