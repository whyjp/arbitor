// ABT_Uninstall_drvNsvc.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <winsvc.h>
#include <io.h>
#include "..\\inc\\F_IFACE.H"
#define DRVNAME "filehide_my"
void Arbiter_Service_unIns();
void Arbiter_Driver_unIns();

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	Arbiter_Service_unIns();
	Arbiter_Driver_unIns();

	if(MessageBox(NULL,"삭제 작업을 마무리하기위해 재부팅해야합니다. 지금 재부팅하려면 실행중인 프로그램을 모두 종료하고 YES를 누르십시오"
		,"warning",MB_YESNO)==IDYES){
		HANDLE hToken;		
		TOKEN_PRIVILEGES tp;		
		LUID luid;
				
		OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
		LookupPrivilegeValue(NULL,"SeShutdownPrivilege",&luid);
		
		
		tp.PrivilegeCount = 1;		
		tp.Privileges[0].Luid = luid;		
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;		
		
		
		AdjustTokenPrivileges(hToken, FALSE, &tp, 0, NULL, NULL);		
		ExitWindowsEx(EWX_REBOOT, 0);
	}
	return 0;
}



void Arbiter_Service_unIns()
{
	SC_HANDLE hScm, hSrv;
	SERVICE_STATUS ss;

	// SCM을 연다
	hScm=OpenSCManager(NULL,NULL,SC_MANAGER_CREATE_SERVICE);
	if (hScm==NULL) {
#ifdef _DEBUG
		MessageBox(NULL,"아비터 SCM을 열 수 없습니다.","서비스",MB_OK);
#endif
		return;
	}

	// 서비스의 핸들을 구한다.
	hSrv=OpenService(hScm,SRVNAME,SERVICE_ALL_ACCESS);
	if (hSrv==NULL) {
		CloseServiceHandle(hScm);
#ifdef _DEBUG
		MessageBox(NULL,"아비터 서비스가 설치되어 있지 않습니다.","서비스",MB_OK);
#endif
		return;
	}

	// 실행중이면 중지시킨다.
	QueryServiceStatus(hSrv,&ss);
	if (ss.dwCurrentState != SERVICE_STOPPED) {
		ControlService(hSrv,SERVICE_CONTROL_STOP,&ss);
		Sleep(2000);
	}

	// 서비스 제거
	if (DeleteService(hSrv)) {
		DeleteFile("c:\\Ab_svc_service.exe");
#ifdef _DEBUG
		MessageBox(NULL,"아비터 서비스를 제거했습니다.","서비스",MB_OK);
#endif		
	} else {
#ifdef _DEBUG
		MessageBox(NULL,"아비터 서비스를 제거하지 못했습니다.","서비스",MB_OK);
#endif
	}
	CloseServiceHandle(hSrv);
	CloseServiceHandle(hScm);
}

void Arbiter_Driver_unIns()
{
	SC_HANDLE hScm, hSrv;


	// SCM을 연다
	hScm=OpenSCManager(NULL,NULL,SC_MANAGER_CREATE_SERVICE);
	if (hScm==NULL) {
#ifdef _DEBUG
		MessageBox(NULL,"SCM을 열 수 없습니다.","드라이버",MB_OK);
#endif
		return;
	}
	
	// 서비스의 핸들을 구한다.
	hSrv=OpenService(hScm,DRVNAME,SERVICE_ALL_ACCESS);
	if (hSrv==NULL) {
		CloseServiceHandle(hScm);
#ifdef _DEBUG
		MessageBox(NULL,"드라이버 서비스가 설치되어 있지 않습니다.","드라이버",MB_OK);
#endif
		return;
	}
	
	

	// 서비스 제거
	if (DeleteService(hSrv)) {
#ifdef _DEBUG
		MessageBox(NULL,"드라이버 서비스를 제거했습니다.","드라이버",MB_OK);
#endif
	} else {
		int a=GetLastError();
#ifdef _DEBUG
		MessageBox(NULL,"드라이버 서비스를 제거하지 못했습니다.","드라이버",MB_OK);
#endif
	}
	CloseServiceHandle(hSrv);
	CloseServiceHandle(hScm);
	DeleteFile("c:\\windows\\system32\\drivers\\filehide_my.sys");
}