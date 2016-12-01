#include <misc/randomgenerator.hpp>

#include "zrect_fixture.hpp"

ZRect_Fixture::ZRect_Fixture() :
	test_rect(RandomGenerator::instance().rnd(), RandomGenerator::instance().rnd(), RandomGenerator::instance().rnd(), RandomGenerator::instance().rnd()),
	test_z(RandomGenerator::instance().rnd()),
	test_zrect(new ZRect(test_rect, test_z))
{ }

ZRect_Fixture::~ZRect_Fixture() 
{ }