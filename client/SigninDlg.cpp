// SigninDlg.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "SigninDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SigninDlg dialog


SigninDlg::SigninDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SigninDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SigninDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void SigninDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SigninDlg)
	DDX_Control(pDX, IDC_EDIT7, m_code2);
	DDX_Control(pDX, IDC_EDIT6, m_code1);
	DDX_Control(pDX, IDC_COMBO1, m_question);
	DDX_Control(pDX, IDC_EDIT4, m_encrypted);
	DDX_Control(pDX, IDC_EDIT3, m_password2);
	DDX_Control(pDX, IDC_EDIT2, m_password1);
	DDX_Control(pDX, IDC_EDIT1, m_name);
	//}}AFX_DATA_MAP
	// 创建socket 
	clsoc=socket(AF_INET,SOCK_STREAM,0);
	// 创建协议地址族
	SOCKADDR_IN addr={0}; 
	addr.sin_family=AF_INET;//协议版本
	addr.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
	addr.sin_port=htons(9000);
	int r=connect(clsoc,(sockaddr*)&addr,sizeof addr);
	if(r==-1)
	{
		MessageBox("服务器还没睡醒吧？");
		closesocket(clsoc);
		exit(0);
	}
	send(clsoc,"signin",6,0);
	memset(code,0,5);
	recv(clsoc,code,5,0);
	m_code1.SetWindowText(code);
}


BEGIN_MESSAGE_MAP(SigninDlg, CDialog)
	//{{AFX_MSG_MAP(SigninDlg)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SigninDlg message handlers

void SigninDlg::OnOK()
{
	// TODO: Add extra validation here
	CString name,password1,password2,question,encrypted,code2;
	char recvbuff[20]={0};
	m_name.GetWindowText(name);
	m_password1.GetWindowText(password1);
	m_password2.GetWindowText(password2);
	m_question.GetWindowText(question);
	m_encrypted.GetWindowText(encrypted);
	m_code2.GetWindowText(code2);
	if(name==""||password1==""||password2==""||question==""||encrypted==""){
		MessageBox("老实把表填满吧");
		return;
	}else if(password1!=password2){
		MessageBox("健忘了？两次输入的密码不一样啊");
		password2=="";
		return;
	}else if (strcmp(strlwr(code),strlwr((LPSTR)(LPCTSTR)code2))) {
		MessageBox("验证码都能输错？");
		code2=="";
		return;
	}else {
		send(clsoc,(char*)(LPCSTR)name,strlen(name),0);
		Sleep(100);
		send(clsoc,(char*)(LPCSTR)password1,strlen(password1),0);
		Sleep(100);
		send(clsoc,(char*)(LPCSTR)question,strlen(question),0);
		Sleep(100);
		send(clsoc,(char*)(LPCSTR)encrypted,strlen(encrypted),0);
		int rval=recv(clsoc,recvbuff,20,0);
		if(rval>0){
			if(!strcmp(recvbuff, "yes")){
				MessageBox("成功潜入敌方阵地!");
				exit(0);
			}else if(!strcmp(recvbuff, "repeat")){
				MessageBox("这哥们都已经在了!");
				this->EndDialog(-1);//关闭对话框
			}else if(!strcmp(recvbuff, "error")){
				MessageBox("潜入失败!");
				this->EndDialog(-1);//关闭对话框
			}else if(!strcmp(recvbuff, "again")){
				MessageBox("再试一次吧!");
				this->EndDialog(-1);//关闭对话框
			}
			else {
				MessageBox("服务器不太行!");
				this->EndDialog(-1);//关闭对话框
			}
		}
	}
	closesocket(clsoc);
}

void SigninDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	send(clsoc,"exit",5,0);
	closesocket(clsoc);
}

void SigninDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
	send(clsoc,"exit",5,0);
	closesocket(clsoc);
}
