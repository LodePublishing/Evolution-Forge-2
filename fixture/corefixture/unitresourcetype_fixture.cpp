#include <iostream>
#include <time.h>

#pragma warning(push, 0)  
#include <boost/assign/list_of.hpp>
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include "unitresourcetype_fixture.hpp"

UnitResourceType_Fixture::UnitResourceType_Fixture():
	test_unitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE),
	seed(time(0))
{
	boost::mt19937 generator(static_cast<boost::uint32_t>(seed));
	boost::uniform_int<> distribution(1, 100);
	boost::variate_generator<boost::mt19937&, boost::uniform_int<> > rnd(generator,  distribution); 
	std::cout << "Setting up unit resource type fixture (seed " << seed << ")" << std::endl;

	test_amount = rnd();
	std::list<unsigned int> t1 = boost::assign::list_of(rnd())(rnd());
	std::list<unsigned int> t2 = boost::assign::list_of(rnd());
	test_unitTypeIDList.push_back(t1);
	test_unitTypeIDList.push_back(t2);

	//test_unitTypeIDList.insert(test_unitTypeIDList.end(), t2);

	test_unitresourcetype = new UnitResourceType(test_unitResourceType, test_unitTypeIDList, test_amount);

}

UnitResourceType_Fixture::~UnitResourceType_Fixture() 
{
	delete test_unitresourcetype;
}