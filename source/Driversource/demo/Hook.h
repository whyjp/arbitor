#ifndef _HOOK_H
#define _HOOK_H

#include <stdio.h>



//
// Type definitions
//
typedef unsigned long	DWORD, *PDWORD;
typedef char			CHAR, *LPSTR;
typedef unsigned char	BYTE, *PBYTE;
typedef HANDLE			HMODULE;

//
// Native Api Server Descriptor Entry
//
#pragma pack(1)
typedef struct ServiceDescriptorEntry {
	unsigned int *ServiceTableBase;
	unsigned int *ServiceCounterTableBase; 
	unsigned int NumberOfServices;
	unsigned char *ParamTableBase;
} ServiceDescriptorTableEntry_t, *PServiceDescriptorTableEntry_t;
#pragma pack()

//
// Native Api Service Table
//
typedef struct _SRVTABLE {
	PVOID           *ServiceTable;
	ULONG           LowCall;        
	ULONG           HiCall;
	PVOID			*ArgTable;
} SRVTABLE, *PSRVTABLE;


//
// System threads structure
// 
typedef struct _SYSTEM_THREADS {
	LARGE_INTEGER		KernelTime;
	LARGE_INTEGER		UserTime;
	LARGE_INTEGER		CreateTime;
	ULONG				WaitTime;
	PVOID				StartAddress;
	CLIENT_ID			ClientIs;
	KPRIORITY			Priority;
	KPRIORITY			BasePriority;
	ULONG				ContextSwitchCount;
	ULONG				ThreadState;
	KWAIT_REASON		WaitReason;
} SYSTEM_THREADS, *PSYSTEM_THREADS;


//
// System processes structure
//
typedef struct _SYSTEM_PROCESSES {
	ULONG				NextEntryDelta;
	ULONG				ThreadCount;
	ULONG				Reserved[6];
	LARGE_INTEGER		CreateTime;
	LARGE_INTEGER		UserTime;
	LARGE_INTEGER		KernelTime;
	UNICODE_STRING		ProcessName;
	KPRIORITY			BasePriority;
	ULONG				ProcessId;
	ULONG				InheritedFromProcessId;
	ULONG				HandleCount;
	ULONG				Reserved2[2];
	//VM_COUNTERS			VmCounters;
	//IO_COUNTERS			IoCounters; //windows 2000 only
	struct _SYSTEM_THREADS		Threads[1];
} SYSTEM_PROCESSES, *PSYSTEM_PROCESSES;
//
// Hook Native Api
//
VOID
HookNativeApi();

//
// Unhook Native Api
//
VOID
UnhookNativeApi();




//////////////////////////////////////////////////////////////////////////
//		  N  A  T  I  V  E      A  P  I      D  E  C  L  A  R  E
//////////////////////////////////////////////////////////////////////////

//
// ZwOpenProcess
//
typedef NTSTATUS (NTAPI *ZWOPENPROCESS)(
										OUT PHANDLE ProcessHandle,
										IN ACCESS_MASK DesiredAccess,
										IN POBJECT_ATTRIBUTES ObjectAttributes,
										IN PCLIENT_ID ClientId OPTIONAL
										);
//
// ZwCreateProcessEx
//
typedef NTSTATUS (NTAPI *ZWCREATEPROCESSEX)(
	OUT PHANDLE ProcessHandle,
	IN ACCESS_MASK DesiredAccess,
	IN POBJECT_ATTRIBUTES ObjectAttributes OPTIONAL,
	IN HANDLE ParentProcessHandle,
	IN BOOLEAN InheritObjectTable,
	IN HANDLE SectionHandle,
	IN HANDLE DebugPort,
	IN HANDLE ExceptionPort, 
	IN HANDLE Unknown
	);

//
// ZwReadVirtualMemory
//
typedef NTSTATUS (NTAPI *ZWREADVIRTUALMEMORY)(
	IN HANDLE hProcess,
	IN PVOID BaseAddress,
	IN PVOID Buffer,
	IN ULONG BytesToRead,
	OUT PULONG BytesRead
	);

//
// ZwWriteVirtualMemory
//
typedef NTSTATUS (NTAPI *ZWWRITEVIRTUALMEMORY)(
	IN HANDLE hProcess,
	IN PVOID BaseAddress,
	IN PVOID Buffer,
	IN ULONG BytesToWrite,
	OUT PULONG BytesWritten
	);


//
// ZwQuerySystemInformation
//
typedef NTSTATUS (NTAPI *ZWQUERYSYSTEMINFORMATION)(
	IN ULONG SystemInformationClass,
	IN PVOID SystemInformation,
	IN ULONG SystemInformationLength,
	OUT PULONG ReturnLength
	);


//////////////////////////////////////////////////////////////////////////
//	O  L  D      N  A  T  I  V  E      A  P  I
//////////////////////////////////////////////////////////////////////////

