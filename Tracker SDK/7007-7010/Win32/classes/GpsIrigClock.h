///////////////////////////////////////////////////////////////////////////////
// GpsIrigClock.h: pure virtual CGpsIrigClock class
//

/*******************************************************************************
 * Copyright (c) 2005 Electro-Optical Imaging, Inc. All Rights Reserved
 *
 * Electro-Optical Imaging, Inc. (E-O Imaging) licenses this software under 
 * specific terms and conditions.  Use of any of the software or derivatives
 * thereof in any product without a Electro-Optical Imaging, Inc. tracker is 
 * strictly prohibited.
 *
 * Electro-Optical Imaging, Inc. provides this software AS IS, WITHOUT ANY 
 * WARRANTY, EXPRESS OR IMPLIED, INCLUDING, WITHOUT LIMITATION, ANY WARRANTY
 * OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  E-O Imaging makes
 * no guarantee or representations regarding the use of, or the results of the
 * use of, the software and documentation in terms of correctness, accuracy,
 * reliability, currentness, or otherwise; and you rely on the software,
 * documentation and results solely at your own risk.
 *
 * IN NO EVENT SHALL E-O IMAGING BE LIABLE FOR ANY LOSS OF USE, LOSS OF BUSINESS,
 * LOSS OF PROFITS, INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES
 * OF ANY KIND.  IN NO EVENT SHALL E-O IMAGING'S TOTAL LIABILITY EXCEED THE SUM
 * PAID TO E-O IMAGING FOR THE PRODUCT LICENSED HEREUNDER.
 *
 ******************************************************************************/

#if !defined(AFX_GpsIrigClock_H__79D2E546_2431_4D20_80EF_093990A118C1__INCLUDED_)
#define AFX_GpsIrigClock_H__79D2E546_2431_4D20_80EF_093990A118C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/* for reference, this is the standard SYSTEMTIME structure

	typedef struct _SYSTEMTIME {
		WORD wYear; 
		WORD wMonth; 
		WORD wDayOfWeek; // NOT USED
		WORD wDay; 
		WORD wHour; 
		WORD wMinute; 
		WORD wSecond; 
		WORD wMilliseconds; 
	} SYSTEMTIME; 
*/

///////////////////////////////////////////////////////////////////////////////
// CGpsIrigClock
//
class CGpsIrigClock
{
protected:
	// general
	BOOL	m_bIsOpen;

public:
	BOOL	m_bEnabled;
	BOOL	m_bSyncPcTime;

	typedef enum
	{
		Acquiring = 0,
		Navigate = 1
			
	} GpsStatus;

public:
	CGpsIrigClock();
	virtual ~CGpsIrigClock();

	CGpsIrigClock(const CGpsIrigClock& Src) { ASSERT(FALSE); /*NEVER CALLED!*/}
	const CGpsIrigClock& operator=(const CGpsIrigClock& Src) { ASSERT(FALSE); return *this; }

public:
	virtual BOOL	IsOpen() { return m_bIsOpen; }
	virtual BOOL	InSync() = 0;

	// registry archive functions
	virtual BOOL	ReadFromRegistry(LPCTSTR lpszSection);
	virtual BOOL	WriteToRegistry(LPCTSTR lpszSection);

	// open and close the interface
	virtual BOOL	Open() = 0;
	virtual BOOL	Close() = 0;

	// access functions
	virtual BOOL	GetTime(SYSTEMTIME& CurrentTime) { return FALSE; } // MUST OVERRIDE THIS FUNCTION
	virtual BOOL	GetTime(CString& CurrentTime);
	virtual CString	FormatTime(const SYSTEMTIME& CurrentTime);

	virtual BOOL	GetPosition(int& latitude, int& longitude, GpsStatus& status) { return FALSE; } // MUST OVERRIDE THIS FUNCTION
	virtual BOOL	GetPosition(CString& CurrentPosition);
	virtual CString	FormatPosition(int latitude, int longitude);

	virtual BOOL	GetAltitude(double& altitude) { return FALSE; } // MUST OVERRIDE THIS FUNCTION
	virtual BOOL	GetAltitude(CString& CurrentAltitude, BOOL bShortFormat=FALSE);
	virtual CString	FormatAltitude(double altitude, BOOL bShortFormat=FALSE);

	// sync the computer's time
	virtual BOOL	SetSystemTime();
};

#endif // !defined(AFX_GpsIrigClock_H__79D2E546_2431_4D20_80EF_093990A118C1__INCLUDED_)
