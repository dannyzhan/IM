
// IM.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "IMProtocol.h"
#include "UserListPanel.h"

// CIMApp:
// See IM.cpp for the implementation of this class
//

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
};

extern CIMApp theApp;