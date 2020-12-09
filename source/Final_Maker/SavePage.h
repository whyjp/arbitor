//{{AFX_INCLUDES()
#include "shockwaveflash.h"
//}}AFX_INCLUDES
#if !defined(AFX_SAVEPAGE_H__1AA51A4A_A4DA_417A_A385_46A6B4EA4E3B__INCLUDED_)
#define AFX_SAVEPAGE_H__1AA51A4A_A4DA_417A_A385_46A6B4EA4E3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SavePage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SavePage dialog

class SavePage : public CPropertyPage
{
	DECLARE_DYNCREATE(SavePage)

// Construction
public:
	SavePage();
	~SavePage();

// Dialog Data
	//{{AFX_DATA(SavePage)
	enum { IDD = IDD_SAVE };
	CString	m_strSavedir;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(SavePage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(SavePage)
	afx_msg void OnFind();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAVEPAGE_H__1AA51A4A_A4DA_417A_A385_46A6B4EA4E3B__INCLUDED_)
