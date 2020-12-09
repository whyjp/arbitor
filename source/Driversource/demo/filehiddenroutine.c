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
		//배열의 각 자리마다 파일이름 사이즈만큼 공간을 할당한다
		if( !g_HiddenFileList[ i ] )
			//할당이 실패하면 실패를 리턴하는듯
			return STATUS_UNSUCCESSFUL;
		RtlZeroMemory( g_HiddenFileList[ i ], MAXHIDDENFILENAMESIZE * sizeof(WCHAR) );
		//할당 된 메모리에 제로메모리해서 초기화
	}
	for( i = 0 ; i < MAXHIDDENFILEENTRIES ; i ++ )
	{
		g_OnlyHiddenFileList[ i ] = (WCHAR *)ExAllocatePool( NonPagedPool, MAXHIDDENFILENAMESIZE * sizeof(WCHAR) );
		//배열의 각 자리마다 파일이름 사이즈만큼 공간을 할당한다
		if( !g_OnlyHiddenFileList[ i ] )
			//할당이 실패하면 실패를 리턴하는듯
			return STATUS_UNSUCCESSFUL;
		RtlZeroMemory( g_OnlyHiddenFileList[ i ], MAXHIDDENFILENAMESIZE * sizeof(WCHAR) );
		//할당 된 메모리에 제로메모리해서 초기화
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
		//총파일갯수만큼 돌린다
		if( !g_HiddenFileList[ i ] )
			//배열의 i 번째칸에 뭔가없다면 다음i+
			continue;
		if( _wcsicmp( g_HiddenFileList[ i ], pwFilename ) ){
			//그파일이 인자로들어온파일이 아니다 그럼 리스트에 있는파일인것따라서 if문을 부정
			continue;
		}else{
			DbgPrint("%s  input file-> %s \n",g_HiddenFileList[ i ],pwFilename);
		}

		return TRUE;
	}
	return FALSE;
	//0->숨길 대상의 파일이 아니다.
	//!0->숨길 대상의 파일이다.
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

		//배열 안에 무언가 이름이 있으면 
		//이름을 경로명 앞까지 나눈다...
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
			//그파일이 인자로들어온파일이 아니다 그럼 리스트에 있는파일인것따라서 if문을 부정
			continue;
		}else{
			DbgPrint("%s  input file-> %s \n",g_HiddenFileList[ i ],pwFilename);
		}
		ExFreePool(FName);
		return TRUE;
		
	}
	ExFreePool(FName);
	return FALSE;
	//0->숨길 대상의 파일이 아니다.
	//!0->숨길 대상의 파일이다.
}
	
ULONG IsExistOnlyHiddenFileList( WCHAR *pwFilename )
{
	int i;

	for( i = 0 ; i < MAXHIDDENFILEENTRIES ; i ++ )
	{
		//총파일갯수만큼 돌린다
		if( !g_OnlyHiddenFileList[ i ] )
			//배열의 i 번째칸에 뭔가없다면 다음i+
			continue;
		if( _wcsicmp( g_OnlyHiddenFileList[ i ], pwFilename ) ){
			//그파일이 인자로들어온파일이 아니다 그럼 리스트에 있는파일인것따라서 if문을 부정
			continue;
		}else{
			DbgPrint("%s  input file-> %s \n",g_OnlyHiddenFileList[ i ],pwFilename);
		}

		return TRUE;
	}
	return FALSE;
	//0->숨길 대상의 파일이 아니다.
	//!0->숨길 대상의 파일이다.
}

