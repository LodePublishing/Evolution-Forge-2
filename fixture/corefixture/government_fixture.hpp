#ifndef _COREFIXTURE_GOVERNMENTFIXTURE_HPP
#define _COREFIXTURE_GOVERNMENTFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <government.hpp>

#include <random_fixture.hpp>

struct Government_Fixture : public Random_Fixture
{
	Government_Fixture();
	~Government_Fixture();

	const std::string test_government_name;

	const boost::shared_ptr<const Government> test_government;
};

#endif // _COREFIXTURE_GOVERNMENTFIXTURE_HPP