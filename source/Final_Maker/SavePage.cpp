// SavePage.cpp : implementation file
//

#include "stdafx.h"
#include "Maker.h"
#include "SavePage.h"
#include "Sheet.h"
#include "Welcome.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SavePage property page

IMPLEMENT_DYNCREATE(SavePage, CPropertyPage)

SavePage::SavePage() : CPropertyPage(SavePage::IDD)
{
	//{{AFX_DATA_INIT(SavePage)
	m_strSavedir = _T("");
	//}}AFX_DATA_INIT
}

SavePage::~SavePage()
{
}

void SavePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SavePage)
	DDX_Text(pDX, IDC_SAVEDIR, m_strSavedir);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SavePage, CPropertyPage)
	//{{AFX_MSG_MAP(SavePage)
	ON_BN_CLICKED(IDC_FIND, OnFind)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SavePage message handlers

void SavePage::OnFind() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	ITEMIDLIST        *pidlBrowse;
	char    pszPathname[MAX_PATH];
	
	BROWSEINFO BrInfo;
	BrInfo.hwndOwner = NULL; //GetSafeHwnd();
	BrInfo.pidlRoot = NULL;
	
	memset( &BrInfo, 0, sizeof(BrInfo) );
	BrInfo.pszDisplayName = pszPathname;
	BrInfo.lpszTitle = "저장할 디렉토리를 선택하세요";
	BrInfo.ulFlags = BIF_RETURNONLYFSDIRS;
	
	// 다이얼로그를 띄우기
	pidlBrowse = ::SHBrowseForFolder(&BrInfo);    
	
	if( pidlBrowse != NULL)
	{
		// 패스를 얻어옴
		::SHGetPathFromIDList(pidlBrowse, pszPathname);
		m_strSavedir.Format(pszPathname);
	}
	
	UpdateData(FALSE);	
}

BOOL SavePage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	((Sheet*)GetParent())->SetWizardButtons(PSWIZB_NEXT|PSWIZB_BACK);
	return CPropertyPage::OnSetActive();
}
