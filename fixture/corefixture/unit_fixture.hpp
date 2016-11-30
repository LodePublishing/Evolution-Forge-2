#ifndef _COREFIXTURE_UNITFIXTURE_HPP
#define _COREFIXTURE_UNITFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <unit.hpp>

struct Unit_Fixture
{
	const unsigned int test_construction_time;

	const boost::shared_ptr<const UnitType> unitType1;
	const boost::shared_ptr<const UnitType> unitType2;

	// TODO evtl unitTypes in unitTypeFixture definieren

	Unit_Fixture();
	~Unit_Fixture();
};

#endif // _COREFIXTURE_UNITFIXTURE_HPP
