#ifndef _HASH_H
#define _HASH_H

///////////////////////////////////////////////////////////////
// typdef¹®..
///////////////////////////////////////////////////////////////
typedef struct tagHASH_ENTRY
{
	PFILE_OBJECT pFileObj;
	PWCHAR pwFileName;
	struct tagHASH_ENTRY* pNext;
} HASH_ENTRY, *PHASH_ENTRY;

///////////////////////////////////////////////////////////////
// define¹®..
///////////////////////////////////////////////////////////////
#define NUM_HASH 1000
#define HASHOBJECT(_fileobject) (((ULONG)_fileobject)>>5)%NUM_HASH

void fInsertHashEntry(PFILE_OBJECT pFileObj, PWCHAR pFileName);
	
BOOLEAN fIsExistInHashTable(PFILE_OBJECT pFileObj, WCHAR** ppwFileName);
		
void fFreeHashEntry(PFILE_OBJECT pFileObj);

#endif //_HASH_H
