#include <ntifs.h>
#include "main.h"
#include "fastio.h"

extern ERESOURCE FsLock;

BOOLEAN
FILEHIDEFastIoCheckIfPossible(
    IN PFILE_OBJECT FileObject,
    IN PLARGE_INTEGER FileOffset,
    IN ULONG Length,
    IN BOOLEAN Wait,
    IN ULONG LockKey,
    IN BOOLEAN CheckForReadOperation,
    OUT PIO_STATUS_BLOCK IoStatus,
    IN PDEVICE_OBJECT DeviceObject
    )
{
    PDEVICE_OBJECT deviceObject;
    PFAST_IO_DISPATCH fastIoDispatch;

    deviceObject = ((PDEVICE_EXTENSION) (DeviceObject->DeviceExtension))->NextDriverDeviceObject;
    if (!deviceObject) {
        return FALSE;
        }
    fastIoDispatch = deviceObject->DriverObject->FastIoDispatch;

    if (fastIoDispatch && fastIoDispatch->FastIoCheckIfPossible) {
        return (fastIoDispatch->FastIoCheckIfPossible)(
                    FileObject,
                    FileOffset,
                    Length,
                    Wait,
                    LockKey,
                    CheckForReadOperation,
                    IoStatus,
                    deviceObject
                    );
        }
    else {
        return FALSE;
        }

}



BOOLEAN
FILEHIDEFastIoRead(
    IN PFILE_OBJECT FileObject,
    IN PLARGE_INTEGER FileOffset,
    IN ULONG Length,
    IN BOOLEAN Wait,
    IN ULONG LockKey,
    OUT PVOID Buffer,
    OUT PIO_STATUS_BLOCK IoStatus,
    IN PDEVICE_OBJECT DeviceObject
    )
{
    PDEVICE_OBJECT deviceObject;
    PFAST_IO_DISPATCH fastIoDispatch;

    deviceObject = ((PDEVICE_EXTENSION) (DeviceObject->DeviceExtension))->NextDriverDeviceObject;
    if (!deviceObject) {
        return FALSE;
        }
    fastIoDispatch = deviceObject->DriverObject->FastIoDispatch;

    if (fastIoDispatch && fastIoDispatch->FastIoRead) {
        return (fastIoDispatch->FastIoRead)(
                    FileObject,
                    FileOffset,
                    Length,
                    Wait,
                    LockKey,
                    Buffer,
                    IoStatus,
                    deviceObject
                    );
        }
    else {
        return FALSE;
        }

}


BOOLEAN
FILEHIDEFastIoWrite(
    IN PFILE_OBJECT FileObject,
    IN PLARGE_INTEGER FileOffset,
    IN ULONG Length,
    IN BOOLEAN Wait,
    IN ULONG LockKey,
    IN PVOID Buffer,
    OUT PIO_STATUS_BLOCK IoStatus,
    IN PDEVICE_OBJECT DeviceObject
    )
{
    PDEVICE_OBJECT deviceObject;
    PFAST_IO_DISPATCH fastIoDispatch;

    deviceObject = ((PDEVICE_EXTENSION) (DeviceObject->DeviceExtension))->NextDriverDeviceObject;
    if (!deviceObject) {
        return FALSE;
        }
    fastIoDispatch = deviceObject->DriverObject->FastIoDispatch;

    if (fastIoDispatch && fastIoDispatch->FastIoWrite) {
        return (fastIoDispatch->FastIoWrite)(
                    FileObject,
                    FileOffset,
                    Length,
                    Wait,
                    LockKey,
                    Buffer,
                    IoStatus,
                    deviceObject
                    );
        }
    else {
        return FALSE;
        }

}

