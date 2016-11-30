#include <random_fixture.hpp>
#include <globalstorage.hpp>

#include "government_fixture.hpp"


Government_Fixture::Government_Fixture():
	test_government_name("my_government_Name"),
	test_government(boost::shared_ptr<const Government>(new Government(test_government_name)))
{ 
	GlobalStorage::instance().addGovernment(test_government);
}

Government_Fixture::~Government_Fixture() 
{ 
	GlobalStorage::instance().removeGovernment(test_government->getId());
}