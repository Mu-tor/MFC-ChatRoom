#if !defined(AFX_MSGEX_H__079847C0_1DAB_4642_88FC_E516CEBCAF0C__INCLUDED_)
#define AFX_MSGEX_H__079847C0_1DAB_4642_88FC_E516CEBCAF0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MsgEx dialog

class MsgEx : public CDialog
{
// Construction
public:
	CString name;
	CString recname;
	void update();
	MsgEx(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MsgEx)
	enum { IDD = IDD_DIALOG1 };
	CListCtrl	m_list;
	CEdit	m_name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MsgEx)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MsgEx)
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGEX_H__079847C0_1DAB_4642_88FC_E516CEBCAF0C__INCLUDED_)
