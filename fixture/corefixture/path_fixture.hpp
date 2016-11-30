#ifndef _COREFIXTURE_PATHFIXTURE_HPP
#define _COREFIXTURE_PATHFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <path.hpp>

struct Path_Fixture
{
	const unsigned int test_source_position;
	const unsigned int test_target_position;
	const unsigned int test_distance;

	const boost::shared_ptr<const Path> test_path;

	Path_Fixture();
	~Path_Fixture();
};

#endif // _COREFIXTURE_PATHFIXTURE_HPP