ULONG IsExistCurrentEntryForHiddenFile( PFILE_BOTH_DIR_INFORMATION pInfo, PWCHAR pwPrefixName )
{
	//pInfo : IRP_MJDIRECTORY_CONTROL 에서 전달되는 디렉토리 엔트리 정보를 보관하는 메모리. 현재 엔트리만 사용한다
	//pwPrefixName : FileObject의 풀패스 이름. 이곳에서는 디렉토리 풀패스이름이 됨 파일이름제외.
	WCHAR * pdwTempPath;
	ULONG bRet;

	pdwTempPath = (WCHAR *)ExAllocatePool( NonPagedPool, MAXHIDDENFILENAMESIZE * sizeof(WCHAR) );
	//패스를위한 캐릭터형 포인터에 총 파일사이즈가능한만큼 할당
	RtlZeroMemory( pdwTempPath, MAXHIDDENFILENAMESIZE * sizeof(WCHAR));
	//그만큼 제로메모리 초기화
	
	wcscpy( pdwTempPath, pwPrefixName );
	//일단 스트링을 와이드니까 wcscpy카피(여기서 pwPrefixName 은 경로명만있음)
	if( pdwTempPath[ wcslen(pdwTempPath) - 1] != L'\\' )
		wcscat( pdwTempPath, L"\\" );
	//만약 경로끝에 \가 없으면 붙여주자

	memcpy( pdwTempPath + wcslen(pdwTempPath), pInfo->FileName, pInfo->FileNameLength );
	//경로 파일명끝에 파일이름을 더해준다.

	bRet = IsExistHiddenFileList(pdwTempPath);
	//리스트에 있는건지 확인한다


	if(bRet==0){
	bRet = IsExistOnlyHiddenFileList(pdwTempPath);
	}

	ExFreePool( pdwTempPath );
	//할당한것을 날린다.
	return bRet;
	//0->숨길 대상의 파일이 아니다.
	//!0->숨길 대상의 파일이다.
}

