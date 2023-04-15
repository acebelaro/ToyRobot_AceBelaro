#pragma once

#include "robot.hpp"

/* Game class */
class CToyRobotApp {
public:
	/**
	* @brief Game constructor
	*/
	CToyRobotApp();
	/**
	* @brief Robot deconstructor
	*/
	~CToyRobotApp();
private:
	CRobot* m_robot;	/* robot instance */
	CTable* m_table;	/* table instance */
	/*
	* @brief prints table
	*/
	void PrintTable();
public:
	/*
	* @brief play function
	*/
	void Play();
};

//******************************************************************************
//               Public function declaration
//******************************************************************************

int main();
