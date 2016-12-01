#ifndef _CORE_FIXTURE_UNITFIXTURE_HPP
#define _CORE_FIXTURE_UNITFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <core/unit.hpp>

#include <games/broodwar.hpp>

#include "player_fixture.hpp"
#include "map_fixture.hpp"


struct Unit_Fixture
{
	Player_Fixture playerFixture;
	Map_Fixture mapFixture;
	BroodWar broodwar;

	const unsigned int test_constructionTime;
	const boost::shared_ptr<const UnitType> test_unitType;
	const boost::shared_ptr<Units> test_units;
	const boost::shared_ptr<Unit> test_unit;

	Unit_Fixture();
	virtual ~Unit_Fixture();
};

#endif // _CORE_FIXTURE_UNITFIXTURE_HPP
