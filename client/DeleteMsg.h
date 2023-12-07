#if !defined(AFX_DELETEMSG_H__5C8E4589_7573_4870_8EC2_F71BFF49460B__INCLUDED_)
#define AFX_DELETEMSG_H__5C8E4589_7573_4870_8EC2_F71BFF49460B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DeleteMsg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DeleteMsg dialog

class DeleteMsg : public CDialog
{
// Construction
public:
	CString name,time,msg;
	DeleteMsg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DeleteMsg)
	enum { IDD = IDD_Delete };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DeleteMsg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DeleteMsg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DELETEMSG_H__5C8E4589_7573_4870_8EC2_F71BFF49460B__INCLUDED_)
