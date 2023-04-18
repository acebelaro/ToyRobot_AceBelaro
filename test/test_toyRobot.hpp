//******************************************************************************
/*! @file       test_toyRobot.cpp
	@brief      Unit test for toy robot
*/
//******************************************************************************
#pragma once

#include <assert.h>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>
#include <stdint.h>

using namespace std;

typedef function<void (void)> tTestFunction;

class TestHashMap
{
	public:
		TestHashMap(string);
		~TestHashMap() = default;
		void AddTest(string, const tTestFunction&);
		void ExecuteTests();
		uint8_t GetTestCount();
	private:
		string _testName;
		vector<string> _tests; // for ordered keys
		map<string,const tTestFunction> _testMap;
};

int testCommandParser();
int testRobot();
int testTable();
int testDirection();
