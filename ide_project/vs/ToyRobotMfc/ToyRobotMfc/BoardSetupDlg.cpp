// BoardSetup.cpp : implementation file
//

#include "pch.h"
#include "ToyRobotMfc.h"
#include "afxdialogex.h"
#include "BoardSetupDlg.h"
#include "id.h"
#include <regex>

using namespace std;

// CBoardSetup dialog

IMPLEMENT_DYNAMIC(CBoardSetupDlg, CDialogEx)

CBoardSetupDlg::CBoardSetupDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BOARD_SETUP_DIALOG, pParent)
{
	_nWidth = -1;
	_nHeight = -1;

	tabMap.insert(make_pair(&_edtWidth, &_edtHeight));
	tabMap.insert(make_pair(&_edtHeight, &_edtWidth));
}

CBoardSetupDlg::~CBoardSetupDlg()
{
}

void CBoardSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBoardSetupDlg, CDialogEx)
	ON_BN_CLICKED(ID_BOARD_SETUP_OK_BUTTON,&CBoardSetupDlg::OnBtnClickedOk)
	ON_EN_CHANGE(ID_BOARD_SETUP_WIDTH_EDIT,&CBoardSetupDlg::OnCEditChangeWidth)
	ON_EN_CHANGE(ID_BOARD_SETUP_HEIGHT_EDIT, &CBoardSetupDlg::OnCEditChangeHeight)
END_MESSAGE_MAP()

BOOL CBoardSetupDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	const int labelWidth = 60;
	const CSize labelSize(labelWidth, 25);
	const CSize edtSize(70, 25);
	const int edtX = labelWidth + 5;

	const int x = 10;
	int y = x;
	_labelWidth.Create(
		_T("Width:"),
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_NOHIDESEL,
		CRect(CPoint(x, y + 3), labelSize),
		this,
		ID_BOARD_SETUP_WIDTH_LABEL);
	_edtWidth.Create(
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_NOHIDESEL,
		CRect(CPoint(edtX, y), edtSize),
		this,
		ID_BOARD_SETUP_WIDTH_EDIT);

	y += 30;
	_labelHeight.Create(
		_T("Height:"),
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_NOHIDESEL,
		CRect(CPoint(x, y + 3), labelSize),
		this,
		ID_BOARD_SETUP_HEIGHT_LABEL);
	_edtHeight.Create(
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_NOHIDESEL,
		CRect(CPoint(edtX, y), edtSize),
		this,
		ID_BOARD_SETUP_HEIGHT_EDIT);

	y += 30;
	const CSize btnSize(labelSize.cx + edtSize.cx, 25);
	_btnOk.Create(
		_T("OK"),
		WS_CHILD | WS_VISIBLE,
		CRect(CPoint(x, y), btnSize),
		this,
		ID_BOARD_SETUP_OK_BUTTON);

	const int windowWidth = btnSize.cx + 35;
	const int windowHeight = y + 75;

	SetWindowPos(NULL, 0, 0, windowWidth, windowHeight, SWP_NOMOVE | SWP_NOZORDER);

	GotoDlgCtrl(GetDlgItem(ID_BOARD_SETUP_WIDTH_EDIT));

	return FALSE;
}

BOOL CBoardSetupDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			OnBtnClickedOk();
			return TRUE; // Do not process further
		}
		else if (pMsg->wParam == VK_ESCAPE)
		{
			EndDialog(IDCANCEL);
			return TRUE; // Do not process further                
		}
		else if (pMsg->wParam == VK_TAB)
		{
			CWnd* wndToFocus = nullptr;
			CWnd* currentWndFocus = GetFocus();
			if (nullptr != currentWndFocus)
			{
				auto wndTabPair = find_if(
					tabMap.begin(),
					tabMap.end(),
					[currentWndFocus](const auto& it) {
						return it.first == currentWndFocus;
					});
				if (tabMap.end() != wndTabPair)
				{
					wndToFocus = wndTabPair->second;
				}
				else
				{
					wndToFocus = &_edtWidth;
				}
			}
			else
			{
				wndToFocus = &_edtWidth;
			}
			if (nullptr != wndToFocus)
			{
				GotoDlgCtrl(wndToFocus);
			}
			return TRUE;
		}
	}

	return CWnd::PreTranslateMessage(pMsg);
}

// CBoardSetup message handlers

void CBoardSetupDlg::OnBtnClickedOk()
{
	LPCTSTR errText = nullptr;

	if (_nWidth <= 0)
	{
		errText = _T("Invalid width!");
	}
	else if (_nHeight <= 0)
	{
		errText = _T("Invalid height!");
	}
	else
	{
		if ((_nWidth * _nHeight) <= TILE_BUTTON_COUNT)
		{
			EndDialog(IDOK);
		}
		else
		{
			errText = _T("Width and height results to exceed tile count!");
		}
	}
	if (nullptr != errText)
	{
		AfxMessageBox(errText, MB_OK | MB_ICONSTOP);
	}
}

void CBoardSetupDlg::OnCEditChangeWidth()
{
	SizeEdit(_nWidth, _edtWidth);
}

void CBoardSetupDlg::OnCEditChangeHeight()
{
	SizeEdit(_nHeight, _edtHeight);
}

void CBoardSetupDlg::SizeEdit(int& s, CEdit& edt)
{
	CString valStr;
	edt.GetWindowText(valStr);

	string w = CT2A(valStr);
	if (w.length() > 0)
	{
		regex rgx("^([0-9]+)$", regex_constants::icase);
		smatch match;
		if (regex_search(w, match, rgx))
		{
			s = stoi(match[1]);
		}
		else
		{
			if (s == -1)
			{
				edt.SetWindowTextW(_T(""));
			}
			else
			{
				CString t;
				t.Format(_T("%d"), s);
				edt.SetWindowTextW(t);
			}
		}
	}
}

int CBoardSetupDlg::GetWidth() const
{
	return _nWidth;
}

int CBoardSetupDlg::GetHeight() const
{
	return _nHeight;
}
