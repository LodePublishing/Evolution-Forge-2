#pragma warning(push, 0)
#include <boost/assign/list_of.hpp>
#pragma warning(pop)

#include <misc/randomgenerator.hpp>

#include "rules_fixture.hpp"
#include <core/rules_storage.hpp>
#include <core/core_directories.hpp>

Rules_Fixture::Rules_Fixture():
	unitTypeFixture(),

	test_rules_name("my_rules_Name" + RandomGenerator::instance().rndString()),
	test_unittype_list(init_unittypelist_helper()),

	test_rules(new Rules(test_rules_name, boost::assign::list_of(unitTypeFixture.raceFixture.test_race), test_unittype_list)),
	test_rulesMap(init_rulesmap_helper())
{ 
	CoreDirectories::initTemp("temp");

	RulesStorage::instance(test_rulesMap);	
}

Rules_Fixture::~Rules_Fixture() 
{ 
	CoreDirectories::initTemp("temp");

	RulesStorage::clear();

	CoreDirectories::init();
}

const std::list<boost::shared_ptr<const UnitType> > Rules_Fixture::init_unittypelist_helper()
{
	const std::list<boost::shared_ptr<const UnitType> > unitTypeList = boost::assign::list_of(unitTypeFixture.test_unittype)(unitTypeFixture.test_unittype_noncorporeal);
	return unitTypeList;		
}


const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Rules> > Rules_Fixture::init_rulesmap_helper() {
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const Rules> > rulesMap;
	rulesMap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const Rules> >(test_rules->getId(), test_rules));
	return rulesMap;
}