#pragma warning(push, 0)  
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#include <boost/assign/list_of.hpp>
#pragma warning(pop)

#include <globalstorage.hpp>

#include "rules_fixture.hpp"
#include "unittype_fixture.hpp"
#include "race_fixture.hpp"
#include <random_fixture.hpp>

Rules_Fixture::Rules_Fixture():
	test_filename_xml("test_rules.xml"), 
	test_file_name("test_rules"),
	test_rules_name("my_rules_Name"),
	unitType1(boost::shared_ptr<const UnitType>(new UnitType(UnitType_Fixture::instance().test_unitName1.test_race.test_buildtime.test_maxcount, false, NO_MOVEMENT_TYPE, 0.test_resources))),
	unitType2(boost::shared_ptr<const UnitType>(new UnitType(UnitType_Fixture::instance().test_unitName2.test_race.test_buildtime.test_maxcount, false, NO_MOVEMENT_TYPE, 0.test_resources))),
	test_rules(boost::shared_ptr<const Rules>(new Rules(test_rules_name, init_unittypelist_helper())))
{
	GLOBAL_STORAGE.addRules(test_rules);
}

Rules_Fixture::~Rules_Fixture() 
{ }


const std::list<boost::shared_ptr<const UnitType> > Rules_Fixture::init_unittypelist_helper()
{
	const std::list<boost::shared_ptr<const UnitType> > unitTypeList = boost::assign::list_of(unitType1)(unitType2);
	return unitTypeList;		
}