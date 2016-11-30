#pragma warning(push, 0)  
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include <globalstorage.hpp>	

#include "race_fixture.hpp"
#include <random_fixture.hpp>

Race_Fixture::Race_Fixture():
	test_race_name("my_race_Name"),
	test_race(boost::shared_ptr<Race>(new Race(test_race_name)))
{ }

Race_Fixture::~Race_Fixture() 
{ }