#ifndef _CORE_FIXTURE_STARTCONDITIONFIXTURE_HPP
#define _CORE_FIXTURE_STARTCONDITIONFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <core/startcondition.hpp>

#include "units_fixture.hpp"

#include <map>

struct StartCondition_Fixture
{
	Units_Fixture unitsFixture;
	

	const std::string test_name;
	const unsigned int test_startingTime;
	
	const boost::shared_ptr<const StartCondition> test_startcondition;

	StartCondition_Fixture();
	virtual ~StartCondition_Fixture();

	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const StartCondition> > test_startconditionMap;

private:
	const std::list<boost::shared_ptr<const Player> > init_playerlist_helper();
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const StartCondition> > init_startconditionmap_helper();
};

#endif // _CORE_FIXTURE_STARTCONDITIONFIXTURE_HPP
