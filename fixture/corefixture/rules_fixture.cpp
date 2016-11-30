#include <iostream>
#include <time.h>

#pragma warning(push, 0)  
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include "rules_fixture.hpp"

Rules_Fixture::Rules_Fixture():
	test_filename_xml("test_rules.xml"), 
	test_file_name("test_rules"),
	test_rules_name("my_rules_Name"), 
	unitTypeFixture(),
	seed(time(0))
{
	boost::mt19937 generator(static_cast<boost::uint32_t>(seed));
	boost::uniform_int<> distribution(1, 100);
	boost::variate_generator<boost::mt19937&, boost::uniform_int<> > rnd(generator,  distribution); 
	std::cout << "Setting up rules fixture (seed " << seed << ")" << std::endl;

	unitType1 = new UnitType(unitTypeFixture.test_unitName1, unitTypeFixture.raceFixture.test_race, unitTypeFixture.test_buildtime, unitTypeFixture.test_maxcount, false, NO_MOVEMENT_TYPE, 0, unitTypeFixture.test_resources);
	unitType2 = new UnitType(unitTypeFixture.test_unitName2, unitTypeFixture.raceFixture.test_race, unitTypeFixture.test_buildtime, unitTypeFixture.test_maxcount, false, NO_MOVEMENT_TYPE, 0, unitTypeFixture.test_resources);

	test_rules = new Rules(test_rules_name);

	test_rules->addUnitType(*unitType1);
	test_rules->addUnitType(*unitType2);
	test_rules->addRace(*unitTypeFixture.raceFixture.test_race);
}

Rules_Fixture::~Rules_Fixture() 
{
	delete unitType1;
	delete unitType2;

	delete test_rules;

	Race::resetCounter();
	Rules::resetCounter();
	UnitType::resetCounter();
}