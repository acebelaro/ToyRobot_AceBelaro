
// ToyRobotMfcDlg.h : header file
//

#pragma once

#include "command_parser.hpp"

#define TABLE_SIZE 5
#define TILE_SIZE 70

enum
{
	EDIT_INPUT_COMMAND = 1000,
	EDIT_OUTPUT
};

// CToyRobotMfcDlg dialog
class CToyRobotMfcDlg : public CDialogEx
{
// Construction
public:
	CToyRobotMfcDlg(CWnd* pParent = nullptr);	// standard constructor
	~CToyRobotMfcDlg();
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
	Table _table;
	CommandParser _commandParser;

	// UI
	vector<CStatic*> _tiles;
	CEdit _edtCommandInput;
	CEdit _edtCommandResponse;

	void ExecuteCommand();
};
