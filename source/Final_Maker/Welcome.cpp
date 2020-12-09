// Welcome.cpp : implementation file
//

#include "stdafx.h"
#include "Maker.h"
#include "Welcome.h"
#include "Sheet.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Welcome property page

IMPLEMENT_DYNCREATE(Welcome, CPropertyPage)

Welcome::Welcome() : CPropertyPage(Welcome::IDD)
{
	//{{AFX_DATA_INIT(Welcome)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

Welcome::~Welcome()
{
}

void Welcome::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Welcome)
	DDX_Control(pDX, IDC_SHOCKWAVEFLASH1, m_Flash);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Welcome, CPropertyPage)
	//{{AFX_MSG_MAP(Welcome)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Welcome message handlers

BOOL Welcome::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	((Sheet*)GetParent())->SetWizardButtons(PSWIZB_NEXT);
	GetCurrentDirectory(MAX_PATH, Path);
	CString temp;
	temp.Format(Path);
	temp+="\\Image\\Arbiter.swf";
	m_Flash.SetMovie(temp);
	return CPropertyPage::OnSetActive();
}
