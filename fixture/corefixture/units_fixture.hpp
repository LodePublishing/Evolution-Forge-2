#ifndef _CORE_FIXTURE_UNITSFIXTURE_HPP
#define _CORE_FIXTURE_UNITSFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)
#include <map>
#include <core/units.hpp>

#include <games/broodwar.hpp>

#include "player_fixture.hpp"
#include "location_fixture.hpp"


struct Units_Fixture
{	
	Player_Fixture playerFixture;
	Location_Fixture locationFixture;
	BroodWar broodwar;

	const unsigned int test_construction_time;
	const boost::shared_ptr<Units> test_units;

	const boost::shared_ptr<Unit> test_unit1;
	const boost::shared_ptr<Unit> test_unit2;
	const boost::shared_ptr<Unit> test_unit3;

	Units_Fixture();
	virtual ~Units_Fixture();

	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Units> > test_unitsMap;

private:
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Units> > init_unitsmap_helper();
};


#endif // _CORE_FIXTURE_UNITSFIXTURE_HPP
