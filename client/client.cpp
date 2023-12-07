// client.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "client.h"
#include "LoginDlg.h"
#include "Dialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CclientApp

BEGIN_MESSAGE_MAP(CclientApp, CWinApp)
	//{{AFX_MSG_MAP(CclientApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CclientApp construction

CclientApp::CclientApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CclientApp object

CclientApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CclientApp initialization

BOOL CclientApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	LoginDlg loginDlg;
	if(IDCANCEL==loginDlg.DoModal())
	{
		return FALSE;
	}
	/////
	Dialog dlg;
	dlg.clsoc=loginDlg.clsoc;
	dlg.name=loginDlg.name;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	return FALSE;
}