BOOLEAN
FILEHIDEFastIoQueryBasicInfo(
    IN PFILE_OBJECT FileObject,
    IN BOOLEAN Wait,
    OUT PFILE_BASIC_INFORMATION Buffer,
    OUT PIO_STATUS_BLOCK IoStatus,
    IN PDEVICE_OBJECT DeviceObject
    )
{
    PDEVICE_OBJECT deviceObject;
    PFAST_IO_DISPATCH fastIoDispatch;

    deviceObject = ((PDEVICE_EXTENSION) (DeviceObject->DeviceExtension))->NextDriverDeviceObject;
    if (!deviceObject) {
        return FALSE;
        }
    fastIoDispatch = deviceObject->DriverObject->FastIoDispatch;

    if (fastIoDispatch && fastIoDispatch->FastIoQueryBasicInfo) {
        return (fastIoDispatch->FastIoQueryBasicInfo)(
                    FileObject,
                    Wait,
                    Buffer,
                    IoStatus,
                    deviceObject
                    );
        }
    else {
        return FALSE;
        }

}


BOOLEAN
FILEHIDEFastIoQueryStandardInfo(
    IN PFILE_OBJECT FileObject,
    IN BOOLEAN Wait,
    OUT PFILE_STANDARD_INFORMATION Buffer,
    OUT PIO_STATUS_BLOCK IoStatus,
    IN PDEVICE_OBJECT DeviceObject
    )
{
    PDEVICE_OBJECT deviceObject;
    PFAST_IO_DISPATCH fastIoDispatch;

    deviceObject = ((PDEVICE_EXTENSION) (DeviceObject->DeviceExtension))->NextDriverDeviceObject;
    if (!deviceObject) {
        return FALSE;
        }
    fastIoDispatch = deviceObject->DriverObject->FastIoDispatch;

    if (fastIoDispatch && fastIoDispatch->FastIoQueryStandardInfo) {
        return (fastIoDispatch->FastIoQueryStandardInfo)(
                    FileObject,
                    Wait,
                    Buffer,
                    IoStatus,
                    deviceObject
                    );
        }
    else {
        return FALSE;
        }

}

BOOLEAN
FILEHIDEFastIoLock(
    IN PFILE_OBJECT FileObject,
    IN PLARGE_INTEGER FileOffset,
    IN PLARGE_INTEGER Length,
    PEPROCESS ProcessId,
    ULONG Key,
    BOOLEAN FailImmediately,
    BOOLEAN ExclusiveLock,
    OUT PIO_STATUS_BLOCK IoStatus,
    IN PDEVICE_OBJECT DeviceObject
    )
{
    PDEVICE_OBJECT deviceObject;
    PFAST_IO_DISPATCH fastIoDispatch;

    deviceObject = ((PDEVICE_EXTENSION) (DeviceObject->DeviceExtension))->NextDriverDeviceObject;
    if (!deviceObject) {
        return FALSE;
        }
    fastIoDispatch = deviceObject->DriverObject->FastIoDispatch;

    if (fastIoDispatch && fastIoDispatch->FastIoLock) {
        return (fastIoDispatch->FastIoLock)(
                    FileObject,
                    FileOffset,
                    Length,
                    ProcessId,
                    Key,
                    FailImmediately,
                    ExclusiveLock,
                    IoStatus,
                    deviceObject
                    );
        }
    else {
        return FALSE;
        }

}


BOOLEAN
FILEHIDEFastIoUnlockSingle(
    IN PFILE_OBJECT FileObject,
    IN PLARGE_INTEGER FileOffset,
    IN PLARGE_INTEGER Length,
    PEPROCESS ProcessId,
    ULONG Key,
    OUT PIO_STATUS_BLOCK IoStatus,
    IN PDEVICE_OBJECT DeviceObject
    )
{
    PDEVICE_OBJECT deviceObject;
    PFAST_IO_DISPATCH fastIoDispatch;

    deviceObject = ((PDEVICE_EXTENSION) (DeviceObject->DeviceExtension))->NextDriverDeviceObject;
    if (!deviceObject) {
        return FALSE;
        }
    fastIoDispatch = deviceObject->DriverObject->FastIoDispatch;

    if (fastIoDispatch && fastIoDispatch->FastIoUnlockSingle) {
        return (fastIoDispatch->FastIoUnlockSingle)(
                    FileObject,
                    FileOffset,
                    Length,
                    ProcessId,
                    Key,
                    IoStatus,
                    deviceObject
                    );
        }
    else {
        return FALSE;
        }

}

