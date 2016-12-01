#pragma warning(push, 0)  
#include <boost/assign/list_of.hpp>
#pragma warning(pop)

#include <misc/randomgenerator.hpp>

#include "unit_fixture.hpp"
#include <games/enums/broodwarunits.hpp>
#include <core/units.hpp>

Unit_Fixture::Unit_Fixture():
	playerFixture(),
	mapFixture(),
	broodwar(),

	test_constructionTime(RandomGenerator::instance().rnd()),
	test_unitType(broodwar.getRules()->getUnitType(broodwar.unit_id_map[SCV])),
	test_units(new Units()),
	test_unit(new Unit(playerFixture.test_player, test_unitType, mapFixture.test_map->getLocationByIndex(0), test_units))
{ 
	test_units->addUnit(test_unit);
}


Unit_Fixture::~Unit_Fixture() 
{ }