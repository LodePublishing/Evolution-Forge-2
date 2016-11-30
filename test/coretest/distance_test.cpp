#pragma warning(push, 0) 
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <distance_fixture.hpp>

#include <sstream>

BOOST_FIXTURE_TEST_SUITE( Distance_test, Distance_Fixture )

	BOOST_AUTO_TEST_CASE (Distance_constructor)
	{
		BOOST_CHECK_EQUAL(test_distance->getWidth(), test_width);
		BOOST_CHECK_EQUAL(test_distance->getHeight(), test_height);

		std::ostringstream os;
		os << (test_width) << "x" << (test_height);
		BOOST_CHECK_EQUAL(test_distance->toString(), os.str());
	}

	BOOST_AUTO_TEST_CASE (Distance_set)
	{
		Distance test_distance2(test_width, test_height);
		test_distance2.setWidth(test_width*2);
		BOOST_CHECK_EQUAL(test_distance2.getWidth(), test_width*2);

		test_distance2.setHeight(test_height*2);
		BOOST_CHECK_EQUAL(test_distance2.getHeight(), test_height*2);		
	}

	BOOST_AUTO_TEST_CASE (Distance_copy_constructor)
	{
		Distance temp_distance(*test_distance);

		BOOST_CHECK_EQUAL(temp_distance.getWidth(), test_width);
		BOOST_CHECK_EQUAL(temp_distance.getHeight(), test_height);
	}

	BOOST_AUTO_TEST_CASE (Distance_assignment_operator)
	{
		Distance temp_distance = *test_distance;

		BOOST_CHECK_EQUAL(temp_distance.getWidth(), test_width);
		BOOST_CHECK_EQUAL(temp_distance.getHeight(), test_height);
	}

	BOOST_AUTO_TEST_CASE (Distance_compare_operator)
	{
		Distance temp_distance(test_width, test_height);

		BOOST_CHECK(temp_distance == *test_distance);

		Distance temp_distance2(test_width+1, test_height);
		Distance temp_distance3(test_width+1, test_height+1);

		BOOST_CHECK(!(temp_distance2 < *test_distance));
		BOOST_CHECK(!(*test_distance > temp_distance2));
		BOOST_CHECK(temp_distance3 > *test_distance);
		BOOST_CHECK(*test_distance < temp_distance3);

		BOOST_CHECK(!(temp_distance != *test_distance));
	}

	BOOST_AUTO_TEST_CASE (Distance_modification_operator)
	{
		Distance temp_distance(test_width, test_height);
		Distance temp_distance2(test_width+1, test_height);
		Distance temp_distance3 = temp_distance + temp_distance2;

		BOOST_CHECK_EQUAL(temp_distance3.getWidth(), test_width+test_width+1);
		BOOST_CHECK_EQUAL(temp_distance3.getHeight(), test_height+test_height);

		Distance temp_distance4 = temp_distance2 - temp_distance;

		BOOST_CHECK_EQUAL(temp_distance4.getWidth(), 1);
		BOOST_CHECK_EQUAL(temp_distance4.getHeight(), 0);

		Distance temp_distance5 = (temp_distance + temp_distance)/2;

		BOOST_CHECK_EQUAL(temp_distance.getWidth(), test_width);
		BOOST_CHECK_EQUAL(temp_distance.getHeight(), test_height);

	}

	BOOST_AUTO_TEST_CASE (Distance_Length)
	{
		BOOST_CHECK_EQUAL(test_distance->getLength(), static_cast<unsigned int>(sqrt(static_cast<float>(test_width * test_width + test_height * test_height))));
	}


BOOST_AUTO_TEST_SUITE_END( )
