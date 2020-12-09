#include <ntifs.h>
#include "fastio.h"
#include "hash.h"
#include "guid_hash.h"
#include "..\\..\\inc\F_IFACE.H"
#include "main.h"
#include "filehiddenroutine.h"
#include "utility.h"
#include "Recognizer.h"
#include "Hook.h"
#include <stdlib.h>
#include <string.h>


//////////////////////////////////////////////////////////////////////////

#define	MYPROCESS	"Ab_svc_service."
//#define	MYPROCESS	"dbgview.exe"
#define	CHEAT	"Cheat Engine.ex"


#define   CR0_WP_MASK     0x0FFFEFFFF 

//드라이브엔트리에서 쓰는 extension 을 위해서 전역으로 선언...
PDEVICE_EXTENSION deviceExtension = NULL;


LPSTR		Name2;


// Open Process information data
LPSTR		CreateProcessName;
LPSTR		OpenProcessName;
//FAST_MUTEX	OpenProcessMutex;


// Create Process information data
//LPSTR		CreateCallerName;
LPSTR		OpenCallerName;
FAST_MUTEX	OpenProcessMutex;
//FAST_MUTEX	CreateProcessMutex;


// Read Process information data
LPSTR		ReadProcessName;
LPSTR		ReadCallerName;
//FAST_MUTEX	ReadProcessMutex;


// Write Process information data
//LPSTR		WriteProcessName;
//LPSTR		WriteCallerName;
//FAST_MUTEX	WriteProcessMutex;


//
// Process name offset
//
ULONG ProcessNameOffset;




// variable to save original api pointer
//
// save
ZWOPENPROCESS				oldZwOpenProcess = NULL;				
//ZWCREATEPROCESSEX			oldZwCreateProcessEx = NULL;
ZWREADVIRTUALMEMORY			oldZwReadVirtualMemory = NULL;
//ZWWRITEVIRTUALMEMORY		oldZwWriteVirtualMemory = NULL;
ZWQUERYSYSTEMINFORMATION	oldZwQuerySystemInformation = NULL;

//
// Imported Native Api Service Table
//
__declspec(dllimport) ULONG	NtBuildNumber;
__declspec(dllimport) ServiceDescriptorTableEntry_t KeServiceDescriptorTable;

// ntoskrnl 이 export 한 함수의 주소를 리턴하는 매크로
// 
#define NT_SERVICE(Function)	KeServiceDescriptorTable.ServiceTableBase[*(PULONG)((PUCHAR)Function+1)]
#define NT_SERVICE_INDEX(Index)	KeServiceDescriptorTable.ServiceTableBase[Index]

//////////////////////////////////////////////////////////////////////////




PDRIVER_OBJECT g_DriverObject=NULL;
PDEVICE_OBJECT g_DeviceObject=NULL;
HANDLE g_EventHandle=NULL;
PKEVENT g_pEventObject=NULL;

LIST_ENTRY FsDeviceQueue;
ERESOURCE FsLock;
STORENAMEINSTANCE DriveNameList[MAXDRIVENUMBER];

extern ERESOURCE LockGUIDHash;
extern PGUID_HASH_ENTRY	GUIDHashTable[ NUM_GUID_HASH ];
extern PGUID_HASH_ENTRY FreeGUIDHashList;

extern ERESOURCE LockHash;
extern PHASH_ENTRY FreeHashList;
extern PHASH_ENTRY HashTable[NUM_HASH];

extern ULONG g_HiddenFileAction;

#ifdef ALLOC_PRAGMA
#pragma alloc_text(INIT, DriverEntry)
#pragma alloc_text(PAGE, FILEHIDECreate)
#pragma alloc_text(PAGE, FILEHIDEFastIoCheckIfPossible)
#pragma alloc_text(PAGE, FILEHIDEFastIoRead)
#pragma alloc_text(PAGE, FILEHIDEFastIoWrite)
#pragma alloc_text(PAGE, FILEHIDEFastIoQueryBasicInfo)
#pragma alloc_text(PAGE, FILEHIDEFastIoQueryStandardInfo)
#pragma alloc_text(PAGE, FILEHIDEFastIoLock)
#pragma alloc_text(PAGE, FILEHIDEFastIoUnlockSingle)
#pragma alloc_text(PAGE, FILEHIDEFastIoUnlockAll)
#pragma alloc_text(PAGE, FILEHIDEFastIoUnlockAllByKey)
#pragma alloc_text(PAGE, FILEHIDEFastIoDeviceControl)
#pragma alloc_text(PAGE, FILEHIDEFastIoDetachDevice)
#pragma alloc_text(PAGE, FILEHIDEFastIoQueryNetworkOpenInfo)
#pragma alloc_text(PAGE, FILEHIDEFastIoMdlRead)
#pragma alloc_text(PAGE, FILEHIDEFastIoPrepareMdlWrite)
#pragma alloc_text(PAGE, FILEHIDEFastIoMdlWriteComplete)
#pragma alloc_text(PAGE, FILEHIDEFastIoReadCompressed)
#pragma alloc_text(PAGE, FILEHIDEFastIoWriteCompressed)
#pragma alloc_text(PAGE, FILEHIDEFastIoQueryOpen)
#endif



