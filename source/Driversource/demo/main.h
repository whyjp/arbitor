#ifndef _MAIN_H_
#define _MAIN_H_

#pragma optimize("",off)

#define FORMON 1
#define FORAPP 2

#define FILEHIDE_DEVICE_TYPE   0x00000022

#define MAGIC_NUMBER 0x75A50386287C53A0

#define DOS_DEVICE_NAME     L"\\DosDevices\\filehide"
#define MAXDRIVENUMBER 26
#define FILENAMESIZE 255
#define PROCESS_NAME_LENGTH 255

typedef struct
{
	WCHAR TranslatedDriveName[200];
} STORENAMEINSTANCE, * PSTORENAMEINSTANCE;

typedef struct _DEVICE_EXTENSION 
{
	ULONGLONG ullMagicNumber;
	CSHORT Type;
	CSHORT Size;
	PDEVICE_OBJECT NextDriverDeviceObject;
	PDEVICE_OBJECT VolDeviceObject;
	BOOLEAN Attached;
	char Drive;
} DEVICE_EXTENSION, *PDEVICE_EXTENSION;

NTSTATUS FILEHIDECommonCompletion(IN PDEVICE_OBJECT pDevObj, IN PIRP pIrp, IN PVOID pContext);

void SetSymbolicDriveName(char DriveName);

NTSYSAPI NTSTATUS NTAPI ZwQuerySymbolicLinkObject(IN HANDLE LinkHandle,
	IN OUT PUNICODE_STRING LinkTarget, OUT PULONG ReturnedLength OPTIONAL);
	
NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath);
NTSTATUS FILEHIDEPassThrough(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);
NTSTATUS FILEHIDECreate(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);
NTSTATUS FILEHIDEFsControl(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);
VOID FILEHIDEFsNotification(IN PDEVICE_OBJECT DeviceObject, IN BOOLEAN FsActive);
NTSTATUS FILEHIDERead(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);

#endif // _MAIN_H_
    
