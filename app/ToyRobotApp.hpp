#pragma once

#include "robot.hpp"

using namespace std;

class CToyRobotApp {
	public:
		CToyRobotApp();
		~CToyRobotApp() = default;
	private:
		Robot _robot;
		Table _table;
		void PrintTable();
	public:
		void Play();
};

//******************************************************************************
//               Public function declaration
//******************************************************************************

int main();
