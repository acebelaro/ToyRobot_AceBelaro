
// ToyRobotMfcDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "ToyRobotMfc.h"
#include "ToyRobotMfcDlg.h"
#include "afxdialogex.h"
#include <sstream>
#include <algorithm>
#include <WinUser.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CToyRobotMfcDlg dialog



CToyRobotMfcDlg::CToyRobotMfcDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TOYROBOTMFC_DIALOG, pParent),
	_table(TABLE_SIZE, TABLE_SIZE),
	_commandParser(_robot, _table),
	_board(TABLE_SIZE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CToyRobotMfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CToyRobotMfcDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CToyRobotMfcDlg message handlers

BOOL CToyRobotMfcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	_board.Create(this);

	int windowWidth = 10 + ((5 + TILE_SIZE) * TABLE_SIZE);

	int editY = ((5 + TILE_SIZE) * TABLE_SIZE);
	int edtWidth = windowWidth - 35;

	_edtCommandInput.Create(
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_NOHIDESEL,
		CRect(CPoint(10, editY), CSize(edtWidth, 35)),
		this,
		ID_COMMAND_INPUT);

	editY += 40;
	_edtCommandResponse.Create(
		ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_NOHIDESEL | ES_READONLY,
		CRect(CPoint(10, editY), CSize(edtWidth, 70)),
		this,
		ID_COMMAND_RESPONSE);

	int windowHeight = editY + 130;
	SetWindowPos(NULL, 0, 0, windowWidth, windowHeight, SWP_NOMOVE | SWP_NOZORDER);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CToyRobotMfcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CToyRobotMfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CToyRobotMfcDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			if (GetFocus() == &_edtCommandInput)
			{
				ExecuteCommand();
				return TRUE;
			}
			else
			{
				return TRUE;
			}
		}
		else if (pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;                // Do not process further
		}
	}

	return CWnd::PreTranslateMessage(pMsg);
}

void CToyRobotMfcDlg::ExecuteCommand()
{
	CString sWindowText;
	string command;
	bool res;
	ostringstream strCout;
	streambuf* stream_buffer_cout;

	// redirect output
	stream_buffer_cout = cout.rdbuf();
	cout.rdbuf(strCout.rdbuf());
	strCout.clear();

	// get command
	_edtCommandInput.GetWindowText(sWindowText);
	command = CT2A(sWindowText);

	res = _commandParser.parseCommand(command);

	// redirect output to original
	cout.rdbuf(stream_buffer_cout);

	stringstream response;
	if (res)
	{
		_board.DisplayRobot(_robot);
		string cmdParserResponse = strCout.str();
		if (!cmdParserResponse.empty())
		{
			response << strCout.str();
		}
		else

		{
			response << "-";
		}
	}
	else
	{
		response << "Invalid command";
	}

	stringstream responseLines;
	responseLines << "Command Input: " << command << "\r\n"
		<< "App Response : " << response.str() << endl;
	_edtCommandResponse.SetWindowTextW(CString(responseLines.str().c_str()));

	// clear command input
	_edtCommandInput.SetWindowTextW(_T(""));
}
