#pragma warning(push, 0) 
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <coordinate_fixture.hpp>

BOOST_FIXTURE_TEST_SUITE( Coordinate_test, Coordinate_Fixture)

	BOOST_AUTO_TEST_CASE (Coordinate_constructor)
	{
		BOOST_CHECK_EQUAL(test_coordinate->getX(), test_x);
		BOOST_CHECK_EQUAL(test_coordinate->getY(), test_y);
	}

	BOOST_AUTO_TEST_CASE (Coordinate_assignment_constructor)
	{
		Coordinate temp_coordinate(*test_coordinate);

		BOOST_CHECK_EQUAL(temp_coordinate.getX(), test_x);
		BOOST_CHECK_EQUAL(temp_coordinate.getY(), test_y);
	}

	BOOST_AUTO_TEST_CASE (Coordinate_assignment_operator)
	{
		Coordinate temp_coordinate = *test_coordinate;

		BOOST_CHECK_EQUAL(temp_coordinate.getX(), test_x);
		BOOST_CHECK_EQUAL(temp_coordinate.getY(), test_y);
	}

	BOOST_AUTO_TEST_CASE (Coordinate_comparison_operator)
	{
		Coordinate temp_coordinate(test_x, test_y);
		Coordinate temp_coordinate2(test_x, test_y+1);
		Coordinate temp_coordinate3(test_x+1, test_y+1);

		BOOST_CHECK(temp_coordinate == *test_coordinate); 
		BOOST_CHECK(temp_coordinate2 != *test_coordinate); 

		BOOST_CHECK(temp_coordinate3 > temp_coordinate);
		BOOST_CHECK(temp_coordinate < temp_coordinate3);
		BOOST_CHECK(temp_coordinate2 >= temp_coordinate);
		BOOST_CHECK(temp_coordinate <= temp_coordinate2);
	}

	BOOST_AUTO_TEST_CASE (Coordinate_movement)
	{
		Coordinate temp_coordinate(test_x, test_y);

		temp_coordinate += Distance(1, 1);

		BOOST_CHECK_EQUAL(temp_coordinate.getX(), test_x+1);
		BOOST_CHECK_EQUAL(temp_coordinate.getY(), test_y+1);

		temp_coordinate -= Distance(0, 2);

		BOOST_CHECK_EQUAL(temp_coordinate.getX(), test_x+1);
		BOOST_CHECK_EQUAL(temp_coordinate.getY(), test_y-1);
	}

	BOOST_AUTO_TEST_CASE (Coordinate_distance)
	{
		Coordinate temp_coordinate(test_x+10, test_y+12);

		Distance temp_distance = temp_coordinate - *test_coordinate;

		BOOST_CHECK_EQUAL(temp_distance.getWidth(), 10);
		BOOST_CHECK_EQUAL(temp_distance.getHeight(), 12);
	}

	BOOST_AUTO_TEST_CASE (Coordinate_arithmetic)
	{
		Coordinate temp_coordinate(test_x, test_y);
		Coordinate temp_coordinate2 = temp_coordinate + temp_coordinate;

		BOOST_CHECK_EQUAL(temp_coordinate2.getX(), 2*test_x);
		BOOST_CHECK_EQUAL(temp_coordinate2.getY(), 2*test_y);

		temp_coordinate2 = temp_coordinate2 + Distance(1,1);

		BOOST_CHECK_EQUAL(temp_coordinate2.getX(), 2*test_x+1);
		BOOST_CHECK_EQUAL(temp_coordinate2.getY(), 2*test_y+1);

		temp_coordinate2 = temp_coordinate2 - Distance(1,1);

		BOOST_CHECK_EQUAL(temp_coordinate2.getX(), 2*test_x);
		BOOST_CHECK_EQUAL(temp_coordinate2.getY(), 2*test_y);

		Coordinate temp_coordinate3 = temp_coordinate * 3;

		BOOST_CHECK_EQUAL(temp_coordinate3.getX(), 3*test_x);
		BOOST_CHECK_EQUAL(temp_coordinate3.getY(), 3*test_y);
}


BOOST_AUTO_TEST_SUITE_END( )