NTSTATUS SkipAndSendIrpToNextDrive(IN PDEVICE_OBJECT pDevObj, IN PIRP pIrp)
{
	//irp명령을 스킵처리하고 하위드라이버에게전달
	//pDevObj : 필터드라이버의 DeviceObject
	//pIrp : IRP명령어

	PDEVICE_EXTENSION pDevExt;
	pDevExt = pDevObj->DeviceExtension;

	IoSkipCurrentIrpStackLocation( pIrp );
	return IoCallDriver(pDevExt->NextDriverDeviceObject, pIrp);
	//아래드라이버에게 그대로 irp 를 넘겨준다
}

NTSTATUS ReturnCurrentStackAfterSendIrpToNextDrive(IN PDEVICE_OBJECT pDevObj, IN PIRP pIrp)
{
	PDEVICE_EXTENSION pDevExt;
	KEVENT Event;
	NTSTATUS ntStatus;

	pDevExt = pDevObj->DeviceExtension;

	IoCopyCurrentIrpStackLocationToNext( pIrp );

	KeInitializeEvent( &Event, NotificationEvent, FALSE );

	IoCopyCurrentIrpStackLocationToNext( pIrp );
	IoSetCompletionRoutine(
		pIrp,
		FILEHIDECommonCompletion,
		&Event,
		TRUE,
		TRUE,
		TRUE
		);
	//작업중단시호출될 함수를 설정해준다

	ntStatus = IoCallDriver( pDevExt->NextDriverDeviceObject, pIrp );
	//다음드라이버디바이스오브젝트로 IRP 를 넘긴다.
	if( ntStatus == STATUS_PENDING )
	{
		KeWaitForSingleObject( &Event, Executive, KernelMode, FALSE, 0 );
		ntStatus = pIrp->IoStatus.Status;
	}
	return ntStatus;
}

NTSTATUS FILEHIDEDeviceIoControl(IN PDEVICE_OBJECT pDevObj, IN PIRP pIrp)
{
	PIO_STACK_LOCATION pCurIrpStack;
	PDEVICE_EXTENSION pDevExt;
	NTSTATUS ntStatus;
	ULONG ulIoControlCode;
	//명령분류
	PVOID pInputBuffer, pOutputBuffer;
	ULONG ulInputBufferLength, ulOutputBufferLength;
	//인풋 아웃풋 버퍼와 그 사이즈

	if( g_DeviceObject != pDevObj )//디바이스오브젝트가 서로다른거면 그만 넘겨준다 다음으로 
	{
		return SkipAndSendIrpToNextDrive( pDevObj, pIrp );
	}

	pDevExt = pDevObj->DeviceExtension;
	pIrp->IoStatus.Information = 0;
	pCurIrpStack = IoGetCurrentIrpStackLocation(pIrp);
	ulIoControlCode = pCurIrpStack->Parameters.DeviceIoControl.IoControlCode;

	pInputBuffer = pIrp->AssociatedIrp.SystemBuffer;
	pOutputBuffer = pIrp->AssociatedIrp.SystemBuffer;
	ulInputBufferLength = pCurIrpStack->Parameters.DeviceIoControl.InputBufferLength;
	ulOutputBufferLength = pCurIrpStack->Parameters.DeviceIoControl.OutputBufferLength;

	switch(ulIoControlCode) 
	{
	case IOCTL_SET_EVENT:
		{
			PSEND_EVENT pEvent;
			pEvent = (PSEND_EVENT)pInputBuffer;

			ntStatus = ObReferenceObjectByHandle( pEvent->hEvent,
				0x80000000,
				NULL,
				0,
				&g_pEventObject,
				NULL );
			if( ntStatus == STATUS_SUCCESS )
			{
				KeClearEvent(g_pEventObject);
				g_EventHandle = pEvent->hEvent;
			}
			else
			{
				g_pEventObject = NULL;
				g_EventHandle = NULL;
			}
			pIrp->IoStatus.Information = 0;
		}
		break;

	case IOCTL_SET_DRIVE:
		{
			PSEND_DRIVE pDrive;
			pDrive = (PSEND_DRIVE)pInputBuffer;
			SetSymbolicDriveName(pDrive->Drive); 	// 'A' or 'a' 부터..
			//
			ntStatus = STATUS_SUCCESS;
			pIrp->IoStatus.Information = 0;
		}
		break;

#ifdef _FILEHIDDEN_H
	case IOCTL_HIDDEN_FILES:
	case IOCTL_SHOW_FILES:
	case IOCTL_ADD_HIDDEN_FILE:
	case IOCTL_DEL_HIDDEN_FILE:
	case IOCTL_ALL_RESET_HIDDEN_FILES:
	case IOCTL_ADD_GUID:
		return HiddenFilesRoutine( pDevObj, pIrp );

#endif //_FILEHIDDEN_H

	default:
		ntStatus = STATUS_SUCCESS;
		pIrp->IoStatus.Information = 0;
		break;
	}

	pIrp->IoStatus.Status = ntStatus;
	//각 디스패치에서 결정된 스태이터스를 담는다
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);
	//끝났다는걸 그전에것에 알린다.
	return ntStatus;
}

