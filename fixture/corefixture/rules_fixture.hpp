#ifndef _CORETEST_RULESFIXTURE_HPP
#define _CORETEST_RULESFIXTURE_HPP

#include <rules.hpp>
#include "unittype_fixture.hpp"

struct Rules_Fixture
{
	Rules_Fixture();
	~Rules_Fixture();

	const std::string test_filename_xml;
	const std::string test_file_name;
	const std::string test_rules_name;
	const UnitType_Fixture unitTypeFixture;

	Race* test_race;
	UnitType* unitType1;
	UnitType* unitType2;

	Rules* test_rules;

	time_t seed;
};


#endif // _CORETEST_RULESFIXTURE_HPP
