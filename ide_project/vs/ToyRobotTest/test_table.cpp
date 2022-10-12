#include "CppUnitTest.h"
#include "table.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ToyRobotTest
{
	TEST_CLASS(TableTest)
	{
	private:
		void AssertTableExceptionForInvalidSize(int width, int height)
		{
			bool exceptionThrown = false;
			try
			{
				CTable table(width, height);
			}
			catch (TableInvalidSizeException& e)
			{
				exceptionThrown = true;
				Assert::AreEqual("Unable to create size with non-positive width and/or height", e.what());
			}
			Assert::IsTrue(exceptionThrown);
		}
	public:
		
		TEST_METHOD(Test_TableInitialisation)
		{
			CTable table(5, 10);

			// Test
			Assert::AreEqual(5, table.GetWidth());
			Assert::AreEqual(10, table.GetHeight());
		}

		TEST_METHOD(Test_CreatingTableExceptionForInvalidSize)
		{
			AssertTableExceptionForInvalidSize(-1, 5);
			AssertTableExceptionForInvalidSize(5, -1);
			AssertTableExceptionForInvalidSize(-1, -1);
		};

		TEST_METHOD(Test_AllowedPositionChecking)
		{
			CTable table(5, 10);

			stPosition testPosition;
			
			// zero
			testPosition.x = 0;
			testPosition.y = 0;
			Assert::IsTrue(table.IsPositionAllowed(&testPosition));

			// non-edge positions
			testPosition.x = 1;
			testPosition.y = 3;
			Assert::IsTrue(table.IsPositionAllowed(&testPosition));

			// max x, y
			testPosition.x = 4;
			testPosition.y = 9;
			Assert::IsTrue(table.IsPositionAllowed(&testPosition));
		}

		TEST_METHOD(Test_NotAllowedPositionChecking)
		{
			CTable table(5, 10);

			stPosition testPosition;

			// invalid x
			testPosition.x = 5;
			testPosition.y = 3;
			Assert::IsFalse(table.IsPositionAllowed(&testPosition));

			testPosition.x = -1;
			testPosition.y = 3;
			Assert::IsFalse(table.IsPositionAllowed(&testPosition));

			// invalid y
			testPosition.x = 1;
			testPosition.y = 10;
			Assert::IsFalse(table.IsPositionAllowed(&testPosition));

			testPosition.x = 1;
			testPosition.y = -1;
			Assert::IsFalse(table.IsPositionAllowed(&testPosition));

			// invalid x and y
			testPosition.x = 5;
			testPosition.y = 10;
			Assert::IsFalse(table.IsPositionAllowed(&testPosition));

			testPosition.x = -1;
			testPosition.y = -1;
			Assert::IsFalse(table.IsPositionAllowed(&testPosition));
		}
	};
}
