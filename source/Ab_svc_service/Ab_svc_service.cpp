
#include <windows.h>
#include <winioctl.h>
#include <winsvc.h>
#include <io.h>
#include "..\\inc\\F_IFACE.H"
#include "..\\inc\\des\\include.h"
#include <vector>
using namespace std;

#define HFLISTPATH "c:\\hFList.abt"
#define MAXHFARR 30
#define UNINSTALL_ABTNSVC_PATH "c:\\hidden\\ABT_Uninstall_drvNsvc.exe"

void MyServiceMain(DWORD argc, LPTSTR *argv);
void MyServiceHandler(DWORD opCode);
void MyDeviceHandler(DWORD fdwControl);
BOOL InitDIOStart();
void MyGuidMaker(char* ResultGUIDSt);
wchar_t* CharToWChar(const char* pstrSrc);

void Open_HFList();
BOOL Save_HFList();

SERVICE_STATUS_HANDLE g_hSrv;
DWORD g_NowState;
BOOL g_bPause;

HANDLE handle;
ULONG dwRet;
HANDLE Event;
HANDLE hMutex;

HANDLE g_ExitEvent;



PHFILE_ATT phfile_arr[MAXHFARR];

int main()
{
	SERVICE_TABLE_ENTRY ste[]={
		{SRVNAME,(LPSERVICE_MAIN_FUNCTION)MyServiceMain},
		{NULL,NULL}
	};
	
	StartServiceCtrlDispatcher(ste);
	
	return 0;
}

// ������ ���� ���¸� �����ϴ� �Լ�
void MySetStatus(DWORD dwState, DWORD dwAccept=SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE)
{
	SERVICE_STATUS ss;
	ss.dwServiceType=SERVICE_WIN32_OWN_PROCESS|SERVICE_INTERACTIVE_PROCESS;
	ss.dwCurrentState=dwState;
	ss.dwControlsAccepted=dwAccept;
	ss.dwWin32ExitCode=0;
	ss.dwServiceSpecificExitCode=0;
	ss.dwCheckPoint=0;
	ss.dwWaitHint=0;
	
	// ���� ���¸� ������ �д�.
	g_NowState=dwState;
	SetServiceStatus(g_hSrv,&ss);
}

