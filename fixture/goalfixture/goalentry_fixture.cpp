#pragma warning(push, 0)  
#include <boost/assign/list_of.hpp>
#pragma warning(pop)

#include <misc/randomgenerator.hpp>

#include "goalentry_fixture.hpp"


GoalEntry_Fixture::GoalEntry_Fixture():
	test_goalentry_name("my_goalentry_Name"),
	test_goalentry_goalitemlist(init_goalitemlist_helper()),
	test_goalentry(boost::shared_ptr<const GoalEntry>(new GoalEntry(test_goalentry_name, test_goalentry_goalitemlist)))		
{ }

GoalEntry_Fixture::~GoalEntry_Fixture() { }

const std::list<std::list<std::list<GoalItem> > > GoalEntry_Fixture::init_goalitemlist_helper() {
	const std::list<std::list<std::list<GoalItem> > > l = 
		boost::assign::list_of
			(boost::assign::list_of
				(boost::assign::list_of
					(GoalItem(boost::uuids::random_generator()(), boost::uuids::random_generator()(), RandomGenerator::instance().rnd()))
					(GoalItem(boost::uuids::random_generator()(), boost::uuids::random_generator()(), RandomGenerator::instance().rnd()))
				)
				(boost::assign::list_of
					(GoalItem(boost::uuids::random_generator()(), boost::uuids::random_generator()(), RandomGenerator::instance().rnd(), RandomGenerator::instance().rnd()))
				)
			)
			(boost::assign::list_of
				(boost::assign::list_of
					(GoalItem(boost::uuids::random_generator()(), boost::uuids::random_generator()(), 0))
					(GoalItem(boost::uuids::random_generator()(), boost::uuids::random_generator()(), RandomGenerator::instance().rnd()))
					(GoalItem(boost::uuids::random_generator()(), boost::uuids::random_generator()(), RandomGenerator::instance().rnd(), 0))
				)
			);
	// TODO reale IDs?
	return l;
}
