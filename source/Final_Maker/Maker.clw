; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=Start
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "maker.h"
LastPage=0

ClassCount=10
Class1=FindFilePage
Class2=FindFilePage2
Class3=FindLSCPage
Class4=FinishPage
Class5=ChangePage
Class6=CMakerApp
Class7=SavePage
Class8=Sheet
Class9=Start
Class10=Welcome

ResourceCount=9
Resource1=IDD_WELCOME
Resource2=IDD_CHANGE
Resource3=IDD_FINISH
Resource4=IDD_FINDLSC
Resource5=IDD_FINDFILE
Resource6=IDD_FINDFILE1
Resource7=IDD_SAVE
Resource8=IDD_START
Resource9=IDD_SHEET

[CLS:FindFilePage]
Type=0
BaseClass=CPropertyPage
HeaderFile=FindFilePage.h
ImplementationFile=FindFilePage.cpp
Filter=D
VirtualFilter=idWC

[CLS:FindFilePage2]
Type=0
BaseClass=CPropertyPage
HeaderFile=FindFilePage2.h
ImplementationFile=FindFilePage2.cpp
Filter=D
VirtualFilter=idWC
LastObject=IDC_ANIMATE1

[CLS:FindLSCPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=FindLSCPage.h
ImplementationFile=FindLSCPage.cpp

[CLS:FinishPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=FinishPage.h
ImplementationFile=FinishPage.cpp

[CLS:ChangePage]
Type=0
BaseClass=CPropertyPage
HeaderFile=hangePage.h
ImplementationFile=hangePage.cpp

[CLS:CMakerApp]
Type=0
BaseClass=CWinApp
HeaderFile=Maker.h
ImplementationFile=Maker.cpp

[CLS:SavePage]
Type=0
BaseClass=CPropertyPage
HeaderFile=SavePage.h
ImplementationFile=SavePage.cpp

[CLS:Sheet]
Type=0
BaseClass=CPropertySheet
HeaderFile=Sheet.h
ImplementationFile=Sheet.cpp

[CLS:Start]
Type=0
BaseClass=CPropertyPage
HeaderFile=Start.h
ImplementationFile=Start.cpp
Filter=D
VirtualFilter=idWC
LastObject=IDC_OK

[CLS:Welcome]
Type=0
BaseClass=CPropertyPage
HeaderFile=Welcome.h
ImplementationFile=Welcome.cpp
Filter=D
VirtualFilter=idWC

[DLG:IDD_FINDFILE]
Type=1
Class=FindFilePage
ControlCount=9
Control1=IDC_FINDFILE,edit,1350633600
Control2=IDC_FIND2,button,1342242816
Control3=IDC_FILE,listbox,1353777419
Control4=IDC_FIND,button,1342242816
Control5=IDC_CANCLE,button,1342242816
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,button,1342177287
Control9=IDC_STATIC,static,1342177294

[DLG:IDD_FINDFILE1]
Type=1
Class=FindFilePage2
ControlCount=6
Control1=IDC_FILE,listbox,1353777418
Control2=IDC_FIND,button,1342242816
Control3=IDC_CANCLE,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,static,1342177294

[DLG:IDD_FINDLSC]
Type=1
Class=FindLSCPage
ControlCount=13
Control1=IDC_LSCDIR,edit,1350633600
Control2=IDC_FIND,button,1342242816
Control3=IDC_ICONDIR,edit,1350633600
Control4=IDC_FIND2,button,1342242816
Control5=IDC_UICON,edit,1350633600
Control6=IDC_FIND4,button,1342242816
Control7=IDC_VER,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,static,1342177294

[DLG:IDD_FINISH]
Type=1
Class=FinishPage
ControlCount=2
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342177294

[DLG:IDD_CHANGE]
Type=1
Class=ChangePage
ControlCount=11
Control1=IDC_CONAME,edit,1350631552
Control2=IDC_SETUPNAME,edit,1350631552
Control3=IDC_SAVE,edit,1350633600
Control4=IDC_FIND2,button,1342242816
Control5=IDC_PRONAME,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,button,1342177287
Control11=IDC_STATIC,static,1342177294

[DLG:IDD_SAVE]
Type=1
Class=SavePage
ControlCount=5
Control1=IDC_SAVEDIR,edit,1350633600
Control2=IDC_FIND,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,static,1342177294

[DLG:IDD_START]
Type=1
Class=Start
ControlCount=2
Control1=IDC_OK,button,1342242819
Control2=IDC_STATIC,static,1342177294

[DLG:IDD_WELCOME]
Type=1
Class=Welcome
ControlCount=1
Control1=IDC_SHOCKWAVEFLASH1,{D27CDB6E-AE6D-11CF-96B8-444553540000},1342242816

[DLG:IDD_SHEET]
Type=1
Class=?
ControlCount=0

