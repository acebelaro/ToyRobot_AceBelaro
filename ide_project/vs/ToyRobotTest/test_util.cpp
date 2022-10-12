#include "CppUnitTest.h"
#include "util.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ToyRobotTest
{
	TEST_CLASS(UtilTest)
	{
	public:
		TEST_METHOD(Test_SplitNonEmptyString)
		{
			std::vector<std::string> tokens;
			SplitString("PLACE 0,0,EAST", ' ', tokens);
			Assert::AreEqual((size_t)2, tokens.size());
			Assert::AreEqual(std::string("PLACE"), tokens[0]);
			Assert::AreEqual(std::string("0,0,EAST"), tokens[1]);
		}

		TEST_METHOD(Test_SplitEmptyString)
		{
			std::vector<std::string> tokens;
			SplitString("", ' ', tokens);
			Assert::AreEqual((size_t)0, tokens.size());
		}
	
		TEST_METHOD(Test_StringToDirectionValidDirectionNames)
		{
			std::string directionName;
			CDirection directionVal;
			bool valid;

			// NORTH
			directionName = "NORTH";
			valid = StringToDirection(directionName, &directionVal);
			Assert::IsTrue(valid);
			Assert::AreEqual(
				static_cast<int>(CDirection::NORTH),
				static_cast<int>(directionVal));

			// EAST
			directionName = "EAST";
			valid = StringToDirection(directionName, &directionVal);
			Assert::IsTrue(valid);
			Assert::AreEqual(
				static_cast<int>(CDirection::EAST),
				static_cast<int>(directionVal));

			// SOUTH
			directionName = "SOUTH";
			valid = StringToDirection(directionName, &directionVal);
			Assert::IsTrue(valid);
			Assert::AreEqual(
				static_cast<int>(CDirection::SOUTH),
				static_cast<int>(directionVal));

			// WEST
			directionName = "WEST";
			valid = StringToDirection(directionName, &directionVal);
			Assert::IsTrue(valid);
			Assert::AreEqual(
				static_cast<int>(CDirection::WEST),
				static_cast<int>(directionVal));
		}

		TEST_METHOD(Test_StringToDirectionInvalidDirectionNames) {
			std::string directionName;
			CDirection directionVal;
			bool valid;

			directionName = "";
			valid = StringToDirection(directionName, &directionVal);
			Assert::IsFalse(valid);

			directionName = "~";
			valid = StringToDirection(directionName, &directionVal);
			Assert::IsFalse(valid);

			directionName = "nORTH";
			valid = StringToDirection(directionName, &directionVal);
			Assert::IsFalse(valid);

			directionName = "north";
			valid = StringToDirection(directionName, &directionVal);
			Assert::IsFalse(valid);

			directionName = "NORTHx";
			valid = StringToDirection(directionName, &directionVal);
			Assert::IsFalse(valid);

			directionName = "xNORTH";
			valid = StringToDirection(directionName, &directionVal);
			Assert::IsFalse(valid);
		}

		TEST_METHOD(Test_DirectionToStringValidDirectionValues) {
			CDirection directionVal;
			std::string directionName;

			// NORTH
			directionVal = CDirection::NORTH;
			Assert::AreEqual(std::string("NORTH"), DirectionToString(directionVal));
			// EAST
			directionVal = CDirection::EAST;
			Assert::AreEqual(std::string("EAST"), DirectionToString(directionVal));
			// SOUTH
			directionVal = CDirection::SOUTH;
			Assert::AreEqual(std::string("SOUTH"), DirectionToString(directionVal));
			// WEST
			directionVal = CDirection::WEST;
			Assert::AreEqual(std::string("WEST"), DirectionToString(directionVal));
		}
	};
}
