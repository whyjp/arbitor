#include <ntifs.h>
#include "main.h"
#include "utility.h"

extern PDRIVER_OBJECT g_DriverObject;

extern STORENAMEINSTANCE DriveNameList[MAXDRIVENUMBER];

void ResetList()
{
	int i;

	for( i = 0 ; i < MAXDRIVENUMBER ; i ++ )
	{
		DriveNameList[i].TranslatedDriveName[0] = 0;
	}
}

int SearchDriveNameHint( char Drive )
{
    IO_STATUS_BLOCK     ioStatus;
    HANDLE              ntFileHandle;   
    OBJECT_ATTRIBUTES   objectAttributes;
    PDEVICE_OBJECT      fileSysDevice;
    PDEVICE_OBJECT      hookDevice;
    UNICODE_STRING      fileNameUnicodeString;
    PFILE_FS_ATTRIBUTE_INFORMATION fileFsAttributes;
    ULONG               fileFsAttributesSize;
    WCHAR               filename[] = L"\\DosDevices\\A:\\";
    NTSTATUS            ntStatus;
    ULONG               i;
    PFILE_OBJECT        fileObject;
	PDEVICE_OBJECT MyDeviceObject;

    filename[12] = Drive;

    RtlInitUnicodeString( &fileNameUnicodeString, filename );
    InitializeObjectAttributes( &objectAttributes, &fileNameUnicodeString, 
                                    OBJ_CASE_INSENSITIVE, NULL, NULL );
    ntStatus = ZwCreateFile( &ntFileHandle, SYNCHRONIZE|FILE_ANY_ACCESS, 
                                 &objectAttributes, &ioStatus, NULL, 0, FILE_SHARE_READ|FILE_SHARE_WRITE, 
                                 FILE_OPEN, 
                                 FILE_SYNCHRONOUS_IO_NONALERT|FILE_DIRECTORY_FILE, 
                                 NULL, 0 );
    if( !NT_SUCCESS( ntStatus ) ) {
		return FALSE;
    }

    ntStatus = ObReferenceObjectByHandle( ntFileHandle, FILE_READ_DATA, 
                                              NULL, KernelMode, &fileObject, NULL );
    if( !NT_SUCCESS( ntStatus )) {
        ZwClose( ntFileHandle );
        return FALSE;
    }
    fileSysDevice = IoGetRelatedDeviceObject( fileObject );

    if( ! fileSysDevice ) {
		ObDereferenceObject( fileObject );
        ZwClose( ntFileHandle );
        return FALSE;
    }

	MyDeviceObject = g_DriverObject->DeviceObject;
	while( MyDeviceObject )
	{
		PDEVICE_EXTENSION deviceExtension;
		deviceExtension = MyDeviceObject->DeviceExtension;
		if( deviceExtension->Type != FORMON )
		{
			MyDeviceObject = MyDeviceObject->NextDevice;
			continue;
		}
		
		fileSysDevice = fileObject->DeviceObject;
		while( fileSysDevice )
		{
			if( fileSysDevice != MyDeviceObject )
			{
				fileSysDevice = fileSysDevice->AttachedDevice;
				continue;
			}
			deviceExtension->Drive = Drive;			
			ObDereferenceObject( fileObject );
			ZwClose( ntFileHandle );
			return TRUE;
		}
		MyDeviceObject = MyDeviceObject->NextDevice;
	}

	ObDereferenceObject( fileObject );
    ZwClose( ntFileHandle );
	return FALSE;
}

void SetSymbolicDriveName(char DriveName) 
{
	UNICODE_STRING StringName;
	int i;
	NTSTATUS St;
	HANDLE LinkHandle;
	OBJECT_ATTRIBUTES ObjectAttributes;
	WCHAR * Buffer;

	int dwRet;
	WCHAR RawDriveBaseName[] = L"\\??\\A:";

	Buffer = (WCHAR * )ExAllocatePool( NonPagedPool, 1000 * sizeof(WCHAR) );

	i = DriveName - 'A';
	if( DriveName >= 'a' )
		i -= 0x20;

	if( (i + 'A') >= 'C' )
	{
		if( SearchDriveNameHint( i + 'A' ) == TRUE )
		{
			ExFreePool( Buffer );
			return;
		}
	}

	RawDriveBaseName[4] = L'A' + i;
	RtlInitUnicodeString( &StringName, RawDriveBaseName );
	InitializeObjectAttributes( &ObjectAttributes, &StringName, OBJ_CASE_INSENSITIVE, 0, 0 );
	St = ZwOpenSymbolicLinkObject( &LinkHandle, 0x80000000, &ObjectAttributes );
	if( STATUS_SUCCESS != St )
	{
		DriveNameList[i].TranslatedDriveName[0] = 0;
		ExFreePool( Buffer );
		return;
	}
	RtlZeroMemory( (unsigned char *)Buffer, 1000 * 2 );
	RtlInitUnicodeString( &StringName, Buffer );
	StringName.MaximumLength = 1000;
	St = ZwQuerySymbolicLinkObject( LinkHandle, &StringName, &dwRet );
	if( St != STATUS_SUCCESS )
	{
		DriveNameList[i].TranslatedDriveName[0] = 0;
		ZwClose( LinkHandle );
		ExFreePool( Buffer );
		return;
	}
	RtlCopyMemory( (unsigned char *)(DriveNameList[i].TranslatedDriveName), Buffer, dwRet * 2 );
	DriveNameList[i].TranslatedDriveName[dwRet] = 0;
	ZwClose( LinkHandle );
	ExFreePool( Buffer );
}

