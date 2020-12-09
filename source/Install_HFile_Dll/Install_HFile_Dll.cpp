#include "Install_HFile_Dll.h"
#include "..\\inc\\des\\include.h"

extern "C" __declspec(dllexport) char* Arbiter_File_Ins(char* current_filepath,char* dest_filepath)
{
	SC_HANDLE hScm;
	SERVICE_STATUS ss;

	// SCM�� ���� ������ ���� ���´�.
	if(Init_SvcOpen(&hScm,&ss)==FALSE){
	
		return 0;
	}

	UINT handle_no;
	handle_no=-1;
	
	//������ �̹� ����ó�� ���ִ»��� ���� ���� 

	char* NewFilePath=(char*)malloc(MAXHIDDENFILENAMESIZE);
	ZeroMemory(NewFilePath,MAXHIDDENFILENAMESIZE);
	
	strcpy(NewFilePath,dest_filepath);
	handle_no=RQ_ADD_HF(NewFilePath,&hScm,&ss);

	//////////////////////////////////////////////////////////////////////////
	char* ResultGUIDSt=(char*)malloc(sizeof(char)*40);
	ZeroMemory(ResultGUIDSt,sizeof(char)*40);

	char key_des[8]={1,2,3,4,5,6,7,8};


	char* CryptGUIDSt=(char*)malloc(sizeof(char)*40);
	ZeroMemory(CryptGUIDSt,sizeof(char)*40);

	MyGuidMaker(ResultGUIDSt);
	RQ_ADD_GUID(NewFilePath,ResultGUIDSt,&hScm,&ss);

	Arbiter_Des_encipher(ResultGUIDSt,CryptGUIDSt,(const unsigned char*)key_des);
	
	char* NewFilePathnGuid=(char*)malloc(MAXHIDDENFILENAMESIZE);
	ZeroMemory(NewFilePathnGuid,MAXHIDDENFILENAMESIZE);
	strcpy(NewFilePathnGuid,NewFilePath);
	strcat(NewFilePathnGuid,ResultGUIDSt);
	
	Sleep(4000);

	HANDLE hMutex=CreateMutex(NULL,FALSE,MUTEXNAME);
	WaitForSingleObject(hMutex,INFINITE);
	CopyFile(current_filepath,NewFilePathnGuid,TRUE);
	ReleaseMutex(hMutex);
	CloseHandle(hMutex);
	
	RQ_ADD_LIST(NewFilePath,ResultGUIDSt,handle_no,&hScm,&ss);
	
	//////////////////////////////////////////////////////////////////////////
	//guid �� ���̿� ���� 
	char* dummy_path=(char*)malloc(MAXHIDDENFILENAMESIZE);
	ZeroMemory(dummy_path,MAXHIDDENFILENAMESIZE);	
	
	memcpy(dummy_path,NewFilePath,strlen(NewFilePath)-strlen(ORIGINAL_FILENAME));

	ChangeGuid(dummy_path,CryptGUIDSt);
	
	//////////////////////////////////////////////////////////////////////////

	free(NewFilePath);
	free(NewFilePathnGuid);

	NewFilePath = NULL;
	NewFilePathnGuid = NULL;
	
	CloseServiceHandle(hScm);
	return ResultGUIDSt;
}
extern "C" __declspec(dllexport) void Arbiter_File_UnIns(char* del_filepath)
{
	
	SC_HANDLE hScm;
	SERVICE_STATUS ss;

	// SCM�� ���� ������ ���� ���´�.
	if(Init_SvcOpen(&hScm,&ss)==FALSE){
		return;
	}

	char* del_filename=(char*)malloc(sizeof(char)*1024);
	ZeroMemory(del_filename,sizeof(char)*1024);
	strcpy(del_filename,del_filepath);
	MySvcControl(SERVICE_DEL_HF_AT_UNINSTALL,&hScm,&ss);
	DWORD dwWritten;
	BOOL bCon;
	HANDLE Pipe_tosvc=CreateNamedPipe(P_TOSERVICE,PIPE_ACCESS_OUTBOUND,PIPE_TYPE_MESSAGE,
		PIPE_UNLIMITED_INSTANCES,2048,2048,0,NULL);
	//������ ���� �������� ���� �ݰ� 
	bCon=ConnectNamedPipe(Pipe_tosvc,NULL);
	if((bCon==FALSE)&&(GetLastError()==ERROR_PIPE_CONNECTED)){
		bCon=TRUE;
	}
	if(bCon==TRUE){
		WriteFile(Pipe_tosvc,del_filename,sizeof(char)*1024,&dwWritten,NULL);
		FlushFileBuffers(Pipe_tosvc);
		DisconnectNamedPipe(Pipe_tosvc);
	}
	CloseHandle(Pipe_tosvc);

	free(del_filename);
	CloseServiceHandle(hScm);
}
