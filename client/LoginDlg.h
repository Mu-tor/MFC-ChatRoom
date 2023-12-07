#if !defined(AFX_LOGINDLG_H__951159FB_AE9B_41B8_9974_8642E205681F__INCLUDED_)
#define AFX_LOGINDLG_H__951159FB_AE9B_41B8_9974_8642E205681F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoginDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// LoginDlg dialog

class LoginDlg : public CDialog
{
// Construction
public:
	SOCKET clsoc;
	CString name;
	int error;//ÃÜÂë´íÎó´ÎÊý
	LoginDlg(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(LoginDlg)
	enum { IDD = IDD_Login };
	CEdit	m_password;
	CEdit	m_name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LoginDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(LoginDlg)
	afx_msg void OnLogin();
	//afx_msg void OnSignin();
	afx_msg void OnSignin();
	afx_msg void OnForget();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGINDLG_H__951159FB_AE9B_41B8_9974_8642E205681F__INCLUDED_)
