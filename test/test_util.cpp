//******************************************************************************
/*! @file       test_util.cpp
	@brief      Unit test for util
*/
//******************************************************************************

#include "gtest/gtest.h"
#include "util.hpp"

//******************************************************************************
//               Test functions
//******************************************************************************

/*! @brief Test string split for non-empty string and there are delimiter instances
*/
TEST( TestUtil, Test_SplitNonEmptyStringHasDelimiters )
{
    std::vector<std::string> tokens;
    SplitString( "PLACE 0,0,EAST", ' ', tokens );
    EXPECT_EQ( (size_t)2, tokens.size() );
    EXPECT_EQ( std::string("PLACE"), tokens[0] );
    EXPECT_EQ( std::string("0,0,EAST"), tokens[1] );
}

/*! @brief Test string split for empty string
*/
TEST( TestUtil, Test_SplitEmptyString )
{
    std::vector<std::string> tokens;
    SplitString( "", ' ', tokens );
    EXPECT_EQ( (size_t)0, tokens.size() );
}

/*! @brief Test string split for non-empty string and there are no delimiters found
*/
TEST( TestUtil, Test_SplitNonEmptyStringNoDelimiter )
{
    std::vector<std::string> tokens;
    SplitString( "TEST", ' ', tokens );
    EXPECT_EQ( (size_t)1, tokens.size() );
    EXPECT_EQ( std::string("TEST"), tokens[0] );
}

/*! @brief Test valid string directions to direction conversion
*/
TEST( TestUtil, Test_StringToDirectionValidDirectionNames )
{
    std::string directionName;
    CDirection directionVal;
    bool valid;

    // NORTH
    directionName = "NORTH";
    valid = StringToDirection(directionName, &directionVal);
    EXPECT_TRUE(valid);
    EXPECT_EQ(
        static_cast<int>(CDirection::NORTH),
        static_cast<int>(directionVal));

    // EAST
    directionName = "EAST";
    valid = StringToDirection(directionName, &directionVal);
    EXPECT_TRUE(valid);
    EXPECT_EQ(
        static_cast<int>(CDirection::EAST),
        static_cast<int>(directionVal));

    // SOUTH
    directionName = "SOUTH";
    valid = StringToDirection(directionName, &directionVal);
    EXPECT_TRUE(valid);
    EXPECT_EQ(
        static_cast<int>(CDirection::SOUTH),
        static_cast<int>(directionVal));

    // WEST
    directionName = "WEST";
    valid = StringToDirection(directionName, &directionVal);
    EXPECT_TRUE(valid);
    EXPECT_EQ(
        static_cast<int>(CDirection::WEST),
        static_cast<int>(directionVal));
}

/*! @brief Test invalid string directions to direction conversion
*/
TEST( TestUtil, Test_StringToDirectionInvalidDirectionNames ) {
    std::string directionName;
    CDirection directionVal;
    bool valid;

    directionName = "";
    valid = StringToDirection(directionName, &directionVal);
    EXPECT_FALSE(valid);

    directionName = "~";
    valid = StringToDirection(directionName, &directionVal);
    EXPECT_FALSE(valid);

    directionName = "nORTH";
    valid = StringToDirection(directionName, &directionVal);
    EXPECT_FALSE(valid);

    directionName = "north";
    valid = StringToDirection(directionName, &directionVal);
    EXPECT_FALSE(valid);

    directionName = "NORTHx";
    valid = StringToDirection(directionName, &directionVal);
    EXPECT_FALSE(valid);

    directionName = "xNORTH";
    valid = StringToDirection(directionName, &directionVal);
    EXPECT_FALSE(valid);
}

/*! @brief Test valid directions to string conversion
*/
TEST( TestUtil, Test_DirectionToStringValidDirectionValues ) {
    CDirection directionVal;
    std::string directionName;

    // NORTH
    directionVal = CDirection::NORTH;
    EXPECT_EQ(std::string("NORTH"), DirectionToString(directionVal));
    // EAST
    directionVal = CDirection::EAST;
    EXPECT_EQ(std::string("EAST"), DirectionToString(directionVal));
    // SOUTH
    directionVal = CDirection::SOUTH;
    EXPECT_EQ(std::string("SOUTH"), DirectionToString(directionVal));
    // WEST
    directionVal = CDirection::WEST;
    EXPECT_EQ(std::string("WEST"), DirectionToString(directionVal));
}
