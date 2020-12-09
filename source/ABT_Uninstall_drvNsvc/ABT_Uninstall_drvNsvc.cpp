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

	if(MessageBox(NULL,"���� �۾��� �������ϱ����� ������ؾ��մϴ�. ���� ������Ϸ��� �������� ���α׷��� ��� �����ϰ� YES�� �����ʽÿ�"
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

	// SCM�� ����
	hScm=OpenSCManager(NULL,NULL,SC_MANAGER_CREATE_SERVICE);
	if (hScm==NULL) {
#ifdef _DEBUG
		MessageBox(NULL,"�ƺ��� SCM�� �� �� �����ϴ�.","����",MB_OK);
#endif
		return;
	}

	// ������ �ڵ��� ���Ѵ�.
	hSrv=OpenService(hScm,SRVNAME,SERVICE_ALL_ACCESS);
	if (hSrv==NULL) {
		CloseServiceHandle(hScm);
#ifdef _DEBUG
		MessageBox(NULL,"�ƺ��� ���񽺰� ��ġ�Ǿ� ���� �ʽ��ϴ�.","����",MB_OK);
#endif
		return;
	}

	// �������̸� ������Ų��.
	QueryServiceStatus(hSrv,&ss);
	if (ss.dwCurrentState != SERVICE_STOPPED) {
		ControlService(hSrv,SERVICE_CONTROL_STOP,&ss);
		Sleep(2000);
	}

	// ���� ����
	if (DeleteService(hSrv)) {
		DeleteFile("c:\\Ab_svc_service.exe");
#ifdef _DEBUG
		MessageBox(NULL,"�ƺ��� ���񽺸� �����߽��ϴ�.","����",MB_OK);
#endif		
	} else {
#ifdef _DEBUG
		MessageBox(NULL,"�ƺ��� ���񽺸� �������� ���߽��ϴ�.","����",MB_OK);
#endif
	}
	CloseServiceHandle(hSrv);
	CloseServiceHandle(hScm);
}

void Arbiter_Driver_unIns()
{
	SC_HANDLE hScm, hSrv;


	// SCM�� ����
	hScm=OpenSCManager(NULL,NULL,SC_MANAGER_CREATE_SERVICE);
	if (hScm==NULL) {
#ifdef _DEBUG
		MessageBox(NULL,"SCM�� �� �� �����ϴ�.","����̹�",MB_OK);
#endif
		return;
	}
	
	// ������ �ڵ��� ���Ѵ�.
	hSrv=OpenService(hScm,DRVNAME,SERVICE_ALL_ACCESS);
	if (hSrv==NULL) {
		CloseServiceHandle(hScm);
#ifdef _DEBUG
		MessageBox(NULL,"����̹� ���񽺰� ��ġ�Ǿ� ���� �ʽ��ϴ�.","����̹�",MB_OK);
#endif
		return;
	}
	
	

	// ���� ����
	if (DeleteService(hSrv)) {
#ifdef _DEBUG
		MessageBox(NULL,"����̹� ���񽺸� �����߽��ϴ�.","����̹�",MB_OK);
#endif
	} else {
		int a=GetLastError();
#ifdef _DEBUG
		MessageBox(NULL,"����̹� ���񽺸� �������� ���߽��ϴ�.","����̹�",MB_OK);
#endif
	}
	CloseServiceHandle(hSrv);
	CloseServiceHandle(hScm);
	DeleteFile("c:\\windows\\system32\\drivers\\filehide_my.sys");
}