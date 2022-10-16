//******************************************************************************
/*! @file       toy_robot.hpp
	@brief      External interface for toy robot
*/
//******************************************************************************
#pragma once

#include "robot.hpp"

/* Toy Robot class */
class CToyRobot {
public:
	/**
	* @brief Toy Robot constructor
	*/
	CToyRobot();
	/**
	* @brief Toy Robot deconstructor
	*/
	~CToyRobot();
private:
	CTable m_table;	/* table instance */
	CRobot m_robot;	/* robot instance */
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
