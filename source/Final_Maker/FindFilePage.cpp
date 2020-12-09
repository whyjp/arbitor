// FindFilePage.cpp : implementation file
//

#include "stdafx.h"
#include "Maker.h"
#include "FindFilePage.h"
#include "Sheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// FindFilePage property page

IMPLEMENT_DYNCREATE(FindFilePage, CPropertyPage)

FindFilePage::FindFilePage() : CPropertyPage(FindFilePage::IDD)
{
	m_nMaxSize = 0;	
	//{{AFX_DATA_INIT(FindFilePage)
	m_strFile = _T("");
	//}}AFX_DATA_INIT

}

FindFilePage::~FindFilePage()
{
}

void FindFilePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(FindFilePage)
	DDX_Control(pDX, IDC_FILE, m_ctrlList);
	DDX_Text(pDX, IDC_FINDFILE, m_strFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FindFilePage, CPropertyPage)
	//{{AFX_MSG_MAP(FindFilePage)
	ON_BN_CLICKED(IDC_FIND, OnFind)
	ON_BN_CLICKED(IDC_CANCLE, OnCancle)
	ON_BN_CLICKED(IDC_FIND2, OnFind2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FindFilePage message handlers

BOOL FindFilePage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	((Sheet*)GetParent())->SetWizardButtons(PSWIZB_NEXT|PSWIZB_BACK);
	return CPropertyPage::OnSetActive();
}

void FindFilePage::OnFind() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);

	CString str;
	
	ITEMIDLIST        *pidlBrowse;
	char    pszPathname[MAX_PATH];
	
	BROWSEINFO BrInfo;
	BrInfo.hwndOwner = NULL; //GetSafeHwnd();
	BrInfo.pidlRoot = NULL;
	
	memset( &BrInfo, 0, sizeof(BrInfo) );
	BrInfo.pszDisplayName = pszPathname;
	BrInfo.lpszTitle = "설치할 파일들의 폴더 설정";
	BrInfo.ulFlags = BIF_RETURNONLYFSDIRS;
	
	// 다이얼로그를 띄우기
	pidlBrowse = ::SHBrowseForFolder(&BrInfo);    
	
	if( pidlBrowse != NULL)
	{
		// 패스를 얻어옴
		::SHGetPathFromIDList(pidlBrowse, pszPathname);
		str.Format(pszPathname);
		m_strDir.Format(pszPathname);
		FindSubDir(str);
	}

	UpdateData(FALSE);	
}


void FindFilePage::FindSubDir(CString strDir)
{
	strDir += "\\*.*";
	
	CFileFind ff;
	BOOL bFound = ff.FindFile(strDir);
	
	while(bFound)
	{
		bFound = ff.FindNextFile();
		
		if(ff.IsDots()) continue;
		if(ff.IsDirectory())
		{
			FindSubDir(ff.GetFilePath());
		}
		else
		{
			m_ListArray.Add(ff.GetFilePath());//파일 풀 디렉토리
			m_fileArray.Add(ff.GetFileName());//파일 네임
			m_ctrlList.AddString(ff.GetFilePath());
			m_DirArray.Add(FindDir(ff.GetRoot()));
			ListBoxSize(ff.GetFilePath());
		}
	}
}


void FindFilePage::OnCancle() 
{
	// TODO: Add your control notification handler code here
	if(m_ListArray.GetSize()==0)
	{
		AfxMessageBox("삭제할파일이 없습니다.");
	}
	else
	{
		m_ListArray.RemoveAt(m_ctrlList.GetCurSel());
		m_fileArray.RemoveAt(m_ctrlList.GetCurSel());
		m_ctrlList.DeleteString(m_ctrlList.GetCurSel());
		m_DirArray.RemoveAt(m_ctrlList.GetCurSel());
	}
	
	UpdateData(FALSE);
	
}

void FindFilePage::OnFind2() 
{
	// TODO: Add your control notification handler code here

	char szFilter[] = "PE Files(*.exe)|*.exe||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST|OFN_EXPLORER, szFilter);
	
	if(IDOK == dlg.DoModal())
	{
		m_strFile.Format(dlg.GetPathName());
		m_strFileName.Format(dlg.GetFileName());
	}
	
	UpdateData(FALSE);
}

CString FindFilePage::FindDir(CString dir)
{
	CString temp;
	temp = dir.Right(dir.GetLength()-m_strDir.GetLength());
	return temp;
}

//리스트박스를 글자 길이에 따라 Width를 변경하는 함수
void FindFilePage::ListBoxSize(CString tmp)
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
