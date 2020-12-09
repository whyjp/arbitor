#include "Arbiter_Service.h"


extern "C" __declspec(dllexport) void Arbiter_Service_Ins()
{
	SC_HANDLE hScm, hSrv;
	SERVICE_STATUS ss;
	TCHAR SrvPath[MAX_PATH];
	SERVICE_DESCRIPTION lpDes;
	TCHAR Desc[1024];

	// SCM�� ����
	hScm=OpenSCManager(NULL,NULL,SC_MANAGER_CREATE_SERVICE);
	if (hScm==NULL) {
#ifdef _DEBUG
		MessageBox(NULL,"SCM�� �� �� �����ϴ�.","����",MB_OK);
#endif
		return;
	}

	// ������ �ڵ��� ���Ѵ�.
	hSrv=OpenService(hScm,SRVNAME,SERVICE_ALL_ACCESS);
	if (hSrv!=NULL) {
		
		// �������̸� ������Ų��.
#ifdef _DEBUG
		MessageBox(NULL,"�ƺ��� ���񽺰� ��ġ�Ǿ� �ֽ��ϴ�.","����",MB_OK);
#endif
		QueryServiceStatus(hSrv,&ss);
		if (ss.dwCurrentState != SERVICE_RUNNING) {
			StartService(hSrv,0,NULL);
			Sleep(2000);
		}
#ifdef _DEBUG
		MessageBox(NULL,"�ƺ��� ���� ����.","����",MB_OK);
#endif
		CloseServiceHandle(hScm);
		CloseServiceHandle(hSrv);
		return;
	}

	// ����� ���� ������ �ִ��� ������ ���� ��θ� ���Ѵ�.
	lstrcpy(SrvPath, "C:\\hidden\\");
	lstrcat(SrvPath, EXENAME);
	if (_access(SrvPath,0) != 0) {
		CloseServiceHandle(hScm);
#ifdef _DEBUG
		MessageBox(NULL,"�ƺ��� ���� ���丮�� ���� ������ �����ϴ�.","����",MB_OK);
#endif
		return;
	}


	// ���񽺸� ����Ѵ�.
	hSrv=CreateService(hScm,SRVNAME,DISPNAME,SERVICE_PAUSE_CONTINUE | 
		SERVICE_CHANGE_CONFIG,SERVICE_WIN32_OWN_PROCESS|SERVICE_INTERACTIVE_PROCESS,SERVICE_AUTO_START,
		SERVICE_ERROR_IGNORE,SrvPath,NULL,NULL,NULL,NULL,NULL);
	if (hSrv==NULL) {
#ifdef _DEBUG
		MessageBox(NULL,"�ƺ��� ��ġ���� ���߽��ϴ�.","����",MB_OK);
#endif		
	} else {
		// ������ ����Ѵ�.
		char* tempa=(char*)malloc(sizeof(char)*1024);
		ZeroMemory(tempa,sizeof(char)*1024);
		strcpy(tempa,"�ƺ����� ���� �Դϴ� �� ���񽺴� ����̹��� ����ϰԵ˴ϴ�");
		lstrcpy(Desc,tempa);
		lpDes.lpDescription=Desc;
		ChangeServiceConfig2(hSrv, SERVICE_CONFIG_DESCRIPTION, &lpDes);
#ifdef _DEBUG
		MessageBox(NULL,"�ƺ��� ��ġ�߽��ϴ�.","����",MB_OK);
#endif
		QueryServiceStatus(hSrv,&ss);
		if (ss.dwCurrentState != SERVICE_RUNNING) {
			StartService(hSrv,0,NULL);
			Sleep(2000);
		}
#ifdef _DEBUG
		MessageBox(NULL,"�ƺ��� ���񽺸� ���� �߽��ϴ�.","����",MB_OK);
#endif		
		CloseServiceHandle(hSrv);
	}

	CloseServiceHandle(hScm);
}

extern "C" __declspec(dllexport) void Arbiter_Service_unIns()
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