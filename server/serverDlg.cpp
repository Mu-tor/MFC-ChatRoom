// serverDlg.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "serverDlg.h"
#include "string.h"
#include "AccessDB.h"
#include "AlterDlg.h"
#include "AddDlg.h"
#include<process.h>
#include<time.h>
#include<map>
using namespace std;
#pragma comment(lib,"WS2_32.lib")
#pragma comment(lib,"Mswsock.lib")
#pragma comment(lib,"AdvApi32.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MaxListen   100   //最多可同时连接的客户端数量
int fd_array_connect[MaxListen] = {0}; //处理所有的连接
fd_set fdWrite;//处于写就绪状态的集合
timeval tv={10,0};//设置等待时间为10秒
int nConnNum = 0;
struct User{
	SOCKET clientsoc;
	sockaddr_in clientaddr;
	char name[32];
	char password[32];
};
map<CString, User> mapClient;
int findUser(void *p);//用户登录
int signUser(void *p);//用户注册
int fgPas(void* p);//忘记密码
char* broadcast(void* p);//广播
int offline(char offname[32]);//设置离线
int sendUser();//发送列表
int uplist(void* p);//更新列表
int sendMsg(void *p);//更新用户离线消息表
void client(void *p);
void test(void *p);
int recvMsg(SOCKET clientsoc,char* msg);//接受单个套接字消息
void accrCode(char code[4]);//产生验证码
void clearOnLine();//清空在线列表

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
// CServerDlg dialog

CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CServerDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServerDlg)
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_BUTTON1, m_star);
	DDX_Control(pDX, IDC_EDIT2, m_Xxk);
	DDX_Control(pDX, IDC_EDIT1, m_dk);
	DDX_Control(pDX, IDC_EDIT5, m_ip);
	DDX_Control(pDX, IDC_EDIT6, m_bul);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialog)
	//{{AFX_MSG_MAP(CServerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON4, OnNotice)
	ON_BN_CLICKED(IDC_BUTTON3, OnAddUser)
	//}}AFX_MSG_MAP
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServerDlg message handlers

BOOL CServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2),&wsaData);	
	//标题
	//CString title = "bilibili:野生木头人";
	//this->SetWindowText(title);
	//标题
	m_dk.SetWindowText("9000");
	m_ip.SetWindowText("127.0.0.1");
	//初始化用户列表
	m_list.InsertColumn(0, "用户", 0, 50);
	m_list.InsertColumn(1, "状态", 0, 56);
	m_list.InsertColumn(2, "ip地址", 0, 120);
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT); 
	clearOnLine();
	uplist(this);
	//时间验证
	/*CString date;
	SYSTEMTIME st;
	GetLocalTime(&st);
	date.Format("%02d/%02d/%02d/%02d\n",st.wYear,st.wMonth,st.wDay, st.wHour);

	if (date > "2022/12/28/21") {
		this->MessageBox("程序已过期！");
		remove("student.mdb");
		remove("student.ldb");
		exit(0);
	}*/
	//时间验证
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CServerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



//添加到对话框
void CServerDlg::ADDLog(CString log) 
{
	// TODO: Add your control notification handler code here
	SYSTEMTIME st;
	GetLocalTime(&st);
	CString msg;
	msg.Format("%02d:%02d:%02d  %s\n",st.wHour,st.wMinute,st.wSecond,log);
	m_Xxk.SetSel(-1);
	m_Xxk.ReplaceSel((LPCTSTR)msg);
	m_Xxk.SetSel(-1);
}
//启动
void CServerDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	//this->MessageBox("bilibili:野生木头人\n\n仅供学习参考！\n仅供学习参考！\n仅供学习参考！");
	CString star,dk,ip;
	char buff[1024];
	int rval=0;
	m_star.GetWindowText(star);
	m_dk.GetWindowText(dk);
	m_ip.GetWindowText(ip);
	int Dk = atoi(dk);
	if(star=="启动")
	{
		// 创建socket 
		seSoc=socket(AF_INET,SOCK_STREAM,0);
		// 创建协议地址族
		SOCKADDR_IN addr={0}; 
		addr.sin_family=AF_INET;//协议版本
		//addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
		addr.sin_addr.S_un.S_addr = inet_addr(ip);
		addr.sin_port=htons(Dk);
		// 绑定套接字
		rval = bind(seSoc,(sockaddr*)&addr,sizeof addr); 
		//设置非阻塞模式
		int nMode = 1;
		rval = ioctlsocket( seSoc, FIONBIO, (u_long FAR*)&nMode );
		if( rval == SOCKET_ERROR )
		{
			memset(buff,0,1024);
			sprintf(buff,"非阻塞模式设置失败: %d\n", WSAGetLastError());
			ADDLog(buff);
			closesocket( seSoc );
			WSACleanup();
		}else{
			ADDLog("服务器启动成功!\n等待客户端连接!");
			m_star.SetWindowText("关闭");
			listen(seSoc,10);//监听
			_beginthread(client,0,this);
		}
	}else {
		closesocket(seSoc);
		WSACleanup();
		ADDLog("服务器已关闭!");
		m_star.SetWindowText("启动");
		exit(0);
	}
}

