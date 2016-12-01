#ifndef _CORE_FIXTURE_RACEFIXTURE_HPP
#define _CORE_FIXTURE_RACEFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <core/race.hpp>

#include <map>

struct Race_Fixture
{
	const std::string test_race_name;
	const boost::shared_ptr<const Race> test_race;

	Race_Fixture();
	virtual ~Race_Fixture();


	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Race> > test_raceMap;

private:
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Race> > init_racemap_helper();
};


#endif // _CORE_FIXTURE_RACEFIXTURE_HPP