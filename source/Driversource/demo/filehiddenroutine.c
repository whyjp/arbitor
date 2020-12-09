#include <ntifs.H>
#include <string.h>
#include "..\\..\\inc\F_IFACE.H"
#include "filehiddenroutine.h"
#include "guid_hash.h"
#include "utility.h"

ULONG g_HiddenFileAction;

WCHAR * g_HiddenFileList[MAXHIDDENFILEENTRIES+1];
WCHAR * g_OnlyHiddenFileList[MAXHIDDENFILEENTRIES+1];

NTSTATUS InitializeHiddenFileList()
{
	int i;
	for( i = 0 ; i < MAXHIDDENFILEENTRIES ; i ++ )
	{
		g_HiddenFileList[ i ] = (WCHAR *)ExAllocatePool( NonPagedPool, MAXHIDDENFILENAMESIZE * sizeof(WCHAR) );
		//�迭�� �� �ڸ����� �����̸� �����ŭ ������ �Ҵ��Ѵ�
		if( !g_HiddenFileList[ i ] )
			//�Ҵ��� �����ϸ� ���и� �����ϴµ�
			return STATUS_UNSUCCESSFUL;
		RtlZeroMemory( g_HiddenFileList[ i ], MAXHIDDENFILENAMESIZE * sizeof(WCHAR) );
		//�Ҵ� �� �޸𸮿� ���θ޸��ؼ� �ʱ�ȭ
	}
	for( i = 0 ; i < MAXHIDDENFILEENTRIES ; i ++ )
	{
		g_OnlyHiddenFileList[ i ] = (WCHAR *)ExAllocatePool( NonPagedPool, MAXHIDDENFILENAMESIZE * sizeof(WCHAR) );
		//�迭�� �� �ڸ����� �����̸� �����ŭ ������ �Ҵ��Ѵ�
		if( !g_OnlyHiddenFileList[ i ] )
			//�Ҵ��� �����ϸ� ���и� �����ϴµ�
			return STATUS_UNSUCCESSFUL;
		RtlZeroMemory( g_OnlyHiddenFileList[ i ], MAXHIDDENFILENAMESIZE * sizeof(WCHAR) );
		//�Ҵ� �� �޸𸮿� ���θ޸��ؼ� �ʱ�ȭ
	}
	wcscpy(g_OnlyHiddenFileList[0],L"c:\\hFList.abt");
	wcscpy(g_OnlyHiddenFileList[1],L"c:\\hidden");
	
	return STATUS_SUCCESS;
}

ULONG IsExistHiddenFileList( WCHAR *pwFilename )
{
	int i;

	for( i = 0 ; i < MAXHIDDENFILEENTRIES ; i ++ )
	{
		//�����ϰ�����ŭ ������
		if( !g_HiddenFileList[ i ] )
			//�迭�� i ��°ĭ�� �������ٸ� ����i+
			continue;
		if( _wcsicmp( g_HiddenFileList[ i ], pwFilename ) ){
			//�������� ���ڷε��������� �ƴϴ� �׷� ����Ʈ�� �ִ������ΰ͵��� if���� ����
			continue;
		}else{
			DbgPrint("%s  input file-> %s \n",g_HiddenFileList[ i ],pwFilename);
		}

		return TRUE;
	}
	return FALSE;
	//0->���� ����� ������ �ƴϴ�.
	//!0->���� ����� �����̴�.
}


ULONG IsExistHiddenProcess(WCHAR *pwFilename)
{
	WCHAR *Name;
	WCHAR *FName;
	WCHAR *HName;
	unsigned short tempa=0x5c;

	int i;
	int j;
	int total;
	int tint;
	int tint2;

	FName = (WCHAR *)HjAllocatePool( NonPagedPool, MAXHIDDENFILENAMESIZE * sizeof(WCHAR) );
	HName = (WCHAR *)HjAllocatePool( NonPagedPool, MAXHIDDENFILENAMESIZE * sizeof(WCHAR) );
	
	for (i=0; i<MAXHIDDENFILEENTRIES; i++)
	{
		if( !g_HiddenFileList[ i ][0] )
			continue;

		//�迭 �ȿ� ���� �̸��� ������ 
		//�̸��� ��θ� �ձ��� ������...
		total = wcslen(g_HiddenFileList[i]);
		//Name = wcschr( g_HiddenFileList[i], (int)L"\\");
		
		for (j = total; j > 0; j--)
		{
			if ( g_HiddenFileList[i][j] == tempa )
			{
				break;
			}
				
		}
		 
		Name = g_HiddenFileList[i] + j+1;
		tint = wcslen(Name);
		tint2 = strlen(ORIGINAL_FILENAME)-1;
		*(Name+tint-tint2)=(WCHAR)"\0";
		
		if( wcsncmp(Name,pwFilename,tint-tint2) ){
			//�������� ���ڷε��������� �ƴϴ� �׷� ����Ʈ�� �ִ������ΰ͵��� if���� ����
			continue;
		}else{
			DbgPrint("%s  input file-> %s \n",g_HiddenFileList[ i ],pwFilename);
		}
		ExFreePool(FName);
		return TRUE;
		
	}
	ExFreePool(FName);
	return FALSE;
	//0->���� ����� ������ �ƴϴ�.
	//!0->���� ����� �����̴�.
}
	
