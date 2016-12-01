#ifndef _CORE_FIXTURE_PATHFIXTURE_HPP
#define _CORE_FIXTURE_PATHFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <core/path.hpp>

class Location;

struct Path_Fixture
{
	const boost::uuids::uuid test_source_location_id;
	const boost::uuids::uuid test_target_location_id;
	const unsigned int test_distance;

	const boost::shared_ptr<const Path> test_path;

	Path_Fixture();
	virtual ~Path_Fixture();
};

#endif // _CORE_FIXTURE_PATHFIXTURE_HPP