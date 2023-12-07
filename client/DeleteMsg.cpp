// DeleteMsg.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "DeleteMsg.h"
#include "AccessDB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DeleteMsg dialog


DeleteMsg::DeleteMsg(CWnd* pParent /*=NULL*/)
	: CDialog(DeleteMsg::IDD, pParent)
{
	//{{AFX_DATA_INIT(DeleteMsg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DeleteMsg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DeleteMsg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DeleteMsg, CDialog)
	//{{AFX_MSG_MAP(DeleteMsg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DeleteMsg message handlers

void DeleteMsg::OnOK() 
{
	// TODO: Add extra validation here
	AccessDB db;
	if(!db.OpenDataBase("chatlog.mdb")){
		MessageBox("数据库打开失败");
	}
	//删除指定的聊天记录
	CString str="Delete from ["+name+"] where time ='"+time+"'and msg='"+msg+"'";
	db.Update((char *)(LPCSTR)str);
	db.Close();
	CDialog::OnOK();
}
