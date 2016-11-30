#pragma warning(push, 0) 
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <race_fixture.hpp>

BOOST_FIXTURE_TEST_SUITE( Race_test, Race_Fixture )

	BOOST_AUTO_TEST_CASE (Race_constructor)
	{
		BOOST_CHECK_EQUAL(test_race->getName(), test_race_name);
		BOOST_CHECK_EQUAL(test_race->getID(), 0);
	}

	BOOST_AUTO_TEST_CASE (Race_ID)
	{ 
		int id1 = test_race->getID();

		std::list<Race*> races;
		for(int i = 0; i < 98; i++) {
			races.push_back(new Race(test_race_name));
		}
		
		Race* test_race2 = new Race(test_race_name);
		int id2 = test_race2->getID();
		
		BOOST_CHECK_EQUAL(id1+99, id2);

		delete test_race2;
		for(std::list<Race*>::iterator i = races.begin(); i != races.end(); i++) {
			delete *i;
		}
	}

BOOST_AUTO_TEST_SUITE_END( )
