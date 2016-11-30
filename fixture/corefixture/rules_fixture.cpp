#pragma warning(push, 0)  
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#include <boost/assign/list_of.hpp>
#pragma warning(pop)

#include <globalstorage.hpp>

#include "rules_fixture.hpp"

Rules_Fixture::Rules_Fixture():
	Random_Fixture(),
	test_filename_xml("test_rules.xml"), 
	test_file_name("test_rules"),
	test_rules_name("my_rules_Name"), 
	unitTypeFixture(),
	unitType1(boost::shared_ptr<const UnitType>(new UnitType(unitTypeFixture.test_unitName1, unitTypeFixture.raceFixture.test_race, unitTypeFixture.test_buildtime, unitTypeFixture.test_maxcount, false, NO_MOVEMENT_TYPE, 0, unitTypeFixture.test_resources))),
	unitType2(boost::shared_ptr<const UnitType>(new UnitType(unitTypeFixture.test_unitName2, unitTypeFixture.raceFixture.test_race, unitTypeFixture.test_buildtime, unitTypeFixture.test_maxcount, false, NO_MOVEMENT_TYPE, 0, unitTypeFixture.test_resources))),
	test_rules(boost::shared_ptr<const Rules>(new Rules(test_rules_name, init_unittypelist_helper())))
{
	GLOBAL_STORAGE.addRules(test_rules);
}

Rules_Fixture::~Rules_Fixture() 
{
	Rules::resetCounter();
	UnitType::resetCounter();
}


const std::list<boost::shared_ptr<const UnitType> > Rules_Fixture::init_unittypelist_helper()
{
	const std::list<boost::shared_ptr<const UnitType> > unitTypeList = boost::assign::list_of(unitType1)(unitType2);
	return unitTypeList;		
}