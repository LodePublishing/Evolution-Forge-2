#pragma warning(push, 0)  
#include <boost/assign/list_of.hpp>
#pragma warning(pop)

#include <random_fixture.hpp>

#include "unit_fixture.hpp"


Unit_Fixture::Unit_Fixture():
	playerFixture(),
	mapFixture(),
	broodwar(),

	test_construction_time(Random_Fixture::instance().rnd()), // TODO UnitResourceType ?

	test_units(boost::shared_ptr<Units>(new Units()))
{ }

Unit_Fixture::~Unit_Fixture() 
{ }