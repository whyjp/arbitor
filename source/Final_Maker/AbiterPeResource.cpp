// AbiterPeResource.cpp: implementation of the AbiterPeResource class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Maker.h"
#include "AbiterPeResource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AbiterPeResource::AbiterPeResource()
{

}

AbiterPeResource::~AbiterPeResource()
{

}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

static	PAbiter_LISTNODE	g_Head;
static    DWORD g_Count;

//----------------------------------------------------------------------
//				I  N  I  T  I  A  L  I  Z  A  T  I  O  N
//----------------------------------------------------------------------

//
// Initialize list data
//
BOOL AbiterPeResource::Abiter_ListStartup()
{
	// Allocate head node
	g_Head = (PAbiter_LISTNODE)malloc(sizeof(PAbiter_LISTNODE));
	if (!g_Head)
	{
		return FALSE;
	}
	
	// Set head values to zero ( tail is null )
	g_Head->Data = NULL;
	g_Head->Next = NULL;
	
	return TRUE;
}

//
// Uninitialize list data
//
VOID AbiterPeResource::Abiter_ListCleanup()
{
	// Get rid of all nodes
	//	Abiter_ListPopAll();
	// Free head node
	if (g_Head)
	{
		g_Head = NULL;
		free(g_Head);
		
	}
}


//----------------------------------------------------------------------
//							   P  U  S  H
//----------------------------------------------------------------------

//
// Push a node back
//
BOOL
AbiterPeResource::Abiter_ListPushBack(
							IN PVOID Data
							)
{
	PAbiter_LISTNODE	newNode;
	PAbiter_LISTNODE	curNode;
	
	// Is list initialized ?
	if (!g_Head)
	{
		return FALSE;
	}
	
	// Allocate new node
	newNode = (PAbiter_LISTNODE)malloc(sizeof(Abiter_LISTNODE));
	if (!newNode)
	{
		return FALSE;
	}
	
	// Find place just before tail
	curNode = g_Head;
	while (curNode->Next)
	{
		// Move to next
		curNode = curNode->Next;
	}
	
	// Set data and link it next to head
	newNode->Data = Data;
	newNode->Next = curNode->Next;
	curNode->Next = newNode;
	
	// Add list count
	g_Count++;
	
	return TRUE;
}

//
// Push a node front
//
BOOL 
AbiterPeResource::Abiter_ListPushFront(
							 IN PVOID Data
							 )
{
	PAbiter_LISTNODE	newNode;
	
	// Is list initialized ?
	if (!g_Head)
	{
		return FALSE;
	}
	
	// Allocate new node
	newNode = (PAbiter_LISTNODE)malloc(sizeof(Abiter_LISTNODE));
	if (!newNode)
	{
		return FALSE;
	}
	
	// Set data and link it next to head
	newNode->Data = Data;
	newNode->Next = g_Head->Next;
	g_Head->Next = newNode;
	
	// Add list count
	g_Count++;
	
	return TRUE;
}


//----------------------------------------------------------------------
//								 P  O  P
//----------------------------------------------------------------------

//
// Pop a node back
//
PVOID
AbiterPeResource::Abiter_ListPopBack()
{
	PAbiter_LISTNODE	popNode;
	PAbiter_LISTNODE	prevNode;
	PVOID				popData;
	
	// Is list initialized ?
	if (!g_Head || !g_Count)
	{
		return NULL;
	}
	
	// Find place just before tail
	popNode = g_Head;
	while (popNode->Next)
	{
		// Save current position
		prevNode = popNode;
		
		// Move to next
		popNode = popNode->Next;
	}
	
	// Save data to return
	popData = popNode->Data;
	
	// Change link
	prevNode->Next = popNode->Next;
	
	// Free node
	free(popNode);
	
	// Subtract list count
	g_Count--;
	
	return popData;
}

//
// Pop a node front
//
PVOID
AbiterPeResource::Abiter_ListPopFront()
{
	PAbiter_LISTNODE	popNode;
	PVOID				popData;
	
	// Is list initialized ?
	if (!g_Head || !g_Count)
	{
		return NULL;
	}
	
	// Get node to pop
	popNode = g_Head->Next;
	
	// Save data to return
	popData = popNode->Data;
	
	// Change link
	g_Head->Next = popNode->Next;
	
	// Free node
	free(popNode);
	
	// Subtract list count
	g_Count--;
	
	return popData;
}

