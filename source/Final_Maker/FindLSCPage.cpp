// FindLSCPage.cpp : implementation file
//

#include "stdafx.h"
#include "Maker.h"
#include "FindLSCPage.h"
#include "Sheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// FindLSCPage property page

IMPLEMENT_DYNCREATE(FindLSCPage, CPropertyPage)

FindLSCPage::FindLSCPage() : CPropertyPage(FindLSCPage::IDD)
{
	
	//{{AFX_DATA_INIT(FindLSCPage)
	m_strLSCDir = _T("");
	m_strIcon = _T("");
	m_strVer = _T("");
	m_strUIcon = _T("");
	//}}AFX_DATA_INIT
	m_strIcon.Format("install.ico");
	m_strUIcon.Format("uninstall.ico");
}

FindLSCPage::~FindLSCPage()
{
}

void FindLSCPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(FindLSCPage)
	DDX_Text(pDX, IDC_LSCDIR, m_strLSCDir);
	DDX_Text(pDX, IDC_ICONDIR, m_strIcon);
	DDX_Text(pDX, IDC_VER, m_strVer);
	DDX_Text(pDX, IDC_UICON, m_strUIcon);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FindLSCPage, CPropertyPage)
	//{{AFX_MSG_MAP(FindLSCPage)
	ON_BN_CLICKED(IDC_FIND, OnFind)
	ON_BN_CLICKED(IDC_FIND2, OnFind2)
	ON_BN_CLICKED(IDC_FIND4, OnFind4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FindLSCPage message handlers

BOOL FindLSCPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	((Sheet*)GetParent())->SetWizardButtons(PSWIZB_NEXT|PSWIZB_BACK);
	return CPropertyPage::OnSetActive();
}

void FindLSCPage::OnFind() 
{
	// TODO: Add your control notification handler code here
	char szFilter[] = "Document Files(*.txt, *.hwp, *.rtf, *.doc)|*.txt;*.hwp;*.rtf;*.doc|All Files(*.*)|*.*||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_FILEMUSTEXIST|OFN_EXPLORER|OFN_LONGNAMES, szFilter);
	if(IDOK == dlg.DoModal())
	{
		m_strLSCDir.Format(dlg.GetPathName());
	}
	UpdateData(FALSE);
}

void FindLSCPage::OnFind2() 
{
	// TODO: Add your control notification handler code here
	
	char szFilter[] = "Icon (*.ico)|*.ico||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_FILEMUSTEXIST|OFN_EXPLORER, szFilter);
	
	if(IDOK == dlg.DoModal())
	{
		m_strIcon.Format(dlg.GetPathName());
	}
	
	UpdateData(FALSE);
}

void FindLSCPage::OnFind4() 
{
	// TODO: Add your control notification handler code here
	
	char szFilter[] = "Icon (*.ico)|*.ico||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_FILEMUSTEXIST|OFN_EXPLORER|OFN_LONGNAMES, szFilter);
	
	if(IDOK == dlg.DoModal())
	{
		m_strUIcon.Format(dlg.GetPathName());
	}
	
	UpdateData(FALSE);
}
