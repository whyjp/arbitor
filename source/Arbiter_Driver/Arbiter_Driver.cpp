#include "Arbiter_Driver.h"


extern "C" __declspec(dllexport) void Arbiter_Driver_Ins()
{
	HANDLE hSrv;
	
	HANDLE hScm;

	hScm = OpenSCManager(0,0,SC_MANAGER_ALL_ACCESS);//���� �Ŵ����� ����.
	
	if (hScm==NULL) {
#ifdef _DEBUG
		MessageBox(NULL,"SCM�� �� �� �����ϴ�.","����̹�",MB_OK);
#endif
		return;
	}

	char driverPath[128];                         
	memset(driverPath,0,128);
	
	GetCurrentDirectory(128,driverPath);     //���� ���丮�� ������ �н��� �˾Ƴ���.
	lstrcat(driverPath, "\\");
	
	lstrcat(driverPath, "filehide_my.sys");

	// ������ �ڵ��� ���Ѵ�.
	hSrv=OpenService(hScm,SRVNAME,SERVICE_ALL_ACCESS);
	if (hSrv!=NULL) {
		DeleteFile(driverPath);
		CloseServiceHandle(hScm);
		StartService(hSrv,0,0);      //���񽺸� �����Ѵ�.
#ifdef _DEBUG
		MessageBox(NULL,"���񽺰� ��ġ�Ǿ� �ֽ��ϴ�.","����̹�",MB_OK);
#endif
		return;
	}
	
	CopyFile(driverPath,NEW_DRIVER_PATH,FALSE);
	DeleteFile(driverPath);
	
	hSrv = CreateService(hScm, SRVNAME , SRVNAME, SERVICE_ALL_ACCESS,
		
		SERVICE_KERNEL_DRIVER, SERVICE_SYSTEM_START, SERVICE_ERROR_NORMAL,
		
		NEW_DRIVER_PATH,0,0,0,0,0);             //���񽺸� �����Ѵ�.

	DWORD a=GetLastError();
	if(a!=0){
#ifdef _DEBUG
		MessageBox(NULL,"����̹� ���� ��� ����","����̹�",MB_OK);
#endif
	}
	else{
#ifdef _DEBUG
		MessageBox(NULL,"����̹� ���� ���","����̹�",MB_OK);
#endif
		StartService(hSrv,0,0);      //���񽺸� �����Ѵ�.
	}	
	CloseServiceHandle(hSrv);           //������ �ڵ��� �ݴ´�.
		
	CloseServiceHandle(hScm);        //���� �Ŵ����� �ڵ��� �ݴ´�.
}

extern "C" __declspec(dllexport) void Arbiter_Driver_unIns()
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
	hSrv=OpenService(hScm,SRVNAME,SERVICE_ALL_ACCESS);
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