#if !defined(AFX_SIGNINDLG_H__D3ED66CC_5DE9_4C94_A584_C658FCDED342__INCLUDED_)
#define AFX_SIGNINDLG_H__D3ED66CC_5DE9_4C94_A584_C658FCDED342__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SigninDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SigninDlg dialog

class SigninDlg : public CDialog
{
// Construction
public:
	SOCKET clsoc;	
	char code[5];
	SigninDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SigninDlg)
	enum { IDD = IDD_Signin };
	CEdit	m_code2;
	CEdit	m_code1;
	CComboBox	m_question;
	CEdit	m_encrypted;
	CEdit	m_password2;
	CEdit	m_password1;
	CEdit	m_name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SigninDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SigninDlg)
	virtual void OnOK();
	afx_msg void OnDestroy();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIGNINDLG_H__D3ED66CC_5DE9_4C94_A584_C658FCDED342__INCLUDED_)
