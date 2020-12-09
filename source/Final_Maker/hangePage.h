//{{AFX_INCLUDES()
#include "shockwaveflash.h"
//}}AFX_INCLUDES
#if !defined(AFX_HANGEPAGE_H__B260F1D5_341A_47E9_AD79_98F414F23E9B__INCLUDED_)
#define AFX_HANGEPAGE_H__B260F1D5_341A_47E9_AD79_98F414F23E9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// hangePage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ChangePage dialog

class ChangePage : public CPropertyPage
{
	DECLARE_DYNCREATE(ChangePage)

// Construction
public:
	ChangePage();
	~ChangePage();

// Dialog Data
	//{{AFX_DATA(ChangePage)
	enum { IDD = IDD_CHANGE };
	CString	m_strSetupName;
	CString	m_strCoName;
	CString	m_strSave;
	CString	m_strProName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(ChangePage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(ChangePage)
	afx_msg void OnFind2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HANGEPAGE_H__B260F1D5_341A_47E9_AD79_98F414F23E9B__INCLUDED_)
