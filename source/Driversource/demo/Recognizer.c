#include <ntifs.h>
#include "main.h"
#include "utility.h"
#include "recognizer.h"

extern PDRIVER_OBJECT g_DriverObject;
extern PDEVICE_OBJECT g_DeviceObject;
extern PKEVENT g_pEventObject;

extern LIST_ENTRY FsDeviceQueue;
extern ERESOURCE FsLock;

NTSTATUS
FILEHIDEMountCompletion(
	IN PDEVICE_OBJECT DeviceObject,
	IN PIRP Irp,
	IN PVOID Context
	)
{
	PDEVICE_OBJECT fsfDeviceObject = (PDEVICE_OBJECT) Context;
	PDEVICE_EXTENSION deviceExtension = fsfDeviceObject->DeviceExtension;
	PIO_STACK_LOCATION irpSp = IoGetCurrentIrpStackLocation( Irp );
	PDEVICE_OBJECT deviceObject;
	PVPB vpb;

	FsRtlEnterFileSystem();
	ExAcquireResourceExclusive( &FsLock, TRUE );
	
	if (NT_SUCCESS( Irp->IoStatus.Status )) 
	{
		vpb = irpSp->Parameters.MountVolume.DeviceObject->Vpb;
		deviceObject = IoAttachDeviceToDeviceStack( (PDEVICE_OBJECT) Context, vpb->DeviceObject );
		
		if (deviceObject == NULL) 
		{
			IoDeleteDevice( (PDEVICE_OBJECT) Context );
			ExReleaseResource( &FsLock );
			FsRtlExitFileSystem();
			
			if (Irp->PendingReturned) 
			{
				IoMarkIrpPending( Irp );
			}
			return STATUS_SUCCESS;
		}
		
		deviceExtension->NextDriverDeviceObject = deviceObject;
		deviceExtension->Size = sizeof( DEVICE_EXTENSION );

		if (deviceObject->Flags & DO_BUFFERED_IO) 
		{
			fsfDeviceObject->Flags |= DO_BUFFERED_IO;
		}

		if (deviceObject->Flags & DO_DIRECT_IO) 
		{
			fsfDeviceObject->Flags |= DO_DIRECT_IO;
		}

		((PDEVICE_OBJECT) Context)->Flags &= ~DO_DEVICE_INITIALIZING;

		//if( g_pEventObject )
		//	KeSetEvent( g_pEventObject, NULL, FALSE );

	}
	else 
	{
		IoDeleteDevice( (PDEVICE_OBJECT) Context );
	}

	ExReleaseResource( &FsLock );
	FsRtlExitFileSystem();
	
	if (Irp->PendingReturned) 
	{
		IoMarkIrpPending( Irp );
	}
	return STATUS_SUCCESS;
}

NTSTATUS
FILEHIDELoadFsCompletion(
	IN PDEVICE_OBJECT DeviceObject,
	IN PIRP Irp,
	IN PVOID Context
	)
{
	PDEVICE_EXTENSION deviceExtension = DeviceObject->DeviceExtension;

	if (!NT_SUCCESS( Irp->IoStatus.Status )) 
	{
		IoAttachDeviceToDeviceStack( DeviceObject, deviceExtension->NextDriverDeviceObject );
	}
	else 
	{
		FsRtlEnterFileSystem();
		ExAcquireResourceExclusive( &FsLock, TRUE );
		InsertTailList(
			&FsDeviceQueue,
			&DeviceObject->Queue.ListEntry
			);
		ExReleaseResource( &FsLock );
		FsRtlExitFileSystem();
	}
	if (Irp->PendingReturned) 
	{
		IoMarkIrpPending( Irp );
	}
	return STATUS_SUCCESS;
}