#ifdef _FILEHIDDEN_H

NTSTATUS FILEHIDEDirectoryControl(IN PDEVICE_OBJECT DeviceObject,IN PIRP Irp)
{
	PDEVICE_EXTENSION deviceExtension;
	NTSTATUS ntStatus;
	PIO_STACK_LOCATION irpSp = IoGetCurrentIrpStackLocation( Irp );
	PFILE_BOTH_DIR_INFORMATION pInfo;
	ULONG dwInformation;
	PFILE_OBJECT FileObj;
	PWCHAR pwFileName;
	ULONG dwFileDirecotryInfoSize;

	FileObj = irpSp->FileObject;

	deviceExtension = DeviceObject->DeviceExtension;

	if( irpSp -> MinorFunction != IRP_MN_QUERY_DIRECTORY  )
	{
		return SkipAndSendIrpToNextDrive( DeviceObject, Irp );
	}

	if( irpSp -> Parameters.QueryDirectory.FileInformationClass  != FileBothDirectoryInformation  )
	{
		return SkipAndSendIrpToNextDrive( DeviceObject, Irp );
	}

	if( !fIsExistInHashTable( FileObj, &pwFileName ) )
	{
		return SkipAndSendIrpToNextDrive( DeviceObject, Irp );
	}

	if( !pwFileName )
	{
		return SkipAndSendIrpToNextDrive( DeviceObject, Irp );
	}

	if( Irp->AssociatedIrp.SystemBuffer )
		pInfo = Irp->AssociatedIrp.SystemBuffer;
	else 
		pInfo = Irp->UserBuffer;

	ntStatus = ReturnCurrentStackAfterSendIrpToNextDrive(DeviceObject, Irp);

	if( ntStatus != STATUS_SUCCESS )
	{
		IoCompleteRequest( Irp, IO_NO_INCREMENT );
		return ntStatus;
	}

	dwFileDirecotryInfoSize = GetRealSize( pInfo );
	if( !dwFileDirecotryInfoSize )
	{
		IoCompleteRequest( Irp, IO_NO_INCREMENT );
		return ntStatus;
	}

	dwInformation = HideFiles( pwFileName, pInfo, dwFileDirecotryInfoSize );

	Irp->IoStatus.Information = dwInformation;
	IoCompleteRequest( Irp, IO_NO_INCREMENT );
	return ntStatus;
}
#endif //_FILEHIDDEN_H

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	int i;
	if(DriverObject->DeviceObject)
	{
		IoDeleteDevice(DriverObject->DeviceObject);
		DriverObject->DeviceObject = NULL;
		for( i = 0; i < NUM_GUID_HASH; i++ )   
		{
			if(GUIDHashTable[ i ]){
				ExFreePool(GUIDHashTable[i]);
			}
		}
	}
	if (OpenProcessName)	ExFreePool(OpenProcessName);
	if (OpenCallerName)		ExFreePool(OpenCallerName);
	if (ReadProcessName)	ExFreePool(ReadProcessName);
	if (ReadCallerName)		ExFreePool(ReadCallerName);

	UnhookNativeApi();

	KdPrint(("Driver Unload!!!"));
}
NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject,IN PUNICODE_STRING RegistryPath)
{
	UNICODE_STRING nameString;
	UNICODE_STRING uniWin32NameString;
	PFILE_OBJECT fileObject;
	NTSTATUS status;
	PFAST_IO_DISPATCH fastIoDispatch;
	ULONG i, t;
	//PDEVICE_EXTENSION deviceExtension;

	DriverObject->DriverUnload = DriverUnload;
	
	DbgPrint("Driver Ver is 0.4.3.1+ ReadVM&OpenPcs  //DBmsg//\n");
#ifdef _FILEHIDDEN_H
	status = InitializeHiddenFileList();
	if( status != STATUS_SUCCESS )
		return status;
#endif //_FILEHIDDEN_H

	ResetList();
	ExInitializeFastMutex(&OpenProcessMutex);

	RtlInitUnicodeString( &nameString, L"\\Device\\filehide_my" );
	status = IoCreateDevice(
		DriverObject,
		sizeof( DEVICE_EXTENSION ),
		&nameString,
		FILE_DEVICE_DISK_FILE_SYSTEM,
		0,
		FALSE,
		&g_DeviceObject
		);

	if (!NT_SUCCESS( status )) 
	{
		return status;
	}

	for (i = 0; i <= IRP_MJ_MAXIMUM_FUNCTION; i++) 
	{
		DriverObject->MajorFunction[i] = FILEHIDEPassThrough;
	}
	
	ProcessNameOffset = GetProcessNameOffset();

	DriverObject->MajorFunction[IRP_MJ_CREATE] = FILEHIDECreate;
	DriverObject->MajorFunction[IRP_MJ_FILE_SYSTEM_CONTROL] = FILEHIDEFsControl;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = FILEHIDEDeviceIoControl;
#ifdef _FILEHIDDEN_H	
	DriverObject->MajorFunction[IRP_MJ_DIRECTORY_CONTROL] = FILEHIDEDirectoryControl;
#endif //_FILEHIDDEN_H    

	fastIoDispatch = ExAllocatePool( NonPagedPool, sizeof( FAST_IO_DISPATCH ) );
	if (!fastIoDispatch) {
		IoDeleteDevice( g_DeviceObject );
		return STATUS_INSUFFICIENT_RESOURCES;
	}

	RtlZeroMemory( fastIoDispatch, sizeof( FAST_IO_DISPATCH ) );
	fastIoDispatch->SizeOfFastIoDispatch = sizeof( FAST_IO_DISPATCH );
	fastIoDispatch->FastIoCheckIfPossible = FILEHIDEFastIoCheckIfPossible;
	fastIoDispatch->FastIoRead = FILEHIDEFastIoRead;
	fastIoDispatch->FastIoWrite = FILEHIDEFastIoWrite;
	fastIoDispatch->FastIoQueryBasicInfo = FILEHIDEFastIoQueryBasicInfo;
	fastIoDispatch->FastIoQueryStandardInfo = FILEHIDEFastIoQueryStandardInfo;
	fastIoDispatch->FastIoLock = FILEHIDEFastIoLock;
	fastIoDispatch->FastIoUnlockSingle = FILEHIDEFastIoUnlockSingle;
	fastIoDispatch->FastIoUnlockAll = FILEHIDEFastIoUnlockAll;
	fastIoDispatch->FastIoUnlockAllByKey = FILEHIDEFastIoUnlockAllByKey;
	fastIoDispatch->FastIoDeviceControl = FILEHIDEFastIoDeviceControl;
	fastIoDispatch->FastIoDetachDevice = FILEHIDEFastIoDetachDevice;
	fastIoDispatch->FastIoQueryNetworkOpenInfo = FILEHIDEFastIoQueryNetworkOpenInfo;
	fastIoDispatch->MdlRead = FILEHIDEFastIoMdlRead;
	fastIoDispatch->MdlReadComplete = FILEHIDEFastIoMdlReadComplete;
	fastIoDispatch->PrepareMdlWrite = FILEHIDEFastIoPrepareMdlWrite;
	fastIoDispatch->MdlWriteComplete = FILEHIDEFastIoMdlWriteComplete;
	fastIoDispatch->FastIoReadCompressed = FILEHIDEFastIoReadCompressed;
	fastIoDispatch->FastIoWriteCompressed = FILEHIDEFastIoWriteCompressed;
	fastIoDispatch->MdlReadCompleteCompressed = FILEHIDEFastIoMdlReadCompleteCompressed;
	fastIoDispatch->MdlWriteCompleteCompressed = FILEHIDEFastIoMdlWriteCompleteCompressed;
	fastIoDispatch->FastIoQueryOpen = FILEHIDEFastIoQueryOpen;

	DriverObject->FastIoDispatch = fastIoDispatch;

	status = ExInitializeResourceLite( &LockHash );
	if( !NT_SUCCESS( status ) )
	{
		ExFreePool (fastIoDispatch) ;
		DriverObject->FastIoDispatch = NULL ;
		IoDeleteDevice (g_DeviceObject) ;
		return status ;
	}

	for( i = 0; i < NUM_HASH; i++ )   
	{
		HashTable[ i ] = NULL;
	}

	for( i = 0; i < NUM_GUID_HASH; i++ )   
	{
		GUIDHashTable[ i ] = NULL;
	}

	g_DriverObject = DriverObject;

	InitializeListHead( &FsDeviceQueue );
	ExInitializeResource( &FsLock );

	deviceExtension = g_DeviceObject->DeviceExtension;
	deviceExtension->ullMagicNumber = MAGIC_NUMBER;
	deviceExtension->Type = FORAPP;
	deviceExtension->Drive = 0;

	RtlInitUnicodeString( &uniWin32NameString, DOS_DEVICE_NAME );
	status = IoCreateSymbolicLink( &uniWin32NameString, &nameString );
	if (!NT_SUCCESS(status))
	{
		ExFreePool (fastIoDispatch) ;
		ExDeleteResource( &FsLock );
		IoDeleteDevice( g_DeviceObject );
		return status;
	}

	FILEHIDERecognizer();

	status = IoRegisterFsRegistrationChange( g_DriverObject, FILEHIDEFsNotification );
	if (!NT_SUCCESS( status )) 
	{
		ExFreePool (fastIoDispatch) ;
		ExDeleteResource( &FsLock );
		IoDeleteDevice( g_DeviceObject );
		IoRegisterFsRegistrationChange( g_DriverObject, NULL );
		return status;
	}

//////////////////////////////////////////////////////////////////////////
	
	Name2 = HjAllocatePool(NonPagedPool,NT_PROCNAMELEN);
	OpenProcessName = HjAllocatePool(NonPagedPool,NT_PROCNAMELEN);
	OpenCallerName = HjAllocatePool(NonPagedPool,NT_PROCNAMELEN);
	ReadProcessName = HjAllocatePool(NonPagedPool,NT_PROCNAMELEN);
	ReadCallerName = HjAllocatePool(NonPagedPool,NT_PROCNAMELEN);
	HookNativeApi();

//////////////////////////////////////////////////////////////////////////

	return status;
}