//
// Pop all nodes
//
VOID AbiterPeResource::Abiter_ListPopAll()
{
	PAbiter_LISTNODE	popNode;
	PAbiter_LISTNODE	savedNode;
	
	// Is list initialized ?
	if (!g_Head || !g_Count)
	{
		return;
	}
	
	// Free all nodes by touching tail
	popNode = g_Head->Next;
	while (popNode)
	{
		// Save current position
		savedNode = popNode;
		
		// Move to next
		popNode = popNode->Next;
		
		// Free saved node
		free(savedNode);
	}
	
	// Set head node next pointer
	g_Head->Next = NULL;
	
	// Set list count to zero
	g_Count = 0;
}


//----------------------------------------------------------------------
//								 G  E  T
//----------------------------------------------------------------------

// 
// Get a node back
//
PVOID
AbiterPeResource::Abiter_ListGetBack()
{
	PAbiter_LISTNODE	getNode;
	
	// Is list initialized ?
	if (!g_Head || !g_Count)
	{
		return NULL;
	}
	
	// Find place just before tail
	getNode = g_Head;
	while (getNode->Next)
	{
		// Move to next
		getNode = getNode->Next;
	}
	
	return getNode->Data;	
}

//
// Get a bide front
//
PVOID
AbiterPeResource::Abiter_ListGetFront()
{
	PAbiter_LISTNODE	getNode;
	
	// Is list initialized ?
	if (!g_Head || !g_Count)
	{
		return NULL;
	}
	
	// Get node to get
	getNode = g_Head->Next;
	
	return getNode->Data;
}


//----------------------------------------------------------------------
//					 I  N  F  O  R  M  A  T  I  O  N
//----------------------------------------------------------------------

//
// Get curretn node count
//
DWORD
AbiterPeResource::Abiter_ListGetCount()
{
	return g_Count;
}