void MyServiceMain(DWORD argc, LPTSTR *argv)
{
	// ���� �ڵ鷯�� ����Ѵ�.
	g_hSrv=RegisterServiceCtrlHandler(SRVNAME,(LPHANDLER_FUNCTION)MyServiceHandler);
	if (g_hSrv==0) {
		MySetStatus(SERVICE_STOPPED);
		return;
	}

	
	// ���񽺰� ���������� �˸���.
	MySetStatus(SERVICE_START_PENDING);
	// �̺�Ʈ�� �����Ѵ�.
	g_ExitEvent=CreateEvent(NULL, TRUE, FALSE, "MemStatExit");
	hMutex=CreateMutex(NULL,FALSE,MUTEXNAME);
	
	// ���� ������ �ʱ�ȭ�Ѵ�.
	g_bPause=FALSE;
	
	if(!InitDIOStart()){
		return;
	}
	
	for(int i=0;i<MAXHFARR;i++){
		phfile_arr[i]=NULL;
	}
	
	Open_HFList();
	MySetStatus(SERVICE_RUNNING);
	
	
	for(;;){
		if (WaitForSingleObject(g_ExitEvent, 10000) == WAIT_OBJECT_0)
			break;
	}
	Save_HFList();
	CloseHandle(hMutex);
	MySetStatus(SERVICE_STOPPED);
	
	// �̺�Ʈ�� ������	
	// ���񽺰� ���۵Ǿ����� �˸���.
	
}
void Open_HFList(){
	HANDLE hfList;
	hfList=CreateFile(HFLISTPATH,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hfList == INVALID_HANDLE_VALUE){
		return;
	}
	int* totalcnt=(int*)malloc(sizeof(int));
	DWORD dwRead;
	
	
	PADD_HIDDEN_FILE pFile=(PADD_HIDDEN_FILE)malloc(sizeof(ADD_HIDDEN_FILE));
	ZeroMemory(pFile,sizeof(ADD_HIDDEN_FILE));
	HIDDEN_FILE_HANDLE hiddenhandle;
	PADD_GUID_FNAME pFnguid=(PADD_GUID_FNAME)malloc(sizeof(ADD_GUID_FNAME));
	ZeroMemory(pFnguid,sizeof(ADD_GUID_FNAME));
	//////////////////////////////////////////////////////////////////////////
	LPWSTR tempfname;
	PHFILE_ATT phfile_att_temp;
	
	ReadFile(hfList,totalcnt,sizeof(int),&dwRead,NULL);
	for(int i=0;i<*totalcnt;i++){
		phfile_att_temp=(PHFILE_ATT)malloc(sizeof(HFILE_ATT));
		ZeroMemory(phfile_att_temp,sizeof(HFILE_ATT));
		//�ڸ��ϳ� ��� �޴´� �ϴ�
		ReadFile(hfList,phfile_att_temp,sizeof(HFILE_ATT),&dwRead,NULL);
		phfile_arr[i]=phfile_att_temp;
		
		tempfname=CharToWChar(phfile_arr[i]->Filename);
		wcscpy(pFile->Filename,tempfname);
		DeviceIoControl( handle, IOCTL_ADD_HIDDEN_FILE, pFile, sizeof(ADD_HIDDEN_FILE), &hiddenhandle, sizeof(HIDDEN_FILE_HANDLE), &dwRet, 0 );
		phfile_arr[i]->handleno=hiddenhandle.Handle;

		tempfname=CharToWChar(phfile_arr[i]->Filename);
		wcscpy(pFnguid->Filename,tempfname);

		tempfname=CharToWChar(phfile_arr[i]->Guid);
		wcscpy(pFnguid->Guid,tempfname);

		DeviceIoControl( handle, IOCTL_ADD_GUID, pFnguid, sizeof(ADD_GUID_FNAME), 0, 0, &dwRet, 0 );
		phfile_att_temp=NULL;
	}
	DeviceIoControl( handle, IOCTL_HIDDEN_FILES, NULL, 0, NULL, 0, &dwRet, 0 );
	
	
	//////////////////////////////////////////////////////////////////////////
	//�̺κ��̹�����!!
	if(hfList){
		CloseHandle(hfList);
	}
	free(pFile);
	free(pFnguid);
	pFile=NULL;
	pFnguid=NULL;
}
BOOL Save_HFList(){
	HANDLE hfList;

	int totalcnt=0;
	for(int j=0;j<MAXHFARR;j++){
		if(phfile_arr[j]!=NULL){
			totalcnt++;
		}
	}
	if(totalcnt==0){
		if (_access(HFLISTPATH,0)==0) {
			DeleteFile(HFLISTPATH);
		}
		return TRUE;
	}

	hfList=CreateFile(HFLISTPATH,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hfList==INVALID_HANDLE_VALUE){
		return FALSE;
	}

	DWORD dwWrite;
	
	WriteFile(hfList,&totalcnt,sizeof(int),&dwWrite,NULL);
	for(int i=0;i<totalcnt;i++){
		if(phfile_arr[i]){
			WriteFile(hfList,phfile_arr[i],sizeof(HFILE_ATT),&dwWrite,NULL);
		}
	}
	if(hfList){
		CloseHandle(hfList);
	}
	return FALSE;
}

// �ڵ鷯 �Լ�
void MyServiceHandler(DWORD fdwControl)
{
	// ���� ���¿� ���� ���� �ڵ��� ���� ó���� �ʿ� ����.
	if (fdwControl == g_NowState)
		return;
	
	switch (fdwControl) {
	case SERVICE_CONTROL_PAUSE:
		MySetStatus(SERVICE_PAUSE_PENDING,0);
		g_bPause=TRUE;
		MySetStatus(SERVICE_PAUSED);
		break;
	case SERVICE_CONTROL_CONTINUE:
		MySetStatus(SERVICE_CONTINUE_PENDING,0);
		g_bPause=FALSE;
		MySetStatus(SERVICE_RUNNING);
		break;
	case SERVICE_CONTROL_STOP:
		MySetStatus(SERVICE_STOP_PENDING,0);
		if(handle==(HANDLE)-1){
			return;
		}
		
		CloseHandle( Event );
		CloseHandle( handle );
		
		SetEvent(g_ExitEvent);
		break;
	case SERVICE_HIDDEN_FILES:
	case SERVICE_SHOW_FILES :
	case SERVICE_ADD_HIDDEN_FILE :
	case SERVICE_DEL_HIDDEN_FILE :
	case SERVICE_ALL_RESET_HIDDEN_FILES :
	case SERVICE_SET_DRIVE :
	case SERVICE_SET_EVENT :
	case SERVICE_ADD_GUID :
	case SERVICE_DEL_GUID :
	case SERVICE_RUN_HFILE:
	case SERVICE_DEL_HFILE:
	case SERVICE_ADD_LIST:
	case SERVICE_GET_AT_LIST:
	case SERVICE_DEL_HF_AT_UNINSTALL:
		MyDeviceHandler(fdwControl);
		break;
	case SERVICE_CONTROL_INTERROGATE:
	default:
		MySetStatus(g_NowState);
		break;
	}
}

