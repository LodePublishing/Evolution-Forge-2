#ifndef _COREFIXTURE_PATHFIXTURE_HPP
#define _COREFIXTURE_PATHFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <path.hpp>

#include <random_fixture.hpp>

struct Path_Fixture : public Random_Fixture
{
	Path_Fixture();
	~Path_Fixture();

	unsigned int test_source_position;
	unsigned int test_target_position;
	unsigned int test_distance;

	const boost::shared_ptr<const Path> test_path;
};

#endif // _COREFIXTURE_PATHFIXTURE_HPP