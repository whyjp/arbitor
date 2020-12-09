// Start.cpp : implementation file
//

#include "stdafx.h"
#include "Maker.h"
#include "Start.h"
#include "Sheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Start property page

IMPLEMENT_DYNCREATE(Start, CPropertyPage)

Start::Start() : CPropertyPage(Start::IDD)
{
//	((Sheet*)GetParent())->SetWizardButtons(NULL);
	//{{AFX_DATA_INIT(Start)
	m_Bcheck = FALSE;
	//}}AFX_DATA_INIT
	m_Bcheck=FALSE;

}

Start::~Start()
{
}

void Start::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Start)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Start, CPropertyPage)
	//{{AFX_MSG_MAP(Start)
	ON_BN_CLICKED(IDC_OK, OnOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Start message handlers

BOOL Start::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_Bcheck)
	{
		((Sheet*)GetParent())->SetWizardButtons(PSWIZB_NEXT);
	}
	else
	{
		((Sheet*)GetParent())->SetWizardButtons(NULL);
	}
		
	return CPropertyPage::OnSetActive();
}


void Start::OnOk() 
{
	// TODO: Add your control notification handler code here
	if(m_Bcheck==FALSE)
	{
		m_Bcheck = TRUE;
	}
	else
	{
		m_Bcheck = FALSE;
	}
	((Sheet*)GetParent())->CheckStart();
}
