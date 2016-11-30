#ifndef _CORETEST_GOVERNMENTFIXTURE_HPP
#define _CORETEST_GOVERNMENTFIXTURE_HPP

#include <government.hpp>

struct Government_Fixture
{
	Government_Fixture();
	~Government_Fixture();

	const std::string test_government_name;

	Government* test_government;

	time_t seed;
};

#endif // _CORETEST_GOVERNMENTFIXTURE_HPP