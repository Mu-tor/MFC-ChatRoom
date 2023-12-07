#if !defined(AFX_ALTERDLG_H__0BEACD6F_F9AF_49E1_84A1_652382F02DDA__INCLUDED_)
#define AFX_ALTERDLG_H__0BEACD6F_F9AF_49E1_84A1_652382F02DDA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlterDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// AlterDlg dialog

class AlterDlg : public CDialog
{
// Construction
public:
	CString name;
	AlterDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(AlterDlg)
	enum { IDD = IDD_AlterDlg };
	CEdit	m_encrypted;
	CEdit	m_question;
	CEdit	m_password;
	CEdit	m_name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AlterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(AlterDlg)
	afx_msg void OnAlter();
	afx_msg void OnDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALTERDLG_H__0BEACD6F_F9AF_49E1_84A1_652382F02DDA__INCLUDED_)