ULONG IsExistOnlyHiddenFileList( WCHAR *pwFilename )
{
	int i;

	for( i = 0 ; i < MAXHIDDENFILEENTRIES ; i ++ )
	{
		//�����ϰ�����ŭ ������
		if( !g_OnlyHiddenFileList[ i ] )
			//�迭�� i ��°ĭ�� �������ٸ� ����i+
			continue;
		if( _wcsicmp( g_OnlyHiddenFileList[ i ], pwFilename ) ){
			//�������� ���ڷε��������� �ƴϴ� �׷� ����Ʈ�� �ִ������ΰ͵��� if���� ����
			continue;
		}else{
			DbgPrint("%s  input file-> %s \n",g_OnlyHiddenFileList[ i ],pwFilename);
		}

		return TRUE;
	}
	return FALSE;
	//0->���� ����� ������ �ƴϴ�.
	//!0->���� ����� �����̴�.
}

ULONG IsExistCurrentEntryForHiddenFile( PFILE_BOTH_DIR_INFORMATION pInfo, PWCHAR pwPrefixName )
{
	//pInfo : IRP_MJDIRECTORY_CONTROL ���� ���޵Ǵ� ���丮 ��Ʈ�� ������ �����ϴ� �޸�. ���� ��Ʈ���� ����Ѵ�
	//pwPrefixName : FileObject�� Ǯ�н� �̸�. �̰������� ���丮 Ǯ�н��̸��� �� �����̸�����.
	WCHAR * pdwTempPath;
	ULONG bRet;

	pdwTempPath = (WCHAR *)ExAllocatePool( NonPagedPool, MAXHIDDENFILENAMESIZE * sizeof(WCHAR) );
	//�н������� ĳ������ �����Ϳ� �� ���ϻ�������Ѹ�ŭ �Ҵ�
	RtlZeroMemory( pdwTempPath, MAXHIDDENFILENAMESIZE * sizeof(WCHAR));
	//�׸�ŭ ���θ޸� �ʱ�ȭ
	
	wcscpy( pdwTempPath, pwPrefixName );
	//�ϴ� ��Ʈ���� ���̵�ϱ� wcscpyī��(���⼭ pwPrefixName �� ��θ�����)
	if( pdwTempPath[ wcslen(pdwTempPath) - 1] != L'\\' )
		wcscat( pdwTempPath, L"\\" );
	//���� ��γ��� \�� ������ �ٿ�����

	memcpy( pdwTempPath + wcslen(pdwTempPath), pInfo->FileName, pInfo->FileNameLength );
	//��� ���ϸ��� �����̸��� �����ش�.

	bRet = IsExistHiddenFileList(pdwTempPath);
	//����Ʈ�� �ִ°��� Ȯ���Ѵ�


	if(bRet==0){
	bRet = IsExistOnlyHiddenFileList(pdwTempPath);
	}

	ExFreePool( pdwTempPath );
	//�Ҵ��Ѱ��� ������.
	return bRet;
	//0->���� ����� ������ �ƴϴ�.
	//!0->���� ����� �����̴�.
}

