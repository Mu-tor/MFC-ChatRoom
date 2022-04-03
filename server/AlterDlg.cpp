// AlterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "AlterDlg.h"
#include "AccessDB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AlterDlg dialog


AlterDlg::AlterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(AlterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(AlterDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void AlterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AlterDlg)
	DDX_Control(pDX, IDC_EDIT4, m_encrypted);
	DDX_Control(pDX, IDC_EDIT3, m_question);
	DDX_Control(pDX, IDC_EDIT2, m_password);
	DDX_Control(pDX, IDC_EDIT1, m_name);
	//}}AFX_DATA_MAP
	AccessDB db;
	if(!db.OpenDataBase("student.mdb"))
	{
		MessageBox("数据库打开失败");
	}
	else
	{
		CString str="select * from [user] where name ='"+name+"'";
		if(!db.Query((char *)(LPCSTR)str))
			MessageBox("查询失败");
		if(db.IsEof())
			MessageBox("用户不存在");
		else
		{
			char chpas[32];
			char chname[32];
			char chque[1024];
			char chencr[1024];
			db.ReadString("name",chname);
			m_name.SetWindowText(chname);
			db.ReadString("password",chpas);
			m_password.SetWindowText(chpas);
			db.ReadString("question", chque);
			m_question.SetWindowText(chque);
			db.ReadString("encrypted", chencr);
			m_encrypted.SetWindowText(chencr);
		}
	}
}

BEGIN_MESSAGE_MAP(AlterDlg, CDialog)
	//{{AFX_MSG_MAP(AlterDlg)
	ON_BN_CLICKED(IDOK, OnAlter)
	ON_BN_CLICKED(IDC_BUTTON1, OnDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AlterDlg message handlers

void AlterDlg::OnAlter() 
{
	// TODO: Add your control notification handler code here
	CString password,question,encrypted;
	//获取更改后信息
	m_password.GetWindowText(password);
	m_question.GetWindowText(question);
	m_encrypted.GetWindowText(encrypted);
	AccessDB db;
	if(!db.OpenDataBase("student.mdb"))
	{
		MessageBox("数据库打开失败");
	}
	else
	{
		//修改数据库内用户信息
		CString str="update [user] set [password] = '"+password+"',[question] = '"+question+"',[encrypted] = '"+encrypted+"' where name ='" + name + "'";
		if (db.Update((char*)(LPCSTR)str)) {
			db.Close();
			MessageBox("好家伙,偷偷改别人信息!");
		}
		this->EndDialog(-1);//关闭对话框
	}
}

void AlterDlg::OnDelete() 
{
	// TODO: Add your control notification handler code here
	AccessDB db;
	if(!db.OpenDataBase("student.mdb"))
	{
		MessageBox("数据库打开失败");
	}
	else
	{
		//修改数据库内用户信息
		CString str="delete from [user] where name ='" + name + "'";
		CString str1="drop table [" + name + "]";
		if (db.Update((char*)(LPCSTR)str)) {
			db.Update((char*)(LPCSTR)str1);
			db.Close();
			MessageBox("真不要了？");
		}
		this->EndDialog(-1);//关闭对话框
	}
}