NTSTATUS FILEHIDECommonCompletion(IN PDEVICE_OBJECT DeviceObject,IN PIRP Irp,IN PVOID Context)
{
	//pDevObj : 필터 드라이버의 디바이스오브젝트
	//pIrp : IRP명령어
	//Context : 중단점 루틴 정의 시 언급한 Context 주소

	PKEVENT pEvent = Context;

	KeSetEvent( pEvent, 0, FALSE );
	return STATUS_MORE_PROCESSING_REQUIRED;
}

NTSTATUS FILEHIDEPassThrough(IN PDEVICE_OBJECT pDevObj, IN PIRP pIrp)
{
	PDEVICE_EXTENSION pDevExt;
	NTSTATUS ntStatus;
	PFILE_OBJECT pFileObj;
	WCHAR * pwFullPath = NULL;
	PIO_STACK_LOCATION pCurIrpStack;

	pDevExt = pDevObj->DeviceExtension;

	pCurIrpStack = IoGetCurrentIrpStackLocation(pIrp);

	pFileObj = pCurIrpStack->FileObject;

	if(pDevExt->ullMagicNumber == MAGIC_NUMBER)
	{
		if(pCurIrpStack->MajorFunction == IRP_MJ_CLOSE)
		{
			if( g_pEventObject != NULL )
			{
				ObDereferenceObject( g_pEventObject );
			}
			g_pEventObject = NULL;
			g_EventHandle = NULL;
			ntStatus = STATUS_SUCCESS;
		}
		pIrp->IoStatus.Status = ntStatus;
		pIrp->IoStatus.Information = 0;
		IoCompleteRequest( pIrp, IO_NO_INCREMENT );
		return ntStatus;
	}

	if(!fIsExistInHashTable(pFileObj, &pwFullPath))
	{
		return SkipAndSendIrpToNextDrive( pDevObj, pIrp );
	}

	switch(pCurIrpStack->MajorFunction)
	{
	case IRP_MJ_CLOSE:
		ExFreePool(pwFullPath);
		fFreeHashEntry(pFileObj);
		break;

	default:
		break;
	}

	return SkipAndSendIrpToNextDrive( pDevObj, pIrp );
}


