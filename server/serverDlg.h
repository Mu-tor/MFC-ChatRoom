// serverDlg.h : header file
//

#if !defined(AFX_SERVERDLG_H__C10A097F_40D3_4037_825A_2989EB5580C0__INCLUDED_)
#define AFX_SERVERDLG_H__C10A097F_40D3_4037_825A_2989EB5580C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CServerDlg dialog

class CServerDlg : public CDialog
{
// Construction
public:	
	SOCKET seSoc;
	SOCKET clientsoc;
	sockaddr_in clientaddr;
	void ADDLog(CString log);
	CServerDlg(CWnd* pParent = NULL);
	

	
	
	// standard constructor

// Dialog Data
	//{{AFX_DATA(CServerDlg)
	enum { IDD = IDD_SERVER_DIALOG };
	CListCtrl	m_list;
	CButton	m_star;
	CEdit	m_Xxk;
	CEdit	m_bul;
	CEdit	m_dk;
	CEdit	m_ip;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnNotice();
	afx_msg void OnAddUser();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERDLG_H__C10A097F_40D3_4037_825A_2989EB5580C0__INCLUDED_)
