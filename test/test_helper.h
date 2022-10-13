//******************************************************************************
/*! @file       test_helper.h
	@brief      Test helper
*/
//******************************************************************************

#ifndef TEST_HELPER_H_
#define TEST_HELPER_H_

// Assert string values (constant character pointer) are equal
#define EXPECT_EQUAL_CONST_CHAR_STRING( str1, str2 ) EXPECT_EQ( strcmp( str1, str2 ), 0 )

// Assert object is not null
#define EXPECT_IS_NOT_NULL( obj ) EXPECT_TRUE( nullptr != obj )

#endif /* TEST_HELPER_H_ */
