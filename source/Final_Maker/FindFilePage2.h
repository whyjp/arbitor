//{{AFX_INCLUDES()
#include "shockwaveflash.h"
//}}AFX_INCLUDES
#if !defined(AFX_FINDFILEPAGE2_H__7FB331C2_9088_49D0_B0C9_2DA59F064C79__INCLUDED_)
#define AFX_FINDFILEPAGE2_H__7FB331C2_9088_49D0_B0C9_2DA59F064C79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FindFilePage2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// FindFilePage2 dialog

class FindFilePage2 : public CPropertyPage
{
	DECLARE_DYNCREATE(FindFilePage2)

// Construction
public:
	void ListBoxSize(CString tmp);
	int m_nMaxSize;
	CStringArray m_fileArray;
	CStringArray m_PathArray;
	FindFilePage2();
	~FindFilePage2();

// Dialog Data
	//{{AFX_DATA(FindFilePage2)
	enum { IDD = IDD_FINDFILE1 };
	CListBox	m_ctrlList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(FindFilePage2)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(FindFilePage2)
	afx_msg void OnCancle();
	afx_msg void OnFind();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDFILEPAGE2_H__7FB331C2_9088_49D0_B0C9_2DA59F064C79__INCLUDED_)
