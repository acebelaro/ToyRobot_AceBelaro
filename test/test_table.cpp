//******************************************************************************
/*! @file       test_table.cpp
	@brief      Unit test for table
*/
//******************************************************************************

#include "gtest/gtest.h"
#include "table.hpp"
#include "test_helper.h"

//******************************************************************************
//               Private function declaration
//******************************************************************************

/*
* @brief Test helper to assert thrown TableInvalidSizeException
* @param width
* @param height
*/
static void AssertTableExceptionForInvalidSize(int width, int height);

//******************************************************************************
//               Private function definition
//******************************************************************************

static void AssertTableExceptionForInvalidSize(int width, int height)
{
    bool exceptionThrown = false;
    try
    {
        CTable table(width, height);
    }
    catch (TableInvalidSizeException& e)
    {
        exceptionThrown = true;
        EXPECT_EQUAL_CONST_CHAR_STRING( "Unable to create size with non-positive width and/or height", e.what() );
    }
    EXPECT_TRUE(exceptionThrown);
}

//******************************************************************************
//               Test functions
//******************************************************************************

/*! @brief Test table construction with valid dimension
*/
TEST( TestTable, Test_TableInitialisationWithValidDimension )
{
    CTable table(5, 10);

    // Test
    EXPECT_EQ(5, table.GetWidth());
    EXPECT_EQ(10, table.GetHeight());
}

/*! @brief Test table construction with invalid dimension
*/
TEST( TestTable, Test_TableInitialisationWithInvalidDimension )
{
    AssertTableExceptionForInvalidSize(-1, 5);
    AssertTableExceptionForInvalidSize(5, -1);
    AssertTableExceptionForInvalidSize(-1, -1);
};

/*! @brief Test table when checking for allowed position
*/
TEST( TestTable, Test_AllowedPositionChecking )
{
    CTable table(5, 10);

    stPosition testPosition;
    
    // zero
    testPosition.x = 0;
    testPosition.y = 0;
    EXPECT_TRUE(table.IsPositionAllowed(&testPosition));

    // non-edge positions
    testPosition.x = 1;
    testPosition.y = 3;
    EXPECT_TRUE(table.IsPositionAllowed(&testPosition));

    // max x, y
    testPosition.x = 4;
    testPosition.y = 9;
    EXPECT_TRUE(table.IsPositionAllowed(&testPosition));
}

/*! @brief Test table when checking for not allowed position
*/
TEST( TestTable, Test_NotAllowedPositionChecking )
{
    CTable table(5, 10);

    stPosition testPosition;

    // invalid x
    testPosition.x = 5;
    testPosition.y = 3;
    EXPECT_FALSE(table.IsPositionAllowed(&testPosition));

    testPosition.x = -1;
    testPosition.y = 3;
    EXPECT_FALSE(table.IsPositionAllowed(&testPosition));

    // invalid y
    testPosition.x = 1;
    testPosition.y = 10;
    EXPECT_FALSE(table.IsPositionAllowed(&testPosition));

    testPosition.x = 1;
    testPosition.y = -1;
    EXPECT_FALSE(table.IsPositionAllowed(&testPosition));

    // invalid x and y
    testPosition.x = 5;
    testPosition.y = 10;
    EXPECT_FALSE(table.IsPositionAllowed(&testPosition));

    testPosition.x = -1;
    testPosition.y = -1;
    EXPECT_FALSE(table.IsPositionAllowed(&testPosition));
}
