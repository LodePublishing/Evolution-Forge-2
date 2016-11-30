#pragma warning(push, 0)  
#include <boost/assign/list_of.hpp>
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include "units_fixture.hpp"

Units_Fixture::Units_Fixture():	
	Random_Fixture(),
	unitTypeFixture(), 
	unitFixture(),
	playerFixture(), 
	mapFixture(),

	test_construction_time(rnd()), // TODO UnitType

	test_units(boost::shared_ptr<Units>(new Units())),
	test_unit1(boost::shared_ptr<Unit>(new Unit(playerFixture.test_player, unitFixture.unitType1, mapFixture.test_map->getLocation(0), test_units))),
	test_unit2(boost::shared_ptr<Unit>(new Unit(playerFixture.test_player, unitFixture.unitType1, mapFixture.test_map->getLocation(0), test_units))),
	test_unit3(boost::shared_ptr<Unit>(new Unit(playerFixture.test_player, unitFixture.unitType2, mapFixture.test_map->getLocation(0), test_units)))
{
	test_units->addUnit(test_unit1);
	test_units->addUnit(test_unit2);
	test_units->addUnit(test_unit3);
}

Units_Fixture::~Units_Fixture() 
{
	Unit::resetCounter();
}