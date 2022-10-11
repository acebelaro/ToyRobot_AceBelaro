//******************************************************************************
/*! @file       command.cpp
	@brief      Source definition for command
*/
//******************************************************************************
#include "command.hpp"

//******************************************************************************
//               Class function definition
//******************************************************************************

CCommand::CCommand()
{
	m_isPlace = false;
	m_isMove = false;
	m_rotate = CRotate::NONE;
	m_doReport = false;
}

CCommand::~CCommand()
{
	// Do nothing
}

bool CCommand::IsPlace() {
	return m_isPlace;
}

void CCommand::SetPlacement(stPlacement placement) {
	m_isPlace = true;
	m_placement = placement;
}

stPlacement CCommand::GetPlacement() {
	return m_placement;
}

void CCommand::SetMove(bool move) {
	m_isMove = move;
}

bool CCommand::IsMove() {
	return m_isMove;
}

void CCommand::SetRotate(CRotate rotate) {
	m_rotate = rotate;
}

CRotate CCommand::GetRotate() {
	return m_rotate;
}

bool CCommand::DoReport() {
	return m_doReport;
}

void CCommand::SetReport(bool report)
{
	m_doReport = report;
}
