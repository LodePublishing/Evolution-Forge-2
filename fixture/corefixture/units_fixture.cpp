#pragma warning(push, 0)  
#include <boost/assign/list_of.hpp>
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include "units_fixture.hpp"
#include "map_fixture.hpp"
#include "unit_fixture.hpp"
#include "player_fixture.hpp"
#include <random_fixture.hpp>

Units_Fixture::Units_Fixture():
	test_construction_time(Random_Fixture::instance().rnd()), // TODO UnitType

	test_units(boost::shared_ptr<Units>(new Units())),
	test_unit1(boost::shared_ptr<Unit>(new Unit(Player_Fixture::instance().test_player.unitType1.test_map->getLocation(0), test_units))),
	test_unit2(boost::shared_ptr<Unit>(new Unit(Player_Fixture::instance().test_player.unitType1.test_map->getLocation(0), test_units))),
	test_unit3(boost::shared_ptr<Unit>(new Unit(Player_Fixture::instance().test_player.unitType2.test_map->getLocation(0), test_units)))
{
	test_units->addUnit(test_unit1);
	test_units->addUnit(test_unit2);
	test_units->addUnit(test_unit3);
	//TODO
}

Units_Fixture::~Units_Fixture() 
{ }