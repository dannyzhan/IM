#pragma once
#include "afxwin.h"


// CUserListPanel dialog

class CUserListPanel : public CDialog
{
	DECLARE_DYNAMIC(CUserListPanel)

public:
	CUserListPanel(CWnd* pParent = NULL);   // standard constructor
	virtual ~CUserListPanel();

// Dialog Data
	enum { IDD = IDD_DIALOG_USERLIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnLbnDblclkListUser();
    CListBox m_userList;
    CSize    m_oldSize;
};
