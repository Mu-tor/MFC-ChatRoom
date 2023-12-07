// client.h : main header file for the client application
//

#if !defined(AFX_client_H__7D2AD000_072A_4E31_983E_635594B04308__INCLUDED_)
#define AFX_client_H__7D2AD000_072A_4E31_983E_635594B04308__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CclientApp:
// See client.cpp for the implementation of this class
//

class CclientApp : public CWinApp
{
public:
	CclientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CclientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CclientApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_client_H__7D2AD000_072A_4E31_983E_635594B04308__INCLUDED_)
