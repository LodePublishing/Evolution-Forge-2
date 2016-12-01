#include <misc/randomgenerator.hpp>

#include "objectsize_fixture.hpp"
#include <guicore/objectsize_storage.hpp>
#include <guicore/guicore_directories.hpp>

ObjectSize_Fixture::ObjectSize_Fixture() :
	test_width(RandomGenerator::instance().rnd()),
	test_height(RandomGenerator::instance().rnd()),
	test_objectsize(new ObjectSize(test_width, test_height)),
	test_objectsizeMap(init_objectsizemap_helper())
{ 
	GuiCoreDirectories::initTemp("temp");	

	ObjectSizeStorage::instance(test_objectsizeMap);
}

ObjectSize_Fixture::~ObjectSize_Fixture() 
{ 
	GuiCoreDirectories::initTemp("temp");

	ObjectSizeStorage::clear();
	
	GuiCoreDirectories::init();
}

const std::map<const boost::uuids::uuid, const boost::shared_ptr<const ObjectSize> > ObjectSize_Fixture::init_objectsizemap_helper() {
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const ObjectSize> > objectsizeMap;
	objectsizeMap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const ObjectSize> >(test_objectsize->getId(), test_objectsize));
	return objectsizeMap;
}