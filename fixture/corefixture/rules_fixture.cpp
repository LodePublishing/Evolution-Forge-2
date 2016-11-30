#pragma warning(push, 0)
#include <boost/assign/list_of.hpp>
#pragma warning(pop)

#include <random_fixture.hpp>
#include <globalstorage.hpp>

#include "rules_fixture.hpp"


Rules_Fixture::Rules_Fixture():
	raceFixture(),
	unitTypeFixture(),

	test_filename_xml("test_rules.xml"), 
	test_file_name("test_rules"),
	test_rules_name("my_rules_Name"),
	test_unittype_list(init_unittypelist_helper()),

	test_rules(boost::shared_ptr<const Rules>(new Rules(test_rules_name, boost::assign::list_of(raceFixture.test_race), test_unittype_list)))
{ 
	GlobalStorage::instance().addRules(test_rules);
}

Rules_Fixture::~Rules_Fixture() 
{ 
	GlobalStorage::instance().removeRules(test_rules->getId());
}


const std::list<boost::shared_ptr<const UnitType> > Rules_Fixture::init_unittypelist_helper()
{
	const std::list<boost::shared_ptr<const UnitType> > unitTypeList = boost::assign::list_of(unitTypeFixture.test_unittype)(unitTypeFixture.test_unittype_noncorporeal);
	return unitTypeList;		
}