DWORD WINAPI Add_Hidden_File_Fuc(LPVOID lpParam){
	//�������κ��� �޾Ƽ� �־� �ٽ� �������� �ڵ鰪��  ��� 
	PADD_HIDDEN_FILE pFile=(PADD_HIDDEN_FILE)malloc(sizeof(ADD_HIDDEN_FILE));
	ZeroMemory(pFile,sizeof(ADD_HIDDEN_FILE));
	HIDDEN_FILE_HANDLE hiddenhandle;
	//�������κ��� �޾Ƽ� ����ü �����Ϳ� �־� ����̽��� �ѱ�� 
	DWORD dwRead;
	HANDLE Pipe_tosvc;
	WaitForSingleObject(hMutex,INFINITE);
	for(;;){
		Sleep(100);
		Pipe_tosvc=CreateFile(P_TOSERVICE,GENERIC_READ,0,NULL,OPEN_EXISTING,0,NULL);
		if(Pipe_tosvc!=INVALID_HANDLE_VALUE){
			break;
		}
	}
	
	ReadFile(Pipe_tosvc,pFile,sizeof(ADD_HIDDEN_FILE),&dwRead,NULL);
	CloseHandle(Pipe_tosvc);
	
	DeviceIoControl( handle, IOCTL_ADD_HIDDEN_FILE, pFile, sizeof(ADD_HIDDEN_FILE), &hiddenhandle, sizeof(HIDDEN_FILE_HANDLE), &dwRet, 0 );
	DWORD dwWrite;
	HANDLE Pipe_fromsvc;
	for(;;){
		Sleep(100);
		Pipe_fromsvc=CreateFile(P_FROMSERVICE,GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
		if(Pipe_fromsvc!=INVALID_HANDLE_VALUE){
			break;
		}
	}
	WriteFile(Pipe_fromsvc,&hiddenhandle,sizeof(HIDDEN_FILE_HANDLE),&dwWrite,NULL);
	CloseHandle(Pipe_fromsvc);
	DeviceIoControl( handle, IOCTL_HIDDEN_FILES, NULL, 0, NULL, 0, &dwRet, 0 );

	free(pFile);
	pFile=NULL;
	ReleaseMutex(hMutex);
	return 0;
}
DWORD WINAPI Del_Hidden_File_Fuc(LPVOID lpParam){
	DEL_HIDDEN_FILE Info;
	
	//Info.Handle.Handle
	//�������κ��� �޾Ƽ� �ִ´�  
	DWORD dwRead;
	HANDLE Pipe_tosvc;
	WaitForSingleObject(hMutex,INFINITE);
	for(;;){
		Sleep(100);
		Pipe_tosvc=CreateFile(P_TOSERVICE,GENERIC_READ,0,NULL,OPEN_EXISTING,0,NULL);
		if(Pipe_tosvc!=INVALID_HANDLE_VALUE){
			break;
		}
	}
	ReadFile(Pipe_tosvc,&Info,sizeof(DEL_HIDDEN_FILE),&dwRead,NULL);
	CloseHandle(Pipe_tosvc);
	
	DeviceIoControl( handle, IOCTL_DEL_HIDDEN_FILE, &Info, sizeof(DEL_HIDDEN_FILE), 0, 0, &dwRet, 0 );
	DeviceIoControl( handle, IOCTL_HIDDEN_FILES, NULL, 0, NULL, 0, &dwRet, 0 );
	ReleaseMutex(hMutex);
	return 0;
}
DWORD WINAPI Add_Guid_Fuc(LPVOID lpParam){
	PADD_GUID_FNAME pFnguid=(PADD_GUID_FNAME)malloc(sizeof(ADD_GUID_FNAME));
	ZeroMemory(pFnguid,sizeof(ADD_GUID_FNAME));
	//�������κ��� �޾Ƽ� ����ü �����Ϳ� �־� ����̽��� �ѱ�� 
	DWORD dwRead;
	HANDLE Pipe_tosvc;
	WaitForSingleObject(hMutex,INFINITE);
	for(;;){
		Sleep(100);
		Pipe_tosvc=CreateFile(P_TOSERVICE,GENERIC_READ,0,NULL,OPEN_EXISTING,0,NULL);
		if(Pipe_tosvc!=INVALID_HANDLE_VALUE){
			break;
		}
	}
	ReadFile(Pipe_tosvc,pFnguid,sizeof(ADD_GUID_FNAME),&dwRead,NULL);
	DeviceIoControl( handle, IOCTL_ADD_GUID, pFnguid, sizeof(ADD_GUID_FNAME), 0, 0, &dwRet, 0 );
	CloseHandle(Pipe_tosvc);

	free(pFnguid);
	pFnguid=NULL;
	ReleaseMutex(hMutex);
	return 0;
}
DWORD WINAPI Del_Guid_Fuc(LPVOID lpParam){
	PDEL_GUID_FNAME pDelFileName=(PDEL_GUID_FNAME)malloc(sizeof(DEL_GUID_FNAME));
	ZeroMemory(pDelFileName,sizeof(DEL_GUID_FNAME));
	//�������ι޾Ƽ� ������ ���� 
	DWORD dwRead;
	HANDLE Pipe_tosvc;
	WaitForSingleObject(hMutex,INFINITE);
	for(;;){
		Sleep(100);
		Pipe_tosvc=CreateFile(P_TOSERVICE,GENERIC_READ,0,NULL,OPEN_EXISTING,0,NULL);
		if(Pipe_tosvc!=INVALID_HANDLE_VALUE){
			break;
		}
	}
	ReadFile(Pipe_tosvc,pDelFileName,sizeof(ADD_GUID_FNAME),&dwRead,NULL);
	
	DeviceIoControl( handle, IOCTL_DEL_GUID, pDelFileName, sizeof(DEL_GUID_FNAME), 0, 0, &dwRet, 0 );
	
	CloseHandle(Pipe_tosvc);

	free(pDelFileName);
	pDelFileName=NULL;
	ReleaseMutex(hMutex);
	return 0;
}
DWORD WINAPI Run_Hfile_Fuc(LPVOID lpParam){
	char* run_guidname=(char*)malloc(sizeof(char)*GUIDCNT+1);
	ZeroMemory(run_guidname,sizeof(char)*GUIDCNT+1);
	char* cryp_guidname=(char*)malloc(sizeof(char)*GUIDCNT+1);
	ZeroMemory(cryp_guidname,sizeof(char)*GUIDCNT+1);
	char* run_Fname=(char*)malloc(MAXHIDDENFILENAMESIZE);
	ZeroMemory(run_Fname,MAXHIDDENFILENAMESIZE);
	
	DWORD dwRead;
	HANDLE Pipe_tosvc;
	WaitForSingleObject(hMutex,INFINITE);
	for(;;){
		Sleep(100);
		Pipe_tosvc=CreateFile(P_TOSERVICE,GENERIC_READ,0,NULL,OPEN_EXISTING,0,NULL);
		if(Pipe_tosvc!=INVALID_HANDLE_VALUE){
			break;
		}
	}
	ReadFile(Pipe_tosvc,cryp_guidname,sizeof(char)*GUIDCNT,&dwRead,NULL);
	CloseHandle(Pipe_tosvc);
	
	//cryp_guidname
	//��ȣȭ 
	char key_des[8]={1,2,3,4,5,6,7,8};
	Arbiter_Des_decipher(cryp_guidname,run_guidname,(const unsigned char*)key_des);

	for(int i=0;i<MAXHFARR;i++){
			if(phfile_arr[i]!=NULL && stricmp(phfile_arr[i]->Guid,run_guidname)==0){
				break;
			}
	}

	strcpy(run_Fname,phfile_arr[i]->Filename);
	strcat(run_Fname,run_guidname);

	STARTUPINFO si={0,};
	PROCESS_INFORMATION pi;
	CreateProcess(run_Fname,NULL,NULL,NULL,FALSE,0,NULL,NULL,&si,&pi);

	DWORD dwWrite;
	HANDLE Pipe_fromsvc;
	for(;;){
		Sleep(100);
		Pipe_fromsvc=CreateFile(P_FROMSERVICE,GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
		if(Pipe_fromsvc!=INVALID_HANDLE_VALUE){
			break;
		}
	}
	WriteFile(Pipe_fromsvc,&pi.dwProcessId,sizeof(pi.dwProcessId),&dwWrite,NULL);
	CloseHandle(Pipe_fromsvc);

	free(run_Fname);
	run_Fname=NULL;
	ReleaseMutex(hMutex);
	return 0;
}
DWORD WINAPI Del_Hfile_Fuc(LPVOID lpParam){
	char* del_filename=(char*)malloc(sizeof(char)*1024);
	ZeroMemory(del_filename,sizeof(char)*1024);
	
	DWORD dwRead;
	HANDLE Pipe_tosvc;
	WaitForSingleObject(hMutex,INFINITE);
	for(;;){
		Sleep(100);
		Pipe_tosvc=CreateFile(P_TOSERVICE,GENERIC_READ,0,NULL,OPEN_EXISTING,0,NULL);
		if(Pipe_tosvc!=INVALID_HANDLE_VALUE){
			break;
		}
	}
	ReadFile(Pipe_tosvc,del_filename,sizeof(char)*1024,&dwRead,NULL);
	CloseHandle(Pipe_tosvc);
	
	DeleteFile(del_filename);

	free(del_filename);
	del_filename=NULL;
	ReleaseMutex(hMutex);
	return 0;
}
DWORD WINAPI Add_List_Fuc(LPVOID lpParam){
	PHFILE_ATT phf_att;
	phf_att=(PHFILE_ATT)malloc(sizeof(HFILE_ATT));
	ZeroMemory(phf_att,sizeof(HFILE_ATT));
	
	DWORD dwRead;
	HANDLE Pipe_tosvc;
	WaitForSingleObject(hMutex,INFINITE);
	for(;;){
		Sleep(100);
		Pipe_tosvc=CreateFile(P_TOSERVICE,GENERIC_READ,0,NULL,OPEN_EXISTING,0,NULL);
		if(Pipe_tosvc!=INVALID_HANDLE_VALUE){
			break;
		}
	}
	ReadFile(Pipe_tosvc,phf_att,sizeof(HFILE_ATT),&dwRead,NULL);
	CloseHandle(Pipe_tosvc);
	for(int i=0;i<MAXHFARR;i++){
		if(phfile_arr[i]==NULL){
			phfile_arr[i]=phf_att;
			break;
		}
	}
	ReleaseMutex(hMutex);
	Save_HFList();
	return 0;
}
DWORD WINAPI Get_At_List_Fuc(LPVOID lpParam){
	PHFILE_ATT phf_att;
	phf_att=(PHFILE_ATT)malloc(sizeof(HFILE_ATT));
	ZeroMemory(phf_att,sizeof(HFILE_ATT));
	DWORD dwRead;
	HANDLE Pipe_tosvc;
	WaitForSingleObject(hMutex,INFINITE);
	for(;;){
		Sleep(100);
		Pipe_tosvc=CreateFile(P_TOSERVICE,GENERIC_READ,0,NULL,OPEN_EXISTING,0,NULL);
		if(Pipe_tosvc!=INVALID_HANDLE_VALUE){
			break;
		}
	}
	ReadFile(Pipe_tosvc,phf_att,sizeof(HFILE_ATT),&dwRead,NULL);
	CloseHandle(Pipe_tosvc);
	for(int i=0;i<MAXHFARR;i++){
		if(stricmp(phfile_arr[i]->Filename,phf_att->Filename)==0)
			if(stricmp(phfile_arr[i]->Guid,phf_att->Guid)==0){
				break;
			}
	}
	DWORD dwWrite;
	HANDLE Pipe_fromsvc;
	for(;;){
		Sleep(100);
		Pipe_fromsvc=CreateFile(P_FROMSERVICE,GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
		if(Pipe_fromsvc!=INVALID_HANDLE_VALUE){
			break;
		}
	}
	WriteFile(Pipe_fromsvc,&phfile_arr[i]->handleno,sizeof(phfile_arr[i]->handleno),&dwWrite,NULL);
	CloseHandle(Pipe_fromsvc);
	ReleaseMutex(hMutex);
	return 0;
}

void Uninst_ABtnSVC(){
	STARTUPINFO si={0,};
	PROCESS_INFORMATION pi;
	CreateProcess(UNINSTALL_ABTNSVC_PATH,NULL,NULL,NULL,FALSE,0,NULL,NULL,&si,&pi);
}
DWORD WINAPI Del_Hf_AT_Uninstall_Fuc(LPVOID lpParam){
	char* del_filename=(char*)malloc(sizeof(char)*1024);
	ZeroMemory(del_filename,sizeof(char)*1024);
	
	DWORD dwRead;
	HANDLE Pipe_tosvc;
	int i;
	WaitForSingleObject(hMutex,INFINITE);
	for(;;){
		Sleep(100);
		Pipe_tosvc=CreateFile(P_TOSERVICE,GENERIC_READ,0,NULL,OPEN_EXISTING,0,NULL);
		if(Pipe_tosvc!=INVALID_HANDLE_VALUE){
			break;
		}
	}
	ReadFile(Pipe_tosvc,del_filename,sizeof(char)*1024,&dwRead,NULL);
	CloseHandle(Pipe_tosvc);
	
	for(i=0;i<MAXHFARR;i++){
		if(phfile_arr[i]!=NULL){
			if(stricmp(phfile_arr[i]->Filename,del_filename)==0){
			break;
			}
		}
	}
	
	//////////////////////////////////////////////////////////////////////////
	//������ �������� ����Ʈ���� guid �� ���ϵ� 
	//////////////////////////////////////////////////////////////////////////
	DEL_HIDDEN_FILE Info;
	PDEL_GUID_FNAME pDelGuid=(PDEL_GUID_FNAME)malloc(sizeof(DEL_GUID_FNAME));
	ZeroMemory(pDelGuid,sizeof(DEL_GUID_FNAME));
	//�������ι޾Ƽ� ������ ���� 
	
	LPWSTR tempfname;
	
	Info.Handle.Handle=phfile_arr[i]->handleno;
	DeviceIoControl( handle, IOCTL_DEL_HIDDEN_FILE, &Info, sizeof(DEL_HIDDEN_FILE), 0, 0, &dwRet, 0 );
	tempfname=CharToWChar(phfile_arr[i]->Filename);
	wcscpy(pDelGuid->Filename,tempfname);
	DeviceIoControl( handle, IOCTL_DEL_GUID, pDelGuid, sizeof(DEL_GUID_FNAME), 0, 0, &dwRet, 0 );
	
	DeleteFile(del_filename);
	
	///////////////////////////////////////////////////////////////////////////
	//�����v�� ������ 
	//////////////////////////////////////////////////////////////////////////
	
	free(phfile_arr[i]);
	free(del_filename);
	phfile_arr[i]=NULL;
	del_filename=NULL;
	for(int j=i;j<MAXHFARR;j++){
		phfile_arr[j]=phfile_arr[j+1];
		phfile_arr[j+1]=NULL;
	}
	
	if(Save_HFList()==TRUE){
		Uninst_ABtnSVC();
	}

	ReleaseMutex(hMutex);
	return 0;
}
void MyDeviceHandler(DWORD fdwControl){
	///������ ���� 
	switch(fdwControl){		
	case SERVICE_HIDDEN_FILES:
		DeviceIoControl( handle, IOCTL_HIDDEN_FILES, NULL, 0, NULL, 0, &dwRet, 0 );
		break;
	case SERVICE_SHOW_FILES :
		DeviceIoControl( handle, IOCTL_SHOW_FILES, NULL, 0, NULL, 0, &dwRet, 0 );
		break;
	case SERVICE_ADD_HIDDEN_FILE :
		{
			DWORD Tid;
			CloseHandle(CreateThread(NULL,0,Add_Hidden_File_Fuc,NULL,0,&Tid));
		}
		break;
	case SERVICE_DEL_HIDDEN_FILE :
		{
			DWORD Tid;
			CloseHandle(CreateThread(NULL,0,Del_Hidden_File_Fuc,NULL,0,&Tid));
		}
		break;
	case SERVICE_ALL_RESET_HIDDEN_FILES :
		{
			DeviceIoControl( handle, IOCTL_ALL_RESET_HIDDEN_FILES, NULL, 0, NULL, 0, &dwRet, 0 );
		}
		break;
	case SERVICE_SET_DRIVE :
		break;
	case SERVICE_SET_EVENT :
		break;
	case SERVICE_ADD_GUID :
		{
			DWORD Tid;
			CloseHandle(CreateThread(NULL,0,Add_Guid_Fuc,NULL,0,&Tid));
		}
		break;
	case SERVICE_DEL_GUID :
		{
			DWORD Tid;
			CloseHandle(CreateThread(NULL,0,Del_Guid_Fuc,NULL,0,&Tid));
		}
		break;
	case SERVICE_RUN_HFILE:
		{
			DWORD Tid;
			CloseHandle(CreateThread(NULL,0,Run_Hfile_Fuc,NULL,0,&Tid));
		}
		break;
	case  SERVICE_DEL_HFILE:
		{
			DWORD Tid;
			CloseHandle(CreateThread(NULL,0,Del_Hfile_Fuc,NULL,0,&Tid));
		}
		break;
	case  SERVICE_ADD_LIST:
		{
			DWORD Tid;
			CloseHandle(CreateThread(NULL,0,Add_List_Fuc,NULL,0,&Tid));
		}
		break;
	case SERVICE_GET_AT_LIST:
		{
			DWORD Tid;
			CloseHandle(CreateThread(NULL,0,Get_At_List_Fuc,NULL,0,&Tid));
		}
		break;
	case SERVICE_DEL_HF_AT_UNINSTALL:
		{
			DWORD Tid;
			CloseHandle(CreateThread(NULL,0,Del_Hf_AT_Uninstall_Fuc,NULL,0,&Tid));
		}
		break;
		
	}
}

BOOL InitDIOStart()
{
	char NAME_NAME[] = "\\\\.\\FILEHIDE";
	
	handle = CreateFile( NAME_NAME, GENERIC_READ|GENERIC_WRITE
		, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL
					   , 0 );
	if( handle == (HANDLE)-1 )
		return FALSE;
	
	// Event�˷��ִ� ��� /////////////////////////////////////
	
	// ���ο� ������ �߰��ɶ��� �˷��� Event�� ����ϴ� �κ�
	// ������ũ�Ӹ� �ƴ϶�, � �����̴��� Event�� �ñ׳εȴ�
	
	
	SEND_EVENT SendEvent;
	Event = CreateEvent(NULL,NULL,NULL,NULL );
	SendEvent.hEvent = Event;
	
	// Event�� ����̹����� �˷��ش�.
	
	DeviceIoControl( handle, IOCTL_SET_EVENT, &SendEvent, sizeof(SEND_EVENT), 0, 0, &dwRet, 0 );
	
	// Ư�������� ��������ٴ� ��ȣ�� �޾ұ⶧����, �ý��ۿ� �����ϴ� ��� ����̺�� ���� ������ �����Ѵ�
	// �ý��ۿ� �ִ� ��� ����̺긦 üũ�Ͽ�, �ǹ��ִ� ����̺길 �˷��ش�.
	
	char Drive;
	UINT Type;
	char RootDirectoryString[100];
	
	strcpy( RootDirectoryString, "A:\\" );
	
	for( Drive ='A'; Drive <= 'Z' ; Drive ++ )
	{
		RootDirectoryString[0] = Drive;
		Type = GetDriveType(RootDirectoryString);
		if( Type == DRIVE_UNKNOWN )
			continue;
		DeviceIoControl( handle, IOCTL_SET_DRIVE, &Drive, sizeof(char), 0, 0, &dwRet, 0 );
	}
	
	return TRUE;
}
void MyGuidMaker(char* ResultGUIDSt){
	// GUID�� �����Ѵ�.
	GUID *rGUID = new GUID();
	// CoCreateGuid �����ϱ�
	CoCreateGuid(rGUID);
	// �Ʒ��� String���� ������ִ� �κ��̴�.
	wsprintf(ResultGUIDSt, "{%.8X%.4X%.4X%.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X}", 
		rGUID->Data1, 
		rGUID->Data2, 
		rGUID->Data3, 
		rGUID->Data4[0],
		rGUID->Data4[1],
		rGUID->Data4[2],
		rGUID->Data4[3],
		rGUID->Data4[4],
		rGUID->Data4[5],
		rGUID->Data4[6],
		rGUID->Data4[7]);
	
}

wchar_t* CharToWChar(const char* pstrSrc)
{
    //ASSERT(pstrSrc);
    int nLen = strlen(pstrSrc)+1;
	
    wchar_t* pwstr      = (LPWSTR) malloc ( sizeof( wchar_t )* nLen);
	ZeroMemory(pwstr,sizeof( wchar_t )* nLen);
    mbstowcs(pwstr, pstrSrc, nLen);
	
    return pwstr;
}