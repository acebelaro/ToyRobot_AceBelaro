
// ToyRobotMfc.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CToyRobotMfcApp:
// See ToyRobotMfc.cpp for the implementation of this class
//

class CToyRobotMfcApp : public CWinApp
{
public:
	CToyRobotMfcApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CToyRobotMfcApp theApp;