BOOLEAN
FILEHIDEFastIoUnlockAll(
    IN PFILE_OBJECT FileObject,
    PEPROCESS ProcessId,
    OUT PIO_STATUS_BLOCK IoStatus,
    IN PDEVICE_OBJECT DeviceObject
    )

{
    PDEVICE_OBJECT deviceObject;
    PFAST_IO_DISPATCH fastIoDispatch;

    deviceObject = ((PDEVICE_EXTENSION) (DeviceObject->DeviceExtension))->NextDriverDeviceObject;
    if (!deviceObject) {
        return FALSE;
        }
    fastIoDispatch = deviceObject->DriverObject->FastIoDispatch;

    if (fastIoDispatch && fastIoDispatch->FastIoUnlockAll) {
        return (fastIoDispatch->FastIoUnlockAll)(
                    FileObject,
                    ProcessId,
                    IoStatus,
                    deviceObject
                    );
        }
    else {
        return FALSE;
        }

}

BOOLEAN
FILEHIDEFastIoUnlockAllByKey(
    IN PFILE_OBJECT FileObject,
    PVOID ProcessId,
    ULONG Key,
    OUT PIO_STATUS_BLOCK IoStatus,
    IN PDEVICE_OBJECT DeviceObject
    )
{
    PDEVICE_OBJECT deviceObject;
    PFAST_IO_DISPATCH fastIoDispatch;

    deviceObject = ((PDEVICE_EXTENSION) (DeviceObject->DeviceExtension))->NextDriverDeviceObject;
    if (!deviceObject) {
        return FALSE;
        }
    fastIoDispatch = deviceObject->DriverObject->FastIoDispatch;

    if (fastIoDispatch && fastIoDispatch->FastIoUnlockAllByKey) {
        return (fastIoDispatch->FastIoUnlockAllByKey)(
                    FileObject,
                    ProcessId,
                    Key,
                    IoStatus,
                    deviceObject
                    );
        }
    else {
        return FALSE;
        }

}

BOOLEAN
FILEHIDEFastIoDeviceControl(
    IN PFILE_OBJECT FileObject,
    IN BOOLEAN Wait,
    IN PVOID InputBuffer OPTIONAL,
    IN ULONG InputBufferLength,
    OUT PVOID OutputBuffer OPTIONAL,
    IN ULONG OutputBufferLength,
    IN ULONG IoControlCode,
    OUT PIO_STATUS_BLOCK IoStatus,
    IN PDEVICE_OBJECT DeviceObject
    )
{
    PDEVICE_OBJECT deviceObject;
    PFAST_IO_DISPATCH fastIoDispatch;

    deviceObject = ((PDEVICE_EXTENSION) (DeviceObject->DeviceExtension))->NextDriverDeviceObject;
    if (!deviceObject) {
        return FALSE;
        }
    fastIoDispatch = deviceObject->DriverObject->FastIoDispatch;

    if (fastIoDispatch && fastIoDispatch->FastIoDeviceControl) {
        return (fastIoDispatch->FastIoDeviceControl)(
                    FileObject,
                    Wait,
                    InputBuffer,
                    InputBufferLength,
                    OutputBuffer,
                    OutputBufferLength,
                    IoControlCode,
                    IoStatus,
                    deviceObject
                    );
        }
    else {
        return FALSE;
        }

}

VOID
FILEHIDEFastIoDetachDevice(
    IN PDEVICE_OBJECT SourceDevice,
    IN PDEVICE_OBJECT TargetDevice
    )
{
    FsRtlEnterFileSystem();
    ExAcquireResourceExclusive( &FsLock, TRUE );
    IoDetachDevice( TargetDevice );
    IoDeleteDevice( SourceDevice );
    ExReleaseResource( &FsLock );
    FsRtlExitFileSystem();
}

