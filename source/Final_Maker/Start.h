//{{AFX_INCLUDES()
#include "shockwaveflash.h"
//}}AFX_INCLUDES
#if !defined(AFX_START_H__0E0D191D_F5DA_4AC1_A4F5_A95B1AA81C3D__INCLUDED_)
#define AFX_START_H__0E0D191D_F5DA_4AC1_A4F5_A95B1AA81C3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Start.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Start dialog

class Start : public CPropertyPage
{
	DECLARE_DYNCREATE(Start)

// Construction
public:
	Start();
	~Start();

// Dialog Data
	//{{AFX_DATA(Start)
	enum { IDD = IDD_START };
	BOOL	m_Bcheck;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(Start)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(Start)
	afx_msg void OnOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_START_H__0E0D191D_F5DA_4AC1_A4F5_A95B1AA81C3D__INCLUDED_)
