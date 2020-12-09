#include <ntifs.h>
#include "main.h"

#ifndef _RECOGNIZER_H_
#define _RECOGNIZER_H_

NTSTATUS
FILEHIDEMountCompletion(
	IN PDEVICE_OBJECT DeviceObject,
	IN PIRP Irp,
	IN PVOID Context
	);

NTSTATUS
FILEHIDELoadFsCompletion(
	IN PDEVICE_OBJECT DeviceObject,
	IN PIRP Irp,
	IN PVOID Context
	);

NTSTATUS
FILEHIDEFsControl(
	IN PDEVICE_OBJECT DeviceObject,
	IN PIRP Irp
	);

VOID
FILEHIDEFsNotification(
	IN PDEVICE_OBJECT DeviceObject,
	IN BOOLEAN FsActive
	);

void FILEHIDERecognizer();

#endif //_RECOGNIZER_H_