//
// Is list empty ?
//
BOOL
AbiterPeResource::Abiter_ListIsEmpty()
{
	// Is list initialized ?
	if (!g_Head)
	{
		return TRUE;
	}
	
	return (!g_Count);
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

//PE파일의 리소스를 카피하는 함수
BOOL AbiterPeResource::Abiter_PeCopy(CString TgFileName, CString ObFileName)//타겟파일과 원본파일의 BUF와, 타겟파일의 크기를 알아온다
{
	
	DWORD TgSize=0;
	WORD m_Entries=0;
	BOOL bDataEntry=FALSE;

	DWORD SectionAlignbment=NULL;
	DWORD cbResAligned=NULL;
	DWORD cbLastAligned=NULL;
	DWORD ppResDat=NULL;
	
	HANDLE	m_hObFile= NULL;//원본pe의 핸들
	HANDLE  m_hObMap= NULL;//메모리 멥드할 pe를 선택 
	LPBYTE  m_pObView= NULL;//원본 pe를 메모리에 매핑시킨다
	
	PIMAGE_DOS_HEADER pDosHdrsOb= NULL;//원본 pe의 IMAGE_DOS_HEADER를 받는다.
	PIMAGE_NT_HEADERS pNtHdrsOb= NULL;//원본PE의 PIMAGE_NT_HEADERS를 받는다.
	PIMAGE_DATA_DIRECTORY pResDatDirOb= NULL;//원본pe의 데이타 디렉토리를 받는다. 
	PIMAGE_SECTION_HEADER pResSectionHdrOb = NULL;//리소스섹션의 헤더를 얻는다
	PBYTE pResSectioOb=NULL;//리소스섹션의 오프셋을 얻어온다
	DWORD cbResSection=NULL;
	
    //////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	
	HANDLE	m_hTgFile= NULL;//가짜pe의 핸들
	HANDLE  m_hTgMap= NULL;//메모리 멥드할 pe를 선택 
	LPBYTE  m_pTgView= NULL;//가짜 pe를 메모리에 매핑시킨다
	
	PIMAGE_DATA_DIRECTORY pResDatDirTg= NULL;//원본pe의 데이타 디렉토리를 받는다. 
	PIMAGE_SECTION_HEADER pResLastSectionHdrTg=NULL;
	PIMAGE_SECTION_HEADER pResSectionHdrTg = NULL;//리소스섹션의 헤더를 얻는다
	PBYTE pResSectionTg=NULL;//리소스섹션의 오프셋을 얻어온다
	
	
	PIMAGE_RESOURCE_DIRECTORY pResDir=NULL;
	PIMAGE_RESOURCE_DIRECTORY_ENTRY pResDirEntry=NULL;
	PIMAGE_RESOURCE_DATA_ENTRY pResDatEntry=NULL;
	PIMAGE_RESOURCE_DATA_ENTRY pResDatEntryBuf=NULL;
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	///////////////////////////////////원본PE/////////////////////////////////
	/////////////////////////////////정보추출/////////////////////////////////
	//////////////////////////////////////////////////////////////////////////	
	
	
	
	
	
	
	m_hObFile=CreateFile(ObFileName,GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, 0,NULL);//원본 pe를연다
	if(m_hObFile == INVALID_HANDLE_VALUE)
		throw MAKE_HRESULT(1, FACILITY_WIN32, GetLastError());
	
	m_hObMap = CreateFileMapping(m_hObFile, NULL,PAGE_READONLY, 0, 0, NULL);
	//매핑시킨다
	if(!m_hObMap)
		throw MAKE_HRESULT(1, FACILITY_WIN32, GetLastError());
	
	m_pObView = (LPBYTE)MapViewOfFile(m_hObMap, FILE_MAP_READ, 0, 0, 0);
	
	//맵뷰
	if(!m_pObView)
		throw MAKE_HRESULT(1, FACILITY_WIN32, GetLastError());
	
	//pe의 시작 주소를 알기 위해서는 도스 헤더의 e_lfanew를 알아야된다.
	
	
	
	
	
	pDosHdrsOb = (PIMAGE_DOS_HEADER)m_pObView;//PE에서 PIMAGE_DOS_HEADER 추출  
	if(pDosHdrsOb->e_magic != IMAGE_DOS_SIGNATURE)//PE파일인지를 검증
		throw "PE 포맷을 가진 파일이 아닙니다";
	

	
	pNtHdrsOb = (PIMAGE_NT_HEADERS)(m_pObView + pDosHdrsOb->e_lfanew);//PE에서 PIMAGE_NT_HEADERS를 추출
	
	//pDosHdrsOb->e_lfanew   file address of new exe header
	if(pNtHdrsOb->Signature != IMAGE_NT_SIGNATURE)
		throw "PE 포맷을 가진 파일이 아닙니다";//PE파일인지를 검증
	
	pResDatDirOb=&pNtHdrsOb->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE];
	if(!pResDatDirOb->Size&&!pResDatDirOb->VirtualAddress)
	{
		return FALSE;
	}//리소스섹션의 존재여부를 확인
	
	
	
	
	
	
	
	LPBYTE pIterSec = m_pObView + pDosHdrsOb->e_lfanew + sizeof(IMAGE_NT_HEADERS);
	for(INT i=0; i<pNtHdrsOb->FileHeader.NumberOfSections; i++)
	{
		PIMAGE_SECTION_HEADER pTempOb = (PIMAGE_SECTION_HEADER)pIterSec;
		pIterSec += sizeof(IMAGE_SECTION_HEADER);
		if(!memcmp(pTempOb->Name, ".rsrc\x0\x0\x0", IMAGE_SIZEOF_SHORT_NAME))
		{
			pResSectionHdrOb = pTempOb;//리소스섹션을 찾아 받아옴
			break;
		}
	}
	
	//리소스파일 찾음
	if(!pResSectionHdrOb)
		throw "리소스 섹션이 존재하지 않습니다.";

	pResSectioOb = m_pObView+pResSectionHdrOb->PointerToRawData;//리소스섹션의 실주소 
	cbResSection = pResSectionHdrOb->SizeOfRawData;//리소스섹션의 사이즈
	
	
	
	
	
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	///////////////////////////////////가짜PE/////////////////////////////////
	/////////////////////////////////정보추출/////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	
	
	m_hTgFile=CreateFile(TgFileName,GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,NULL);//가짜 pe를 연다
	
	
	//////////////////////////////////////////////////////////////////////////
	//==============================가  라==================================//
	//////////////////////////////////////////////////////////////////////////
	



	TgSize=GetFileSize(m_hTgFile,NULL);
	
	
	if(m_hTgFile == INVALID_HANDLE_VALUE)
		throw MAKE_HRESULT(1, FACILITY_WIN32, GetLastError());
	
	m_hTgMap = CreateFileMapping(m_hTgFile, NULL ,PAGE_READWRITE, 0, TgSize+cbResSection, NULL);
	//매핑시킨다
	if(!m_hObMap)
		throw MAKE_HRESULT(1, FACILITY_WIN32, GetLastError());
	
	m_pTgView = (LPBYTE)MapViewOfFile(m_hTgMap, FILE_MAP_WRITE, 0, 0, 0);

	//파일 사이즈 와.. 리소스가 들어갈 부분의 사이즈를 더 잡아줘야한다.
	
	//맵뷰
	if(!m_pTgView)
		throw MAKE_HRESULT(1, FACILITY_WIN32, GetLastError());
	
	
	//pe의 시작 주소를 알기 위해서는 도스 헤더의 e_lfanew를 알아야된다.
	
	
	
	PIMAGE_DOS_HEADER pDosHdrsTg = (PIMAGE_DOS_HEADER)m_pTgView;//PE에서 PIMAGE_DOS_HEADER 추출  
	if(pDosHdrsTg->e_magic != IMAGE_DOS_SIGNATURE)//PE파일인지를 검증
		throw "PE 포맷을 가진 파일이 아닙니다";
	
	
	
	PIMAGE_NT_HEADERS pNtHdrsTg = (PIMAGE_NT_HEADERS)(m_pTgView + pDosHdrsTg->e_lfanew);//PE에서 PIMAGE_NT_HEADERS를 추출
	
	//pDosHdrsOb->e_lfanew   file address of new exe header
	if(pNtHdrsTg->Signature != IMAGE_NT_SIGNATURE)
		throw "PE 포맷을 가진 파일이 아닙니다";//PE파일인지를 검증
	
	pResDatDirTg=&pNtHdrsTg->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE];

	
	//////////////////////////////////////////////////////////////////////////
	
	
	if(pResDatDirTg->Size||pResDatDirTg->VirtualAddress)
	{
		return FALSE;
	}//리소스섹션의 존재여부를 확인 없어야한다.
	
	
	
	LPBYTE	pIterSecTg = m_pTgView + pDosHdrsTg->e_lfanew + sizeof(IMAGE_NT_HEADERS);
	PIMAGE_SECTION_HEADER  pTempTg = (PIMAGE_SECTION_HEADER)pIterSecTg;
	while(pTempTg->Name[0]!=0)
	{
		pTempTg=(PIMAGE_SECTION_HEADER)pIterSecTg;
		pIterSecTg += sizeof(IMAGE_SECTION_HEADER);
	}//리소스섹션헤더에서 0인부분을 찾는다
	pResSectionHdrTg=pTempTg;
	pResLastSectionHdrTg=pTempTg-1;//리소스 섹션헤더바로 전의 섹션헤더
	
	//파일의 실주소값과 크기를 더해서 리소스가 붙을부분을 계산한다.
	  pResSectionTg=m_pTgView+TgSize;
	
	
	
	//===========================================================================================================
	// 맵뷰의 핸들값으로 다시 메모리를 잡아준다

	//메로리를 다시잡아주어야한다....?????
	//////////////////////////////////////////////////////////////////////////
	

	
