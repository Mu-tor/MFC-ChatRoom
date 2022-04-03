; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=AddDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "server.h"

ClassCount=5
Class1=CServerApp
Class2=CServerDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_SERVER_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_AlterDlg
Class4=AlterDlg
Resource4=IDD_ABOUTBOX
Class5=AddDlg
Resource5=IDD_DIALOG1

[CLS:CServerApp]
Type=0
HeaderFile=server.h
ImplementationFile=server.cpp
Filter=N

[CLS:CServerDlg]
Type=0
HeaderFile=serverDlg.h
ImplementationFile=serverDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_EDIT1

[CLS:CAboutDlg]
Type=0
HeaderFile=serverDlg.h
ImplementationFile=serverDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SERVER_DIALOG]
Type=1
Class=CServerDlg
ControlCount=9
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT1,edit,1350631552
Control3=IDC_BUTTON1,button,1342242816
Control4=IDC_EDIT3,edit,1350631552
Control5=IDC_BUTTON2,button,1342242816
Control6=IDC_STATIC,static,1342308352
Control7=IDC_LIST1,SysListView32,1350633473
Control8=IDC_BUTTON3,button,1342242816
Control9=IDC_EDIT2,edit,1353779268

[CLS:AlterDlg]
Type=0
HeaderFile=AlterDlg.h
ImplementationFile=AlterDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[DLG:IDD_AlterDlg]
Type=1
Class=AlterDlg
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDIT1,edit,1350633601
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT2,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT3,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EDIT4,edit,1350631552
Control10=IDC_BUTTON1,button,1342242816

[DLG:IDD_DIALOG1]
Type=1
Class=AddDlg
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT2,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT3,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT4,edit,1350631552

[CLS:AddDlg]
Type=0
HeaderFile=AddDlg.h
ImplementationFile=AddDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

