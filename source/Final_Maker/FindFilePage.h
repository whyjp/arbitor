//{{AFX_INCLUDES()
#include "shockwaveflash.h"
//}}AFX_INCLUDES
#if !defined(AFX_FINDFILEPAGE_H__9FF2ACDA_2510_458F_9384_9FCCB554971F__INCLUDED_)
#define AFX_FINDFILEPAGE_H__9FF2ACDA_2510_458F_9384_9FCCB554971F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FindFilePage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// FindFilePage dialog

class FindFilePage : public CPropertyPage
{
	DECLARE_DYNCREATE(FindFilePage)

// Construction
public:
	void ListBoxSize(CString tmp);
	int m_nMaxSize;
	CString FindDir(CString dir);
	CStringArray m_DirArray;
	CString m_strDir;
	FindFilePage();
	~FindFilePage();

	void FindSubDir(CString strDir);
	CStringArray m_ListArray;
	CStringArray m_fileArray;
	CString m_strFileName;
// Dialog Data
	//{{AFX_DATA(FindFilePage)
	enum { IDD = IDD_FINDFILE };
	CListBox	m_ctrlList;
	CString	m_strFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(FindFilePage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(FindFilePage)
	afx_msg void OnFind();
	afx_msg void OnCancle();
	afx_msg void OnFind2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDFILEPAGE_H__9FF2ACDA_2510_458F_9384_9FCCB554971F__INCLUDED_)
