
// IM.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "IMProtocol.h"

// CIMApp:
// See IM.cpp for the implementation of this class
//

class CIMDlg;
class CUserListPanel;
class CIMApp : public CWinAppEx, IMEventHandler
{
public:
	CIMApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
private:
	IMProtocol* m_pClient;
    CIMDlg*     m_pLoginDlg;
	CUserListPanel* m_pUserList;
	HANDLE m_hExit;
public:
	IMProtocol* Client(void);
	void ExitApp(void);
	void ShowUserList(void);
	void UpdateBuddyList(IMEvent* event);
	void UpdateBuddyState(IMEvent* event);
	void UpdateMessage(IMEvent* event);
	virtual bool Handler(IMEvent *event);

    afx_msg void OnLogin( WPARAM, LPARAM );
    afx_msg void OnConnected(WPARAM wParam, LPARAM lParam);
    afx_msg void OnDisConnected(WPARAM wParam, LPARAM lParam);
    afx_msg void OnJIDAdded(WPARAM wParam, LPARAM lParam);
};

extern CIMApp theApp;