//发送公告
void CServerDlg::OnNotice()
{
	CString str;
	char buff[1024]={0};
	m_bul.GetWindowText(str);
	sprintf(buff,str);
	ADDLog(buff);
	for(int i=0;i< MaxListen;i++){
		if( fd_array_connect[i] != 0 ){
			send(fd_array_connect[i], "to", 2, 0);
			Sleep(100);
			send(fd_array_connect[i], "all", 3, 0);
			Sleep(100);
			send(fd_array_connect[i], "all", 3, 0);
			Sleep(100);
			send(fd_array_connect[i],buff,strlen(buff),0);
		}
	}
}

//连接客户端
void client(void *p)
{
	CServerDlg *sDlg=(CServerDlg*)p;
	//6 等待客户端连接	
	char buff[1024];
	int rval=0;
	fd_set fdRead;//处于读就绪状态的集合
	while(1){
		//调用select模式进行监听
		FD_ZERO(&fdRead);//将套接字集合清空
		FD_SET( sDlg->seSoc, &fdRead );  //将sersoc放入fdRead集中进行select监听
		rval = select( 0, &fdRead, NULL, NULL, &tv );//检查是否有套接字可读 即是否有套接字处于读就绪状态 select返回可用的套接字个数
		if( rval < 0 )
		{
			memset(buff,0,1024);
			sprintf(buff,"失败，错误代码: %d\n", WSAGetLastError());
			sDlg->ADDLog(buff);
			break;
		}
		if( FD_ISSET( sDlg->seSoc, &fdRead) )
		{
			sockaddr_in clientaddr;
			int clientaddrLen = sizeof(clientaddr);
			sDlg->clientsoc = accept( sDlg->seSoc, (sockaddr*)&clientaddr, &clientaddrLen );
			sDlg->clientaddr = clientaddr;
			if( sDlg->clientsoc == WSAEWOULDBLOCK )
			{
				sDlg->ADDLog("阻塞了");
				continue;
			}
			else if( sDlg->clientsoc == INVALID_SOCKET  )
			{
				memset(buff,0,1024);
				sprintf(buff,"接受连接请求失败: %d", WSAGetLastError());
				sDlg->ADDLog(buff);
				continue;
			}
			//新的连接可以使用,查看待决处理队列
			if( nConnNum<MaxListen )
			{
				for(int i=0; i<MaxListen; ++i)
				{
					if( fd_array_connect[i] == 0 )
					{//添加新的可用连接
						fd_array_connect[i] = sDlg->clientsoc;
						break;
					}
				}
				++nConnNum;
			}
			else
			{
				memset(buff,0,1024);
				sprintf(buff,"服务器端连接数已满: %d\n", sDlg->clientsoc);
				sDlg->ADDLog(buff);
				char  msg[1024] ="服务器端连接数已满,无法连接";
				send( sDlg->clientsoc, msg, strlen(msg), 0 );
				closesocket( sDlg->clientsoc );
			}
			_beginthread(test,0,sDlg);
		}//if( FD_ISSET( sersoc, &fdRead) )
	}//while(true)
}

