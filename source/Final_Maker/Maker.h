// Maker.h : main header file for the MAKER application
//

#if !defined(AFX_MAKER_H__633AD4C9_0D34_41A3_8072_B3D5A303D440__INCLUDED_)
#define AFX_MAKER_H__633AD4C9_0D34_41A3_8072_B3D5A303D440__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMakerApp:
// See Maker.cpp for the implementation of this class
//


class CMakerApp : public CWinApp
{
public:
	CMakerApp();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMakerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMakerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAKER_H__633AD4C9_0D34_41A3_8072_B3D5A303D440__INCLUDED_)
