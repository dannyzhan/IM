// ChatPanel.cpp : implementation file
//

#include "stdafx.h"
#include "IM.h"
#include "ChatPanel.h"
#include "IMProtocol.h"
#include "UserListPanel.h"


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
	DDX_Control(pDX, IDC_CHAT_HISTORY, m_ChatHistory);
	DDX_Control(pDX, IDC_BTN_FONT, m_btnChatFont);
	DDX_Control(pDX, IDC_CHAT_INPUT, m_Input);
}


BEGIN_MESSAGE_MAP(CChatPanel, CDialog)
	ON_BN_CLICKED(IDC_BTN_SEND, &CChatPanel::OnBnClickedBtnSend)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_FONT, &CChatPanel::OnBnClickedBtnFont)
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
				m_Input.SetWindowText("");
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
	memset(&m_ChatFontFormat, 0, sizeof(m_ChatFontFormat));
	memset(&m_ChatFontFormatBk, 0, sizeof(m_ChatFontFormatBk));
	m_ChatFontFormat.cbSize = sizeof(m_ChatFontFormat);
	m_ChatFontFormatBk.cbSize = sizeof(m_ChatFontFormatBk);
	m_ChatHistory.GetSelectionCharFormat(m_ChatFontFormatBk);
	m_ChatHistory.GetSelectionCharFormat(m_ChatFontFormat);
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
	if (strUser == "I")
	{
		m_ChatHistory.SetSelectionCharFormat(m_ChatFontFormat);
	}
	else
	{
		m_ChatHistory.SetSelectionCharFormat(m_ChatFontFormatBk);
	}

	m_ChatHistory.SetSel(-1, -1);
	m_ChatHistory.ReplaceSel(formatMsg);
}

void CChatPanel::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnClose();
	CUserListPanel* userListPanel = (CUserListPanel*)GetParent();
	userListPanel->CloseChatWindow(m_strChatUser);
}

void CChatPanel::OnBnClickedBtnFont()
{
	// TODO: Add your control notification handler code here
	CFontDialog fontDlg(m_ChatFontFormat);
	fontDlg.DoModal();
	fontDlg.GetCharFormat(*(CHARFORMAT*)&m_ChatFontFormat);
	m_Input.SetDefaultCharFormat(m_ChatFontFormat);
}
