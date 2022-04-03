#if !defined(AFX_DIALOG_H__C8BFD107_7D97_466D_90B8_68A24948ED63__INCLUDED_)
#define AFX_DIALOG_H__C8BFD107_7D97_466D_90B8_68A24948ED63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dialog dialog

class Dialog : public CDialog
{
// Construction
public:
	void update();
	SOCKET clsoc;
	CString name;
	CString strname;
	void ADDLog(CString log);
	Dialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dialog)
	enum { IDD = IDD_Dialog };
	CListCtrl	m_list;
	CEdit	m_bul;
	CEdit	m_Xxk;
	CEdit	m_name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dialog)
	afx_msg void OnSend();
	afx_msg void OnDestroy();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButton2();
	afx_msg void OnButton4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_H__C8BFD107_7D97_466D_90B8_68A24948ED63__INCLUDED_)
