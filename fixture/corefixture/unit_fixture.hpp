#ifndef _COREFIXTURE_UNITFIXTURE_HPP
#define _COREFIXTURE_UNITFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <random_fixture.hpp>

#include "map_fixture.hpp"
#include "player_fixture.hpp"
#include "unittype_fixture.hpp"

class Units;

struct Unit_Fixture : public Random_Fixture
{
	Unit_Fixture();
	~Unit_Fixture();

	const UnitType_Fixture unitTypeFixture;
	const Player_Fixture playerFixture;
	const Map_Fixture mapFixture;

	unsigned int test_construction_time;

	const boost::shared_ptr<Units> test_units;
	const boost::shared_ptr<const UnitType> unitType1;
	const boost::shared_ptr<const UnitType> unitType2;

	// TODO evtl unitTypes in unitTypeFixture definieren
};

#endif // _COREFIXTURE_UNITFIXTURE_HPP
