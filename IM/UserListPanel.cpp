// UserListPanel.cpp : implementation file
//

#include "stdafx.h"
#include "IM.h"
#include "UserListPanel.h"
#include "ChatPanel.h"


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
END_MESSAGE_MAP()


// CUserListPanel message handlers

BOOL CUserListPanel::OnInitDialog()
{
    CDialog::OnInitDialog();

    CRect clientRect;
    GetClientRect(clientRect);
    m_oldSize = CSize(clientRect.Width(), clientRect.Height());

    const int userCount = 10;
    CString username;
    for (int i = 0; i < userCount; ++i)
    {
        username.Format(_T("User %d"), i + 1);
        m_userList.AddString(username);
    }

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
	CString strTitle = CString("Chat with ") + curUserName;
    CChatPanel chatPanel(curUserName);
	chatPanel.DoModal();
}