ULONG HideFiles( PWCHAR pwPrefixName, PFILE_BOTH_DIR_INFORMATION pInfo, ULONG dwInfoSize )
{
	//pwPrefixName: FileObject�� Ǯ�н� �̸� �̰������µ��丮 Ǯ�н��̸� �Ž���
	//pInfo : IRP_MJDIRECTORY_CONTROL ���� ���޵Ǵ� ���丮 ��Ʈ�� ������ �����ϴ� �޸�.
	//dwInfoSize : pInfo ������ ũ��
	PFILE_BOTH_DIR_INFORMATION pBackupInfo, pBackupInfo_for_Delete, pBackupInfo_for_LastEntry;
	PFILE_BOTH_DIR_INFORMATION pBackup_pInfo;
	
	ULONG bRet;
	ULONG dwCopySize=0;
	ULONG dwOriginalInfoLastEntrySize;
	//��¥pInfo������ ����� ��°�

	if( g_HiddenFileAction == FALSE )
		//���������ܾ��ϳ�?
		return dwInfoSize;
	
	dwOriginalInfoLastEntrySize = dwInfoSize;
	pBackup_pInfo = pInfo;
	//������� pInfo �� �ϴ� ����صд�

		
	pBackupInfo = (PFILE_BOTH_DIR_INFORMATION)ExAllocatePool( NonPagedPool, dwInfoSize );
	//��������� �����ŭ �Ҵ�
	if( !pBackupInfo )
	{
		return STATUS_SUCCESS;;
	}
		
	pBackupInfo_for_Delete = pBackupInfo;
	pBackupInfo_for_LastEntry = (PFILE_BOTH_DIR_INFORMATION)0;
	
	RtlZeroMemory( pBackupInfo, dwInfoSize );

	while( pInfo->NextEntryOffset )
	{
		// ��������Ʈ���� �ƴϸ�..
		dwOriginalInfoLastEntrySize -= pInfo->NextEntryOffset;
		
		bRet = IsExistCurrentEntryForHiddenFile( pInfo, pwPrefixName );
		if( bRet == FALSE )
		{
			// �����ص� ����
			memcpy( pBackupInfo, pInfo, pInfo->NextEntryOffset );
			dwCopySize += pInfo->NextEntryOffset;
			pBackupInfo_for_LastEntry = pBackupInfo;
			pBackupInfo = (PFILE_BOTH_DIR_INFORMATION)((PCHAR)pBackupInfo + (ULONG)(pBackupInfo->NextEntryOffset));
			pInfo = (PFILE_BOTH_DIR_INFORMATION)((PCHAR)pInfo + (ULONG)(pInfo->NextEntryOffset));
			continue;
		}

		// �߰ߵǸ� �� ��Ʈ���� �����ϸ� �ȵȴ�
		pInfo = (PFILE_BOTH_DIR_INFORMATION)((PCHAR)pInfo + (ULONG)(pInfo->NextEntryOffset));
		continue;
	}

	// ��������Ʈ��ó��
	bRet = IsExistCurrentEntryForHiddenFile( pInfo, pwPrefixName );
	if( bRet == FALSE )
	{
		// �����ص� ����
		memcpy( pBackupInfo, pInfo,  dwOriginalInfoLastEntrySize );
		dwCopySize += dwOriginalInfoLastEntrySize;
	}
	else
	{
		// �߰ߵǸ� �� ��Ʈ���� �����ϸ� �ȵȴ�
		// ������Ʈ���� ������ó��
		if( pBackupInfo_for_LastEntry )
			pBackupInfo_for_LastEntry->NextEntryOffset = 0;
	}	

	pBackupInfo = pBackupInfo_for_Delete;
		
	if( dwInfoSize != dwCopySize )
	{
		RtlZeroMemory( pBackup_pInfo, dwInfoSize );
		memcpy( pBackup_pInfo, pBackupInfo, dwCopySize );
	}

	ExFreePool( pBackupInfo );
	return dwCopySize;
}	

