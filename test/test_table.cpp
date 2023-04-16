//******************************************************************************
/*! @file       test_table.cpp
	@brief      Unit test for table
*/
//******************************************************************************

#include "test_toyRobot.hpp"
#include "table.hpp"

static void test_dimensionGet()
{
    Table table(5, 10);

    // Test
	assert( table.GetWidth() == 5 );
	assert( table.GetHeight() == 10 );
}

static void test_coordinatesWithinBounds()
{
    Table table(5, 10);

    Coordinate coordinate(0,0);
    
    // zero
	coordinate.SetX(0);
	coordinate.SetY(0);
    assert( table.IsCoordinatesWithinBounds(coordinate) );

    // non-edge positions
	coordinate.SetX(1);
	coordinate.SetY(3);
    assert( table.IsCoordinatesWithinBounds(coordinate) );

    // max x, y
	coordinate.SetX(4);
	coordinate.SetY(9);
    assert( table.IsCoordinatesWithinBounds(coordinate) );
}

static void test_coordinatesOutsideBounds()
{
    Table table(5, 10);

    Coordinate coordinate(0,0);

    // invalid x
	coordinate.SetX(5);
	coordinate.SetY(3);
    assert( table.IsCoordinatesWithinBounds(coordinate) == false );

	coordinate.SetX(-1);
	coordinate.SetY(3);
    assert( table.IsCoordinatesWithinBounds(coordinate) == false );

    // invalid y
	coordinate.SetX(1);
	coordinate.SetY(10);
    assert( table.IsCoordinatesWithinBounds(coordinate) == false );

	coordinate.SetX(1);
	coordinate.SetY(-1);
    assert( table.IsCoordinatesWithinBounds(coordinate) == false );

    // invalid x and y
	coordinate.SetX(5);
	coordinate.SetY(10);
    assert( table.IsCoordinatesWithinBounds(coordinate) == false );

	coordinate.SetX(-1);
	coordinate.SetY(-1);
    assert( table.IsCoordinatesWithinBounds(coordinate) == false );
}

int testTable()
{
	TestHashMap testHashMap("Table");
	testHashMap.AddTest("Test dimension get", test_dimensionGet);
	testHashMap.AddTest("Test coordinates within bounds", test_coordinatesWithinBounds);
	testHashMap.AddTest("Test coordinates outside bounds", test_coordinatesOutsideBounds);

	testHashMap.ExecuteTests();

	return testHashMap.GetTestCount();
}
