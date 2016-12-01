#ifndef _CORE_FIXTURE_GOVERNMENTFIXTURE_HPP
#define _CORE_FIXTURE_GOVERNMENTFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <core/government.hpp>

#include <map>

struct Government_Fixture
{
	const std::string test_government_name;

	const boost::shared_ptr<const Government> test_government;	

	Government_Fixture();	
	virtual ~Government_Fixture();
private:
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Government> > test_governmentMap;
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Government> > init_governmentmap_helper();
};

#endif // _CORE_FIXTURE_GOVERNMENTFIXTURE_HPP