//아직 불분명===========================================================

	  
	CopyMemory(pResSectionTg,pResSectioOb,cbResSection);//리소스섹션을 복사
	
	
	//성공
	CopyMemory(pResDatDirTg,pResDatDirOb,sizeof(IMAGE_DATA_DIRECTORY));//이미지 데이터디렉토리 복사

	//성공
	CopyMemory(pResSectionHdrTg,pResSectionHdrOb,IMAGE_SIZEOF_SECTION_HEADER);//리소스섹션의 헤더를 복사
	

	
	
	
	//===========================================================================================================
	
	
	
	pNtHdrsTg->FileHeader.NumberOfSections++;//리소스섹션을 삽입하기 위해 갯수를 1개 늘려줌
	
	SectionAlignbment=pNtHdrsTg->OptionalHeader.SectionAlignment;//메모리에 매핑할때 올라갈 메모리 크기....
	
	cbResAligned=pResSectionHdrTg->Misc.VirtualSize+((SectionAlignbment-pResSectionHdrTg->Misc.VirtualSize%SectionAlignbment)%SectionAlignbment);
	
	if(cbResAligned%SectionAlignbment)
	{
		return FALSE;
	}
	
	
	pNtHdrsTg->OptionalHeader.SizeOfInitializedData +=cbResAligned;
	pNtHdrsTg->OptionalHeader.SizeOfImage +=cbResAligned;
	
	
	cbLastAligned=pResLastSectionHdrTg->Misc.VirtualSize+((SectionAlignbment-pResLastSectionHdrTg->Misc.VirtualSize%SectionAlignbment)%SectionAlignbment);
	
	if(cbLastAligned%SectionAlignbment)
	{
		return FALSE;
	}
	
	
	pResDatDirTg->VirtualAddress=pResLastSectionHdrTg->VirtualAddress+cbLastAligned;
	
	//pResSectionHdrTg->PointerToRawData=cbTg;
	pResSectionHdrTg->PointerToRawData=TgSize;
	pResSectionHdrTg->VirtualAddress=pResDatDirTg->VirtualAddress;
	
	//====================================================================================================
	//pe파일안으로 찾아가서 복사하는 부분.
	//====================================================================================================
	
	if(!Abiter_ListStartup())//리스트 실행 
	{
		return FALSE;
	}
	

	pResDir=(PIMAGE_RESOURCE_DIRECTORY)pResSectionTg;
	while(TRUE)
	{
		m_Entries=pResDir->NumberOfNamedEntries+pResDir->NumberOfIdEntries;
		pResDirEntry=(PIMAGE_RESOURCE_DIRECTORY_ENTRY)(pResDir+1);//리소스 디렉토리
		for(i=0;i<m_Entries;i++)
		{
			bDataEntry=FALSE;
			
			if(!pResDirEntry->DataIsDirectory)
			{
				bDataEntry=TRUE;
				
				pResDatEntry=(PIMAGE_RESOURCE_DATA_ENTRY)(pResSectionTg+pResDirEntry->OffsetToData);
				
				if(!Abiter_ListPushBack(pResDatEntry))
				{
					Abiter_ListCleanup();
					return FALSE;
				}
			}
			pResDirEntry++;
		}
		
		
		//////////////////////////////////////////////////////////////////////////
		
		
		if(bDataEntry)
		{
			if(((PIMAGE_RESOURCE_DATA_ENTRY)pResDirEntry)->Reserved==0)
			{
				break;
			}
		}
		
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		pResDir=(PIMAGE_RESOURCE_DIRECTORY)pResDirEntry;
	}


	while(!Abiter_ListIsEmpty())
	{
		pResDatEntry=(PIMAGE_RESOURCE_DATA_ENTRY)Abiter_ListPopFront();
		ppResDat=pResSectionHdrTg->PointerToRawData+pResDatEntry->OffsetToData-pResSectionHdrOb->VirtualAddress;


		if(!Abiter_ListIsEmpty())
		{
			pResDatEntryBuf=(PIMAGE_RESOURCE_DATA_ENTRY)Abiter_ListGetFront();
		}
		pResDatEntry->OffsetToData=pResSectionHdrTg->VirtualAddress-pResSectionHdrTg->PointerToRawData+ppResDat;
		
	}
	UnmapViewOfFile(m_pObView);
	CloseHandle(m_hObMap);
	CloseHandle(m_hObFile);
	UnmapViewOfFile(m_pTgView);
	CloseHandle(m_hTgMap);
	CloseHandle(m_hTgFile);
	Abiter_ListCleanup();
	return TRUE;
}


