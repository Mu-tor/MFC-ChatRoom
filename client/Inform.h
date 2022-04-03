#if !defined(AFX_INFORM_H__7964109F_766C_4B51_9B1B_55D4D2426F38__INCLUDED_)
#define AFX_INFORM_H__7964109F_766C_4B51_9B1B_55D4D2426F38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Inform.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Inform dialog

class Inform : public CDialog
{
// Construction
public:
	void ADDLog(CString log);
	void update();
	Inform(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Inform)
	enum { IDD = IDD_DIALOG3 };
	CEdit	m_msg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Inform)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Inform)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INFORM_H__7964109F_766C_4B51_9B1B_55D4D2426F38__INCLUDED_)
