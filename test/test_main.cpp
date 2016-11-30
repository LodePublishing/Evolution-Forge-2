#ifndef WIN32
#define BOOST_TEST_DYN_LINK
#endif

#define BOOST_TEST_MODULE MainTest

#include <iostream>

#pragma warning(push, 0)  
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

struct GlobalStorage_Fixture {
	GlobalStorage_Fixture() {std::cout << "setup" << std::endl; }
	~GlobalStorage_Fixture() {std::cout << "teardown" << std::endl;}
};

BOOST_GLOBAL_FIXTURE( GlobalStorage_Fixture )