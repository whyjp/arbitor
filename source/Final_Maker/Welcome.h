//{{AFX_INCLUDES()
#include "shockwaveflash.h"
//}}AFX_INCLUDES
#if !defined(AFX_WELCOME_H__1B61FC1F_15B6_4BE8_83A3_513FD8B3D531__INCLUDED_)
#define AFX_WELCOME_H__1B61FC1F_15B6_4BE8_83A3_513FD8B3D531__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Welcome.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Welcome dialog

class Welcome : public CPropertyPage
{
	DECLARE_DYNCREATE(Welcome)

// Construction
public:
	Welcome();
	~Welcome();
	TCHAR Path[MAX_PATH];
// Dialog Data
	//{{AFX_DATA(Welcome)
	enum { IDD = IDD_WELCOME };
	CShockwaveFlash	m_Flash;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(Welcome)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(Welcome)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WELCOME_H__1B61FC1F_15B6_4BE8_83A3_513FD8B3D531__INCLUDED_)
