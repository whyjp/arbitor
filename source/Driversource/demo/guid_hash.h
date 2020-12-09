#ifndef _GUID_HASH_H
#define _GUID_HASH_H
#include "..\\..\\inc\F_IFACE.H"
///////////////////////////////////////////////////////////////
// typdef¹®..
///////////////////////////////////////////////////////////////
typedef struct tagGUID_HASH_ENTRY
{
	WCHAR wFileName[MAXHIDDENFILENAMESIZE];
	WCHAR wGuid[GUIDCNT+1];
	struct tagGUID_HASH_ENTRY* pNext;
} GUID_HASH_ENTRY, *PGUID_HASH_ENTRY;

///////////////////////////////////////////////////////////////
// define¹®..
///////////////////////////////////////////////////////////////
#define NUM_GUID_HASH 20
//#define GUIDHASHOBJECT(_FileName) (((ULONG)_FileName)>>5)%NUM_GUID_HASH




void GUIDInsertHashEntry(PWCHAR pFileName,PWCHAR pwGuid);
	
BOOLEAN GUIDIsExistInHashTable(PWCHAR pwFileName, WCHAR** ppwGuid);
		
void GUIDFreeHashEntry(PWCHAR pwFileName);

#endif //_GUID_HASH_H
