// FinishPage.cpp : implementation file
//

#include "stdafx.h"
#include "Maker.h"
#include "FinishPage.h"
#include "Sheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// FinishPage property page

IMPLEMENT_DYNCREATE(FinishPage, CPropertyPage)

FinishPage::FinishPage() : CPropertyPage(FinishPage::IDD)
{
	//{{AFX_DATA_INIT(FinishPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

FinishPage::~FinishPage()
{
}

void FinishPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(FinishPage)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FinishPage, CPropertyPage)
	//{{AFX_MSG_MAP(FinishPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FinishPage message handlers

BOOL FinishPage::OnWizardFinish() 
{
	// TODO: Add your specialized code here and/or call the base class
	return CPropertyPage::OnWizardFinish();
}

BOOL FinishPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	((Sheet*)GetParent())->SetWizardButtons(PSWIZB_BACK|PSWIZB_FINISH);	
	return CPropertyPage::OnSetActive();
}
