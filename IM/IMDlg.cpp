
// IMDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IM.h"
#include "IMDlg.h"
#include "IMProtocol.h"
#include <string>
#include "Event.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIMDlg dialog
CIMDlg::CIMDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIMDlg::IDD, pParent)
	, csUserName(_T(""))
	, csPwd(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UN, csUserName);
	DDX_Text(pDX, IDC_EDIT_PWD, csPwd);
}

BEGIN_MESSAGE_MAP(CIMDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CIMDlg::LoginClick)
    ON_MESSAGE(EVT_CONNECTED, &CIMDlg::handleConnected)
    ON_MESSAGE(EVT_DISCONNECTED, &CIMDlg::handleDisConnected)
    
END_MESSAGE_MAP()


// CIMDlg message handlers

BOOL CIMDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIMDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CIMDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CIMDlg::LoginClick()
{
	// TODO: Add your control notification handler code here
	//OnOK();
	UpdateData(TRUE);

    
    AfxGetApp()->PostThreadMessage(EVT_USER_LOGIN, 0, 0);
}

LRESULT CIMDlg::handleConnected(WPARAM wParam, LPARAM lParam)
{
    // Connect successfully
    ShowWindow(SW_HIDE);
    CIMApp* app = (CIMApp*)::AfxGetApp();
    app->ShowUserList();
    return 0;
}

LRESULT CIMDlg::handleDisConnected(WPARAM wParam, LPARAM lParam)
{
    // Failed to connect to server
    AfxMessageBox(_T("Wrong user name or password, please retry again!"));

    csUserName = _T("");
    csPwd = _T("");
    UpdateData(FALSE);

    return 0;
}

void CIMDlg::OnCancel()
{
    DestroyWindow();
}

void CIMDlg::PostNcDestroy()
{
    CDialog::PostNcDestroy();
    delete this;
}

std::string CIMDlg::getUserName()
{
    return (LPTSTR)(LPCTSTR)csUserName;
}

std::string CIMDlg::getPassword()
{
    return (LPTSTR)(LPCTSTR)csPwd;
}

void CIMDlg::reset()
{
    csUserName = _T("");
    csPwd = _T("");
    UpdateData(FALSE);

    GetDlgItem(IDC_EDIT_UN)->SetFocus();
}