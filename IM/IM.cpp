
// IM.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "IM.h"
#include "IMDlg.h"
#include "UserListPanel.h"
#include "IMProtocol.h"
#include "MainFrame.h"
#include "Event.h"
#include "MsgReactor.h"

#include <boost/thread/thread.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIMApp

BEGIN_MESSAGE_MAP(CIMApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
    ON_THREAD_MESSAGE(EVT_USER_LOGIN, &CIMApp::OnLogin)
    ON_THREAD_MESSAGE(EVT_CONNECTED, &CIMApp::OnConnected)
    ON_THREAD_MESSAGE(EVT_DISCONNECTED, &CIMApp::OnDisConnected)
    ON_THREAD_MESSAGE(EVT_ROSTER_ADD_JID, &CIMApp::OnJIDAdded)
END_MESSAGE_MAP()


// CIMApp construction

CIMApp::CIMApp()
: m_pClient(NULL)
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIMApp object

CIMApp theApp;

extern IMProtocol* Create();
extern void Destroy(IMProtocol*);
// CIMApp initialization

BOOL CIMApp::InitInstance()
{
//TODO: call AfxInitRichEdit2() to initialize richedit2 library.
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	AfxInitRichEdit2();
	CWinAppEx::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	m_hExit = CreateEvent(NULL, FALSE, FALSE, NULL);

//     CMainFrame *pFrame = new CMainFrame;
//     if (!pFrame->Create(NULL, _T("IM")))
//         return FALSE;
//     pFrame->ShowWindow(SW_HIDE);
//     pFrame->UpdateWindow();
//     m_pMainWnd = pFrame;
    m_pLoginDlg = new CIMDlg;
    if (!m_pLoginDlg->Create(CIMDlg::IDD, NULL))
        return FALSE;

    m_pMainWnd = m_pLoginDlg;
    m_pLoginDlg->ShowWindow(SW_SHOW);
    return TRUE;

// 	m_pClient = Create();
// 	m_pClient->EventHandler(this);
// 	CIMDlg dlg;
// 	m_pUserList = new CUserListPanel;
// 	m_pUserList->Create(CUserListPanel::IDD, &dlg);
// 	m_pMainWnd = &dlg;
// 	INT_PTR nResponse = dlg.DoModal();
// 	if (nResponse == IDOK)
// 	{
// 
// 	}
// 	else if (nResponse == IDCANCEL)
// 	{
// 		// TODO: Place code here to handle when the dialog is
// 		//  dismissed with Cancel
// 	}
// 	delete m_pUserList;
// 	Destroy(m_pClient);
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	//return FALSE;
}

IMProtocol* CIMApp::Client(void)
{
	return m_pClient;
}

void CIMApp::UpdateBuddyList(IMEvent* event)
{
	if (m_pUserList)
	{
		m_pUserList->UpdateBuddy(event);
	}
}

void CIMApp::UpdateBuddyState(IMEvent* event) 
{
	if (m_pUserList)
	{
		m_pUserList->UpdateBuddy(event);
	}
}

void CIMApp::UpdateMessage(IMEvent* event)
{
	if (m_pUserList)
	{
		m_pUserList->UpdateMessage(event);
	}
}

bool CIMApp::Handler(IMEvent *event)
{
	if (event->Type() == IMEvent::kPresence) 
	{
		UpdateBuddyState(event);
	}
	else if (event->Type() == IMEvent::kSync) 
	{
		UpdateBuddyList(event);
	}
	else if (event->Type() == IMEvent::kMessageIn)
	{
		UpdateMessage(event);
	}
	EventFactory<IMEvent>::DEL(event);
	return true;
}

void CIMApp::ShowUserList()
{
	m_pUserList->ShowWindow(SW_SHOW);
}

void CIMApp::ExitApp()
{
	m_pMainWnd->DestroyWindow();
}

void CIMApp::OnLogin(WPARAM wparam, LPARAM lparam)
{
    std::string username = m_pLoginDlg->getUserName();
    std::string password = m_pLoginDlg->getPassword();
    boost::thread msgThread(XMPPMsgReactor(username, password));
    msgThread.timed_join(boost::posix_time::seconds(1));
}

void CIMApp::OnConnected(WPARAM wparam, LPARAM lparam)
{
    m_pLoginDlg->ShowWindow(SW_HIDE);

    m_pUserList = new CUserListPanel;
    m_pUserList->Create(CUserListPanel::IDD);
    m_pUserList->SetWindowText(m_pLoginDlg->getUserName().c_str());
    m_pMainWnd = m_pUserList;
    m_pUserList->ShowWindow(SW_SHOW);
}

void CIMApp::OnDisConnected(WPARAM wparam, LPARAM lparam)
{
    AfxMessageBox(_T("Your input is incorrect, please input again!"));

    m_pLoginDlg->reset();
}

void CIMApp::OnJIDAdded(WPARAM wparam, LPARAM lparam)
{
    Swift::JID* jid = (Swift::JID*)(wparam);
    std::string* nickname = (std::string*)(lparam);
    m_pUserList->AddJID(*jid, *nickname);
}