//
// ZwOpenProcess
//
NTSYSAPI
NTSTATUS
NTAPI
ZwOpenProcess( 
			  OUT PHANDLE ProcessHandle,
			  IN ACCESS_MASK DesiredAccess,
			  IN POBJECT_ATTRIBUTES ObjectAttributes,
			  IN PCLIENT_ID ClientId OPTIONAL
			  );


//
// ZwCreateProcessEx
//
#define ZwCreateProcessEx		0x30


//
// ZwQuerySystemInformation
//
NTSYSAPI
NTSTATUS
NTAPI 
ZwQuerySystemInformation(
						 IN ULONG SystemInformationClass,
						 IN PVOID SystemInformation,
						 IN ULONG SystemInformationLength,
						 OUT PULONG ReturnLength
						 );

//
// ZwReadVirtualMemory
//
#define ZwReadVirtualMemory		0xBA

//
// ZwWriteVirtualMemory
//
#define ZwWriteVirtualMemory	0x115

/*

//
// ZwQueryInformationProcess
// 
NTSYSAPI
NTSTATUS
NTAPI
ZwQueryInformationProcess(
						  IN HANDLE ProcessHandle,
						  IN PROCESSINFOCLASS ProcessInformationClass,
						  OUT PVOID ProcessInformation,
						  IN ULONG ProcessInformationLength,
						  OUT PULONG ReturnLength OPTIONAL
						  );

*/
//////////////////////////////////////////////////////////////////////////
//	N  E  W      N  A  T  I  V  E      A  P  I
//////////////////////////////////////////////////////////////////////////


// ZwOpenProcess
//
NTSTATUS 
newZwOpenProcess( 
					   OUT PHANDLE ProcessHandle,
					   IN ACCESS_MASK DesiredAccess,
					   IN POBJECT_ATTRIBUTES ObjectAttributes,
					   IN PCLIENT_ID ClientId OPTIONAL
					   );


//
// ZwCreateProcessEx
//
NTSTATUS 
newZwCreateProcessEx(
						   OUT PHANDLE ProcessHandle,
						   IN ACCESS_MASK DesiredAccess,
						   IN POBJECT_ATTRIBUTES ObjectAttributes OPTIONAL,
						   IN HANDLE ParentProcessHandle,
						   IN BOOLEAN InheritObjectTable,
						   IN HANDLE SectionHandle,
						   IN HANDLE DebugPort,
						   IN HANDLE ExceptionPort, 
						   IN HANDLE Unknown	
						   );


//
// ZwReadVirtualMemory
//
NTSTATUS 
newZwReadVirtualMemory(
							 IN HANDLE hProcess,
							 IN PVOID BaseAddress,
							 IN PVOID Buffer,
							 IN ULONG BytesToRead,
							 OUT PULONG BytesRead
							 );

//
// ZwWriteVirtualMemory
//
NTSTATUS
newZwWriteVirtualMemory(
							  IN HANDLE hProcess,
							  IN PVOID BaseAddress,
							  IN PVOID Buffer,
							  IN ULONG BytesToWrite,
							  OUT PULONG BytesWritten
							  );



//
// ZwQuerySystemInformation
// 
NTSTATUS 
newZwQuerySystemInformation(
								  IN ULONG SystemInformationClass,
								  IN PVOID SystemInformation,
								  IN ULONG SystemInformationLength,
								  OUT PULONG ReturnLength
								  );



//////////////////////////////////////////////////////////////////////////
//		 P  R  O  C  E  S  S      I  N  F  O  R  M  A  T  I  O  N
//////////////////////////////////////////////////////////////////////////


//
// Page size
//
#define PAGE_SIZE			0x1000
//#define PAGE_ROUND_DOWN(x)	(((ULONG_PTR)x)&(~(PAGE_SIZE-1)))
//#define PAGE_ROUND_UP(x)	((((ULONG_PTR)x)%PAGE_SIZE) ? ((((ULONG_PTR)x)&(~(PAGE_SIZE-1)))+PAGE_SIZE) : ((ULONG_PTR)x))

//
// System process name
//
#define SYSNAME			"System"
#define EXPLORERNAME	"explorer.exe"
#define TASKMGRNAME		"taskmgr.exe"
#define SVCHOST			"svchost"
#define LSASS			"lsass.exe"
#define CSRSS			"csrss.exe"
#define AB_SVC			"Ab_svc_service.exe"


//
// Max length of NT process name
//
#define NT_PROCNAMELEN  100

//
// Get process name offset 
// ( * this function must be called in driver entry )
//

ULONG GetProcessNameOffset(
						   void
						   );


//
// Get current process name
//

LPSTR 
GetCurrentProcessName(
					 // OUT  LPSTR Name
					  );







#endif
