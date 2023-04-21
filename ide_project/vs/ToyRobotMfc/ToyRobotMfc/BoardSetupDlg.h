#pragma once
#include "afxdialogex.h"

#include <map>

using namespace std;

#define DEFAULT_WIDTH	5
#define DEFAULT_HEIGHT	5

// CBoardSetup dialog

class CBoardSetupDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBoardSetupDlg)

public:
	CBoardSetupDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CBoardSetupDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BOARD_SETUP_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBtnClickedOk();
	afx_msg void OnCEditChangeWidth();
	afx_msg void OnCEditChangeHeight();
	int GetWidth() const;
	int GetHeight() const;

private:
	map<CWnd*, CWnd*> tabMap;
	int _nWidth;
	int _nHeight;

	CStatic _labelWidth;
	CEdit _edtWidth;
	CStatic _labelHeight;
	CEdit _edtHeight;
	CButton _btnOk;

	void SizeEdit(int&, CEdit&);
};