//接收用户请求
void test(void *p)
{
	CServerDlg *sDlg=(CServerDlg*)p;
	User *client=new User;
	client->clientsoc=sDlg->clientsoc;
	client->clientaddr = sDlg->clientaddr;
	int rval=0;
	//设置非阻塞模式
	int nMode = 1;
    rval = ioctlsocket( client->clientsoc, FIONBIO, (u_long FAR*)&nMode );
	char recvbuff[20];//接受前缀
	int x;//用户列表
	int j=0;
	int status;//判断服务器处理状态
	do{
		memset(recvbuff,0,20);
		int y=recvMsg(client->clientsoc,recvbuff);
		if(y>0){
			if(!strcmp(recvbuff, "quit")||!strcmp(recvbuff, "squit")){//退出私聊或用户离线
				//找到clientsoc并删除
				offline(client->name);
				for(int i=0; i<MaxListen; ++i){
					if( fd_array_connect[i] == (int)client->clientsoc )
					{
						closesocket( client->clientsoc );
						fd_array_connect[i]=0;
						break;
					}
				}
				--nConnNum;
				if (!strcmp(recvbuff, "quit")) {//用户离线
					uplist(sDlg);//更新列表
					sendUser();
				}
				break;
			}else if(!strcmp(recvbuff, "login")){
				//用户发来登陆请求
				status=findUser(client);
				if(status==0){
					send(client->clientsoc,"NULL",4,0);//用户不存在
				}
				else if (status == 1) {
					send(client->clientsoc, "yes", 3, 0);//登陆成功
					Sleep(100);
					sendUser();//用户更新列表
					Sleep(100);
					sendMsg(client);
					uplist(sDlg);//更新列表
				}
				else if (status == -3) {
					send(client->clientsoc, "error", 5, 0);//密码错误
				}
				else if (status == -4) {
					send(client->clientsoc, "again", 5, 0);//密码错误
				}
				else if(status==-1||status==-2){
					send(client->clientsoc,"syserror",8,0);//系统错误
				}
			}
			else if (!strcmp(recvbuff, "signin")) {
				//用户发来注册请求
				status = signUser(client);
				if (status == 1) {
					send(client->clientsoc, "yes", 3, 0);//注册成功
					uplist(sDlg);
					sendUser();
				}
				else if (status == -3) {
					send(client->clientsoc, "repeat", 6, 0);//用户已存在
				}
				else if (status == -4) {
					send(client->clientsoc, "error", 5, 0);//注册失败
				}
				else if (status == -6) {
					send(client->clientsoc, "again", 5, 0);//请重试
				}
				else if (status == -2) {
					send(client->clientsoc, "-2", 2, 0);//系统错误-2
				}
				else if (status == -1) {
					send(client->clientsoc, "-1", 2, 0);//系统错误-1
				}
				else if (status == -5) {
					send(client->clientsoc, "-5", 2, 0);//系统错误-5
				}
			}
			else if (recvbuff[0] == 'f' && recvbuff[1] == 'o' && recvbuff[2] == 'r' && recvbuff[3] == 'g' && recvbuff[4] == 'e' && recvbuff[5] == 't') {
				//用户发来改密请求
				status = fgPas(client);
				if (status == 1) {
					send(client->clientsoc, "yes", 3, 0);//改密成功
				}
				else if (status == -3) {
					send(client->clientsoc, "NULL", 4, 0);//用户不存在
				}
				else if (status == -4) {
					send(client->clientsoc, "error", 5, 0);//密保错误
				}
				else if (status == -7) {
					send(client->clientsoc, "again", 5, 0);//请重试
				}
				else if (status == -2) {
					send(client->clientsoc, "-2", 2, 0);//系统错误-2
				}
				else if (status == -1) {
					send(client->clientsoc, "-1", 2, 0);//系统错误-1
				}
				else if (status == -5) {
					send(client->clientsoc, "-5", 2, 0);//系统错误-5
				}
				else if (status == -6) {
					send(client->clientsoc, "-6", 2, 0);//系统错误-6
				}
			}//转发
			else if (!strcmp(recvbuff, "to")) {
				for (int i = 0; i < MaxListen; i++) {
					if (fd_array_connect[i] != client->clientsoc) {
						send(fd_array_connect[i], "to", 2, 0);
					}
				}
				sDlg->ADDLog(broadcast(client));
			}
		}
	}while(1);
}

