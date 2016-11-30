#ifndef _COREFIXTURE_UNITFIXTURE_HPP
#define _COREFIXTURE_UNITFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <unit.hpp>

#include <broodwar.hpp>

#include "player_fixture.hpp"
#include "map_fixture.hpp"


struct Unit_Fixture
{
	Player_Fixture playerFixture;
	Map_Fixture mapFixture;
	Broodwar broodwar;

	const unsigned int test_construction_time;

	const boost::shared_ptr<Units> test_units;

	Unit_Fixture();
	virtual ~Unit_Fixture();
};

#endif // _COREFIXTURE_UNITFIXTURE_HPP