NTSTATUS
FILEHIDEFsControl(
	IN PDEVICE_OBJECT DeviceObject,
	IN PIRP Irp
	)
{
	NTSTATUS status;
	PIO_STACK_LOCATION irpSp = IoGetCurrentIrpStackLocation( Irp );
	PIO_STACK_LOCATION nextIrpSp;
	PDEVICE_OBJECT deviceObject;
	PDEVICE_EXTENSION deviceExtension = DeviceObject->DeviceExtension;

	if (irpSp->MinorFunction == IRP_MN_MOUNT_VOLUME) 
	{
		deviceObject = (PDEVICE_OBJECT) NULL;
		if (!IsListEmpty( &FsDeviceQueue )) 
		{
			PLIST_ENTRY entry;

			FsRtlEnterFileSystem();
			ExAcquireResourceExclusive( &FsLock, TRUE );
			
			if (!IsListEmpty( &FsDeviceQueue )) 
			{
				entry = FsDeviceQueue.Flink;
				deviceObject = CONTAINING_RECORD(
									entry,
									DEVICE_OBJECT,
									Queue.ListEntry
									);
				if (!deviceObject->ReferenceCount) 
				{
					RemoveHeadList( &FsDeviceQueue );
					status = STATUS_SUCCESS;
				}
				else 
				{
					deviceObject = (PDEVICE_OBJECT) NULL;
				}
			}
			ExReleaseResource(&FsLock );
			FsRtlExitFileSystem();
		}
		
		if (!deviceObject) 
		{
			status = IoCreateDevice(
						g_DriverObject,
						sizeof( DEVICE_EXTENSION ),
						(PUNICODE_STRING) NULL,
						FILE_DEVICE_DISK_FILE_SYSTEM,
						0,
						FALSE,
						&deviceObject
						);
		}
		
		if (NT_SUCCESS( status ) && deviceObject) 
		{
			PDEVICE_EXTENSION deviceExtension;
			deviceExtension = deviceObject->DeviceExtension;

			deviceExtension->Type = FORMON;
			deviceExtension->Drive = 0;
			nextIrpSp = IoGetNextIrpStackLocation( Irp );
			RtlMoveMemory( nextIrpSp, irpSp, sizeof( IO_STACK_LOCATION ) );

			IoSetCompletionRoutine(
				Irp,
				FILEHIDEMountCompletion,
				deviceObject,
				TRUE,
				TRUE,
				TRUE
				);

			irpSp->Parameters.MountVolume.DeviceObject = irpSp->Parameters.MountVolume.Vpb->RealDevice;
		}
		else 
		{
			IoSkipCurrentIrpStackLocation( Irp );
		}
	}
	else if (irpSp->MinorFunction == IRP_MN_LOAD_FILE_SYSTEM) 
	{
		nextIrpSp = IoGetNextIrpStackLocation( Irp );
		RtlMoveMemory( nextIrpSp, irpSp, sizeof( IO_STACK_LOCATION ) );

		IoDetachDevice( deviceExtension->NextDriverDeviceObject );
		deviceExtension->Attached = FALSE;

		IoSetCompletionRoutine(
			Irp,
			FILEHIDELoadFsCompletion,
			DeviceObject,
			TRUE,
			TRUE,
			TRUE
			);
		}

	else if (!deviceExtension->Type) 
	{
		Irp->IoStatus.Status = STATUS_INVALID_DEVICE_REQUEST;
		Irp->IoStatus.Information = 0;

		IoCompleteRequest( Irp, IO_DISK_INCREMENT );

		return STATUS_INVALID_DEVICE_REQUEST;
	}
	else 
	{
		IoSkipCurrentIrpStackLocation( Irp );
	}

	return IoCallDriver( deviceExtension->NextDriverDeviceObject, Irp );
}

VOID
FILEHIDEFsNotification(
	IN PDEVICE_OBJECT DeviceObject,
	IN BOOLEAN FsActive
	)
{
	NTSTATUS status;
	PDEVICE_OBJECT deviceObject;
	PDEVICE_OBJECT nextAttachedDevice;
	PDEVICE_OBJECT fsDevice;
	BOOLEAN bRet=FALSE;
	if ((DeviceObject->DeviceType != FILE_DEVICE_DISK_FILE_SYSTEM) && 
		(DeviceObject->DeviceType != FILE_DEVICE_CD_ROM_FILE_SYSTEM) ) 
	{
		return;
	}

	if (FsActive) 
	{
		PDEVICE_EXTENSION deviceExtension;

		FsRtlEnterFileSystem();
		ExAcquireResourceExclusive( &FsLock, TRUE );

		fsDevice = DeviceObject;
		while(1)
		{
			nextAttachedDevice = fsDevice->AttachedDevice;
			if( !nextAttachedDevice )
				break;
		
			if( g_DriverObject != (PDRIVER_OBJECT)nextAttachedDevice )
			{
				fsDevice = fsDevice->AttachedDevice;
				continue;
			}

			bRet = TRUE;
			break;
		}

		if( bRet == TRUE )
		{
			ExReleaseResource( &FsLock );
			FsRtlExitFileSystem();
			return;
		}
		
		status = IoCreateDevice(
					g_DriverObject,
					sizeof( DEVICE_EXTENSION ),
					(PUNICODE_STRING) NULL,
					FILE_DEVICE_DISK_FILE_SYSTEM,
					0,
					FALSE,
					&deviceObject
					);
		if (NT_SUCCESS( status )) 
		{
			PDEVICE_EXTENSION deviceExtension;
			deviceExtension = deviceObject->DeviceExtension;
			deviceExtension->Drive = 0;
			deviceExtension->Type = FORMON;

			DeviceObject = IoAttachDeviceToDeviceStack( deviceObject, DeviceObject );
			if(DeviceObject == NULL) 
			{
				IoDeleteDevice( deviceObject );
			}
			else 
			{
				deviceExtension->NextDriverDeviceObject = DeviceObject;
				deviceObject->Flags &= ~DO_DEVICE_INITIALIZING;
			}
		}
		ExReleaseResource( &FsLock );
		FsRtlExitFileSystem();
	}
	else 
	{
		FsRtlEnterFileSystem();
		ExAcquireResourceExclusive( &FsLock, TRUE );
		
		fsDevice = DeviceObject;
		while(1)
		{
			nextAttachedDevice = fsDevice->AttachedDevice;
			if( !nextAttachedDevice )
				break;
		
			if( g_DriverObject != (PDRIVER_OBJECT)nextAttachedDevice )
			{
				fsDevice = fsDevice->AttachedDevice;
				continue;
			}

			IoDetachDevice( fsDevice );
			IoDeleteDevice( nextAttachedDevice );
			break;
		}
		
		ExReleaseResource( &FsLock );
		FsRtlExitFileSystem();
	}
	return;
}

