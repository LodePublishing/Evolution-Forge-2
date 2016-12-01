#ifndef _CORE_FIXTURE_RULESFIXTURE_HPP
#define _CORE_FIXTURE_RULESFIXTURE_HPP

#include <core/rules.hpp>

#include "race_fixture.hpp"
#include "unittype_fixture.hpp"

#include <map>

struct Rules_Fixture
{
	const UnitType_Fixture unitTypeFixture;

	const std::string test_rules_name;
	const std::list<boost::shared_ptr<const UnitType> > test_unittype_list;

	const boost::shared_ptr<const Rules> test_rules;

	Rules_Fixture();
	virtual ~Rules_Fixture();

	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Rules> > test_rulesMap;

private:
	const std::list<boost::shared_ptr<const UnitType> > init_unittypelist_helper();
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Rules> > init_rulesmap_helper();
};


#endif // _CORE_FIXTURE_RULESFIXTURE_HPP