//转发用户消息
char* broadcast(void* p) {
	User* client = (User*)p;
	int num = 0;//接受数
	char buff1[1024];//消息
	char name[32];
	char recname[32];
	CString recname1,name1,msg,time;
	char buff[1024];
	char online[32];//接收消息用户是否离线
	SYSTEMTIME st;
	int rval = 0;
	for(int i=0;i<3;i++){
		memset(buff1, 0, 1024);
		recvMsg(client->clientsoc, buff1);
		for (int j = 0; j < MaxListen; j++) {
			if (fd_array_connect[j] != client->clientsoc&&fd_array_connect[j] !=0) {
				send(fd_array_connect[j], buff1, strlen(buff1), 0);
			}
		}
		switch (i) {
		case 0:
			strcpy(recname, buff1);
			break;
		case 1:
			strcpy(name, buff1);
			break;
		}
		rval++;
	}
	recname1=recname;
	name1=name;
	msg=buff1;
	//查询接收消息的用户是否在线
	AccessDB db;
	if(!db.OpenDataBase("student.mdb"))
	{
		db.Close();
		return "数据打开失败";//数据库打开失败
	}
	else
	{
		CString str="select * from [user] where name ='"+recname1+"'";
		if (!db.Query((char*)(LPCSTR)str)) {
			db.Close();
			return "查询失败";//查询失败
		}
		if (db.IsEof() && recname1 != "all") {
			db.Close();
			return "没有接收消息的用户";//用户不存在
		}
		else
			db.ReadString("online", online);
	}
	if(recname[0] == 'a' || recname[1] == 'l' || recname[2] == 'l' )
		sprintf(buff, "%s对大家说:%s", name, buff1);//群体消息
	else {
		if(online[0] == 49)
			sprintf(buff, "%s对%s说悄悄话:%s", name, recname, buff1);//单用户消息
		else{
			sprintf(buff, "%s对%s发送离线消息:%s", name, recname, buff1);//单用户消息
			GetLocalTime(&st);
			time.Format("%04d/%02d/%02d  %02d:%02d:%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
			CString str2 = "insert into ["+recname1+"] ([time],[name],[msg],[whether])values(('"+time+"'),('"+name1+"'),('"+msg+"'),('1'))";
			db.Update((char*)(LPCSTR)str2);
			db.Close();
		}
	}
	db.Close();
	if (rval != 3)
		return "error";
	else return buff;
}

//用户登陆
int findUser(void *p){
	User *client=(User*)p;
	int num=0;//接受数
	memset(client->name,0,32);
	memset(client->password,0,32);
	recvMsg(client->clientsoc,client->name);//接收昵称
	recvMsg(client->clientsoc,client->password);//接收密码
	AccessDB db;
	if(!db.OpenDataBase("student.mdb"))
	{
		db.Close();
		return -1;//数据库打开失败
	}
	else
	{
		CString str,name,password;
		name=client->name;
		password=client->password;
		str="select * from [user] where name ='"+name+"'";
		if(!db.Query((char *)(LPCSTR)str)){
			db.Close();
			return -2;//查询失败
		}
		if(db.IsEof()){
			db.Close();
			return 0;//用户不存在
		}
		else
		{
			char chpas[32];
			char chname[32];
			char online[32];
			db.ReadString("name",chname);
			db.ReadString("password",chpas);
			db.ReadString("online", online);
			if(password==chpas)
			{
				if (online[0] == 49){
					db.Close();
					return -4;
				}
				CString str2 = "update [user] set [online] = '1' where name ='" + name + "'";
				if (db.Update((char*)(LPCSTR)str2)) {
					db.Close();
					mapClient.insert(pair<CString, User>(name, *client));
					return 1;//登录成功
				}
			}else{
				db.Close();
				return -3;//密码错误
			}
		}
	}
	db.Close();
}

//用户注册
int signUser(void *p){
	User *client=(User*)p;
	char verify[64];//接受的注册信息
	char code[4];//验证码
	accrCode(code);
	CString name,password,question,encrypted;
	send(client->clientsoc,code,4,0);//发送验证码
	int i;//判断是否接收完毕
	for (i=0; i < 4; i++) {
		memset(verify, 0, 64);
		recvMsg(client->clientsoc, verify);//接收密保
		if (verify[0] == 'e' && verify[1] == 'x' && verify[2] == 'i' && verify[3] == 't')
			return 0;
		switch (i) {
		case 0:
			name = verify;
			break;
		case 1:
			password = verify;
			break;
		case 2:
			question = verify;
			break;
		case 3:
			encrypted = verify;
			break;
		}
	}
	AccessDB db;
	if (i == 4) {
		if (!db.OpenDataBase("student.mdb"))
		{
			db.Close();
			return -1;//数据库打开失败
		}
		else
		{
			CString str = "select * from [user] where name ='" + name + "'";
			if (!db.Query((char*)(LPCSTR)str)) {
				db.Close();
				return -2;//查询失败
			}
			if (!db.IsEof()){
				db.Close();
				return -3;//用户已存在
			}
			else {
				CString str2 = "insert into [user]([name],[password],[question],[encrypted]) values('"+name+"','"+password+"','"+question+"','"+encrypted+"')";
				CString str3 = "create table ["+name+"] ([time] varchar,[name] varchar,[msg] varchar,[whether] varchar(1))";//添加离线消息列
				if (db.Update((char*)(LPCSTR)str2)) {
					if(db.Update((char*)(LPCSTR)str3)){
						db.Close();
						return 1;//注册成功
					}
				}
				else {
					db.Close();
					return -4;//注册失败
				} 
			}
		}
		db.Close(); 
		//MessageBox(NULL, "系统错误", "Application Error", MB_ICONSTOP);
		return -5;//系统错误
	}
	db.Close();
	//MessageBox(NULL, "接受不完全", "Application Error", MB_ICONSTOP);
	return -6;//接受不完全
}

//忘记密码
int fgPas(void* p) {
	User* client = (User*)p;
	char verify[64];//接受信息
	char code[4];//验证码
	accrCode(code);
	CString name, password, question, encrypted;
	send(client->clientsoc, code, 4, 0);//发送验证码
	int i;//判断是否接收完毕
	for (i = 0; i < 4; i++) {
		memset(verify, 0, 64);
		recvMsg(client->clientsoc, verify);//接收密保
		if (verify[0] == 'e' && verify[1] == 'x' && verify[2] == 'i' && verify[3] == 't')
			return 0;
		switch (i) {
		case 0:
			name = verify;
			break;
		case 1:
			password = verify;
			break;
		case 2:
			question = verify;
			break;
		case 3:
			encrypted = verify;
			break;
		}
	}
	AccessDB db;
	if (i == 4) {
		if (!db.OpenDataBase("student.mdb"))
		{
			db.Close();
			return -1;//数据库打开失败
		}
		else {
			CString str = "select * from [user] where name ='"+name+"'";
			if (!db.Query((char*)(LPCSTR)str))
				db.Close();
				return -2;//查询失败
			if (db.IsEof()) {
				db.Close();
				return -3;//用户不存在
			}
			else {
				char question_2[64];//密保问题
				char encrypted_2[64];//密保
				memset(question_2, 0, 64);
				memset(encrypted_2, 0, 64);
				db.ReadString("question", question_2);
				db.ReadString("encrypted", encrypted_2);
				if (question != question_2 || encrypted != encrypted_2)
					db.Close();
					return -4;//密保错误
			}
			db.Close();
		}

		if (!db.OpenDataBase("student.mdb"))
		{
			db.Close();
			return -1;//数据库打开失败
		}
		else {
			CString str2 = "update [user] set [password] = '"+password+"' where name ='"+name+"'";
			if (db.Update((char*)(LPCSTR)str2)) {
				db.Close();
				return 1;//改密成功
			}
			db.Close();
		}
		db.Close(); 
		return -6;
	}
	db.Close();
	return -7;//接受不完全
}

//生成验证码
void accrCode(char code[4]){
	srand(time(0));
	code[0]=rand()%26+97;
	Sleep(10);
	code[1]=rand()%26+65;
	Sleep(10);
	code[2]=rand()%10+48;
	Sleep(10);
	code[3]=rand()%26+65;
}

//设置离线
int offline(char offname[32]) {
	AccessDB db;
	CString name = offname;
	if (!db.OpenDataBase("student.mdb"))
	{
		db.Close();
		return -1;//数据库打开失败
	}
	else {
		CString str2 = "update [user] set [online] = '0' where name ='" + name + "'";
		if (db.Update((char*)(LPCSTR)str2)) {
			db.Close();
			mapClient.erase(name);
			return 1;//离线成功
		}
		db.Close();
	}
}

//发送用户列表
int sendUser() {
	AccessDB db;
	int i;
	if (!db.OpenDataBase("student.mdb"))
	{
		db.Close();
		return -1;//数据库打开失败
	}
	else {
		for (i = 0; i < MaxListen; i++) {
			if( fd_array_connect[i] ){
				send(fd_array_connect[i], "update", 6, 0);
			}
		}
		CString str = "select * from [user]";
		if (!db.Query((char*)(LPCSTR)str)) {
			db.Close();
			return -2;//查询失败
		}
		else  do{
			char name[32];//昵称
			char line[32];//在线状态
			db.ReadString("name", name); 
			db.ReadString("online", line);
			Sleep(100);
			for (i = 0; i < MaxListen; i++) {
				if( fd_array_connect[i] ){
					send(fd_array_connect[i], name, 32, 0);
				}
			}
			Sleep(100);
			for (i = 0; i < MaxListen; i++) {
				if( fd_array_connect[i] ){
					send(fd_array_connect[i], line, 32, 0);
				}
			}
			db.Next();
		}while (!db.IsEof());
		Sleep(100);
		for (i = 0; i < MaxListen; i++) {
			if( fd_array_connect[i] ){
				send(fd_array_connect[i], "endl", 4, 0);
			}
		}
	}
	db.Close();
}

//更新列表
int uplist(void *p) {
	CServerDlg* sDlg = (CServerDlg*)p;
	sDlg->m_list.DeleteAllItems();// 清空列表
	AccessDB db;
	int i = 0;
	if (!db.OpenDataBase("student.mdb"))
	{
		db.Close();
		return -1;//数据库打开失败
	}
	else {
		CString str = "select * from [user]";
		if (!db.Query((char*)(LPCSTR)str)) {
			db.Close();
			return -2;//查询失败
		}
		else  do {
			char name[32];//昵称
			char line[32];//在线状态
			db.ReadString("name", name);
			db.ReadString("online", line);
			sDlg->m_list.InsertItem(i, name);//添加昵称到用户列表
			if (line[0] == 49) {
				sDlg->m_list.SetItemText(i, 1, "在线");//添加在线状态
				sDlg->m_list.SetItemText(i, 2, inet_ntoa(mapClient.find(name)->second.clientaddr.sin_addr));//添加在线状态
			}
			else {
				sDlg->m_list.SetItemText(i, 1, "离线");//添加在线状态
				sDlg->m_list.SetItemText(i, 2, "无");//添加在线状态
			}
			db.Next();
			i++;
		} while (!db.IsEof());
		db.Close();
	}
}

//接受消息
int recvMsg(SOCKET clientsoc,char* msg){
	while (1) {
		fd_set fdRead;//处于读就绪状态的集合
		FD_ZERO(&fdRead);//将套接字集合清空
		int num=0;//接收数据大小
		FD_SET( clientsoc, &fdRead );//将感兴趣的套接字加入到fdRead集合中
		if (select(0, &fdRead, NULL, NULL, &tv)) {//检查是否有套接字可读 即是否有套接字处于读就绪状态 select返回可用的套接字个数
			ioctlsocket(clientsoc, FIONREAD, (u_long FAR*) & num);//判断接受消息的数据量
			if (recv(clientsoc, msg, num, 0) > 0)
				return 1;
			else return 0;
		}
	}
}

//打开用户信息
void CServerDlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int nselect;
	CString strname;
	nselect=m_list.GetSelectionMark();
	strname=m_list.GetItemText(nselect,0);
	AlterDlg dlg;
	dlg.name=strname;
	dlg.DoModal();
	uplist(this);
	*pResult = 0;
}

