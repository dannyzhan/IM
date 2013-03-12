
// IMDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "..//IPWorks//include//ipworks.h"
#include "IMGlobal.h"
#include "Resource.h"

#include <string>

// CIMDlg dialog
class CIMDlg : public CDialog
{
// Construction
public:
	CIMDlg(CWnd* pParent = NULL);	// standard constructor
    std::string getUserName();
    std::string getPassword();
    void reset();

// Dialog Data
	enum { IDD = IDD_IM_DIALOG };

    afx_msg LRESULT handleConnected(WPARAM wParam, LPARAM lParam); 

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implemen tation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
    void OnCancel();
    void PostNcDestroy();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
    //afx_msg LRESULT handleConnected(WPARAM wParam, LPARAM lParam); 
    afx_msg LRESULT handleDisConnected(WPARAM wParam, LPARAM lParam); 

	DECLARE_MESSAGE_MAP()
public:
	CString csUserName;
	CString csPwd;
	afx_msg void LoginClick();
};