PDRIVER_OBJECT SearchDriverObject( PUNICODE_STRING pUni, PDEVICE_OBJECT *ppDeviceObject )
{
	NTSTATUS st;
	HANDLE Handle;
	UNICODE_STRING Uni;
	OBJECT_ATTRIBUTES ObjectAttributes;
	PDRIVER_OBJECT Object;
	PDEVICE_OBJECT DeviceObject;

	*ppDeviceObject = NULL;
	
       InitializeObjectAttributes( &ObjectAttributes,
	                                pUni,
	                                OBJ_CASE_INSENSITIVE,
	                                NULL,
	                                NULL );

    	st = ObOpenObjectByName( &ObjectAttributes,
                                 0L,
                                 0L,
                                 0L,
                                 0L,
                                 0L,
                                 &Handle );
	if( st != STATUS_SUCCESS )
		return (PDRIVER_OBJECT)0;

    	st = ObReferenceObjectByHandle( Handle,
                                        0x80000000,
                                        NULL,
                                        0,
                                        &Object,
                                        NULL );
	if( st != STATUS_SUCCESS )
	{
		ZwClose( Handle );
		return (PDRIVER_OBJECT)0;
	}
		
	ZwClose( Handle );
	ObDereferenceObject( Object );

	DeviceObject = Object->DeviceObject;

	while( DeviceObject->NextDevice )
	{
		DeviceObject = DeviceObject->NextDevice;
	}
	
	*ppDeviceObject = DeviceObject;
	
	return Object;	
}

PVOID HjAllocatePool( ULONG dwType, ULONG dwSize )
{
	unsigned char * pTemp;
	pTemp = (unsigned char *)ExAllocatePool( dwType, dwSize );
	if( !pTemp )
		return pTemp;

	RtlZeroMemory( pTemp, dwSize );
	return pTemp;
}

NTSTATUS HjCreateNameInformationMemory( PHJ_NAME_INFORMATION * ppObjNameInfo )
{
	PHJ_NAME_INFORMATION pInfo;

	if( !ppObjNameInfo )
		return STATUS_INVALID_PARAMETER;

	pInfo = (PHJ_NAME_INFORMATION)HjAllocatePool( NonPagedPool, sizeof(HJ_NAME_INFORMATION) );
	if( !pInfo )
		return STATUS_INSUFFICIENT_RESOURCES;

	pInfo->uniName.Buffer = (unsigned short *)HjAllocatePool( NonPagedPool, HJ_NAME_INFORMATION_UNICODE_STRING_BUFFER_SIZE );
	if( !pInfo->uniName.Buffer )
	{
		ExFreePool( pInfo );
		return STATUS_INSUFFICIENT_RESOURCES;
	}
	pInfo->uniName.MaximumLength = HJ_NAME_INFORMATION_UNICODE_STRING_BUFFER_SIZE;

	pInfo->ansiString.Buffer = (unsigned char *)HjAllocatePool( NonPagedPool, HJ_NAME_INFORMATION_ANSI_STRING_BUFFER_SIZE );
	if( !pInfo->ansiString.Buffer )
	{
		ExFreePool( pInfo->uniName.Buffer );
		ExFreePool( pInfo );
		return STATUS_INSUFFICIENT_RESOURCES;
	}
	pInfo->ansiString.MaximumLength = HJ_NAME_INFORMATION_ANSI_STRING_BUFFER_SIZE;
	*ppObjNameInfo = pInfo;

	return STATUS_SUCCESS;
}

// 메모리제거함수
NTSTATUS HjDeleteNameInformationMemory( PHJ_NAME_INFORMATION pObjNameInfo )
{
	if( !pObjNameInfo )
		return STATUS_INVALID_PARAMETER;

	if( pObjNameInfo->uniName.Buffer )
	{
		ExFreePool( pObjNameInfo->uniName.Buffer );
	}
	if( pObjNameInfo->ansiString.Buffer )
	{
		ExFreePool( pObjNameInfo->ansiString.Buffer );
	}
	ExFreePool( pObjNameInfo );
	return STATUS_SUCCESS;
}

