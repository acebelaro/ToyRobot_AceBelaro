//******************************************************************************
/*! @file       robot.hpp
	@brief      External interface of robot class
*/
//******************************************************************************
#pragma once

#include "robot_if.hpp"
#include "table.hpp"
#include "command.hpp"

//******************************************************************************
//               Public definitions
//******************************************************************************

/** Robot class */
class CRobot {
public:
	/**
	* @brief Robot constructor
	* @param table	- where robot is placed
	* @return robot
	* @exception	RobotNullTableException - when created with null table
	*/
	CRobot(CTable* const);
	/**
	* @brief Robot deconstructor
	*/
	~CRobot();
private:
	CTable* m_table;		/* holder of table where robot is put */
	bool m_isPlaced;		/* flag is robot is already placed */
	CDirection m_direction; /* robot direction : NORTH, EAST, SOUTH, WEST */
	stPosition m_position;	/* robot position in table : x and y coordinates */
private:
	/**
	* @brief Moves robot to next position by 1 step
	* @retval true	- movment sucessful
	* @retval false	- movement error due to falling off from table
	*/
	bool Move();
	/**
	* @brief Rotates robot
	* @param rotate		- rotation to execute
	*/
	void Rotate(CRotate);
public:
	/**
	* @brief Gets the table the robot is placed
	* @return table
	*/
	CTable* GetTable();
	/**
	* @brief Checks if robot is placed
	* @retval true	- robot is placed
	* @retval false - robot is not placed
	*/
	bool IsPlaced();
	/**
	* @brief Gets robot direction
	* @return robot direction
	*/
	CDirection GetDirection();
	/**
	* @brief Gets robot position
	* @return robot position
	*/
	stPosition GetPosition();
	/**
	* @brief Applies command to robot
	* 
	* @param command	- command to apply
	* @retval OK					- command ok
	* @retval ROBOT_NOT_YET_PLACED	- robot not yet placed
	* @retval IGNORE_FALL_OFF_MOVE	- robot ignored move that results tofalling off
	*/
	CCommandApplyResult ApplyCommand(CCommand* const command);
};
