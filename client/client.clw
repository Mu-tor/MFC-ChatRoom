; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=DeleteMsg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "client.h"

ClassCount=10
Class1=CclientApp
Class3=SigninDlg

ResourceCount=10
Resource1=IDD_Dialog2
Resource2=IDR_MAINFRAME
Resource3=IDD_DIALOG1
Class4=LoginDlg
Resource4=IDD_Forget
Class2=CAboutDlg
Class5=Dialog
Resource5=IDD_ABOUTBOX
Class6=ForgetDlg
Resource6=IDD_DIALOG3
Class7=Dialog2
Resource7=IDD_Login
Class8=MsgEx
Resource8=IDD_Dialog
Class9=Inform
Resource9=IDD_Signin
Class10=DeleteMsg
Resource10=IDD_Delete

[CLS:CclientApp]
Type=0
HeaderFile=client.h
ImplementationFile=client.cpp
Filter=N

[CLS:CAboutDlg]
Type=0
HeaderFile=clientDlg.h
ImplementationFile=clientDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_Login]
Type=1
Class=LoginDlg
ControlCount=7
Control1=IDD_Signin,button,1342242816
Control2=IDC_STATIC,static,1342308353
Control3=IDC_STATIC,static,1342308353
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_EDIT2,edit,1350631584
Control6=ID_Login,button,1342242816
Control7=IDC_Forget,button,1342242816

[DLG:IDD_Signin]
Type=1
Class=SigninDlg
ControlCount=15
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308354
Control4=IDC_STATIC,static,1342308354
Control5=IDC_STATIC,static,1342308354
Control6=IDC_STATIC,static,1342308354
Control7=IDC_STATIC,static,1342308354
Control8=IDC_EDIT1,edit,1350631552
Control9=IDC_EDIT4,edit,1350631552
Control10=IDC_EDIT2,edit,1350631584
Control11=IDC_EDIT3,edit,1350631584
Control12=IDC_COMBO1,combobox,1344340226
Control13=IDC_STATIC,static,1342308354
Control14=IDC_EDIT6,edit,1350633600
Control15=IDC_EDIT7,edit,1350631552

[CLS:SigninDlg]
Type=0
HeaderFile=SigninDlg.h
ImplementationFile=SigninDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT1

[CLS:LoginDlg]
Type=0
HeaderFile=LoginDlg.h
ImplementationFile=LoginDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT1


[DLG:IDD_Dialog]
Type=1
Class=Dialog
ControlCount=8
Control1=IDC_Xxk,edit,1353780292
Control2=IDC_Bul,edit,1350631552
Control3=IDC_Send,button,1342242816
Control4=IDC_Name,edit,1350633600
Control5=IDC_LIST1,SysListView32,1350631437
Control6=IDC_STATIC,static,1342308352
Control7=IDC_BUTTON2,button,1342242816
Control8=IDC_BUTTON4,button,1342242816

[CLS:Dialog]
Type=0
HeaderFile=Dialog.h
ImplementationFile=Dialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=Dialog

[CLS:ForgetDlg]
Type=0
HeaderFile=ForgetDlg.h
ImplementationFile=ForgetDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT2
VirtualFilter=dWC

[DLG:IDD_Forget]
Type=1
Class=ForgetDlg
ControlCount=15
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308354
Control4=IDC_COMBO1,combobox,1344340226
Control5=IDC_EDIT2,edit,1350631552
Control6=IDC_STATIC,static,1342308354
Control7=IDC_EDIT1,edit,1350631552
Control8=IDC_STATIC,static,1342308354
Control9=IDC_EDIT4,edit,1350631584
Control10=IDC_STATIC,static,1342308354
Control11=IDC_EDIT3,edit,1350631584
Control12=IDC_STATIC,static,1342308354
Control13=IDC_STATIC,static,1342308354
Control14=IDC_EDIT6,edit,1350633600
Control15=IDC_EDIT7,edit,1350631552

[CLS:Dialog2]
Type=0
HeaderFile=Dialog2.h
ImplementationFile=Dialog2.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT1
VirtualFilter=dWC

[DLG:IDD_Dialog2]
Type=1
Class=Dialog2
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT1,edit,1350633472
Control3=IDC_EDIT2,edit,1353780420
Control4=IDC_EDIT3,edit,1350631552
Control5=IDC_BUTTON1,button,1342242816
Control6=IDC_BUTTON2,button,1342242816

[DLG:IDD_DIALOG1]
Type=1
Class=MsgEx
ControlCount=4
Control1=IDC_LIST1,SysListView32,1350631429
Control2=IDC_EDIT1,edit,1350633601
Control3=IDC_STATIC,static,1342308864
Control4=IDC_STATIC,static,1342308864

[CLS:MsgEx]
Type=0
HeaderFile=MsgEx.h
ImplementationFile=MsgEx.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT2

[DLG:IDD_DIALOG3]
Type=1
Class=Inform
ControlCount=3
Control1=IDCANCEL,button,1342242817
Control2=IDC_STATIC,static,1342308865
Control3=IDC_EDIT1,edit,1352730757

[CLS:Inform]
Type=0
HeaderFile=Inform.h
ImplementationFile=Inform.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT1

[DLG:IDD_Delete]
Type=1
Class=DeleteMsg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342178055

[CLS:DeleteMsg]
Type=0
HeaderFile=DeleteMsg.h
ImplementationFile=DeleteMsg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDOK
VirtualFilter=dWC