ULONG HideFiles( PWCHAR pwPrefixName, PFILE_BOTH_DIR_INFORMATION pInfo, ULONG dwInfoSize )
{
	//pwPrefixName: FileObject의 풀패스 이름 이곳에서는디렉토리 풀패스이름 매스만
	//pInfo : IRP_MJDIRECTORY_CONTROL 에서 전달되는 디렉토리 엔트리 정보를 보관하는 메모리.
	//dwInfoSize : pInfo 정보의 크기
	PFILE_BOTH_DIR_INFORMATION pBackupInfo, pBackupInfo_for_Delete, pBackupInfo_for_LastEntry;
	PFILE_BOTH_DIR_INFORMATION pBackup_pInfo;
	
	ULONG bRet;
	ULONG dwCopySize=0;
	ULONG dwOriginalInfoLastEntrySize;
	//진짜pInfo정보의 사이즈를 담는곳

	if( g_HiddenFileAction == FALSE )
		//파일을숨겨야하나?
		return dwInfoSize;
	
	dwOriginalInfoLastEntrySize = dwInfoSize;
	pBackup_pInfo = pInfo;
	//사이즈와 pInfo 를 일단 백업해둔다

		
	pBackupInfo = (PFILE_BOTH_DIR_INFORMATION)ExAllocatePool( NonPagedPool, dwInfoSize );
	//백업인포에 사이즈만큼 할당
	if( !pBackupInfo )
	{
		return STATUS_SUCCESS;;
	}
		
	pBackupInfo_for_Delete = pBackupInfo;
	pBackupInfo_for_LastEntry = (PFILE_BOTH_DIR_INFORMATION)0;
	
	RtlZeroMemory( pBackupInfo, dwInfoSize );

	while( pInfo->NextEntryOffset )
	{
		// 마지막엔트리가 아니면..
		dwOriginalInfoLastEntrySize -= pInfo->NextEntryOffset;
		
		bRet = IsExistCurrentEntryForHiddenFile( pInfo, pwPrefixName );
		if( bRet == FALSE )
		{
			// 복사해도 좋다
			memcpy( pBackupInfo, pInfo, pInfo->NextEntryOffset );
			dwCopySize += pInfo->NextEntryOffset;
			pBackupInfo_for_LastEntry = pBackupInfo;
			pBackupInfo = (PFILE_BOTH_DIR_INFORMATION)((PCHAR)pBackupInfo + (ULONG)(pBackupInfo->NextEntryOffset));
			pInfo = (PFILE_BOTH_DIR_INFORMATION)((PCHAR)pInfo + (ULONG)(pInfo->NextEntryOffset));
			continue;
		}

		// 발견되면 이 엔트리는 복사하면 안된다
		pInfo = (PFILE_BOTH_DIR_INFORMATION)((PCHAR)pInfo + (ULONG)(pInfo->NextEntryOffset));
		continue;
	}

	// 마지막엔트리처리
	bRet = IsExistCurrentEntryForHiddenFile( pInfo, pwPrefixName );
	if( bRet == FALSE )
	{
		// 복사해도 좋다
		memcpy( pBackupInfo, pInfo,  dwOriginalInfoLastEntrySize );
		dwCopySize += dwOriginalInfoLastEntrySize;
	}
	else
	{
		// 발견되면 이 엔트리는 복사하면 안된다
		// 이전엔트리의 연결점처리
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
	//현재 IRP 의 스택로케이션을 얻어온다

    ulIoControlCode = pCurIrpStack->Parameters.DeviceIoControl.IoControlCode;
	//IO콘트롤 코드를 담는다
    
    pInputBuffer = pIrp->AssociatedIrp.SystemBuffer;
	pOutputBuffer = pIrp->AssociatedIrp.SystemBuffer;
    ulInputBufferLength = pCurIrpStack->Parameters.DeviceIoControl.InputBufferLength;
    ulOutputBufferLength = pCurIrpStack->Parameters.DeviceIoControl.OutputBufferLength;
	//인풋 아웃풋 버퍼를 담아두고 사이즈도 담아준다

	ntStatus = STATUS_UNSUCCESSFUL;
	//실패로 초기화해둔상태
	Information = 0;
	
	switch(ulIoControlCode) 
	{
		case IOCTL_HIDDEN_FILES:
			//숨김파일일경우의처리
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
			//들어오는나가는포인터를 각 포인터에담는다.

			for( i = 0 ; i < MAXHIDDENFILEENTRIES ; i ++ )
			{
				if( g_HiddenFileList[ i ][0] )
					continue;
				//해당칸에뭔가있으면다음칸으로~~
				memcpy( g_HiddenFileList[ i ], &pEntry->Filename[0], MAXHIDDENFILENAMESIZE * sizeof(WCHAR) );
				//빈칸에파일이름을넣는다!!
				break;				
			}
			if( i >= MAXHIDDENFILEENTRIES )
			{
				break;
			}
			pReturnHandle->Handle = i;
			//몇번째꺼에넣었는지 아웃풋버펑넣어준다
			ntStatus = STATUS_SUCCESS;
			Information = sizeof(HIDDEN_FILE_HANDLE);
			//정보에 숨김파일핸들사이즈를 넣어준다
		}
			break;
		case IOCTL_DEL_HIDDEN_FILE:
		{
			int i;
			PDEL_HIDDEN_FILE pEntry;
			
			pEntry = (PDEL_HIDDEN_FILE)pInputBuffer;
			//인풋버퍼로 들어온걸 엔트리로
			if( (int)pEntry->Handle.Handle >= MAXHIDDENFILEENTRIES )
				break;

			RtlZeroMemory( g_HiddenFileList[ pEntry->Handle.Handle ], MAXHIDDENFILENAMESIZE * sizeof(WCHAR) );
			//날려준다초기화~
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
			//갯수만큼다 날려준다
		}
				
			break;
		case IOCTL_ADD_GUID:
		{
			PADD_GUID_FNAME pEntry;
			//pEntry=(PADD_GUID_FNAME)HjAllocatePool( NonPagedPool, sizeof(ADD_GUID_FNAME));

			pEntry = (PADD_GUID_FNAME)pInputBuffer;
			//인풋버퍼로 들어온걸 엔트리로

			GUIDInsertHashEntry(pEntry->Filename,pEntry->Guid);
			//ExFreePool(pEntry);
			ntStatus = STATUS_SUCCESS;
		}
			break;
		case IOCTL_DEL_GUID:
		{
			PDEL_GUID_FNAME pEntry;

			pEntry = (PDEL_GUID_FNAME)pInputBuffer;
			//인풋버퍼로 들어온걸 엔트리로
			
			GUIDFreeHashEntry(pEntry->Filename);

			ntStatus = STATUS_SUCCESS;
		}
			break;
	}
	pIrp->IoStatus.Status = ntStatus;
	pIrp->IoStatus.Information = Information;
	//IRP에 상태와 정보를 최종으로넣는다 그리고 다음으로넘긴다~
	IoCompleteRequest( pIrp, IO_NO_INCREMENT );
	return ntStatus;
}

ULONG GetRealSize( PFILE_BOTH_DIR_INFORMATION pInfo )
{
	ULONG dwCopySize=0;

	while( pInfo->NextEntryOffset )
	{
		// 마지막엔트리가 아니면..
		dwCopySize += pInfo->NextEntryOffset;
		pInfo = (PFILE_BOTH_DIR_INFORMATION)((PCHAR)pInfo + (ULONG)(pInfo->NextEntryOffset));
		continue;
	}

	dwCopySize += (sizeof( FILE_BOTH_DIR_INFORMATION ) - 2 + pInfo->FileNameLength);
	return dwCopySize;
}	
	
