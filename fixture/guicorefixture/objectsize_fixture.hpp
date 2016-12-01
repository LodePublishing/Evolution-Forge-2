#ifndef _GUICORE_FIXTURE_OBJECTSIZEFIXTURE_HPP
#define _GUICORE_FIXTURE_OBJECTSIZEFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/shared_ptr.hpp>
#pragma warning(pop)

#include <guicore/objectsize.hpp>
#include <map>

struct ObjectSize_Fixture
{
	const Uint16 test_width;
	const Uint16 test_height;

	const boost::shared_ptr<const ObjectSize> test_objectsize;

	ObjectSize_Fixture();	
	~ObjectSize_Fixture();
private:
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const ObjectSize> > test_objectsizeMap;
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const ObjectSize> > init_objectsizemap_helper();
};

#endif // _GUICORE_FIXTURE_OBJECTSIZEFIXTURE_HPP
