#ifndef _COREFIXTURE_RACEFIXTURE_HPP
#define _COREFIXTURE_RACEFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <race.hpp>

#include <random_fixture.hpp>

struct Race_Fixture : public Random_Fixture
{
	Race_Fixture();
	~Race_Fixture();
	
	const std::string test_race_name;
	const boost::shared_ptr<const Race> test_race;
};


#endif // _COREFIXTURE_RACEFIXTURE_HPP