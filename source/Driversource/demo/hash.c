#include <ntifs.h>
#include "main.h"
#include "hash.h"

ERESOURCE LockHash;
PHASH_ENTRY	HashTable[ NUM_HASH ] = { NULL, NULL, NULL };
PHASH_ENTRY FreeHashList = NULL;

void fInsertHashEntry(PFILE_OBJECT pFileObj, PWCHAR pwFileName)
{
	PHASH_ENTRY pNewEntry;
	KeEnterCriticalRegion();
	ExAcquireResourceExclusiveLite(&LockHash, TRUE);

	if(FreeHashList)
	{
		pNewEntry = FreeHashList;
		FreeHashList = pNewEntry->pNext;
	}
	else
	{
		pNewEntry = ExAllocatePool(NonPagedPool, sizeof(HASH_ENTRY));
	}
	
	if(pNewEntry)
	{
		pNewEntry->pFileObj = pFileObj;
		pNewEntry->pwFileName = pwFileName;
		pNewEntry -> pNext = HashTable[HASHOBJECT(pFileObj)];
		HashTable[ HASHOBJECT(pFileObj)] = pNewEntry;
	}
	
	ExReleaseResourceLite(&LockHash);
	KeLeaveCriticalRegion();
}

BOOLEAN fIsExistInHashTable(PFILE_OBJECT pFileObj,	WCHAR** ppwFileName)
{
	PHASH_ENTRY pHashEntry;
	BOOLEAN blRet;
	
	KeEnterCriticalRegion();
	ExAcquireResourceExclusiveLite(&LockHash, TRUE);
	
	pHashEntry = HashTable[HASHOBJECT(pFileObj)];
	while(pHashEntry && pHashEntry->pFileObj != pFileObj)
	{
		pHashEntry = pHashEntry->pNext;
	}
	
	if(pHashEntry)
	{
		blRet = TRUE;
		if(ppwFileName)
			*ppwFileName = pHashEntry->pwFileName;
	}
	else
	{
		blRet = FALSE;
	}
	
	ExReleaseResourceLite(&LockHash);
	KeLeaveCriticalRegion();
	
	return blRet;
}

void fFreeHashEntry(PFILE_OBJECT pFileObj)
{
	PHASH_ENTRY	pHashEntry, pPreHashEntry;
	
	KeEnterCriticalRegion();
	ExAcquireResourceExclusiveLite(&LockHash, TRUE);
	
	pHashEntry = HashTable[HASHOBJECT(pFileObj)];
	pPreHashEntry = NULL;
	
	while(pHashEntry && pHashEntry->pFileObj != pFileObj)
	{
		pPreHashEntry = pHashEntry;
		pHashEntry = pHashEntry->pNext;
	}
	
	if(!pHashEntry) 
	{
		ExReleaseResourceLite(&LockHash);
		KeLeaveCriticalRegion();
		return;
	}
	
	if(pPreHashEntry) 
	{
		pPreHashEntry->pNext = pHashEntry->pNext;
	} 
	else 
	{
		HashTable[HASHOBJECT(pFileObj)] = pHashEntry->pNext;
	}
	
	pHashEntry->pNext = FreeHashList;
	FreeHashList = pHashEntry;
	
	ExReleaseResourceLite(&LockHash);
	KeLeaveCriticalRegion();
}


