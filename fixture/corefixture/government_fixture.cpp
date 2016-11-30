#pragma warning(push, 0)  
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include "government_fixture.hpp"

Government_Fixture::Government_Fixture():
	Random_Fixture(),
	test_government_name("my_government_Name"),
	test_government(boost::shared_ptr<const Government>(new Government(test_government_name)))
{
}

Government_Fixture::~Government_Fixture() 
{
	Government::resetCounter();
}