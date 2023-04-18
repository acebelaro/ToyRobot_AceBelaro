//******************************************************************************
/*! @file       test_toyRobot.cpp
	@brief      Unit test for toy robot
*/
//******************************************************************************

#include <assert.h>
#include <iostream>
#include "test_toyRobot.hpp"

using namespace std;

TestHashMap::TestHashMap(string testName):
	_testName(testName)
{

}

void TestHashMap::AddTest(string testDescription, const tTestFunction& testFunction)
{
	_tests.push_back(testDescription); // ordered key
	_testMap.insert(make_pair(testDescription,testFunction));
}

void TestHashMap::ExecuteTests()
{
	cout << _testName << " Tests:" << endl;
	for( auto & testName: _tests )
	{
		cout << "\t" << testName << endl;
		_testMap[testName]();
	}
	cout << "\tCompleted tests for " << _testName << " : " << _testMap.size() << " tests" << endl;
}

uint8_t TestHashMap::GetTestCount()
{
	return _testMap.size();
}

int main(int /* argc */, char ** /* argv */) {

	uint32_t allTestCount = 0;

	allTestCount+= testCommandParser();
	allTestCount+= testRobot();
	allTestCount+= testTable();
	allTestCount+= testDirection();

	cout << "Completed all " << allTestCount << " tests." << endl;

    return EXIT_SUCCESS;
}
