// AbiterPeResource.h: interface for the AbiterPeResource class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABITERPERESOURCE_H__1C5E8A9F_9181_466A_AB3E_87840E3439DF__INCLUDED_)
#define AFX_ABITERPERESOURCE_H__1C5E8A9F_9181_466A_AB3E_87840E3439DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


typedef struct _Abiter_LISTNODE
{
	PVOID						Data;
	struct _Abiter_LISTNODE*	Next;
}Abiter_LISTNODE, *PAbiter_LISTNODE;



class AbiterPeResource  
{
	
public:
	AbiterPeResource();
	virtual ~AbiterPeResource();
	
	BOOL Abiter_PeCopy(CString TgFileName, CString ObFileName);

	BOOL Abiter_ListStartup();
 	VOID Abiter_ListCleanup();
 	BOOL Abiter_ListPushBack(IN PVOID Data);
 	BOOL Abiter_ListPushFront(IN PVOID Data);
 	PVOID Abiter_ListPopBack();
 	PVOID Abiter_ListPopFront();
 	VOID Abiter_ListPopAll();
 	PVOID Abiter_ListGetBack();
 	PVOID Abiter_ListGetFront();
 	DWORD Abiter_ListGetCount();
 	BOOL Abiter_ListIsEmpty();
};

#endif // !defined(AFX_ABITERPERESOURCE_H__1C5E8A9F_9181_466A_AB3E_87840E3439DF__INCLUDED_)
