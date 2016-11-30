#ifndef _COREFIXTURE_RULESFIXTURE_HPP
#define _COREFIXTURE_RULESFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <rules.hpp>

#include <random_fixture.hpp>

#include "unittype_fixture.hpp"


struct Rules_Fixture : public Random_Fixture
{
public:
	Rules_Fixture();
	~Rules_Fixture();

	const std::string test_filename_xml;
	const std::string test_file_name;
	const std::string test_rules_name;

	const UnitType_Fixture unitTypeFixture;

	const boost::shared_ptr<const UnitType> unitType1;
	const boost::shared_ptr<const UnitType> unitType2;

	const boost::shared_ptr<const Rules> test_rules;

private:
	const std::list<boost::shared_ptr<const UnitType> > init_unittypelist_helper();
};


#endif // _COREFIXTURE_RULESFIXTURE_HPP
