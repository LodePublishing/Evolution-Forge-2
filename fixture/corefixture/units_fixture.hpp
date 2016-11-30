#ifndef _COREFIXTURE_UNITSFIXTURE_HPP
#define _COREFIXTURE_UNITSFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <units.hpp>

struct Units_Fixture
{	
	const unsigned int test_construction_time;
	const boost::shared_ptr<Units> test_units;

	const boost::shared_ptr<Unit> test_unit1;
	const boost::shared_ptr<Unit> test_unit2;
	const boost::shared_ptr<Unit> test_unit3;

	Units_Fixture();
	~Units_Fixture();
};


#endif // _COREFIXTURE_UNITSFIXTURE_HPP
