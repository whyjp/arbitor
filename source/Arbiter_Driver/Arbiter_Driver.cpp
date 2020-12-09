#include "Arbiter_Driver.h"


extern "C" __declspec(dllexport) void Arbiter_Driver_Ins()
{
	HANDLE hSrv;
	
	HANDLE hScm;

	hScm = OpenSCManager(0,0,SC_MANAGER_ALL_ACCESS);//서비스 매니저를 연다.
	
	if (hScm==NULL) {
#ifdef _DEBUG
		MessageBox(NULL,"SCM을 열 수 없습니다.","드라이버",MB_OK);
#endif
		return;
	}

	char driverPath[128];                         
	memset(driverPath,0,128);
	
	GetCurrentDirectory(128,driverPath);     //현재 디렉토리의 절대경로 패스를 알아낸다.
	lstrcat(driverPath, "\\");
	
	lstrcat(driverPath, "filehide_my.sys");

	// 서비스의 핸들을 구한다.
	hSrv=OpenService(hScm,SRVNAME,SERVICE_ALL_ACCESS);
	if (hSrv!=NULL) {
		DeleteFile(driverPath);
		CloseServiceHandle(hScm);
		StartService(hSrv,0,0);      //서비스를 시작한다.
#ifdef _DEBUG
		MessageBox(NULL,"서비스가 설치되어 있습니다.","드라이버",MB_OK);
#endif
		return;
	}
	
	CopyFile(driverPath,NEW_DRIVER_PATH,FALSE);
	DeleteFile(driverPath);
	
	hSrv = CreateService(hScm, SRVNAME , SRVNAME, SERVICE_ALL_ACCESS,
		
		SERVICE_KERNEL_DRIVER, SERVICE_SYSTEM_START, SERVICE_ERROR_NORMAL,
		
		NEW_DRIVER_PATH,0,0,0,0,0);             //서비스를 생성한다.

	DWORD a=GetLastError();
	if(a!=0){
#ifdef _DEBUG
		MessageBox(NULL,"드라이버 서비스 등록 실패","드라이버",MB_OK);
#endif
	}
	else{
#ifdef _DEBUG
		MessageBox(NULL,"드라이버 서비스 등록","드라이버",MB_OK);
#endif
		StartService(hSrv,0,0);      //서비스를 시작한다.
	}	
	CloseServiceHandle(hSrv);           //서비스의 핸들을 닫는다.
		
	CloseServiceHandle(hScm);        //서비스 매니저의 핸들을 닫는다.
}

extern "C" __declspec(dllexport) void Arbiter_Driver_unIns()
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
	hSrv=OpenService(hScm,SRVNAME,SERVICE_ALL_ACCESS);
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