enum
{
	NTFS_ID = 0,
	CDFS_ID,
	FASTFAT_ID,
	MAX_ID,
};

unsigned long FSD_ID[MAX_ID+1] = { NTFS_ID, CDFS_ID, FASTFAT_ID, 0 };
unsigned short * FSD_NAME[MAX_ID+1] = { L"\\FileSystem\\NTFS", L"\\FileSystem\\CDFS", L"\\FileSystem\\FASTFAT", 0 };

BOOLEAN IsExistOurDO( PDEVICE_OBJECT DeviceObject )
{
	PDEVICE_OBJECT MyCDO;
	PDEVICE_EXTENSION pDevExt;

	while( DeviceObject->AttachedDevice )
	{
		MyCDO = DeviceObject->AttachedDevice;
		DeviceObject = MyCDO;
		if( MyCDO->DriverObject == g_DriverObject )
			return TRUE;
	}
	return FALSE;
}

void FILEHIDERecognizer()
{
	int count;
	UNICODE_STRING uniname;
	PDEVICE_OBJECT DeviceObject;
	PDEVICE_OBJECT LowerCDO;
	PDEVICE_OBJECT MyCDO, MYVDO;
	BOOLEAN bRet;
	NTSTATUS status;
	PDEVICE_EXTENSION deviceExtension;
	PDRIVER_OBJECT FSDDriverObject;
	PDEVICE_OBJECT VDO;
	
	FsRtlEnterFileSystem();
	ExAcquireResourceExclusive( &FsLock, TRUE );

	for( count = 0 ; count < MAX_ID ; count ++ )
	{
		RtlInitUnicodeString( &uniname, FSD_NAME[count] );
		FSDDriverObject = SearchDriverObject( &uniname, &DeviceObject );
		if( !DeviceObject )
			continue;

		bRet = IsExistOurDO( DeviceObject );
		if( bRet == TRUE )
			continue;

		// Attach My CDO to Current CDO.
        	status = IoCreateDevice( 
                    g_DriverObject,
                    sizeof( DEVICE_EXTENSION ),
                    (PUNICODE_STRING) NULL,
                    FILE_DEVICE_DISK_FILE_SYSTEM,
                    0,
                    FALSE,
                    &MyCDO
                    );
		
        	if (NT_SUCCESS( status )) 
		{
             		deviceExtension = MyCDO->DeviceExtension;
			deviceExtension->Type = FORMON;
			deviceExtension->Drive = 0;
        	       MyCDO->Flags &= ~DO_DEVICE_INITIALIZING;

			LowerCDO = IoGetAttachedDevice( DeviceObject );
			status = IoAttachDeviceByPointer( MyCDO, DeviceObject );
			if( status == STATUS_SUCCESS )
		              deviceExtension->NextDriverDeviceObject = LowerCDO;
			else
			{
				IoDeleteDevice( MyCDO );
				continue;
			}
                }
		else
		{
			IoDeleteDevice( MyCDO );
			continue;
		}

		// Volume Atttach..
		VDO = DeviceObject->DriverObject->DeviceObject;
		
		while( VDO !=  DeviceObject )
		{
			bRet = IsExistOurDO( VDO );
			if( bRet == TRUE )
			{
				VDO = VDO->NextDevice;
				if( !VDO )
					break;
				continue;
			}

	        	status = IoCreateDevice( 
	                    g_DriverObject,
	                    sizeof( DEVICE_EXTENSION ),
	                    (PUNICODE_STRING) NULL,
	                    FILE_DEVICE_DISK_FILE_SYSTEM,
	                    0,
	                    FALSE,
	                    &MYVDO
	                    );
			
	        	if (NT_SUCCESS( status )) 
			{
	            		deviceExtension = MYVDO->DeviceExtension;
 	       	       MYVDO->Flags &= ~DO_DEVICE_INITIALIZING;
				deviceExtension->Type = FORMON;
				deviceExtension->Drive = 0;
				   
				LowerCDO = IoGetAttachedDevice( VDO );
				status = IoAttachDeviceByPointer( MYVDO, VDO );
				
				if( status == STATUS_SUCCESS )
				{
			              deviceExtension->NextDriverDeviceObject = LowerCDO;
					MYVDO->Flags |= ( LowerCDO->Flags & (DO_BUFFERED_IO|DO_DIRECT_IO));	  
				}
				else
				{
					IoDeleteDevice( MYVDO );
				}
	                }
			else
			{
				VDO = VDO->NextDevice;
				if( !VDO )
					break;
				continue;
			}

			VDO = VDO->NextDevice;
			if( !VDO )
				break;
		}
        }

	ExReleaseResource( &FsLock );
	FsRtlExitFileSystem();

}

