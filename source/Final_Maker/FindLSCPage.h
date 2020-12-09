//{{AFX_INCLUDES()
#include "shockwaveflash.h"
//}}AFX_INCLUDES
#if !defined(AFX_FINDLSCPAGE_H__0FD2A4C7_FE9C_4A0F_A0CA_A1E187010274__INCLUDED_)
#define AFX_FINDLSCPAGE_H__0FD2A4C7_FE9C_4A0F_A0CA_A1E187010274__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FindLSCPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// FindLSCPage dialog

class FindLSCPage : public CPropertyPage
{
	DECLARE_DYNCREATE(FindLSCPage)

// Construction
public:
	FindLSCPage();
	~FindLSCPage();

// Dialog Data
	//{{AFX_DATA(FindLSCPage)
	enum { IDD = IDD_FINDLSC };
	CString	m_strLSCDir;
	CString	m_strIcon;
	CString	m_strVer;
	CString	m_strUIcon;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(FindLSCPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(FindLSCPage)
	afx_msg void OnFind();
	afx_msg void OnFind2();
	afx_msg void OnFind4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDLSCPAGE_H__0FD2A4C7_FE9C_4A0F_A0CA_A1E187010274__INCLUDED_)
