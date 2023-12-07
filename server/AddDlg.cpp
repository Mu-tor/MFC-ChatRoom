// AddDlg.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "AddDlg.h"
#include "AccessDB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AddDlg dialog


AddDlg::AddDlg(CWnd* pParent /*=NULL*/)
	: CDialog(AddDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(AddDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void AddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AddDlg)
	DDX_Control(pDX, IDC_EDIT4, m_encrypted);
	DDX_Control(pDX, IDC_EDIT3, m_question);
	DDX_Control(pDX, IDC_EDIT2, m_password);
	DDX_Control(pDX, IDC_EDIT1, m_name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(AddDlg, CDialog)
	//{{AFX_MSG_MAP(AddDlg)
	ON_BN_CLICKED(IDOK, OnAdd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AddDlg message handlers

void AddDlg::OnAdd() 
{
	// TODO: Add your control notification handler code here
	CString name,password,question,encrypted;
	//获取更改后信息
	m_name.GetWindowText(name);
	m_password.GetWindowText(password);
	m_question.GetWindowText(question);
	m_encrypted.GetWindowText(encrypted);
	AccessDB db;
	if(!db.OpenDataBase("student.mdb"))
	{
		MessageBox("数据库好像打不开啊!");
	}
	else
	{
		CString str = "select * from [user] where name ='" + name + "'";
		if (!db.Query((char*)(LPCSTR)str))
			MessageBox("出错了!");
		if (!db.IsEof()) {
			MessageBox("这哥们都已经在了!");
		}else{
			//修改数据库内用户信息
			CString str2="insert into [user]([name],[password],[question],[encrypted]) values('"+name+"','"+password+"','"+question+"','"+encrypted+"')";
			CString str3 = "create table [" + name + "] ([time] varchar,[name] varchar,[msg] varchar,[whether] varchar(1))";//添加离线消息表
			if (db.Update((char*)(LPCSTR)str2)) {
				db.Update((char*)(LPCSTR)str3);
				db.Close();
				MessageBox("好家伙,又多了一个人!");
			}
			this->EndDialog(-1);//关闭对话框
		}
	}
}