BOOLEAN
FILEHIDEFastIoQueryNetworkOpenInfo(
    IN PFILE_OBJECT FileObject,
    IN BOOLEAN Wait,
    OUT PFILE_NETWORK_OPEN_INFORMATION Buffer,
    OUT PIO_STATUS_BLOCK IoStatus,
    IN PDEVICE_OBJECT DeviceObject
    )
{
    PDEVICE_OBJECT deviceObject;
    PFAST_IO_DISPATCH fastIoDispatch;

    deviceObject = ((PDEVICE_EXTENSION) (DeviceObject->DeviceExtension))->NextDriverDeviceObject;
    if (!deviceObject) {
        return FALSE;
        }
    fastIoDispatch = deviceObject->DriverObject->FastIoDispatch;

    if (fastIoDispatch &&
        fastIoDispatch->SizeOfFastIoDispatch > FIELD_OFFSET( FAST_IO_DISPATCH, FastIoQueryNetworkOpenInfo ) &&
        fastIoDispatch->FastIoQueryNetworkOpenInfo) {
        return (fastIoDispatch->FastIoQueryNetworkOpenInfo)(
                    FileObject,
                    Wait,
                    Buffer,
                    IoStatus,
                    deviceObject
                    );
        }
    else {
        return FALSE;
        }

}

BOOLEAN
FILEHIDEFastIoMdlRead(
    IN PFILE_OBJECT FileObject,
    IN PLARGE_INTEGER FileOffset,
    IN ULONG Length,
    IN ULONG LockKey,
    OUT PMDL *MdlChain,
    OUT PIO_STATUS_BLOCK IoStatus,
    IN PDEVICE_OBJECT DeviceObject
    )
{
    PDEVICE_OBJECT deviceObject;
    PFAST_IO_DISPATCH fastIoDispatch;

    deviceObject = ((PDEVICE_EXTENSION) (DeviceObject->DeviceExtension))->NextDriverDeviceObject;
    if (!deviceObject) {
        return FALSE;
        }
    fastIoDispatch = deviceObject->DriverObject->FastIoDispatch;

    if (fastIoDispatch &&
        fastIoDispatch->SizeOfFastIoDispatch > FIELD_OFFSET( FAST_IO_DISPATCH, MdlRead ) &&
        fastIoDispatch->MdlRead) {
        return (fastIoDispatch->MdlRead)(
                    FileObject,
                    FileOffset,
                    Length,
                    LockKey,
                    MdlChain,
                    IoStatus,
                    deviceObject
                    );
        }
    else {
        return FALSE;
        }

}

BOOLEAN
FILEHIDEFastIoMdlReadComplete(
    IN PFILE_OBJECT FileObject,
    IN PMDL MdlChain,
    IN PDEVICE_OBJECT DeviceObject
    )
{
    PDEVICE_OBJECT deviceObject;
    PFAST_IO_DISPATCH fastIoDispatch;

    deviceObject = ((PDEVICE_EXTENSION) (DeviceObject->DeviceExtension))->NextDriverDeviceObject;
    if (!deviceObject) {
        return FALSE;
        }
    fastIoDispatch = deviceObject->DriverObject->FastIoDispatch;

    if (fastIoDispatch &&
        fastIoDispatch->SizeOfFastIoDispatch > FIELD_OFFSET( FAST_IO_DISPATCH, MdlReadComplete ) &&
        fastIoDispatch->MdlReadComplete) {
        return (fastIoDispatch->MdlReadComplete)(
                    FileObject,
                    MdlChain,
                    deviceObject
                    );
        }

    return FALSE;
}

BOOLEAN
FILEHIDEFastIoPrepareMdlWrite(
    IN PFILE_OBJECT FileObject,
    IN PLARGE_INTEGER FileOffset,
    IN ULONG Length,
    IN ULONG LockKey,
    OUT PMDL *MdlChain,
    OUT PIO_STATUS_BLOCK IoStatus,
    IN PDEVICE_OBJECT DeviceObject
    )
{
    PDEVICE_OBJECT deviceObject;
    PFAST_IO_DISPATCH fastIoDispatch;

    deviceObject = ((PDEVICE_EXTENSION) (DeviceObject->DeviceExtension))->NextDriverDeviceObject;
    if (!deviceObject) {
        return FALSE;
        }
    fastIoDispatch = deviceObject->DriverObject->FastIoDispatch;

    if (fastIoDispatch &&
        fastIoDispatch->SizeOfFastIoDispatch > FIELD_OFFSET( FAST_IO_DISPATCH, PrepareMdlWrite ) &&
        fastIoDispatch->PrepareMdlWrite) {
        return (fastIoDispatch->PrepareMdlWrite)(
                    FileObject,
                    FileOffset,
                    Length,
                    LockKey,
                    MdlChain,
                    IoStatus,
                    deviceObject
                    );
        }
    else {
        return FALSE;
        }

}

