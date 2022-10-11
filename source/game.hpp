#pragma once

#include "robot.hpp"

/* Game class */
class CGame {
public:
	/**
	* @brief Game constructor
	*/
	CGame();
	/**
	* @brief Robot deconstructor
	*/
	~CGame();
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
