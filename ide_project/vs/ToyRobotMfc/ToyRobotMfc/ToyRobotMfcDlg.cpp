
// ToyRobotMfcDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "ToyRobotMfc.h"
#include "ToyRobotMfcDlg.h"
#include "BoardSetupDlg.h"
#include "afxdialogex.h"

#include <sstream>
#include <algorithm>
#include <WinUser.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CToyRobotMfcDlg dialog



CToyRobotMfcDlg::CToyRobotMfcDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TOYROBOTMFC_DIALOG, pParent)
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
	ON_CONTROL_RANGE(BN_CLICKED, ID_TILE_BUTTON, ID_TILE_BUTTON_MAX, &CToyRobotMfcDlg::OnBtnClickedTile)
END_MESSAGE_MAP()


// CToyRobotMfcDlg message handlers

BOOL CToyRobotMfcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CBoardSetupDlg boardSetupDlg(this);
	INT_PTR nResponse = boardSetupDlg.DoModal();
	int width, height;
	if (nResponse == IDOK)
	{
		width = boardSetupDlg.GetWidth();
		height = boardSetupDlg.GetHeight();
	}
	else
	{
		// default
		width = DEFAULT_WIDTH;
		height = DEFAULT_HEIGHT;
	}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	_board.SetWidth(width);
	_board.SetHeight(height);
	_board.Create(this);

	const int margin = 10;
	const int tileSize = TILE_SIZE;
	const int windowWidth = (tileSize * width) + 15 + (2 * margin);

	const int edtWidth = windowWidth - (15 + (2 * margin));
	const int commandInputHeight = 35;
	int editY = (tileSize * height) + 20;
	_edtCommandInput.Create(
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_NOHIDESEL,
		CRect(CPoint(margin, editY), CSize(edtWidth, commandInputHeight)),
		this,
		ID_COMMAND_INPUT);

	editY += 40;
	const int commandResponseHeight = 70;
	_edtCommandResponse.Create(
		ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_NOHIDESEL | ES_READONLY,
		CRect(CPoint(margin, editY), CSize(edtWidth, commandResponseHeight)),
		this,
		ID_COMMAND_RESPONSE);

	const int windowHeight = editY + 130;
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
			}
			return TRUE; // Do not process further
		}
		else if (GetKeyState(VK_CONTROL) & 0x80)
		{
			if (_robot.IsPlaced())
			{
				bool handled = true;
				switch (pMsg->wParam)
				{
				case 'M':
					// CTRL + M
					_robot.Move(_board);
					break;
				case 'R':
					// CTRL + R
					_robot.RotateRight();
					break;
				case 'L':
					// CTRL + L
					_robot.RotateLeft();
					break;
				default:
					handled = false;
					break;
				}
				if (handled)
				{
					_board.DisplayRobot(_robot);
				}
			}
			return TRUE; // Do not process further
		}
		else if (pMsg->wParam == VK_ESCAPE)
		{
			return TRUE; // Do not process further                
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

	if (!command.empty())
	{
		UPTR_COMMAND cmd;
		res = _commandParser.parseCommand(command, cmd);

		// redirect output to original
		cout.rdbuf(stream_buffer_cout);

		stringstream response;
		if (res)
		{
			cmd->Execute(_robot, _board);

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
}

void CToyRobotMfcDlg::OnBtnClickedTile(UINT nID)
{
	if (_robot.IsPlaced() && _board.IsRobotTileClicked(nID))
	{
		_robot.Move(_board);
		_board.DisplayRobot(_robot);
	}
}
