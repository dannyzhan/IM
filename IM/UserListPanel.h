#pragma once
#include "afxwin.h"

#include <map>


// CUserListPanel dialog
namespace Swift
{
    class JID;
}

class CUserListPanel : public CDialog
{
	DECLARE_DYNAMIC(CUserListPanel)

public:
	CUserListPanel(CWnd* pParent = NULL);   // standard constructor
	virtual ~CUserListPanel();

    void AddJID(Swift::JID& jid, std::string& name);

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
	void UpdateBuddy(IMEvent* event);
	void UpdateMessage(IMEvent* event);
	void CloseChatWindow(CString strUser);
	afx_msg void OnClose();

private:
    std::map<Swift::JID, std::string> m_rosterMap;
};