NTSTATUS HiddenFilesRoutine( PDEVICE_OBJECT pDevObj, PIRP pIrp )
{
	PIO_STACK_LOCATION pCurIrpStack;
	NTSTATUS ntStatus;
	ULONG Information;
	ULONG ulIoControlCode;
	PVOID pInputBuffer, pOutputBuffer;
	ULONG ulInputBufferLength, ulOutputBufferLength;
	
	pIrp->IoStatus.Information = 0;
	
	pCurIrpStack = IoGetCurrentIrpStackLocation(pIrp);
	//���� IRP �� ���÷����̼��� ���´�

    ulIoControlCode = pCurIrpStack->Parameters.DeviceIoControl.IoControlCode;
	//IO��Ʈ�� �ڵ带 ��´�
    
    pInputBuffer = pIrp->AssociatedIrp.SystemBuffer;
	pOutputBuffer = pIrp->AssociatedIrp.SystemBuffer;
    ulInputBufferLength = pCurIrpStack->Parameters.DeviceIoControl.InputBufferLength;
    ulOutputBufferLength = pCurIrpStack->Parameters.DeviceIoControl.OutputBufferLength;
	//��ǲ �ƿ�ǲ ���۸� ��Ƶΰ� ����� ����ش�

	ntStatus = STATUS_UNSUCCESSFUL;
	//���з� �ʱ�ȭ�صл���
	Information = 0;
	
	switch(ulIoControlCode) 
	{
		case IOCTL_HIDDEN_FILES:
			//���������ϰ����ó��
			g_HiddenFileAction = TRUE;
			ntStatus = STATUS_SUCCESS;
			break;
		case IOCTL_SHOW_FILES:
			g_HiddenFileAction = FALSE;
			ntStatus = STATUS_SUCCESS;
			break;
		case IOCTL_ADD_HIDDEN_FILE:
		{
			int i;
			PADD_HIDDEN_FILE pEntry;
			PHIDDEN_FILE_HANDLE pReturnHandle;
			
			pEntry = (PADD_HIDDEN_FILE)pInputBuffer;
			pReturnHandle = (PHIDDEN_FILE_HANDLE)pOutputBuffer;
			//�����³����������͸� �� �����Ϳ���´�.

			for( i = 0 ; i < MAXHIDDENFILEENTRIES ; i ++ )
			{
				if( g_HiddenFileList[ i ][0] )
					continue;
				//�ش�ĭ���������������ĭ����~~
				memcpy( g_HiddenFileList[ i ], &pEntry->Filename[0], MAXHIDDENFILENAMESIZE * sizeof(WCHAR) );
				//��ĭ�������̸����ִ´�!!
				break;				
			}
			if( i >= MAXHIDDENFILEENTRIES )
			{
				break;
			}
			pReturnHandle->Handle = i;
			//���°�����־����� �ƿ�ǲ����־��ش�
			ntStatus = STATUS_SUCCESS;
			Information = sizeof(HIDDEN_FILE_HANDLE);
			//������ ���������ڵ����� �־��ش�
		}
			break;
		case IOCTL_DEL_HIDDEN_FILE:
		{
			int i;
			PDEL_HIDDEN_FILE pEntry;
			
			pEntry = (PDEL_HIDDEN_FILE)pInputBuffer;
			//��ǲ���۷� ���°� ��Ʈ����
			if( (int)pEntry->Handle.Handle >= MAXHIDDENFILEENTRIES )
				break;

			RtlZeroMemory( g_HiddenFileList[ pEntry->Handle.Handle ], MAXHIDDENFILENAMESIZE * sizeof(WCHAR) );
			//�����ش��ʱ�ȭ~
			ntStatus = STATUS_SUCCESS;
		}
			break;
		case IOCTL_ALL_RESET_HIDDEN_FILES:
		{
			int i;
			for( i = 0 ; i < MAXHIDDENFILEENTRIES ; i ++ )
			{
				RtlZeroMemory( g_HiddenFileList[ i ], MAXHIDDENFILENAMESIZE * sizeof(WCHAR) );
			}
			//������ŭ�� �����ش�
		}
				
			break;
		case IOCTL_ADD_GUID:
		{
			PADD_GUID_FNAME pEntry;
			//pEntry=(PADD_GUID_FNAME)HjAllocatePool( NonPagedPool, sizeof(ADD_GUID_FNAME));

			pEntry = (PADD_GUID_FNAME)pInputBuffer;
			//��ǲ���۷� ���°� ��Ʈ����

			GUIDInsertHashEntry(pEntry->Filename,pEntry->Guid);
			//ExFreePool(pEntry);
			ntStatus = STATUS_SUCCESS;
		}
			break;
		case IOCTL_DEL_GUID:
		{
			PDEL_GUID_FNAME pEntry;

			pEntry = (PDEL_GUID_FNAME)pInputBuffer;
			//��ǲ���۷� ���°� ��Ʈ����
			
			GUIDFreeHashEntry(pEntry->Filename);

			ntStatus = STATUS_SUCCESS;
		}
			break;
	}
	pIrp->IoStatus.Status = ntStatus;
	pIrp->IoStatus.Information = Information;
	//IRP�� ���¿� ������ �������γִ´� �׸��� �������γѱ��~
	IoCompleteRequest( pIrp, IO_NO_INCREMENT );
	return ntStatus;
}

ULONG GetRealSize( PFILE_BOTH_DIR_INFORMATION pInfo )
{
	ULONG dwCopySize=0;

	while( pInfo->NextEntryOffset )
	{
		// ��������Ʈ���� �ƴϸ�..
		dwCopySize += pInfo->NextEntryOffset;
		pInfo = (PFILE_BOTH_DIR_INFORMATION)((PCHAR)pInfo + (ULONG)(pInfo->NextEntryOffset));
		continue;
	}

	dwCopySize += (sizeof( FILE_BOTH_DIR_INFORMATION ) - 2 + pInfo->FileNameLength);
	return dwCopySize;
}	
	
