// MsgEx.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "MsgEx.h"
#include "DeleteMsg.h"
#include "AccessDB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MsgEx dialog


MsgEx::MsgEx(CWnd* pParent /*=NULL*/)
	: CDialog(MsgEx::IDD, pParent)
{
	//{{AFX_DATA_INIT(MsgEx)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void MsgEx::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MsgEx)
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_EDIT1, m_name);
	//}}AFX_DATA_MAP
	m_name.SetWindowText(recname);
	m_list.InsertColumn(0,"啥时候",0,150);
	m_list.InsertColumn(1,"叫啥",0,80);
	m_list.InsertColumn(2,"说了啥",0,200);
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT );
	update();
}


BEGIN_MESSAGE_MAP(MsgEx, CDialog)
	//{{AFX_MSG_MAP(MsgEx)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MsgEx message handlers

void MsgEx::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nselect;
	CString time,msg;
	nselect = m_list.GetSelectionMark();
	time = m_list.GetItemText(nselect, 0);
	msg = m_list.GetItemText(nselect, 2);
	DeleteMsg dlg;
	dlg.name = name;
	dlg.time = time;
	dlg.msg = msg;
	dlg.DoModal();
	m_list.DeleteAllItems();// 清空列表
	update();
	*pResult = 0;
}

void MsgEx::update(){
	AccessDB db;
	int i=0;
	if(!db.OpenDataBase("chatlog.mdb")){
		MessageBox("数据库打开失败");
	}
	//查询与recname的聊天记录
	CString str="select * from ["+name+"] where name ='"+recname+"'or rename='"+recname+"'";
	if(!db.Query((char *)(LPCSTR)str)){
		MessageBox("聊天记录查询失败");
	}
	while(!db.IsEof()){
		char time[255];
		char sendname[255];
		char msg[255];
		db.ReadString("time",time);
		m_list.InsertItem(i, time);//添加昵称到用户列表
		db.ReadString("name",sendname);
		m_list.SetItemText(i, 1, sendname);//添加发送人
		db.ReadString("msg", msg);
		m_list.SetItemText(i, 2, msg);//添加消息
		i++;
		db.Next();
	}
	db.Close();
}
