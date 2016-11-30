#pragma warning(push, 0)  
#include <boost/assign/list_of.hpp>
#pragma warning(pop)

#include <random_fixture.hpp>

#include "units_fixture.hpp"


Units_Fixture::Units_Fixture():
	playerFixture(),
	locationFixture(),
	broodwar(),

	test_construction_time(Random_Fixture::instance().rnd()), // TODO UnitType

	test_units(boost::shared_ptr<Units>(new Units())),

	test_unit1(boost::shared_ptr<Unit>(new Unit(playerFixture.test_player, broodwar.getRules()->getUnitType(broodwar.unit_id_map.find(Broodwar::SCV)->second), locationFixture.test_location, test_units))), // scv
	test_unit2(boost::shared_ptr<Unit>(new Unit(playerFixture.test_player, broodwar.getRules()->getUnitType(broodwar.unit_id_map.find(Broodwar::SCV)->second), locationFixture.test_location, test_units))), // scv
	test_unit3(boost::shared_ptr<Unit>(new Unit(playerFixture.test_player, broodwar.getRules()->getUnitType(broodwar.unit_id_map.find(Broodwar::COMMAND_CENTER)->second), locationFixture.test_location, test_units))) // cc
{
	test_units->addUnit(test_unit1);
	test_units->addUnit(test_unit2);
	test_units->addUnit(test_unit3);
}

Units_Fixture::~Units_Fixture() 
{ }