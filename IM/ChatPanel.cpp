// ChatPanel.cpp : implementation file
//

#include "stdafx.h"
#include "IM.h"
#include "ChatPanel.h"
#include "IMProtocol.h"


// CChatPanel dialog

IMPLEMENT_DYNAMIC(CChatPanel, CDialog)

CChatPanel::CChatPanel(CString strUser, CWnd* pParent /*=NULL*/)
	: CDialog(CChatPanel::IDD, pParent)
{
	m_strChatUser = strUser;
}

CChatPanel::~CChatPanel()
{
}

void CChatPanel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHAT_INPUT, m_Input);
	DDX_Control(pDX, IDC_CHAT_HISTORY, m_ChatHistory);
}


BEGIN_MESSAGE_MAP(CChatPanel, CDialog)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CChatPanel::OnBnClickedBtnClose)
	ON_BN_CLICKED(IDC_BTN_SEND, &CChatPanel::OnBnClickedBtnSend)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CChatPanel message handlers

void CChatPanel::OnBnClickedBtnClose()
{
	// TODO: Add your control notification handler code here
	EndDialog(0);
}

void CChatPanel::OnBnClickedBtnSend()
{
	// TODO: Add your control notification handler code here
	CString strMessage;
	m_Input.GetWindowText(strMessage);
	if (!strMessage.IsEmpty())
	{
		CIMApp* app = (CIMApp*)::AfxGetApp();
		if (app->Client())
		{
			if (app->Client()->SendMessage(strMessage.GetBuffer(0), m_strChatUser.GetBuffer(0)))
			{
				AppendChatHistory(strMessage, "I");
				m_Input.Clear();
			}
			else
			{
				CString msg;
				msg.Format(_T("Can not send message to %s"), m_strChatUser);
				MessageBox(msg);
			}
		}

	}
}

BOOL CChatPanel::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CString strTitle = CString("Chat with ") + m_strChatUser;
	SetWindowText(strTitle);
	m_Input.SetFocus();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CChatPanel::MessageIn(CString strMessage)
{
	AppendChatHistory(strMessage, m_strChatUser);
}

void CChatPanel::AppendChatHistory(CString strMessage, CString strUser)
{
	CTime currentTime = CTime::GetCurrentTime();
	CString strTime = currentTime.Format("%H:%M:%S") + " ";
	CString formatMsg = strTime + strUser + CString(" says: ") + strMessage + "\r\n";
	int length = m_ChatHistory.GetWindowTextLength();
	m_ChatHistory.SetSel(length, length);
	m_ChatHistory.ReplaceSel(formatMsg);
}

void CChatPanel::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnClose();
	CUserListPanel* userListPanel = (CUserListPanel*)GetParent();
	userListPanel->CloseChatWindow(m_strChatUser);
}
