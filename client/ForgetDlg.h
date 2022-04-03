#if !defined(AFX_FORGETDLG_H__FCD1994D_E0B5_4F3D_A3C9_E6E2A982EFA5__INCLUDED_)
#define AFX_FORGETDLG_H__FCD1994D_E0B5_4F3D_A3C9_E6E2A982EFA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ForgetDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ForgetDlg dialog

class ForgetDlg : public CDialog
{
// Construction
public:
	SOCKET clsoc;	
	char code[5];
	ForgetDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ForgetDlg)
	enum { IDD = IDD_Forget };
	CEdit	m_code2;
	CEdit	m_code1;
	CEdit	m_password2;
	CEdit	m_password1;
	CEdit	m_encrypted;
	CEdit	m_name;
	CComboBox	m_question;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ForgetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ForgetDlg)
	virtual void OnOK();
	afx_msg void OnDestroy();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORGETDLG_H__FCD1994D_E0B5_4F3D_A3C9_E6E2A982EFA5__INCLUDED_)
