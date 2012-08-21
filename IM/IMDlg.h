
// IMDlg.h : header file
//

#pragma once
#include "afxwin.h"

// CIMDlg dialog
class CIMDlg : public CDialog
{
// Construction
public:
	CIMDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_IM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString csUserName;
	CString csPwd;
	afx_msg void LoginClick();

	CStatic staticLoginMessage;
private:
	bool Login(CString &user, CString &pwd);
	void ShowChatDialog();
};
