#if !defined(AFX_DIALOG2_H__18B81DEA_2B5D_497A_B6D4_1C7EC89E7C24__INCLUDED_)
#define AFX_DIALOG2_H__18B81DEA_2B5D_497A_B6D4_1C7EC89E7C24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dialog2 dialog

class Dialog2 : public CDialog
{
// Construction
public:
	SOCKET clsoc;
	CString name;
	CString recname;
	bool flag;
	void ADDLog(CString log);
	Dialog2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dialog2)
	enum { IDD = IDD_Dialog2 };
	CEdit	m_bul;
	CEdit	m_Xxk;
	CEdit	m_name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dialog2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dialog2)
	afx_msg void OnSend();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG2_H__18B81DEA_2B5D_497A_B6D4_1C7EC89E7C24__INCLUDED_)
