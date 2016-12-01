#include <core/government_storage.hpp>

#include <boost/uuid/uuid.hpp>
#include <boost/shared_ptr.hpp>
#include <core/government.hpp>
#include <map>
#include <misc/uuid.hpp>
#include <sstream>

int main()
{
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const Government> > mymap;
	
	boost::shared_ptr<Government> mygov(new Government(Misc::uuid("{03e05de0-3a08-11e0-9207-0800200c9a66}"), "mygovernment"));
	boost::shared_ptr<Government> mygov2(new Government(Misc::uuid("{0fa33b20-3a08-11e0-9207-0800200c9a66}"), "mygovernment2"));
	boost::shared_ptr<Government> mygov3(new Government(Misc::uuid("{129021e0-3a08-11e0-9207-0800200c9a66}"), "mygovernment3"));
	boost::shared_ptr<Government> mygov4(new Government(Misc::uuid("{154f1ad0-3a08-11e0-9207-0800200c9a66}"), "mygovernment4"));

	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Government> >::const_iterator i = GovernmentStorage::instance().get(mygov3->getId());
	
	boost::shared_ptr<const Government> mynewgov = i->second;

	std::cout << mynewgov->getName();
	}/*
	
	mymap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const Government> >(mygov->getId(), mygov));
	mymap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const Government> >(mygov2->getId(), mygov2));
	mymap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const Government> >(mygov3->getId(), mygov3));
	mymap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const Government> >(mygov4->getId(), mygov4));
	GovernmentStorage::instance(mymap);

	GovernmentStorage::saveToXML("government.xml", "mygov");*/
}