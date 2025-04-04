// Callback.h : main header file for the CALLBACK application
//

#if !defined(AFX_CALLBACK_H__F2ABE182_6ABF_4768_9E63_2646685FEB70__INCLUDED_)
#define AFX_CALLBACK_H__F2ABE182_6ABF_4768_9E63_2646685FEB70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCallbackApp:
// See Callback.cpp for the implementation of this class
//

class CCallbackApp : public CWinApp
{
public:
	CCallbackApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCallbackApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCallbackApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALLBACK_H__F2ABE182_6ABF_4768_9E63_2646685FEB70__INCLUDED_)
