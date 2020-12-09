#include "4Svc_lib.h"
#include <winioctl.h>
#include <winsvc.h>

wchar_t* CharToWChar(const char* pstrSrc)
{
    //ASSERT(pstrSrc);
    int nLen = strlen(pstrSrc)+1;
	
    wchar_t* pwstr      = (LPWSTR) malloc ( sizeof( wchar_t )* nLen);
    mbstowcs(pwstr, pstrSrc, nLen);
	
    return pwstr;
}


/////////////////////////////////////////////////////////////////////

// wchar -> char
char* WCharToChar(const wchar_t* pwstrSrc)
{
    //ASSERT(pwstrSrc);
	
#if !defined _DEBUG
    int len = 0;
    len = (wcslen(pwstrSrc) + 1)*2;
    char* pstr      = (char*) malloc ( sizeof( char) * len);
	
    WideCharToMultiByte( 949, 0, pwstrSrc, -1, pstr, len, NULL, NULL);
#else
	
    int nLen = wcslen(pwstrSrc);
	
    char* pstr      = (char*) malloc ( sizeof( char) * nLen + 1);
    wcstombs(pstr, pwstrSrc, nLen+1);
#endif
	
    return pstr;
}

/////////////////////////////////////////////////////////////////////////////
void MyGuidMaker(char* ResultGUIDSt){
//	CHAR ResultGUIDSt[40] = {0,};

	// GUID를 생성한다.
	GUID *rGUID = new GUID();
	// CoCreateGuid 생성하기
	CoCreateGuid(rGUID);
	// 아래는 String으로 만들어주는 부분이다.
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
///utility

void ChangeGuid(char *filename, char *guid)
{
	HANDLE hfile=NULL;
	DWORD dwread;
	DWORD dwWrite;
	char *buf;
	int len = 34;
	buf = new char[sizeof(char)*35];
	ZeroMemory(buf, sizeof(char)*35);
	char *findGUID = "{aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa}";
	
	DWORD dwFileSize;
    DWORD dwSizeLow;
    DWORD dwSizeHigh;

	int lc = 0;
	hfile = CreateFile(filename, GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	dwSizeLow = GetFileSize(hfile, &dwSizeHigh);
    dwFileSize = dwSizeHigh << 16 | dwSizeLow;

	if(hfile!=INVALID_HANDLE_VALUE)
	{
		while ((DWORD)lc != dwFileSize)
		{
			SetFilePointer(hfile, lc, NULL, FILE_BEGIN); 
			
			ReadFile(hfile, buf, 34,&dwread, NULL);
			if(!stricmp(buf, findGUID))
			{
				SetFilePointer(hfile, lc, NULL, FILE_BEGIN); 
				WriteFile(hfile, guid, len, &dwWrite, NULL);
				break;
			}
			lc++;
		}
	}
	delete buf;
	CloseHandle(hfile); 
}

void ChangeEXfilePath(char *filename,char *ex_file_path)
{
	HANDLE hfile=NULL;
	DWORD dwread;
	DWORD dwWrite;
	char *buf;
	int len=0;
	buf = new char[sizeof(char)*23];
	ZeroMemory(buf, sizeof(char)*23);
	
	DWORD dwFileSize;
    DWORD dwSizeLow;
    DWORD dwSizeHigh;

	int lc = 0;
	hfile = CreateFile(filename, GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	dwSizeLow = GetFileSize(hfile, &dwSizeHigh);
    dwFileSize = dwSizeHigh << 16 | dwSizeLow;

	if(hfile!=INVALID_HANDLE_VALUE)
	{
		while ((DWORD)lc != dwFileSize)
		{
			SetFilePointer(hfile, lc, NULL, FILE_BEGIN); 
			
			ReadFile(hfile, buf, 23,&dwread, NULL);
			if(!stricmp(buf, EXCUTE_FILEPATH))
			{
				SetFilePointer(hfile, lc, NULL, FILE_BEGIN); 
				len=strlen(ex_file_path);
				WriteFile(hfile, ex_file_path, len, &dwWrite, NULL);
				break;
			}
			lc++;
		}
	}
	delete buf;
	CloseHandle(hfile); 
}

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
///Device Part
//////////////////////////////////////////////////////////////////////////

void RQ_ADD_GUID(char* fname,char* guid,SC_HANDLE* hScm,SERVICE_STATUS* ss)
{
	PADD_GUID_FNAME pFnguid=(PADD_GUID_FNAME)malloc(sizeof(ADD_GUID_FNAME));
	ZeroMemory(pFnguid,sizeof(ADD_GUID_FNAME));
	//초기화 
	LPWSTR tempfname=CharToWChar(fname);
	wcscpy( pFnguid->Filename, tempfname );
	tempfname=CharToWChar(guid);
	wcscpy( pFnguid->Guid, tempfname );
	//입력받은걸 와이드형으로 바꾼다 

	MySvcControl(SERVICE_ADD_GUID,hScm,ss);
	//서비스에 요청 

	DWORD dwWritten;
	BOOL bCon;
	HANDLE Pipe_tosvc=CreateNamedPipe(P_TOSERVICE,PIPE_ACCESS_OUTBOUND,PIPE_TYPE_MESSAGE,
		PIPE_UNLIMITED_INSTANCES,4056,4056,0,NULL);
	//파이프 열고 파이프에 쓰고 닫고 
	bCon=ConnectNamedPipe(Pipe_tosvc,NULL);
	if((bCon==FALSE)&&(GetLastError()==ERROR_PIPE_CONNECTED)){
		bCon=TRUE;
	}
	if(bCon==TRUE){
		WriteFile(Pipe_tosvc,pFnguid,sizeof(ADD_GUID_FNAME),&dwWritten,NULL);
		FlushFileBuffers(Pipe_tosvc);
		DisconnectNamedPipe(Pipe_tosvc);
	}
	CloseHandle(Pipe_tosvc);
	free(pFnguid);
}

void RQ_DEL_GUID(char* fname,SC_HANDLE* hScm,SERVICE_STATUS* ss)
{
	PDEL_GUID_FNAME pDelFileName=(PDEL_GUID_FNAME)malloc(sizeof(DEL_GUID_FNAME));
	ZeroMemory(pDelFileName,sizeof(DEL_GUID_FNAME));
	//초기화 
	LPWSTR tempfname=CharToWChar(fname);
	wcscpy( pDelFileName->Filename, tempfname );
	//와이드형으로변환
	MySvcControl(SERVICE_DEL_GUID,hScm,ss);
	//서비스에 요청 
	DWORD dwWritten;
	BOOL bCon;
	HANDLE Pipe_tosvc=CreateNamedPipe(P_TOSERVICE,PIPE_ACCESS_OUTBOUND,PIPE_TYPE_MESSAGE,
		PIPE_UNLIMITED_INSTANCES,4056,4056,0,NULL);
	//파이프 열고 파이프에 쓰고 닫고 
	bCon=ConnectNamedPipe(Pipe_tosvc,NULL);
	if((bCon==FALSE)&&(GetLastError()==ERROR_PIPE_CONNECTED)){
		bCon=TRUE;
	}
	if(bCon==TRUE){
		WriteFile(Pipe_tosvc,pDelFileName,sizeof(DEL_GUID_FNAME),&dwWritten,NULL);
		FlushFileBuffers(Pipe_tosvc);
		DisconnectNamedPipe(Pipe_tosvc);
	}
	CloseHandle(Pipe_tosvc);
	free(pDelFileName);
}

UINT RQ_ADD_HF(char *add_file_name,SC_HANDLE* hScm,SERVICE_STATUS* ss)
{
	PADD_HIDDEN_FILE File=(PADD_HIDDEN_FILE)malloc(sizeof(ADD_HIDDEN_FILE));
	ZeroMemory(File,sizeof(ADD_HIDDEN_FILE));

	HIDDEN_FILE_HANDLE hiddenhandle;
	hiddenhandle.Handle=0;
	
	LPWSTR tempfname=CharToWChar(add_file_name);
	wcscpy( File->Filename, tempfname );
	MySvcControl(SERVICE_ADD_HIDDEN_FILE,hScm,ss);
	//파이프에넣는다 
	//파이프로부터 핸들을 받는다 
	DWORD dwWritten;
	BOOL bCon;
	HANDLE Pipe_tosvc=CreateNamedPipe(P_TOSERVICE,PIPE_ACCESS_OUTBOUND,PIPE_TYPE_MESSAGE,
		PIPE_UNLIMITED_INSTANCES,4056,4056,0,NULL);
	bCon=ConnectNamedPipe(Pipe_tosvc,NULL);
	if((bCon==FALSE)&&(GetLastError()==ERROR_PIPE_CONNECTED)){
		bCon=TRUE;
	}
	if(bCon==TRUE){
		WriteFile(Pipe_tosvc,File,sizeof(ADD_HIDDEN_FILE),&dwWritten,NULL);
		FlushFileBuffers(Pipe_tosvc);
		DisconnectNamedPipe(Pipe_tosvc);
	}
	CloseHandle(Pipe_tosvc);

	DWORD dwRead;
	HANDLE Pipe_fromsvc=CreateNamedPipe(P_FROMSERVICE,PIPE_ACCESS_INBOUND,PIPE_TYPE_MESSAGE,
		PIPE_UNLIMITED_INSTANCES,4056,4056,0,NULL);
	bCon=ConnectNamedPipe(Pipe_fromsvc,NULL);
	if((bCon==FALSE)&&(GetLastError()==ERROR_PIPE_CONNECTED)){
		bCon=TRUE;
	}
	if(bCon==TRUE){
		ReadFile(Pipe_fromsvc,&hiddenhandle,sizeof(HIDDEN_FILE_HANDLE),&dwRead,NULL);
		FlushFileBuffers(Pipe_fromsvc);
		DisconnectNamedPipe(Pipe_fromsvc);
	}
	CloseHandle(Pipe_fromsvc);
	free(File);
	return hiddenhandle.Handle;
}

void RQ_DEL_HF(UINT handle_no,SC_HANDLE* hScm,SERVICE_STATUS* ss)
{
	DEL_HIDDEN_FILE Info;
	
	Info.Handle.Handle = handle_no;
	
	MySvcControl(SERVICE_DEL_HIDDEN_FILE,hScm,ss);
	//히든파일 핸들을 파이프에 넣는다 
	DWORD dwWritten;
	BOOL bCon;
	HANDLE Pipe_tosvc=CreateNamedPipe(P_TOSERVICE,PIPE_ACCESS_OUTBOUND,PIPE_TYPE_MESSAGE,
		PIPE_UNLIMITED_INSTANCES,4056,4056,0,NULL);
	bCon=ConnectNamedPipe(Pipe_tosvc,NULL);
	if((bCon==FALSE)&&(GetLastError()==ERROR_PIPE_CONNECTED)){
		bCon=TRUE;
	}
	if(bCon==TRUE){
		WriteFile(Pipe_tosvc,&Info,sizeof(DEL_HIDDEN_FILE),&dwWritten,NULL);
		FlushFileBuffers(Pipe_tosvc);
		DisconnectNamedPipe(Pipe_tosvc);
	}
	CloseHandle(Pipe_tosvc);
}

void RQ_RUN_HFILE(char* guid,SC_HANDLE* hScm,SERVICE_STATUS* ss) 
{
	// TODO: Add your control notification handler code here
	char* run_filename=(char*)malloc(sizeof(char)*GUIDCNT+1);
	ZeroMemory(run_filename,sizeof(char)*GUIDCNT+1);
	strcat(run_filename,guid);

	MySvcControl(SERVICE_RUN_HFILE,hScm,ss);
	//서비스에 요청 

	DWORD dwWritten;
	BOOL bCon;
	HANDLE Pipe_tosvc=CreateNamedPipe(P_TOSERVICE,PIPE_ACCESS_OUTBOUND,PIPE_TYPE_MESSAGE,
		PIPE_UNLIMITED_INSTANCES,2048,2048,0,NULL);
	//파이프 열고 파이프에 쓰고 닫고 
	bCon=ConnectNamedPipe(Pipe_tosvc,NULL);
	if((bCon==FALSE)&&(GetLastError()==ERROR_PIPE_CONNECTED)){
		bCon=TRUE;
	}
	if(bCon==TRUE){
		WriteFile(Pipe_tosvc,run_filename,sizeof(char)*GUIDCNT,&dwWritten,NULL);
		FlushFileBuffers(Pipe_tosvc);
		DisconnectNamedPipe(Pipe_tosvc);
	}
	CloseHandle(Pipe_tosvc);
	free(run_filename);
}
void RQ_ADD_LIST(char* fname,char* guid,ULONG handle_no,SC_HANDLE* hScm,SERVICE_STATUS* ss)
{
	PHFILE_ATT phf_att;
	phf_att=(PHFILE_ATT)malloc(sizeof(HFILE_ATT));
	ZeroMemory(phf_att,sizeof(HFILE_ATT));
	//초기화 
	strcpy((char*)phf_att->Filename,fname);
	strcpy((char*)phf_att->Guid,guid);
	phf_att->handleno=handle_no;

	//와이드형으로변환
	MySvcControl(SERVICE_ADD_LIST,hScm,ss);
	//서비스에 요청 
	DWORD dwWritten;
	BOOL bCon;
	HANDLE Pipe_tosvc=CreateNamedPipe(P_TOSERVICE,PIPE_ACCESS_OUTBOUND,PIPE_TYPE_MESSAGE,
		PIPE_UNLIMITED_INSTANCES,4056,4056,0,NULL);
	//파이프 열고 파이프에 쓰고 닫고 
	bCon=ConnectNamedPipe(Pipe_tosvc,NULL);
	if((bCon==FALSE)&&(GetLastError()==ERROR_PIPE_CONNECTED)){
		bCon=TRUE;
	}
	if(bCon==TRUE){
		WriteFile(Pipe_tosvc,phf_att,sizeof(HFILE_ATT),&dwWritten,NULL);
		FlushFileBuffers(Pipe_tosvc);
		DisconnectNamedPipe(Pipe_tosvc);
	}
	CloseHandle(Pipe_tosvc);
	free(phf_att);
}
ULONG RQ_GET_AT_LIST(char *fname, char *guid,SC_HANDLE* hScm,SERVICE_STATUS* ss)
{
	PHFILE_ATT phf_att;
	phf_att=(PHFILE_ATT)malloc(sizeof(HFILE_ATT));
	ZeroMemory(phf_att,sizeof(HFILE_ATT));
	strcpy(phf_att->Filename,fname);
	strcpy(phf_att->Guid,guid);

	MySvcControl(SERVICE_GET_AT_LIST,hScm,ss);

	DWORD dwWrite;
	BOOL bCon;
	HANDLE Pipe_tosvc=CreateNamedPipe(P_TOSERVICE,PIPE_ACCESS_OUTBOUND,PIPE_TYPE_MESSAGE,
		PIPE_UNLIMITED_INSTANCES,4056,4056,0,NULL);
	//파이프 열고 파이프에 쓰고 닫고 
	bCon=ConnectNamedPipe(Pipe_tosvc,NULL);
	if((bCon==FALSE)&&(GetLastError()==ERROR_PIPE_CONNECTED)){
		bCon=TRUE;
	}
	if(bCon==TRUE){
		WriteFile(Pipe_tosvc,phf_att,sizeof(HFILE_ATT),&dwWrite,NULL);
		FlushFileBuffers(Pipe_tosvc);
		DisconnectNamedPipe(Pipe_tosvc);
	}
	CloseHandle(Pipe_tosvc);

	DWORD dwRead;	
	HANDLE Pipe_fromsvc=CreateNamedPipe(P_FROMSERVICE,PIPE_ACCESS_INBOUND,PIPE_TYPE_MESSAGE,
		PIPE_UNLIMITED_INSTANCES,4056,4056,0,NULL);
	//파이프 열고 파이프에 쓰고 닫고 
	bCon=ConnectNamedPipe(Pipe_fromsvc,NULL);
	if((bCon==FALSE)&&(GetLastError()==ERROR_PIPE_CONNECTED)){
		bCon=TRUE;
	}
	ULONG *handleno=(ULONG*)malloc(sizeof(ULONG));
	ZeroMemory(handleno,sizeof(ULONG));
	if(bCon==TRUE){
		ReadFile(Pipe_fromsvc,handleno,sizeof(ULONG),&dwRead,NULL);
		FlushFileBuffers(Pipe_fromsvc);
		DisconnectNamedPipe(Pipe_fromsvc);
	}
	
	CloseHandle(Pipe_fromsvc);
	phf_att=NULL;
	free(phf_att);
	
	return *handleno;
}
void RQ_ALL_HIDE(SC_HANDLE* hScm,SERVICE_STATUS* ss) 
{
	// TODO: Add your control notification handler code here
	MySvcControl(SERVICE_HIDDEN_FILES,hScm,ss);
}

void RQ_ALL_SHOW(SC_HANDLE* hScm,SERVICE_STATUS* ss) 
{
	// TODO: Add your control notification handler code here

	MySvcControl(SERVICE_SHOW_FILES,hScm,ss);
}


void MySvcControl(DWORD dwControl,SC_HANDLE* hScm,SERVICE_STATUS* ss)
{
	SC_HANDLE hSrv;
	hSrv=OpenService(*hScm,SRVNAME,SERVICE_ALL_ACCESS);

	ControlService(hSrv,dwControl,ss);

	CloseServiceHandle(hSrv);
}

BOOL Init_SvcOpen(SC_HANDLE* hScm,SERVICE_STATUS* ss)
{
	SC_HANDLE hSrv;
	// SCM을 전역 변수로 열어 놓는다.
	*hScm=OpenSCManager(NULL,NULL,GENERIC_READ);
	if (hScm==NULL) {
#ifdef _DEBUG
		MessageBox(NULL,"서비스매니저호출실패","PE복사/삭제",MB_OK);
#endif
		return FALSE;
	}
	
	// 서비스가 설치되어 있지 않으면 실행할 수 없다.
	hSrv=OpenService(*hScm,SRVNAME,SERVICE_ALL_ACCESS);
	if (hSrv==NULL) {
#ifdef _DEBUG
		MessageBox(NULL,"서비스 오픈실패","PE복사/삭제",MB_OK);
#endif
		CloseServiceHandle(hScm);
		return FALSE;
	} else {
		QueryService(hScm,ss);
		QueryServiceStatus(hSrv, ss);
		if (ss->dwCurrentState!=SERVICE_RUNNING && StartService(hSrv,0,NULL)==TRUE) {
			QueryServiceStatus(hSrv, ss);
			while (ss->dwCurrentState != SERVICE_RUNNING) {
				Sleep(ss->dwWaitHint);
				QueryServiceStatus(hSrv, ss);
			}
		}
#ifdef _DEBUG
		MessageBox(NULL,"서비스 실행","PE복사/삭제",MB_OK);
#endif
		CloseServiceHandle(hSrv);
	}
	return TRUE;
}

void QueryService(SC_HANDLE* hScm,SERVICE_STATUS* ss)
{
	SC_HANDLE hSrv;
	hSrv=OpenService(*hScm,SRVNAME,SERVICE_INTERROGATE);

	do {
		ControlService(hSrv,SERVICE_CONTROL_INTERROGATE,ss);
	} while ((ss->dwCurrentState != SERVICE_STOPPED) &&
		(ss->dwCurrentState != SERVICE_RUNNING) &&
		(ss->dwCurrentState != SERVICE_PAUSED));

	CloseServiceHandle(hSrv);
}