#pragma warning(push, 0)  
#include <boost/assign/list_of.hpp>
#pragma warning(pop)

#include <time.h>

#include <random_fixture.hpp>

#include "goalentry_fixture.hpp"


GoalEntry_Fixture::GoalEntry_Fixture():
	test_goalentry_name("my_goalentry_Name"),
	test_goalentry_goallist(init_goallist_helper()),
	test_goalentry(boost::shared_ptr<const GoalEntry>(new GoalEntry(test_goalentry_name, test_goalentry_goallist)))		
{ }

GoalEntry_Fixture::~GoalEntry_Fixture() { }

const std::list<std::list<std::list<Goal> > > GoalEntry_Fixture::init_goallist_helper() {
	const std::list<std::list<std::list<Goal> > > l = 
		boost::assign::list_of
			(boost::assign::list_of
				(boost::assign::list_of
					(Goal(boost::uuids::random_generator()(), boost::uuids::random_generator()(), Random_Fixture::instance().rnd()))
					(Goal(boost::uuids::random_generator()(), boost::uuids::random_generator()(), Random_Fixture::instance().rnd()))
				)
				(boost::assign::list_of
					(Goal(boost::uuids::random_generator()(), boost::uuids::random_generator()(), Random_Fixture::instance().rnd(), Random_Fixture::instance().rnd()))
				)
			)
			(boost::assign::list_of
				(boost::assign::list_of
					(Goal(boost::uuids::random_generator()(), boost::uuids::random_generator()(), 0))
					(Goal(boost::uuids::random_generator()(), boost::uuids::random_generator()(), Random_Fixture::instance().rnd()))
					(Goal(boost::uuids::random_generator()(), boost::uuids::random_generator()(), Random_Fixture::instance().rnd(), 0))
				)
			);
	// TODO reale IDs?
	return l;
}