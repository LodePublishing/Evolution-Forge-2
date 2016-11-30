#ifndef _COREFIXTURE_UNITSFIXTURE_HPP
#define _COREFIXTURE_UNITSFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <random_fixture.hpp>

#include "map_fixture.hpp"
#include "player_fixture.hpp"
#include "unittype_fixture.hpp"
#include "unit_fixture.hpp"

struct Units_Fixture : public Random_Fixture
{		
	Units_Fixture();
	~Units_Fixture();

	const UnitType_Fixture unitTypeFixture;
	const Unit_Fixture unitFixture;
	const Player_Fixture playerFixture;
	const Map_Fixture mapFixture;

	const unsigned int test_construction_time;
	const boost::shared_ptr<Units> test_units;

	const boost::shared_ptr<Unit> test_unit1;
	const boost::shared_ptr<Unit> test_unit2;
	const boost::shared_ptr<Unit> test_unit3;
};


#endif // _COREFIXTURE_UNITSFIXTURE_HPP
