// UserListPanel.cpp : implementation file
//

#include "stdafx.h"
#include "IM.h"
#include "UserListPanel.h"
#include "ChatPanel.h"

#include "Swiften.h"

#include <algorithm>


// CUserListPanel dialog

IMPLEMENT_DYNAMIC(CUserListPanel, CDialog)

CUserListPanel::CUserListPanel(CWnd* pParent /*=NULL*/)
	: CDialog(CUserListPanel::IDD, pParent)
{

}

CUserListPanel::~CUserListPanel()
{
}

void CUserListPanel::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_USER, m_userList);
}


BEGIN_MESSAGE_MAP(CUserListPanel, CDialog)
    ON_WM_SIZE()
    ON_LBN_DBLCLK(IDC_LIST_USER, &CUserListPanel::OnLbnDblclkListUser)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CUserListPanel message handlers

BOOL CUserListPanel::OnInitDialog()
{
    CDialog::OnInitDialog();

    CRect clientRect;
    GetClientRect(clientRect);
    m_oldSize = CSize(clientRect.Width(), clientRect.Height());

    return FALSE; 
}

void CUserListPanel::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    if (cx <= 1 || cy <=1) return;

    if (NULL == m_userList.m_hWnd) return;
    CRect listRect;
    m_userList.GetWindowRect(listRect);
    this->ScreenToClient(listRect);
    m_userList.MoveWindow(listRect.left, listRect.top, 
        listRect.Width() + cx - m_oldSize.cx,
        listRect.Height() + cy - m_oldSize.cy);
    m_oldSize = CSize(cx, cy);
}

void CUserListPanel::OnLbnDblclkListUser()
{
    CString curUserName;
    m_userList.GetText(m_userList.GetCurSel(), curUserName);
    CChatPanel* chatPanel = new CChatPanel(curUserName);
	chatPanel->Create(CChatPanel::IDD, this);
	chatPanel->ShowWindow(SW_SHOW);
	m_userList.SetItemData(m_userList.GetCurSel(), (DWORD_PTR)chatPanel);
}

void CUserListPanel::UpdateBuddy(IMEvent* event)
{
	if (event->Type() == IMEvent::kSync)
	{
		IMEventSync* ev = (IMEventSync*)event;
		std::vector<Buddy>::iterator buddy;
		for (buddy = ev->Buddies.begin(); buddy != ev->Buddies.end(); ++buddy)
		{
			if (m_userList.FindString(-1, buddy->Jid.c_str()) == -1)
			{
				m_userList.AddString(buddy->Jid.c_str());
			}
		}
	}
	else if (event->Type() == IMEvent::kPresence)
	{
	}
}

void CUserListPanel::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnClose();
	CIMApp* app = (CIMApp*)::AfxGetApp();
	app->ExitApp();
}

void CUserListPanel::UpdateMessage(IMEvent* event)
{
	IMEventMessage* ev = (IMEventMessage*)event;
	CString userName = ev->From.c_str();
	int index = m_userList.FindString(-1, userName);
	if (index != -1)
	{
		CChatPanel* chatChanel = NULL;
		DWORD_PTR itemData = m_userList.GetItemData(index);
		if (itemData) 
		{
			chatChanel = (CChatPanel*)itemData;
		}
		else
		{
			chatChanel = new CChatPanel(userName);
			chatChanel->Create(CChatPanel::IDD, this);
			chatChanel->ShowWindow(SW_SHOW);
		}
		if (chatChanel)
		{
			chatChanel->MessageIn(ev->MessageText.c_str());
		}
	}
}

void CUserListPanel::CloseChatWindow(CString strUser)
{
	int index = m_userList.FindString(-1, strUser);
	if (index != -1)
	{
		DWORD_PTR itemData = m_userList.GetItemData(index);
		if (itemData) 
		{
			delete (CChatPanel*)itemData;
			m_userList.SetItemData(index, NULL);
		}
	}
}

void CUserListPanel::AddJID(Swift::JID& jid, std::string& name)
{
    bool exist = false;
    std::map<Swift::JID, std::string>::iterator itr = m_rosterMap.begin();
    for (; itr != m_rosterMap.end(); ++itr)
    {
       if (itr->first == jid) 
       {
           exist = true; 
           break;
       }
    }

    if (!exist)
    {
        m_userList.AddString(name.c_str());
        m_rosterMap[jid] = name;
    }

//     m_rosterMap[jid] = name;
//     std::map<Swift::JID, std::string>::iterator itrS = m_rosterMap.begin();
//     std::map<Swift::JID, std::string>::iterator itrE = m_rosterMap.end();
//     std::map<Swift::JID, std::string>::iterator find = std::find(itrS, itrE, 100);
//     if (find != NULL)
//     {
// 
//     }
}
