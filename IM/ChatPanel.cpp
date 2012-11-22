// ChatPanel.cpp : implementation file
//

#include "stdafx.h"
#include "IM.h"
#include "ChatPanel.h"
//#include "IMSwiften.h"


// CChatPanel dialog

IMPLEMENT_DYNAMIC(CChatPanel, CDialog)

CChatPanel::CChatPanel(CString strUser, CWnd* pParent /*=NULL*/)
	: CDialog(CChatPanel::IDD, pParent)
{
	m_strChatUser = strUser;
	//m_pImCore = new IMSwiften;
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
		globalJabber.SetMessageText(strMessage);
		globalJabber.SendMessage(m_strChatUser);

		strMessage = "\r\n I said:" + strMessage;
		int length = m_ChatHistory.GetWindowTextLength();
		m_ChatHistory.SetSel(length, length);
		m_ChatHistory.ReplaceSel(strMessage);
		m_Input.Clear();	

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
