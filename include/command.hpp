//******************************************************************************
/*! @file       command.hpp
	@brief      External interface of command class
*/
//******************************************************************************
#pragma once

#include "command_if.hpp"
#include "table_if.hpp"

//******************************************************************************
//               Public definitions
//******************************************************************************

/** Command class */
class CCommand {
public:
	/**
	* @brief Command constructor
	*/
	CCommand();
	/**
	* @brief Command deconstructor
	*/
	~CCommand();
private:
	bool m_isPlace;				/* flag to indicate command is for placing */
	stPlacement m_placement;	/* placement parameters */
	bool m_isMove;				/* flag to indicate command is for moving */
	CRotate m_rotate;			/* flag to indicate command is for rotating */
	bool m_doReport;			/* flag to indicate command is for reporting */
public:
	/**
	* @brief Checks if command is for placing
	* @retval true	- command is for placing
	* @retval false - command is not for placing
	*/
	bool IsPlace();
	/**
	* @brief Sets command placement parameter
	* @param placement - command placement parameter
	*/
	void SetPlacement(stPlacement);
	/**
	* @brief Gets the command placement parameter
	* @return command placement parameter
	*/
	stPlacement GetPlacement();
	/**
	* @brief Sets the command move flag
	* @param move - move flag
	*/
	void SetMove(bool);
	/**
	* @brief Checks if command is for moving
	* @retval true	- command is for moving
	* @retval false - command is not for moving
	*/
	bool IsMove();
	/**
	* @brief Sets command rotate parameter
	* @param rotate - command rotate parameter
	*/
	void SetRotate(CRotate);
	/**
	* @brief Gets command rotate parameter
	* @return command rotate parameter
	*/
	CRotate GetRotate();
	/**
	* @brief Checks if command is for reporting
	* @retval true	- command is for reporting
	* @retval false - command is not for reporting
	*/
	bool DoReport();
	/**
	* @brief Sets command report parameter
	* @param rotate - command report parameter
	*/
	void SetReport(bool);
};