BOOLEAN
FILEHIDEFastIoMdlWriteComplete(
    IN PFILE_OBJECT FileObject,
    IN PLARGE_INTEGER FileOffset,
    IN PMDL MdlChain,
    IN PDEVICE_OBJECT DeviceObject
    )
{
    PDEVICE_OBJECT deviceObject;
    PFAST_IO_DISPATCH fastIoDispatch;

    deviceObject = ((PDEVICE_EXTENSION) (DeviceObject->DeviceExtension))->NextDriverDeviceObject;
    if (!deviceObject) {
        return FALSE;
        }
    fastIoDispatch = deviceObject->DriverObject->FastIoDispatch;

    if (fastIoDispatch &&
        fastIoDispatch->SizeOfFastIoDispatch > FIELD_OFFSET( FAST_IO_DISPATCH, MdlWriteComplete ) &&
        fastIoDispatch->MdlWriteComplete) {
        return (fastIoDispatch->MdlWriteComplete)(
                    FileObject,
                    FileOffset,
                    MdlChain,
                    deviceObject
                    );
        }

    return FALSE;
}

BOOLEAN
FILEHIDEFastIoReadCompressed(
    IN PFILE_OBJECT FileObject,
    IN PLARGE_INTEGER FileOffset,
    IN ULONG Length,
    IN ULONG LockKey,
    OUT PVOID Buffer,
    OUT PMDL *MdlChain,
    OUT PIO_STATUS_BLOCK IoStatus,
    OUT struct _COMPRESSED_DATA_INFO *CompressedDataInfo,
    IN ULONG CompressedDataInfoLength,
    IN PDEVICE_OBJECT DeviceObject
    )
{
    PDEVICE_OBJECT deviceObject;
    PFAST_IO_DISPATCH fastIoDispatch;

    deviceObject = ((PDEVICE_EXTENSION) (DeviceObject->DeviceExtension))->NextDriverDeviceObject;
    if (!deviceObject) {
        return FALSE;
        }
    fastIoDispatch = deviceObject->DriverObject->FastIoDispatch;

    if (fastIoDispatch &&
        fastIoDispatch->SizeOfFastIoDispatch > FIELD_OFFSET( FAST_IO_DISPATCH, FastIoReadCompressed ) &&
        fastIoDispatch->FastIoReadCompressed) {
        return (fastIoDispatch->FastIoReadCompressed)(
                    FileObject,
                    FileOffset,
                    Length,
                    LockKey,
                    Buffer,
                    MdlChain,
                    IoStatus,
                    CompressedDataInfo,
                    CompressedDataInfoLength,
                    deviceObject
                    );
        }
    else {
        return FALSE;
        }

}

BOOLEAN
FILEHIDEFastIoWriteCompressed(
    IN PFILE_OBJECT FileObject,
    IN PLARGE_INTEGER FileOffset,
    IN ULONG Length,
    IN ULONG LockKey,
    IN PVOID Buffer,
    OUT PMDL *MdlChain,
    OUT PIO_STATUS_BLOCK IoStatus,
    IN struct _COMPRESSED_DATA_INFO *CompressedDataInfo,
    IN ULONG CompressedDataInfoLength,
    IN PDEVICE_OBJECT DeviceObject
    )
{
    PDEVICE_OBJECT deviceObject;
    PFAST_IO_DISPATCH fastIoDispatch;

    deviceObject = ((PDEVICE_EXTENSION) (DeviceObject->DeviceExtension))->NextDriverDeviceObject;
    if (!deviceObject) {
        return FALSE;
        }
    fastIoDispatch = deviceObject->DriverObject->FastIoDispatch;

    if (fastIoDispatch &&
        fastIoDispatch->SizeOfFastIoDispatch > FIELD_OFFSET( FAST_IO_DISPATCH, FastIoWriteCompressed ) &&
        fastIoDispatch->FastIoWriteCompressed) {
        return (fastIoDispatch->FastIoWriteCompressed)(
                    FileObject,
                    FileOffset,
                    Length,
                    LockKey,
                    Buffer,
                    MdlChain,
                    IoStatus,
                    CompressedDataInfo,
                    CompressedDataInfoLength,
                    deviceObject
                    );
        }
    else {
        return FALSE;
        }

}

