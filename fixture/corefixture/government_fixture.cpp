#include <misc/randomgenerator.hpp>

#include "government_fixture.hpp"
#include <core/government_storage.hpp>
#include <core/core_directories.hpp>

Government_Fixture::Government_Fixture():
	test_government_name("my_government_Name"),
	test_government(new Government(test_government_name)),
	test_governmentMap(init_governmentmap_helper())
{ 
	CoreDirectories::initTemp("temp");

	GovernmentStorage::instance(test_governmentMap);
}

Government_Fixture::~Government_Fixture() 
{ 
	CoreDirectories::initTemp("temp");

	GovernmentStorage::clear();

	CoreDirectories::init();
}


const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Government> > Government_Fixture::init_governmentmap_helper() {
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const Government> > governmentMap;
	governmentMap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const Government> >(test_government->getId(), test_government));
	return governmentMap;
}