NTSTATUS FILEHIDECreate(IN PDEVICE_OBJECT pDevObj, IN PIRP pIrp)
{
	PIO_STACK_LOCATION pCurIrpStack;
	NTSTATUS ntStatus;
	PDEVICE_EXTENSION pDevExt;
	WCHAR * pwFullPath = NULL;
	UCHAR * pFullPath = NULL;
	ULONG ulSize;
	ULONG preInformation;
	PFILE_OBJECT pFileObj;
	PHJ_NAME_INFORMATION pNameInfo;	
	ULONG dwRet;

	BOOLEAN blFolder;

	PWCHAR pwFileName;
	PFILE_BOTH_DIR_INFORMATION pInfo;

	int tempn;
	unsigned short *pwOriginalPath;
	unsigned short *pwGUIDPartofPath;
	unsigned short *ResultGUIDSt;
	unsigned short *pwOriginalPath_fObj;

	pDevExt = pDevObj->DeviceExtension;

	pCurIrpStack = IoGetCurrentIrpStackLocation(pIrp);
	
	pFileObj = pCurIrpStack->FileObject;

	if(pDevExt-> ullMagicNumber == MAGIC_NUMBER)
	{
		pIrp->IoStatus.Status = STATUS_SUCCESS;
		pIrp->IoStatus.Information = 0;
		IoCompleteRequest(pIrp, IO_NO_INCREMENT);
		return STATUS_SUCCESS;
	}

	{ // FullPath구하기..
		ntStatus = HjCreateNameInformationMemory( &pNameInfo );
		if( ntStatus == STATUS_SUCCESS )
		{
			ntStatus = HjQueryNameString(
				pFileObj, 
				pNameInfo
				);
			if( ntStatus == STATUS_SUCCESS )
			{
				// FullPath가 구해지면 이곳으로 온다
			}
			else
			{	
				HjDeleteNameInformationMemory( pNameInfo );
				return SkipAndSendIrpToNextDrive( pDevObj, pIrp );
			}
		}
		else
		{
			return SkipAndSendIrpToNextDrive( pDevObj, pIrp );
		}
	}

	pwFullPath = (WCHAR *)HjAllocatePool(NonPagedPool, FILENAMESIZE * sizeof(WCHAR));
	if( !pwFullPath )
	{
		HjDeleteNameInformationMemory( pNameInfo );
		return SkipAndSendIrpToNextDrive( pDevObj, pIrp );
	}

	memcpy( (unsigned char *)pwFullPath, (unsigned char *)pNameInfo->uniName.Buffer, pNameInfo->uniName.Length );
	HjDeleteNameInformationMemory( pNameInfo );
	

	tempn=wcslen(pwFullPath);
	
	if(IsExistHiddenFileList(pwFullPath) )
	{
		DbgPrint("now file is HIDDEN file//DBmsg//");
		return STATUS_ACCESS_DENIED;	
	}
	else if( tempn > GUIDCNT){
		pwOriginalPath = (unsigned short *)HjAllocatePool( NonPagedPool, MAXHIDDENFILENAMESIZE );
		memcpy(pwOriginalPath,pwFullPath,tempn*2-GUIDCNTX2);


		ResultGUIDSt = (unsigned short *)HjAllocatePool( NonPagedPool, MAXHIDDENFILENAMESIZE );
		if(pwOriginalPath != NULL && GUIDIsExistInHashTable(pwOriginalPath, &ResultGUIDSt))
		{
			DbgPrint("find GUID in hash//DBmsg//");
			pwGUIDPartofPath = (unsigned short *)HjAllocatePool( NonPagedPool, MAXHIDDENFILENAMESIZE );
			memcpy(pwGUIDPartofPath,pwFullPath+(tempn-GUIDCNT),GUIDCNTX2);
			//갯수대로

			if(_wcsicmp( ResultGUIDSt, pwGUIDPartofPath)==0){	
				DbgPrint("GUID is matching OK//DBmsg//");
				pwOriginalPath_fObj = (unsigned short *)HjAllocatePool( NonPagedPool, MAXHIDDENFILENAMESIZE );
				memcpy(pwOriginalPath_fObj,pFileObj->FileName.Buffer,pFileObj->FileName.Length-GUIDCNTX2);

				memcpy(pFileObj->FileName.Buffer,pwOriginalPath_fObj,pFileObj->FileName.Length);
				pFileObj->FileName.Length=pFileObj->FileName.Length-GUIDCNTX2;		
				ExFreePool( pwOriginalPath_fObj );
			}
			ExFreePool( pwGUIDPartofPath );
		}
		ExFreePool( ResultGUIDSt );		
		ExFreePool( pwOriginalPath );		
	}
	
	ntStatus = ReturnCurrentStackAfterSendIrpToNextDrive( pDevObj, pIrp);

	if( ntStatus == STATUS_SUCCESS )
	{
		fInsertHashEntry(pFileObj, pwFullPath );
	}
	else
	{
		ExFreePool( pwFullPath );
	}

	IoCompleteRequest(pIrp, IO_NO_INCREMENT);
	
	
	
	//////////////////////////////////////////////////////////////////////////
	return ntStatus;
}