BOOLEAN
FILEHIDEFastIoMdlReadCompleteCompressed(
    IN PFILE_OBJECT FileObject,
    IN PMDL MdlChain,
    IN PDEVICE_OBJECT DeviceObject
    )
{
    PDEVICE_OBJECT deviceObject;
    PFAST_IO_DISPATCH fastIoDispatch;

    deviceObject = ((PDEVICE_EXTENSION) (DeviceObject->DeviceExtension))->NextDriverDeviceObject;
    if (!deviceObject) {
        return FALSE;
        }
    fastIoDispatch = deviceObject->DriverObject->FastIoDispatch;

    if (fastIoDispatch &&
        fastIoDispatch->SizeOfFastIoDispatch > FIELD_OFFSET( FAST_IO_DISPATCH, MdlReadCompleteCompressed ) &&
        fastIoDispatch->MdlReadCompleteCompressed) {
        return (fastIoDispatch->MdlReadCompleteCompressed)(
                    FileObject,
                    MdlChain,
                    deviceObject
                    );
        }

    return FALSE;
}



BOOLEAN
FILEHIDEFastIoMdlWriteCompleteCompressed(
    IN PFILE_OBJECT FileObject,
    IN PLARGE_INTEGER FileOffset,
    IN PMDL MdlChain,
    IN PDEVICE_OBJECT DeviceObject
    )
{
    PDEVICE_OBJECT deviceObject;
    PFAST_IO_DISPATCH fastIoDispatch;

    deviceObject = ((PDEVICE_EXTENSION) (DeviceObject->DeviceExtension))->NextDriverDeviceObject;
    if (!deviceObject) {
        return FALSE;
        }
    fastIoDispatch = deviceObject->DriverObject->FastIoDispatch;

    if (fastIoDispatch &&
        fastIoDispatch->SizeOfFastIoDispatch > FIELD_OFFSET( FAST_IO_DISPATCH, MdlWriteCompleteCompressed ) &&
        fastIoDispatch->MdlWriteCompleteCompressed) {
        return (fastIoDispatch->MdlWriteCompleteCompressed)(
                    FileObject,
                    FileOffset,
                    MdlChain,
                    deviceObject
                    );
        }

    return FALSE;
}

BOOLEAN
FILEHIDEFastIoQueryOpen(
    IN PIRP Irp,
    OUT PFILE_NETWORK_OPEN_INFORMATION NetworkInformation,
    IN PDEVICE_OBJECT DeviceObject
    )
{
    PDEVICE_OBJECT deviceObject;
    PFAST_IO_DISPATCH fastIoDispatch;
    BOOLEAN result;

    deviceObject = ((PDEVICE_EXTENSION) (DeviceObject->DeviceExtension))->NextDriverDeviceObject;
    if (!deviceObject) {
        return FALSE;
        }
    fastIoDispatch = deviceObject->DriverObject->FastIoDispatch;

    if (fastIoDispatch &&
        fastIoDispatch->SizeOfFastIoDispatch > FIELD_OFFSET( FAST_IO_DISPATCH, FastIoQueryOpen ) &&
        fastIoDispatch->FastIoQueryOpen) {
        PIO_STACK_LOCATION irpSp = IoGetCurrentIrpStackLocation( Irp );

        irpSp->DeviceObject = deviceObject;

        result = (fastIoDispatch->FastIoQueryOpen)(
                    Irp,
                    NetworkInformation,
                    deviceObject
                    );
        if (!result) {
            irpSp->DeviceObject = DeviceObject;
            }
        return result;
        }
    else {
        return FALSE;
        }

}
