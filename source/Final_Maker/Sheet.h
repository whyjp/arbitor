#if !defined(AFX_SHEET_H__11ECF3FB_C434_4BD4_AD6C_582FB84C9B92__INCLUDED_)
#define AFX_SHEET_H__11ECF3FB_C434_4BD4_AD6C_582FB84C9B92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Sheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Sheet
#include "Start.h"
#include "FindFilePage.h"
#include "FindLSCPage.h"
#include "hangePage.h"
#include "FinishPage.h"
#include "SavePage.h"
#include "FindFilePage2.h"
#include "AbiterPeResource.h"
#include "Welcome.h"

class Sheet : public CPropertySheet
{
	DECLARE_DYNAMIC(Sheet)
	
// Construction
public:
	Sheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	Sheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	
// Attributes
public:
	Start			m_start;
	FinishPage		m_finish;
	ChangePage		m_change;
	FindFilePage	m_findfile;
	FindLSCPage		m_findlsc;
	SavePage		m_save;
	FindFilePage2	m_findfile2;
	Welcome			m_welcome;
	CString			appPath;
private:
	CStringArray m_array;
	CStringArray m_PEarray;//가짜pe파일
	CStringArray m_OriginalPE;//진짜 pe파일
	CStringArray m_DirArray; //디렉토리저장 공간
	CStringArray m_DirPEarray;//디렉토리pe 저장 공간
	AbiterPeResource APR;


	PROCESS_INFORMATION Loadingpi;
// Operations
public:
	CFile m_file;
	CFile m_copyfile;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Sheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL mainCheck;
	void MainPECheck();
	void SortDirectory();
	void SetDir();
	void MakePE();
	BOOL FindEXE(CString str);
	void RunSetup();
	void CheckStart();
	void MakeSetup();
	void OnCreateFile();
	void MakeFile();
	void FinishSetup();


	
	virtual ~Sheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(Sheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHEET_H__11ECF3FB_C434_4BD4_AD6C_582FB84C9B92__INCLUDED_)
