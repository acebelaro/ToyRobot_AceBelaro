
// ToyRobotMfcDlg.h : header file
//

#pragma once

#include <memory>
#include "command_parser.hpp"
#include "Board.h"
#include "id.h"

// CToyRobotMfcDlg dialog
class CToyRobotMfcDlg : public CDialogEx
{
// Construction
public:
	CToyRobotMfcDlg(CWnd* pParent = nullptr);	// standard constructor
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TOYROBOTMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()

private:
	Robot _robot;
	CommandParser _commandParser;

	// UI
	CBoard _board;
	CEdit _edtCommandInput;
	CEdit _edtCommandResponse;

	void ExecuteCommand();
public:
	afx_msg void OnBtnClickedTile(UINT nID);
};
