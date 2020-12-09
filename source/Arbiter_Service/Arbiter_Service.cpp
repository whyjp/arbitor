#include "Arbiter_Service.h"


extern "C" __declspec(dllexport) void Arbiter_Service_Ins()
{
	SC_HANDLE hScm, hSrv;
	SERVICE_STATUS ss;
	TCHAR SrvPath[MAX_PATH];
	SERVICE_DESCRIPTION lpDes;
	TCHAR Desc[1024];

	// SCM을 연다
	hScm=OpenSCManager(NULL,NULL,SC_MANAGER_CREATE_SERVICE);
	if (hScm==NULL) {
#ifdef _DEBUG
		MessageBox(NULL,"SCM을 열 수 없습니다.","서비스",MB_OK);
#endif
		return;
	}

	// 서비스의 핸들을 구한다.
	hSrv=OpenService(hScm,SRVNAME,SERVICE_ALL_ACCESS);
	if (hSrv!=NULL) {
		
		// 실행중이면 중지시킨다.
#ifdef _DEBUG
		MessageBox(NULL,"아비터 서비스가 설치되어 있습니다.","서비스",MB_OK);
#endif
		QueryServiceStatus(hSrv,&ss);
		if (ss.dwCurrentState != SERVICE_RUNNING) {
			StartService(hSrv,0,NULL);
			Sleep(2000);
		}
#ifdef _DEBUG
		MessageBox(NULL,"아비터 서비스 실행.","서비스",MB_OK);
#endif
		CloseServiceHandle(hScm);
		CloseServiceHandle(hSrv);
		return;
	}

	// 등록할 서비스 파일이 있는지 조사해 보고 경로를 구한다.
	lstrcpy(SrvPath, "C:\\hidden\\");
	lstrcat(SrvPath, EXENAME);
	if (_access(SrvPath,0) != 0) {
		CloseServiceHandle(hScm);
#ifdef _DEBUG
		MessageBox(NULL,"아비터 같은 디렉토리에 서비스 파일이 없습니다.","서비스",MB_OK);
#endif
		return;
	}


	// 서비스를 등록한다.
	hSrv=CreateService(hScm,SRVNAME,DISPNAME,SERVICE_PAUSE_CONTINUE | 
		SERVICE_CHANGE_CONFIG,SERVICE_WIN32_OWN_PROCESS|SERVICE_INTERACTIVE_PROCESS,SERVICE_AUTO_START,
		SERVICE_ERROR_IGNORE,SrvPath,NULL,NULL,NULL,NULL,NULL);
	if (hSrv==NULL) {
#ifdef _DEBUG
		MessageBox(NULL,"아비터 설치하지 못했습니다.","서비스",MB_OK);
#endif		
	} else {
		// 설명을 등록한다.
		char* tempa=(char*)malloc(sizeof(char)*1024);
		ZeroMemory(tempa,sizeof(char)*1024);
		strcpy(tempa,"아비터의 서비스 입니다 이 서비스는 드라이버와 통신하게됩니다");
		lstrcpy(Desc,tempa);
		lpDes.lpDescription=Desc;
		ChangeServiceConfig2(hSrv, SERVICE_CONFIG_DESCRIPTION, &lpDes);
#ifdef _DEBUG
		MessageBox(NULL,"아비터 설치했습니다.","서비스",MB_OK);
#endif
		QueryServiceStatus(hSrv,&ss);
		if (ss.dwCurrentState != SERVICE_RUNNING) {
			StartService(hSrv,0,NULL);
			Sleep(2000);
		}
#ifdef _DEBUG
		MessageBox(NULL,"아비터 서비스를 실행 했습니다.","서비스",MB_OK);
#endif		
		CloseServiceHandle(hSrv);
	}

	CloseServiceHandle(hScm);
}

extern "C" __declspec(dllexport) void Arbiter_Service_unIns()
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