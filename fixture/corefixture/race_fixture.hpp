#ifndef _CORETEST_RACEFIXTURE_HPP
#define _CORETEST_RACEFIXTURE_HPP

#include <race.hpp>

struct Race_Fixture
{
	Race_Fixture();
	~Race_Fixture();
	
	const std::string test_race_name;

	Race* test_race;

	time_t seed;
};


#endif // _CORETEST_RACEFIXTURE_HPP