//////////////////////////////////////////////////////////////////////////
//
//		 P  R  O  C  E  S  S      I  N  F  O  R  M  A  T  I  O  N
//
//////////////////////////////////////////////////////////////////////////





// Get process name offset
ULONG GetProcessNameOffset(void)
{
	PEPROCESS curproc;
	int i;

	curproc = PsGetCurrentProcess();

	//KdPrint(("[*] Name : %s ",curproc));

	for (i=0; i < 3*PAGE_SIZE; i++)
	{
		if(!strncmp(SYSNAME, (LPSTR)curproc + i, strlen(SYSNAME)))
		{
			//KdPrint(("[*]  : %d ",i));
			return i;


		}
	}
	return 0;
}


//
// Get current process name
//
LPSTR
GetCurrentProcessName()//OUT LPSTR Name)
{
	PEPROCESS       curproc;
	LPSTR			nameptr;

	if (ProcessNameOffset) 
	{
		curproc	= PsGetCurrentProcess();
		
		nameptr	= (LPSTR)curproc + ProcessNameOffset;
		//strncpy(Name,nameptr,NT_PROCNAMELEN);
		//Name[NT_PROCNAMELEN] = 0;
		return nameptr;
	} 

	return NULL;
}

unsigned short * CharToWChar(const char* pstrSrc)
{
	//ASSERT(pstrSrc);
	int nLen = strlen(pstrSrc)+1;

	unsigned short *pwstr = (unsigned short *)HjAllocatePool( NonPagedPool, sizeof( wchar_t )* nLen );
	mbstowcs(pwstr, pstrSrc, nLen);

	return pwstr;
}


//
// oldZwOpenProcess
//

