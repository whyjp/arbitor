#ifndef _UTILITY_H_
#define _UTILITY_H_

typedef struct
{
	UNICODE_STRING uniName;
	ANSI_STRING ansiString;
} HJ_NAME_INFORMATION, *PHJ_NAME_INFORMATION;

#define HJ_NAME_INFORMATION_UNICODE_STRING_BUFFER_SIZE 0x400
#define HJ_NAME_INFORMATION_ANSI_STRING_BUFFER_SIZE 0x400

PVOID HjAllocatePool( 
	ULONG dwType, 
	ULONG dwSize 
	);

NTSTATUS HjCreateNameInformationMemory( 
	PHJ_NAME_INFORMATION * ppObjNameInfo 
	);

NTSTATUS HjDeleteNameInformationMemory( 
	PHJ_NAME_INFORMATION pObjNameInfo 
	);

NTSTATUS HjQueryNameString(
	PFILE_OBJECT pFileObj, 
	PHJ_NAME_INFORMATION pObjNameInfo
	);

void ResetList();

int SearchDriveNameHint( 
	char Drive 
	);

void SetSymbolicDriveName(
	char DriveName
	);

NTSYSAPI
NTSTATUS
NTAPI
ZwOpenSymbolicLinkObject(
    OUT PHANDLE LinkHandle,
    IN ACCESS_MASK DesiredAccess,
    IN POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSTATUS
ObOpenObjectByName(
    IN POBJECT_ATTRIBUTES ObjectAttributes,
    IN ULONG  OPTIONAL,
    IN ULONG AccessMode,
    IN ULONG OPTIONAL2,
    IN ULONG DesiredAccess OPTIONAL,
    IN OUT PVOID ParseContext OPTIONAL,
    OUT PHANDLE Handle
    );

PDRIVER_OBJECT SearchDriverObject( 
	PUNICODE_STRING pUni,
	PDEVICE_OBJECT * pDeviceObject
    );


#endif //_UTILITY_H_