NTSTATUS HjQueryNameString(PFILE_OBJECT pFileObj, PHJ_NAME_INFORMATION pObjNameInfo )
{
	NTSTATUS st;
	ULONG dwRet;
	POBJECT_NAME_INFORMATION pObjNameInfo_os;

	if( !pFileObj )
		return STATUS_INVALID_PARAMETER;
	if( !pObjNameInfo )
		return STATUS_INVALID_PARAMETER;

	{ // DBG
		unsigned short *pwTempString;
		unsigned short *pwFullString;
		pwFullString = (unsigned short *)HjAllocatePool( NonPagedPool, HJ_NAME_INFORMATION_UNICODE_STRING_BUFFER_SIZE );

		if( !pwFullString )
			return STATUS_INVALID_PARAMETER;

		pObjNameInfo_os = ExAllocatePool(NonPagedPool, HJ_NAME_INFORMATION_UNICODE_STRING_BUFFER_SIZE * sizeof(WCHAR));
		st = ObQueryNameString(pFileObj->DeviceObject, pObjNameInfo_os, HJ_NAME_INFORMATION_UNICODE_STRING_BUFFER_SIZE, &dwRet);
		if( st != STATUS_SUCCESS )
		{
			ExFreePool(pObjNameInfo_os);
			ExFreePool( pwFullString );
			return STATUS_INVALID_PARAMETER;
		}
		
		memcpy( pwFullString, pObjNameInfo_os->Name.Buffer, pObjNameInfo_os->Name.Length );
		
		ExFreePool(pObjNameInfo_os);

		{ // 사용자에 의해서 관심을 표명한 드라이브에 대한 Raw이름표를 찾아보고, 없으면, 이 함수를 에러리턴한다
			int i;
			for( i = 0 ; i < 26 ; i ++ )
			{
				if( DriveNameList[i].TranslatedDriveName[0] == 0 )
					continue;
				if( _wcsicmp( &DriveNameList[i].TranslatedDriveName[0], pwFullString ) != 0 )
					continue;
				break;
			}
			if( i >= 26 )
			{
				ExFreePool( pwFullString );
				return STATUS_INVALID_PARAMETER;
			}
			ExFreePool( pwFullString );

			pwFullString = (unsigned short *)HjAllocatePool( NonPagedPool, HJ_NAME_INFORMATION_UNICODE_STRING_BUFFER_SIZE );

			if( !pwFullString )
				return STATUS_INVALID_PARAMETER;

			pwFullString[0] = L'A' + i;
			pwFullString[1] = L':';
		}

		if( pFileObj->RelatedFileObject )
		{		
			pwTempString = (unsigned short *)HjAllocatePool( NonPagedPool, pFileObj->RelatedFileObject->FileName.Length + 2 );
			if( !pwTempString )
			{
				ExFreePool( pwFullString );
				return STATUS_INVALID_PARAMETER;
			}

			memcpy( pwTempString + wcslen(pwTempString), pFileObj->RelatedFileObject->FileName.Buffer, pFileObj->RelatedFileObject->FileName.Length );

			wcscat( pwFullString, pwTempString );
			if( pwTempString[wcslen(pwTempString)-1] != L'\\' )
				wcscat( pwFullString, L"\\" );

			ExFreePool( pwTempString );

			{
				// DriverName
				unsigned short *pwNameString;
				if( pFileObj->RelatedFileObject->DeviceObject->DriverObject->DriverName.Length )
				{
					pwNameString = (unsigned short *)HjAllocatePool( NonPagedPool, pFileObj->RelatedFileObject->DeviceObject->DriverObject->DriverName.Length + 2 );
					memcpy( pwNameString, pFileObj->RelatedFileObject->DeviceObject->DriverObject->DriverName.Buffer, pFileObj->RelatedFileObject->DeviceObject->DriverObject->DriverName.Length );
					ExFreePool( pwNameString );
				}
			}
		}

		if( pFileObj->FileName.Length )
		{		
			pwTempString = (unsigned short *)HjAllocatePool( NonPagedPool, pFileObj->FileName.Length + 2 );
			if( !pwTempString )
			{
				ExFreePool( pwFullString );
				return STATUS_INVALID_PARAMETER;
			}

			memcpy( pwTempString, pFileObj->FileName.Buffer, pFileObj->FileName.Length );

			wcscat( pwFullString, pwTempString );
			ExFreePool( pwTempString );
		}

		if( pFileObj->DeviceObject )
		{		
			{
				// DriverName
				unsigned short *pwNameString;
				if( pFileObj->DeviceObject->DriverObject->DriverName.Length )
				{
					pwNameString = (unsigned short *)HjAllocatePool( NonPagedPool, pFileObj->DeviceObject->DriverObject->DriverName.Length + 2 );
					memcpy( pwNameString, pFileObj->DeviceObject->DriverObject->DriverName.Buffer, pFileObj->DeviceObject->DriverObject->DriverName.Length );
					ExFreePool( pwNameString );
				}
			}
		}

		wcscpy( pObjNameInfo->uniName.Buffer, pwFullString );
		pObjNameInfo->uniName.Length = wcslen( pwFullString ) * sizeof(WCHAR);
		ExFreePool( pwFullString );
	}

	return STATUS_SUCCESS;
}

