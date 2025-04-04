// TimeStamp.h: interface for the CTimeStamp class.
//

/*******************************************************************************
 * Copyright (c) 2006 Electro-Optical Imaging, Inc. All Rights Reserved
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

#if !defined(AFX_TIMESTAMP_H__DAF55505_BB60_4826_BA80_C2C3C0A7CC4A__INCLUDED_)
#define AFX_TIMESTAMP_H__DAF55505_BB60_4826_BA80_C2C3C0A7CC4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GpsIrigClock.h"

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
// CTimeStamp
//
class CTimeStamp  
{
public:
	typedef enum
	{
		Invalid = -1,
		PCTime = 0,
		IrigTime = 1
	} TimeSource;

protected:
	static CGpsIrigClock*	m_pGpsIrigClock;	// static pointer to time source

	SYSTEMTIME				m_TimeStamp;
	TimeSource				m_TimeSource;

public:
	CTimeStamp(BOOL bSetNow=FALSE);
	CTimeStamp(const CTimeStamp& src) { Copy(src); }
	virtual ~CTimeStamp();

	CTimeStamp& Copy(const CTimeStamp& src);
	CTimeStamp& operator=(const CTimeStamp& src) { return Copy(src); }

	BOOL IsEqual(const CTimeStamp& ts2) const;

public:
	static void			SetGpsIrigClock(CGpsIrigClock* pGpsIrigClock) { m_pGpsIrigClock = pGpsIrigClock; }

	BOOL				IsValid() const { return (m_TimeSource != Invalid) ? TRUE : FALSE; }
	void				Clear() { m_TimeSource = Invalid; memset(&m_TimeStamp, 0, sizeof(m_TimeStamp)); }

	TimeSource			GetTimeSource() const { return m_TimeSource; }

	// set time functions
	void				SetTimeStamp();
	void				SetTimeStamp(double timet, TimeSource source=IrigTime);
	void				SetTimeStamp(const char* pTimeStr, TimeSource source=IrigTime);

	// get time functions
	const SYSTEMTIME&	GetTimeStamp() const { return m_TimeStamp; }
	double				GetAsVariantTime() const;
	double				GetAsTimet() const;

	// time string formatting
	CString				GetTimeString(BOOL bNoMilliseconds=FALSE, char seperator=':') const;
	CString				GetDateString(BOOL bYearFirst=TRUE, char seperator='-') const;
	CString				GetAlphaDateString() const;
};

BOOL operator ==(const CTimeStamp& ts1, const CTimeStamp& ts2);

#endif // !defined(AFX_TIMESTAMP_H__DAF55505_BB60_4826_BA80_C2C3C0A7CC4A__INCLUDED_)
