#include <ntifs.H>

#ifndef _FILEHIDDEN_H
#define _FILEHIDDEN_H

NTSTATUS InitializeHiddenFileList();
NTSTATUS HiddenFilesRoutine( PDEVICE_OBJECT pDevObj, PIRP pIrp );
ULONG IsExistHiddenFileList( WCHAR *pwFilename );
ULONG IsExistCurrentEntryForHiddenFile( PFILE_BOTH_DIR_INFORMATION pInfo, PWCHAR pwPrefixName );
ULONG HideFiles( PWCHAR pwPrefixName, PFILE_BOTH_DIR_INFORMATION pInfo, ULONG dwInfoSize );
ULONG GetRealSize( PFILE_BOTH_DIR_INFORMATION pInfo );
ULONG IsExistHiddenProcess(WCHAR *pwFilename);

#endif //_FILEHIDDEN_H
