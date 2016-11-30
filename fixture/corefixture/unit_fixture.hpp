#ifndef _CORETEST_UNITFIXTURE_HPP
#define _CORETEST_UNITFIXTURE_HPP

#include "map_fixture.hpp"
#include "player_fixture.hpp"
#include "unittype_fixture.hpp"

struct Unit_Fixture
{
	Unit_Fixture();
	~Unit_Fixture();

	unsigned int test_construction_time;
	const UnitType_Fixture unitTypeFixture;
	const Player_Fixture playerFixture;
	const Map_Fixture mapFixture;

	GoalEntry* test_goalEntry;
	Player* test_player;
	Race* test_race;

	UnitType* unitType1;
	UnitType* unitType2;

	time_t seed;
};

#endif // _CORETEST_UNITFIXTURE_HPP
