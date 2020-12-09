// Arbiter_.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

 //#include <winioctl.h>
 //#include <iostream>
 //#include <direct.h>
#include "..\\inc\\F_IFACE.H"
#include "..\\inc\\4Svc_lib.h"


//using namespace::std;

void GetCurrentPath(char* totalPath){
	getcwd(totalPath,100);
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	static DWORD ProcID=0;
	static HANDLE hProc=0;
	DWORD ExitCode;

	char* cGuid;
	cGuid=(char*)malloc(GUIDCNT);
	strcpy(cGuid,"{aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa}");
	int n=strlen(cGuid);
	
	

	SC_HANDLE hScm;
	SERVICE_STATUS ss;

	// SCM을 전역 변수로 열어 놓는다.
	if(Init_SvcOpen(&hScm,&ss)==FALSE){
		return 0;
	}
	
	ProcID=RQ_RUN_HFILE(cGuid,&hScm,&ss); 
#ifdef _DEBUG
	char* temp=(char*)malloc(1024);
	ZeroMemory(temp,1024);
	itoa(ProcID,temp,10);
	
	MessageBox(NULL,temp,"hi",IDOK);
#endif
	//ProcID로 프로시저 아이디를 받는다
	CloseServiceHandle(hScm);
	
	Sleep(5000);
	//while문을 돌려서 비교 한후 DestroyWindow()를 해준다
	hProc=OpenProcess(PROCESS_QUERY_INFORMATION,FALSE,ProcID);
	
#ifdef _DEBUG
	ZeroMemory(temp,1024);
	itoa((int)hProc,temp,10);
	
	MessageBox(NULL,temp,"hi2",IDOK);
#endif
	
	while(1)
	{
		Sleep(5000);
		GetExitCodeProcess(hProc,&ExitCode);
		if(ExitCode!=STILL_ACTIVE)
		{
			break;
		}
	}
	TerminateProcess(hProc,0);
	
	return 0;
}



