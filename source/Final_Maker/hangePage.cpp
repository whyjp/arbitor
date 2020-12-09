// hangePage.cpp : implementation file
//

#include "stdafx.h"
#include "Maker.h"
#include "hangePage.h"
#include "Sheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ChangePage property page

IMPLEMENT_DYNCREATE(ChangePage, CPropertyPage)

ChangePage::ChangePage() : CPropertyPage(ChangePage::IDD)
{
	//{{AFX_DATA_INIT(ChangePage)
	m_strSetupName = _T("Setup");
	m_strCoName = _T("");
	m_strSave = _T("C:\\Program Files");
	m_strProName = _T("");
	//}}AFX_DATA_INIT
}

ChangePage::~ChangePage()
{
}

void ChangePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ChangePage)
	DDX_Text(pDX, IDC_SETUPNAME, m_strSetupName);
	DDX_Text(pDX, IDC_CONAME, m_strCoName);
	DDX_Text(pDX, IDC_SAVE, m_strSave);
	DDX_Text(pDX, IDC_PRONAME, m_strProName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ChangePage, CPropertyPage)
	//{{AFX_MSG_MAP(ChangePage)
	ON_BN_CLICKED(IDC_FIND2, OnFind2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ChangePage message handlers

BOOL ChangePage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	((Sheet*)GetParent())->SetWizardButtons(PSWIZB_NEXT|PSWIZB_BACK);
	return CPropertyPage::OnSetActive();
}

void ChangePage::OnFind2() 
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
		m_strSave.Format(pszPathname);
	}
	
	UpdateData(FALSE);	
}