NTSTATUS newZwOpenProcess(					// new function
						  OUT PHANDLE ProcessHandle,
						  IN ACCESS_MASK DesiredAccess,
						  IN POBJECT_ATTRIBUTES ObjectAttributes,
						  IN PCLIENT_ID ClientId OPTIONAL
						  )
{


	NTSTATUS	status;
	PEPROCESS	Process;
	unsigned short *OpenPName_UNI;

	OpenCallerName = GetCurrentProcessName();

	status = ((ZWOPENPROCESS)(oldZwOpenProcess))(
		ProcessHandle,
		DesiredAccess,
		ObjectAttributes,
		ClientId);	

	if (NT_SUCCESS(status))
	{
		// Is process handle all accessible ?
		if (DesiredAccess == PROCESS_ALL_ACCESS)
		{
			if (NT_SUCCESS(
				ObReferenceObjectByHandle(
				*ProcessHandle,
				PROCESS_ALL_ACCESS,
				NULL,
				KernelMode,
				(PVOID *)&Process,
				NULL))) 
			{
			
				//ExAcquireFastMutex(&OpenProcessMutex);

				strncpy(OpenProcessName,((PCHAR)Process) + ProcessNameOffset, NT_PROCNAMELEN);


				// Is caller not explorer or task manager ?
				if (_stricmp(OpenCallerName, EXPLORERNAME) != 0 && 
					_stricmp(OpenCallerName, TASKMGRNAME) != 0&&
					_stricmp(OpenCallerName, AB_SVC) != 0 &&
					_stricmp(OpenCallerName, CSRSS) != 0)
				{
					if (_stricmp(OpenCallerName, OpenProcessName) != 0 )
					{
						OpenPName_UNI=CharToWChar(OpenProcessName);
						if (!_stricmp(OpenProcessName,MYPROCESS) || IsExistHiddenProcess((WCHAR*)(OpenPName_UNI)))
						{
							//DbgBreakPoint();
							//ZwClose(ProcessHandle);
											
							KdPrint(("[Alarm] OpenProcess Detected"));
							KdPrint(("Called by %s Call %s",OpenCallerName,OpenProcessName));
							//ExFreePool(OpenPName_UNI);
							status = STATUS_INVALID_HANDLE;
							ProcessHandle=NULL;
						}
						//ExFreePool(OpenPName_UNI);
					}
				}
				//ExReleaseFastMutex(&OpenProcessMutex);
				ObDereferenceObject(Process);
		
			}
			
		}
	}
	return status;

}


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
							 )
{
	NTSTATUS	ntStatus;
	PEPROCESS	Process;
	unsigned short *ReadPName_UNI;


	if (NT_SUCCESS(
		ObReferenceObjectByHandle(
		hProcess,
		PROCESS_ALL_ACCESS,
		NULL,
		KernelMode,
		(PVOID *)&Process,
		NULL)))
	
	{	
		// Get caller name
		ReadCallerName = GetCurrentProcessName();

		// Get process name
		//strncpy(ReadProcessName, ((PCHAR)Process) + ProcessNameOffset, NT_PROCNAMELEN);
		strcpy(ReadProcessName, ((PCHAR)Process) + ProcessNameOffset);


		// Is caller not explorer ?
		if (_stricmp(ReadCallerName, EXPLORERNAME) != 0 && 
			_stricmp(ReadCallerName, TASKMGRNAME) != 0 &&
			_stricmp(ReadCallerName, AB_SVC) != 0 &&
			_stricmp(ReadCallerName, CSRSS) != 0)
		{
			// Is caller not the process ?

			if (strcmp(ReadCallerName, ReadProcessName) != 0)
			{
				KdPrint(("Called by %s Call %s",ReadCallerName,ReadProcessName));

				// Is caller not the process ?
				ReadPName_UNI=CharToWChar(ReadProcessName);
				if (!_stricmp(ReadProcessName,MYPROCESS) || IsExistHiddenProcess((WCHAR*)(ReadPName_UNI)))
				{
					// Is read process request ?
					if ((BytesToRead != 0x50) && 
						(BaseAddress != (void *)0x7FFDC00C) && 
						(BaseAddress != (void *)0x7FFDB00C) && 
						(BaseAddress != (void *)0x1A1EA4) && 
						(BaseAddress != (void *)0x20840))
					{
						KdPrint(("[Warring] ReadMemory Detected!! denined"));
						KdPrint(("Called by %s",ReadCallerName));
						// return invalid handle status
						ExFreePool(ReadPName_UNI);
						return STATUS_INVALID_HANDLE;
					}

				}
				ExFreePool(ReadPName_UNI);

			}
		}
		
	}

	// Call old ZwReadVirtualMemory
	ntStatus = ((ZWREADVIRTUALMEMORY)(oldZwReadVirtualMemory))(
		hProcess,
		BaseAddress,
		Buffer,
		BytesToRead,
		BytesRead
		);

	return	ntStatus;
}

