#ifndef _COREFIXTURE_RULESFIXTURE_HPP
#define _COREFIXTURE_RULESFIXTURE_HPP

#include <rules.hpp>

#include "race_fixture.hpp"
#include "unittype_fixture.hpp"

struct Rules_Fixture
{
	const Race_Fixture raceFixture;
	const UnitType_Fixture unitTypeFixture;

	const std::string test_filename_xml;
	const std::string test_file_name;
	const std::string test_rules_name;
	const std::list<boost::shared_ptr<const UnitType> > test_unittype_list;

	const boost::shared_ptr<const Rules> test_rules;

	Rules_Fixture();
	virtual ~Rules_Fixture();

private:
	const std::list<boost::shared_ptr<const UnitType> > init_unittypelist_helper();
};


#endif // _COREFIXTURE_RULESFIXTURE_HPP
