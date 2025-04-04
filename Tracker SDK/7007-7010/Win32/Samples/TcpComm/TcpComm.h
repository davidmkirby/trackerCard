// TcpComm.h : main header file for the TcpComm application
//

#if !defined(AFX_TCPCOMM_H__F2ABE182_6ABF_4768_9E63_2646685FEB70__INCLUDED_)
#define AFX_TCPCOMM_H__F2ABE182_6ABF_4768_9E63_2646685FEB70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTcpCommApp:
// See TcpComm.cpp for the implementation of this class
//

class CTcpCommApp : public CWinApp
{
public:
	CTcpCommApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTcpCommApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTcpCommApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TCPCOMM_H__F2ABE182_6ABF_4768_9E63_2646685FEB70__INCLUDED_)
