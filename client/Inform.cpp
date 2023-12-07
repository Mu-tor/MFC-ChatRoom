// Inform.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "Inform.h"
#include "AccessDB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Inform dialog


Inform::Inform(CWnd* pParent /*=NULL*/)
	: CDialog(Inform::IDD, pParent)
{
	//{{AFX_DATA_INIT(Inform)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Inform::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Inform)
	DDX_Control(pDX, IDC_EDIT1, m_msg);
	//}}AFX_DATA_MAP
	update();
}



BEGIN_MESSAGE_MAP(Inform, CDialog)
	//{{AFX_MSG_MAP(Inform)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Inform message handlers
void Inform::ADDLog(CString log) 
{
	// TODO: Add your control notification handler code here
	CString msg;
	msg.Format("%s\n",log);
	m_msg.SetSel(-1);
	m_msg.ReplaceSel((LPCTSTR)msg);
	m_msg.SetSel(-1);
}

void Inform::update(){
	AccessDB db;
	int i=0;
	if(!db.OpenDataBase("chatlog.mdb")){
		MessageBox("数据库打开失败");
	}
	//查询与recname的聊天记录
	CString str="select * from [公告] ";
	if(!db.Query((char *)(LPCSTR)str)){
		MessageBox("聊天记录查询失败");
	}
	while(!db.IsEof()){
		char time[255];
		char msg[255];
		db.ReadString("time",time);
		ADDLog(time);
		db.ReadString("msg", msg);
		ADDLog(msg);
		ADDLog("\n");
		db.Next();
	}
	db.Close();
}
