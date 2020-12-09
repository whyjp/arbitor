#include <ntifs.h>
#include "main.h"
#include "guid_hash.h"
#include "utility.h"

ERESOURCE LockGUIDHash;
PGUID_HASH_ENTRY	GUIDHashTable[ NUM_GUID_HASH ] = { NULL, NULL, NULL };
PGUID_HASH_ENTRY FreeGUIDHashList = NULL;

unsigned long GUIDHASHOBJECT(PWCHAR str)
{
	unsigned int hash = 0;
	int c;
	int i=0;
	unsigned short* str2=str;


	while (c = (*(str2+(i++)))){
		hash += c;
	}

	hash=hash%NUM_GUID_HASH;

	return hash;
}


void GUIDInsertHashEntry(PWCHAR pwFileName,PWCHAR pwGuid)
{
	PGUID_HASH_ENTRY pNewEntry;
	unsigned int hashpoint=0;
	KeEnterCriticalRegion();
	ExAcquireResourceExclusiveLite(&LockGUIDHash, TRUE);
	if(FreeGUIDHashList)
	{
		pNewEntry = FreeGUIDHashList;
		FreeGUIDHashList = pNewEntry->pNext;
	}
	else
	{
		pNewEntry = (PGUID_HASH_ENTRY)HjAllocatePool(NonPagedPool, sizeof(GUID_HASH_ENTRY));
	}
	
	if(pNewEntry)
	{
		memcpy(pNewEntry->wFileName , pwFileName,wcslen(pwFileName)*2);
		memcpy(pNewEntry->wGuid , pwGuid,wcslen(pwGuid)*2);
		hashpoint=GUIDHASHOBJECT(pwFileName);
		pNewEntry -> pNext = GUIDHashTable[hashpoint];
		GUIDHashTable[hashpoint] = pNewEntry;
	}
	
	ExReleaseResourceLite(&LockGUIDHash);
	KeLeaveCriticalRegion();
}

BOOLEAN GUIDIsExistInHashTable(PWCHAR pwFileName, WCHAR** ppwGuid)
{
	PGUID_HASH_ENTRY pHashEntry;
	BOOLEAN blRet;
	unsigned int hashpoint=0;

	KeEnterCriticalRegion();
	ExAcquireResourceExclusiveLite(&LockGUIDHash, TRUE);
	hashpoint=GUIDHASHOBJECT(pwFileName);
	pHashEntry = GUIDHashTable[hashpoint];
	while(pHashEntry && _wcsicmp(pHashEntry->wFileName , pwFileName)!=0)
	{
		pHashEntry = pHashEntry->pNext;
	}
	
	if(pHashEntry)
	{
		blRet = TRUE;
		if(ppwGuid)
			memcpy(*ppwGuid , pHashEntry->wGuid,GUIDCNTX2);
	}
	else
	{
		blRet = FALSE;
	}
	
	ExReleaseResourceLite(&LockGUIDHash);
	KeLeaveCriticalRegion();
	
	return blRet;
}

void GUIDFreeHashEntry(PWCHAR pwFileName)
{
	PGUID_HASH_ENTRY	pHashEntry, pPreHashEntry;
	
	KeEnterCriticalRegion();
	ExAcquireResourceExclusiveLite(&LockGUIDHash, TRUE);
	
	pHashEntry = GUIDHashTable[GUIDHASHOBJECT(pwFileName)];
	pPreHashEntry = NULL;
	
	while(pHashEntry && _wcsicmp(pHashEntry->wFileName , pwFileName)==0)
	{
		pPreHashEntry = pHashEntry;
		pHashEntry = pHashEntry->pNext;
		pHashEntry =NULL;
	}
	
	if(!pHashEntry) 
	{
		ExReleaseResourceLite(&LockGUIDHash);
		KeLeaveCriticalRegion();
		return;
	}
	
	if(pPreHashEntry) 
	{
		pPreHashEntry->pNext = pHashEntry->pNext;
	} 
	else 
	{
		GUIDHashTable[GUIDHASHOBJECT(pwFileName)] = pHashEntry->pNext;
	}
	
	pHashEntry->pNext = FreeGUIDHashList;
	FreeGUIDHashList = pHashEntry;
	
	ExReleaseResourceLite(&LockGUIDHash);
	KeLeaveCriticalRegion();
}


