#pragma warning(push, 0)  
#include <boost/assign/list_of.hpp>
#pragma warning(pop)

#include <misc/randomgenerator.hpp>

#include "units_fixture.hpp"
#include <games/enums/broodwarunits.hpp>
#include <core/units_storage.hpp>
#include <core/core_directories.hpp>

Units_Fixture::Units_Fixture():
	playerFixture(),
	locationFixture(),
	broodwar(),

	test_construction_time(RandomGenerator::instance().rnd()), // TODO UnitType

	test_units(new Units()),

	test_unit1(new Unit(playerFixture.test_player, broodwar.getRules()->getUnitType(broodwar.unit_id_map[SCV]), locationFixture.test_location, test_units)), // scv
	test_unit2(new Unit(playerFixture.test_player, broodwar.getRules()->getUnitType(broodwar.unit_id_map[SCV]), locationFixture.test_location, test_units)), // scv
	test_unit3(new Unit(playerFixture.test_player, broodwar.getRules()->getUnitType(broodwar.unit_id_map[COMMAND_CENTER]), locationFixture.test_location, test_units)), // cc

	test_unitsMap(init_unitsmap_helper())
{
	CoreDirectories::initTemp("temp");

	test_units->addUnit(test_unit1);
	test_units->addUnit(test_unit2);
	test_units->addUnit(test_unit3);

	UnitsStorage::instance(test_unitsMap);
}

Units_Fixture::~Units_Fixture() 
{ 
	CoreDirectories::initTemp("temp");

	UnitsStorage::clear();

	CoreDirectories::init();
}


const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Units> > Units_Fixture::init_unitsmap_helper() {
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const Units> > unitsMap;
	unitsMap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const Units> >(test_units->getId(), test_units));
	return unitsMap;
}