//添加用户
void CServerDlg::OnAddUser() 
{
	// TODO: Add your control notification handler code here
	AddDlg dlg;
	dlg.DoModal();
	uplist(this);
}

//发送离线消息
int sendMsg(void *p){
	User *client=(User*)p;
	CString name;
	name=client->name;
	AccessDB db;
	int i=0;
	if (!db.OpenDataBase("student.mdb"))
	{
		return -1;//数据库打开失败
	}
	else {
		CString str = "select * from ["+name+"] where whether='1'";
		if (!db.Query((char*)(LPCSTR)str))
			return -2;//查询失败
		else {
				send(client->clientsoc, "offmsg", 6, 0);
				Sleep(100);
				while (!db.IsEof()){
					char time[255];
					char name[255];
					char msg[255];
					db.ReadString("time", time);
					send(client->clientsoc,time,strlen(time),0);
					Sleep(100);
					db.ReadString("name", name);
					send(client->clientsoc,name,strlen(name),0);
					Sleep(100);
					db.ReadString("msg", msg);
					send(client->clientsoc,msg,strlen(msg),0);
					Sleep(100);
					i++;
					db.Next();
				}
				send(client->clientsoc, "end", 3, 0);
		}
		CString str2 = "update ["+name+"] set [whether] = '0' where whether ='1'";
		db.Update((char*)(LPCSTR)str2);
		db.Close();
		return i;
	}
}
void clearOnLine() {
	AccessDB db;
	if (!db.OpenDataBase("student.mdb"))
	{
		db.Close();
		return;//数据库打开失败
	}
	else {
		CString str2 = "update [user] set [online] = '0'";
		if (db.Update((char*)(LPCSTR)str2)) {
			db.Close();
			return;//离线成功
		}
	}
}

void CServerDlg::OnDestroy()
{
	CDialog::OnDestroy();
	clearOnLine();
	// TODO: 在此处添加消息处理程序代码
}
