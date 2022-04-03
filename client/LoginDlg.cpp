// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "LoginDlg.h"
#include "SigninDlg.h"
#include "ForgetDlg.h"
#include "AccessDB.h"
#pragma comment(lib,"WS2_32.lib")
#pragma comment(lib,"Mswsock.lib")
#pragma comment(lib,"AdvApi32.lib")
extern CclientApp theApp;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LoginDlg dialog


LoginDlg::LoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(LoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(LoginDlg)
	//}}AFX_DATA_INIT
}


void LoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(LoginDlg)
	DDX_Control(pDX, IDC_EDIT2, m_password);
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
	error=3;//设置错误次数
}


BEGIN_MESSAGE_MAP(LoginDlg, CDialog)
	//{{AFX_MSG_MAP(LoginDlg)
	ON_BN_CLICKED(ID_Login, OnLogin)
	ON_BN_CLICKED(IDD_Signin, OnSignin)
	ON_BN_CLICKED(IDC_Forget, OnForget)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LoginDlg message handlers

void LoginDlg::OnLogin()
{
	CString star,password;
	m_name.GetWindowText(name);
	m_password.GetWindowText(password);
	if(password.GetLength()==0||name.GetLength()==0)
	{
		MessageBox("账号密码输完再说!");
		return;
	}
	//发送账号密码
	send(clsoc,"login",5,0);
	Sleep(100);
	send(clsoc,(char*)(LPCSTR)name,strlen(name),0);
	Sleep(100);
	send(clsoc,(char*)(LPCSTR)password,strlen(password),0);

	char recvbuff[10]={0};
	//接受账号密码是否正确
	char msg[48];
	int rval=recv(clsoc,recvbuff,10,0);
	if(rval>0){
		if(recvbuff[0]=='y'&&recvbuff[1]=='e'&&recvbuff[2]=='s'){
			AccessDB db;
			if (!db.OpenDataBase("chatlog.mdb")){
				MessageBox("数据库打开失败");//数据库打开失败
			}
			else{
				CString str = "create table ["+name+"] ([time] varchar,[name] varchar,[msg] varchar,[rename] varchar)";//添加用户聊天记录表
				db.Update((char*)(LPCSTR)str);
				db.Close();
			}
			//登录成功，进入消息页面
			this->EndDialog(-1);//关闭登陆框
		}else if(recvbuff[0]=='N'&&recvbuff[1]=='U'&&recvbuff[2]=='L'&&recvbuff[3]=='L'){
			MessageBox("有没有这个人啊？");
		}else if(recvbuff[0]=='e'&&recvbuff[1]=='r'&&recvbuff[2]=='r'&&recvbuff[3]=='o'&&recvbuff[4]=='r'){
			sprintf(msg,"忘记密码了？你还有%d次机会哦",error);
			MessageBox(msg);
			m_password.SetWindowText("");
			if(error==0)
				exit(0);
			error--;
		}
		else if (recvbuff[0] == 's' && recvbuff[1] == 'y' && recvbuff[2] == 's' && recvbuff[3] == 'e' &&
			recvbuff[4] == 'r' && recvbuff[5] == 'r' && recvbuff[6] == 'o' && recvbuff[7] == 'r') {
			MessageBox("服务器好像爆炸了,待会再来看看吧");
		}
		else if (recvbuff[0] == 'a' && recvbuff[1] == 'g' && recvbuff[2] == 'a' && recvbuff[3] == 'i' &&
			recvbuff[4] == 'n' ) {
			MessageBox("你都登陆过了还登？");
		}
	}else MessageBox("服务器睡着了？待会再来看看吧");
}

void LoginDlg::OnSignin() 
{
	// TODO: Add your control notification handler code here
	//注册用户
	SigninDlg dlg;
	dlg.DoModal();
}

void LoginDlg::OnForget() 
{
	// TODO: Add your control notification handler code here
	//忘记密码
	ForgetDlg dlg;
	dlg.DoModal();
}

