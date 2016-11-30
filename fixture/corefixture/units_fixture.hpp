#ifndef _COREFIXTURE_UNITSFIXTURE_HPP
#define _COREFIXTURE_UNITSFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <units.hpp>

#include <broodwar.hpp>

#include "player_fixture.hpp"
#include "location_fixture.hpp"


struct Units_Fixture
{	
	Player_Fixture playerFixture;
	Location_Fixture locationFixture;
	Broodwar broodwar;

	const unsigned int test_construction_time;
	const boost::shared_ptr<Units> test_units;

	const boost::shared_ptr<Unit> test_unit1;
	const boost::shared_ptr<Unit> test_unit2;
	const boost::shared_ptr<Unit> test_unit3;

	Units_Fixture();
	virtual ~Units_Fixture();
};


#endif // _COREFIXTURE_UNITSFIXTURE_HPP
