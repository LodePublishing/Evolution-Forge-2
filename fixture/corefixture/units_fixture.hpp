#ifndef _CORETEST_UNITSFIXTURE_HPP
#define _CORETEST_UNITSFIXTURE_HPP

#include "map_fixture.hpp"
#include "player_fixture.hpp"
#include "unittype_fixture.hpp"
#include "unit_fixture.hpp"

struct Units_Fixture
{		
	Units_Fixture();
	~Units_Fixture();

	unsigned int test_construction_time;
	const UnitType_Fixture unitTypeFixture;
	const Unit_Fixture unitFixture;
	const Player_Fixture playerFixture;
	const Map_Fixture mapFixture;

	GoalEntry* test_goalEntry;
	Player* test_player;

	Unit* test_unit1;
	Unit* test_unit2;
	Unit* test_unit3;

	time_t seed;
};


#endif // _CORETEST_UNITSFIXTURE_HPP
