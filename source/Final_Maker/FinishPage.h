//{{AFX_INCLUDES()
#include "shockwaveflash.h"
//}}AFX_INCLUDES
#if !defined(AFX_FINISHPAGE_H__8CD52CEF_B545_4AA6_8B1F_D768B44476F8__INCLUDED_)
#define AFX_FINISHPAGE_H__8CD52CEF_B545_4AA6_8B1F_D768B44476F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FinishPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// FinishPage dialog

class FinishPage : public CPropertyPage
{
	DECLARE_DYNCREATE(FinishPage)

// Construction
public:
	FinishPage();
	~FinishPage();

// Dialog Datas
	//{{AFX_DATA(FinishPage)
	enum { IDD = IDD_FINISH };
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(FinishPage)
	public:
	virtual BOOL OnWizardFinish();
	virtual BOOL OnSetActive();
	protected:
		virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(FinishPage)
	
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINISHPAGE_H__8CD52CEF_B545_4AA6_8B1F_D768B44476F8__INCLUDED_)
