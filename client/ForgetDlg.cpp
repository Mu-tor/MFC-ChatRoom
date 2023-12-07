// ForgetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "ForgetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ForgetDlg dialog


ForgetDlg::ForgetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ForgetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(ForgetDlg)
	//}}AFX_DATA_INIT
}


void ForgetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ForgetDlg)
	DDX_Control(pDX, IDC_EDIT7, m_code2);
	DDX_Control(pDX, IDC_EDIT6, m_code1);
	DDX_Control(pDX, IDC_EDIT4, m_password2);
	DDX_Control(pDX, IDC_EDIT3, m_password1);
	DDX_Control(pDX, IDC_EDIT2, m_encrypted);
	DDX_Control(pDX, IDC_EDIT1, m_name);
	DDX_Control(pDX, IDC_COMBO1, m_question);
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
		WSACleanup();
		closesocket(clsoc);
		exit(0);
	}
	send(clsoc,"forget",6,0);
	memset(code,0,5);
	recv(clsoc,code,5,0);
	m_code1.SetWindowText(code);
}


BEGIN_MESSAGE_MAP(ForgetDlg, CDialog)
	//{{AFX_MSG_MAP(ForgetDlg)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ForgetDlg message handlers

void ForgetDlg::OnOK() 
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
	if(name==""||password1==""||password2==""||question==""||encrypted==""||code2==""){
		MessageBox("老实把表填满吧");
		return;
	}else if(password1!=password2){
		MessageBox("睡迷糊了？两次输入的密码不一样啊");
		password2=="";
		return;
	}else if (strcmp(strlwr(code), strlwr((LPSTR)(LPCTSTR)code2))) {
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
			if(!strcmp(recvbuff,"yes")) {
				MessageBox("密码修改成功!别再忘了哦");
				exit(0);
			}else if(!strcmp(recvbuff, "NULL")){
				MessageBox("有没有这个人呀!");
				this->EndDialog(-1);//关闭对话框
			}else if(!strcmp(recvbuff, "error")){
				MessageBox("密保不对哦!");
				this->EndDialog(-1);//关闭对话框
			}else if(!strcmp(recvbuff, "syserror")){
				MessageBox("系统错误!");
				this->EndDialog(-1);//关闭对话框
			}else if(!strcmp(recvbuff, "again")){
				MessageBox("请重试!");
				this->EndDialog(-1);//关闭对话框
			}else{
				char str[20];
				sprintf(str, "系统错误,代码%s!", recvbuff);
				MessageBox(str);
				this->EndDialog(-1);//关闭对话框
			}
		}
	}
	send(clsoc, "exit", 5, 0);
	closesocket(clsoc);
}

void ForgetDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	send(clsoc,"exit",5,0);
	closesocket(clsoc);
	
	// TODO: Add your message handler code here
	
}

void ForgetDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
	send(clsoc,"exit",5,0);
	closesocket(clsoc);
}
