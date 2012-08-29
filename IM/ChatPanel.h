#pragma once
#include "afxwin.h"


// CChatPanel dialog

class CChatPanel : public CDialog
{
	DECLARE_DYNAMIC(CChatPanel)

public:
	CChatPanel(CString strUser, CWnd* pParent = NULL);   // standard constructor
	virtual ~CChatPanel();

// Dialog Data
	enum { IDD = IDD_CHAT_PANEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnBnClickedBtnSend();
private:
	CEdit m_Input;
	CEdit m_ChatHistory;
	CString m_strChatUser;
public:
	virtual BOOL OnInitDialog();
};
