#ifndef _GOALTEST_PROCESSEDGOALFIXTURE_HPP
#define _GOALTEST_PROCESSEDGOALFIXTURE_HPP

#include <processedgoal.hpp>

struct ProcessedGoal_Fixture
{
	ProcessedGoal_Fixture();
	~ProcessedGoal_Fixture();

	const std::string test_filename_xml;
	const std::string test_file_name;

	bool test_isHaveable;
	bool test_isBuildable;
	bool test_isBuildableAtStart;


	ProcessedGoal* test_processedgoal;

	time_t seed;
};


#endif // _GOALTEST_PROCESSEDGOALFIXTURE_HPP
