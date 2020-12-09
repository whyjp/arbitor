// FindFilePage2.cpp : implementation file
//

#include "stdafx.h"
#include "Maker.h"
#include "FindFilePage2.h"
#include "Sheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// FindFilePage2 property page

IMPLEMENT_DYNCREATE(FindFilePage2, CPropertyPage)

FindFilePage2::FindFilePage2() : CPropertyPage(FindFilePage2::IDD)
{
	//{{AFX_DATA_INIT(FindFilePage2)
	//}}AFX_DATA_INIT
	m_nMaxSize = 0;

}

FindFilePage2::~FindFilePage2()
{
}

void FindFilePage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(FindFilePage2)
	DDX_Control(pDX, IDC_FILE, m_ctrlList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FindFilePage2, CPropertyPage)
	//{{AFX_MSG_MAP(FindFilePage2)
	ON_BN_CLICKED(IDC_CANCLE, OnCancle)
	ON_BN_CLICKED(IDC_FIND, OnFind)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FindFilePage2 message handlers

BOOL FindFilePage2::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	((Sheet*)GetParent())->SetWizardButtons(PSWIZB_NEXT|PSWIZB_BACK);
	return CPropertyPage::OnSetActive();
}

void FindFilePage2::OnCancle() 
{
	// TODO: Add your control notification handler code here
	if(m_PathArray.GetSize()==0)
	{
		AfxMessageBox("삭제할파일이 없습니다.");
	}
	else
	{
		m_PathArray.RemoveAt(m_ctrlList.GetCurSel());
		m_fileArray.RemoveAt(m_ctrlList.GetCurSel());
		m_ctrlList.DeleteString(m_ctrlList.GetCurSel());
	}
	
	UpdateData(FALSE);	
}

void FindFilePage2::OnFind() 
{
	// TODO: Add your control notification handler code here
	char szFilter[] = "All Files(*.*)|*.*||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST|OFN_EXPLORER, szFilter);
	
	if(IDOK == dlg.DoModal())
	{
		m_PathArray.Add(dlg.GetPathName());
		m_fileArray.Add(dlg.GetFileName());
		m_ctrlList.AddString(dlg.GetPathName());
		ListBoxSize(dlg.GetPathName());
	}
	UpdateData(FALSE);
}

//리스트박스를 글자 길이에 따라 Width를 변경하는 함수
void FindFilePage2::ListBoxSize(CString tmp)
{	
   CDC *pDC = m_ctrlList.GetDC();

   if (pDC)
   {
    int nTextWidth = pDC->GetTextExtent(tmp).cx;

    if (nTextWidth > m_nMaxSize)
    {
     m_nMaxSize = nTextWidth;
     m_ctrlList.SetHorizontalExtent(m_nMaxSize);
    }
   }
}
