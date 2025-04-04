// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__1EE742F2_0F8F_4BD8_B264_6C8A221E1062__INCLUDED_)
#define AFX_STDAFX_H__1EE742F2_0F8F_4BD8_B264_6C8A221E1062__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN			// Exclude rarely-used stuff from Windows headers
#endif

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.

// NOTE: CHOOSE THE LOWEST LEVELS FOR MAX COMPATIBILITY (IE-LESS FUNCTIONALITY)
#ifndef WINVER					// Allow use of features specific to Windows 95/NT or later.
#define WINVER 0x0400
#endif

#ifndef _WIN32_WINNT			// Allow use of features specific to Windows NT or later.                   
#define _WIN32_WINNT 0x0400
#endif						

//#ifndef _WIN32_WINDOWS			// Allow use of features specific to Windows 95 or later.
//#define _WIN32_WINDOWS 0x0400
//#endif

#ifndef _WIN32_IE				// Allow use of features specific to IE 5.0 or later.
#define _WIN32_IE 0x0500
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

#define _AFX_ALL_WARNINGS		// turns off MFC's hiding of some common and often safely ignored warning messages


//
//  These two defines to remove warnings due to port from Visual C++ 6.0 to Visual Studio 2005
//
#define _CRT_SECURE_NO_DEPRECATE					// Ok to use old less secure CRT functions (printf, etc...)
#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1	// automatically change older functions (strcpy to strcpy_s, etc...)


#include <afxwin.h>				// MFC core and standard components
#include <afxext.h>				// MFC extensions
#include <afxdisp.h>			// MFC Automation classes

#include <afxpriv.h>
#include <afxmt.h>				// Multi-threaded support
#include <winsock2.h>			// Winsock 2 (needed for old VC++ 6.0)
#include <afxsock.h>			// Windows sockets support

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>			// MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>				// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


#include "../../classes/TrackerTcpInterface.h"
#include "../../classes/MSG_FMT.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__1EE742F2_0F8F_4BD8_B264_6C8A221E1062__INCLUDED_)