//
// ZwQuerySystemInformation
// 
NTSTATUS 
newZwQuerySystemInformation(
							IN ULONG SystemInformationClass,
							IN PVOID SystemInformation,
							IN ULONG SystemInformationLength,
							OUT PULONG ReturnLength
							)
{
	NTSTATUS ntStatus;
	PSYSTEM_PROCESSES curr; 
	PSYSTEM_PROCESSES prev;
	int i;


	// Call old ZwQuerySystemInformation
	ntStatus = ((ZWQUERYSYSTEMINFORMATION)(oldZwQuerySystemInformation))(
		SystemInformationClass,
		SystemInformation,
		SystemInformationLength,
		ReturnLength);

	// Is old ZwQuerySystemInformation succeeded ?
	if (NT_SUCCESS(ntStatus))
	{
		if(g_HiddenFileAction==TRUE)
		if (5 == SystemInformationClass)
		{
			curr = (PSYSTEM_PROCESSES)SystemInformation;
			prev = NULL;
			while (curr)
			{
				ANSI_STRING process_name;
				RtlUnicodeStringToAnsiString(&process_name,&(curr->ProcessName),TRUE);
				
				
				if ((255 > process_name.Length) && (0 < process_name.Length))
				{
					if (0 == memcmp(process_name.Buffer,MYPROCESS,strlen(MYPROCESS)) 
						|| IsExistHiddenProcess((WCHAR*)(curr->ProcessName.Buffer)))
					{
						if (prev)
						{
							if (curr->NextEntryDelta)
							{
								prev->NextEntryDelta += curr->NextEntryDelta;
							}
							else
							{
								prev->NextEntryDelta = 0;
							}
						}
						else
						{
							if (curr->NextEntryDelta)
							{
								(char*)SystemInformation += curr->NextEntryDelta;
							}
							else
							{
								SystemInformation = NULL;
							}
						}

					}
				
				}
				


				RtlFreeAnsiString(&process_name);
				prev = curr;
				if(curr->NextEntryDelta)	((char*)curr += curr->NextEntryDelta);
				else curr = NULL;
			}



		}
	}

	return ntStatus;
}



void HookNativeApi(void)
{

	// save old function pointer
	
	oldZwOpenProcess				= (ZWOPENPROCESS)NT_SERVICE(ZwOpenProcess);
	//oldZwCreateProcessEx			= (ZWCREATEPROCESSEX)(NT_SERVICE_INDEX(ZwCreateProcessEx));
	oldZwReadVirtualMemory			= (ZWREADVIRTUALMEMORY)(NT_SERVICE_INDEX(ZwReadVirtualMemory));
	//oldZwWriteVirtualMemory		= (ZWWRITEVIRTUALMEMORY)(NT_SERVICE_INDEX(ZwWriteVirtualMemory));
	oldZwQuerySystemInformation		= (ZWQUERYSYSTEMINFORMATION)(NT_SERVICE(ZwQuerySystemInformation));

	// Disable system interrupt
	_asm
	{
		CLI
		MOV	EAX, CR0	
		AND EAX, NOT 10000H 
		MOV	CR0, EAX
	}


	// change my function
	//

	(ZWOPENPROCESS)(NT_SERVICE(ZwOpenProcess))						= newZwOpenProcess;
	//(ZWCREATEPROCESSEX)(NT_SERVICE_INDEX(ZwCreateProcessEx))			= newZwCreateProcessEx;
	(ZWREADVIRTUALMEMORY)(NT_SERVICE_INDEX(ZwReadVirtualMemory))		= newZwReadVirtualMemory;
	//(ZWWRITEVIRTUALMEMORY)(NT_SERVICE_INDEX(ZwWriteVirtualMemory))	= newZwWriteVirtualMemory;
	(ZWQUERYSYSTEMINFORMATION)(NT_SERVICE(ZwQuerySystemInformation))	= newZwQuerySystemInformation;

	// Enable system interrupt
	_asm
	{
		MOV	EAX, CR0		
		OR	EAX, 10000H		
		MOV	CR0, EAX			
		STI	
	}

}

void UnhookNativeApi(void)
{

	// Disable system interrupt
	_asm
	{
		CLI
		MOV	EAX, CR0	
		AND EAX, NOT 10000H 
		MOV	CR0, EAX
	}

	(ZWOPENPROCESS)(NT_SERVICE(ZwOpenProcess))						= oldZwOpenProcess;
	//(ZWCREATEPROCESSEX)(NT_SERVICE_INDEX(ZwCreateProcessEx))			= oldZwCreateProcessEx;
	(ZWREADVIRTUALMEMORY)(NT_SERVICE_INDEX(ZwReadVirtualMemory))		= oldZwReadVirtualMemory;
	//(ZWWRITEVIRTUALMEMORY)(NT_SERVICE_INDEX(ZwWriteVirtualMemory))	= oldZwWriteVirtualMemory;
	(ZWQUERYSYSTEMINFORMATION)(NT_SERVICE(ZwQuerySystemInformation))	= oldZwQuerySystemInformation;

	// Enable system interrupt
	_asm
	{
		MOV	EAX, CR0		
		OR	EAX, 10000H		
		MOV	CR0, EAX			
		STI	
	}
}

