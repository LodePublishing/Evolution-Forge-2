#include <iostream>
#include <time.h>

#pragma warning(push, 0)  
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include "goalentry_fixture.hpp"

GoalEntry_Fixture::GoalEntry_Fixture():
	test_goalentry_name("my_goalentry_Name"),
	seed(time(0))
{
	boost::mt19937 generator(static_cast<boost::uint32_t>(seed));
	boost::uniform_int<> distribution(1, 100);
	boost::variate_generator<boost::mt19937&, boost::uniform_int<> > rnd(generator,  distribution); 
	std::cout << "Setting up goal entry fixture (seed " << seed << ")" << std::endl;

	std::list<Goal> test1;
	std::list<Goal> test2;
	std::list<Goal> test3;

	test1.push_back(Goal(rnd(), rnd(), rnd()));
	test1.push_back(Goal(rnd(), rnd(), rnd()));
	test2.push_back(Goal(rnd(), rnd(), rnd(), rnd()));
	test3.push_back(Goal(rnd(), rnd(), 0));
	test3.push_back(Goal(rnd(), rnd(), rnd()));
	test3.push_back(Goal(rnd(), rnd(), rnd(), 0));

	std::list<std::list<Goal> > test4;
	std::list<std::list<Goal> > test5;

	test4.push_back(test1);
	test4.push_back(test2);
	test5.push_back(test3);

	test_goalentry_goallist.push_back(test4);
	test_goalentry_goallist.push_back(test5);

	test_goalentry = new GoalEntry(test_goalentry_name, test_goalentry_goallist);
}

GoalEntry_Fixture::~GoalEntry_Fixture() {
	delete test_goalentry;
	GoalEntry::resetCounter();
}
