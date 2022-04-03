#if !defined(AFX_ADDDLG_H__E11764C1_36DB_4699_B70F_BBAB373DCFC0__INCLUDED_)
#define AFX_ADDDLG_H__E11764C1_36DB_4699_B70F_BBAB373DCFC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// AddDlg dialog

class AddDlg : public CDialog
{
// Construction
public:
	AddDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(AddDlg)
	enum { IDD = IDD_DIALOG1 };
	CEdit	m_encrypted;
	CEdit	m_question;
	CEdit	m_password;
	CEdit	m_name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AddDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(AddDlg)
	afx_msg void OnAdd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDDLG_H__E11764C1_36DB_4699_B70F_BBAB373DCFC0__INCLUDED_)
