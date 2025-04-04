///////////////////////////////////////////////////////////////////////////////
// GpsIrigClock.cpp - pure virtual CGpsIrigClock class
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

#include "stdafx.h"
#include "GpsIrigClock.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


///////////////////////////////////////////////////////////////////////////////
// Construction/Destruction
//
CGpsIrigClock::CGpsIrigClock()
{
	m_bIsOpen = FALSE;
	m_bEnabled = FALSE;
	m_bSyncPcTime = TRUE;
}

CGpsIrigClock::~CGpsIrigClock()
{
}

//////////////////////////////////////////////////////////////////////////////
// CGpsIrigClock::ReadFromRegistry(LPCTSTR lpszSection)
//
// Gets the settings from the registry
//
BOOL CGpsIrigClock::ReadFromRegistry(LPCTSTR lpszSection)
{
	CWinApp* pApp = AfxGetApp();
	if( pApp == NULL )
		return FALSE;

	m_bEnabled = pApp->GetProfileInt(lpszSection, "Enabled", FALSE);
	m_bSyncPcTime = pApp->GetProfileInt(lpszSection, "Sync PC Time", TRUE);

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
// CGpsIrigClock::WriteToRegistry(LPCTSTR lpszSection)
//
// Saves the settings to the registry
//
BOOL CGpsIrigClock::WriteToRegistry(LPCTSTR lpszSection)
{
	CWinApp* pApp = AfxGetApp();
	if( pApp == NULL )
		return FALSE;

	pApp->WriteProfileInt(lpszSection, "Enabled", m_bEnabled);
	pApp->WriteProfileInt(lpszSection, "Sync PC Time", m_bSyncPcTime);

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
// CGpsIrigClock::GetTime(CString& CurrentTime)
//
// Returns a formated string for the current time
//
BOOL CGpsIrigClock::GetTime(CString& CurrentTime)
{
	SYSTEMTIME sysTime;
	if( !GetTime(sysTime) )
		return FALSE;

	CurrentTime = FormatTime(sysTime);

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
// CGpsIrigClock::FormatTime(const SYSTEMTIME& CurrentTime)
//
// Returns a formated string for the given time
//
CString	CGpsIrigClock::FormatTime(const SYSTEMTIME& CurrentTime)
{
	CString strTime;

	// format hour:minute:second.msec
	strTime.Format("%02d:%02d:%02d.%03d", CurrentTime.wHour, CurrentTime.wMinute,
					CurrentTime.wSecond, CurrentTime.wMilliseconds);

	return strTime;
}

//////////////////////////////////////////////////////////////////////////////
// CGpsIrigClock::GetPosition(CString& CurrentPosition)
//
// Returns a formated string for the current position
//
BOOL CGpsIrigClock::GetPosition(CString& CurrentPosition)
{
	int latitude, longitude;
	CGpsIrigClock::GpsStatus status;

	if( !GetPosition(latitude, longitude, status) )
		return FALSE;

	CurrentPosition = FormatPosition(latitude, longitude);

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
// CGpsIrigClock::FormatPosition(int latitude, int longitude)
//
// Returns the current GPS position
//
CString	CGpsIrigClock::FormatPosition(int latitude, int longitude)
{
/*	char NA;
	if( status == Navigate )
		NA = 'N';
	else
		NA = 'A';
*/
	// format latitude
	char NS;
	if( latitude < 0 )
	{
		NS = 'S';
		latitude = -latitude;
	}
	else
		NS = 'N';

	int latdeg = latitude / (60*60*1000);
	int latmin = latitude % (60*60*1000) / (60*1000);
	int latsec = (latitude/1000) % 60;
	int latmsec = latitude % 1000;

	// format longitude
	char EW;
	if( longitude < 0 )
	{
		EW = 'W';
		longitude = -longitude;
	}
	else
		EW = 'E';

	int londeg = longitude / (60*60*1000);
	int lonmin = longitude % (60*60*1000) / (60*1000);
	int lonsec = (longitude/1000) % 60;
	int lonmsec = longitude % 1000;

	CString strPosition;

	strPosition.Format("%c%03d %02d'%02d.%03d\"  %c%03d %02d'%02d.%03d\"",
						NS,latdeg,latmin,latsec,latmsec,
						EW,londeg,lonmin,lonsec,lonmsec);

	return strPosition;
}

//////////////////////////////////////////////////////////////////////////////
// CGpsIrigClock::GetAltitude(CString& CurrentAltitude, BOOL bShortFormat=FALSE)
//
// Returns a formated string for the given altitude
//
BOOL CGpsIrigClock::GetAltitude(CString& CurrentAltitude, BOOL bShortFormat)
{
	double altitude;

	if( !GetAltitude(altitude) )
		return FALSE;

	CurrentAltitude = FormatAltitude(altitude, bShortFormat);

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
// CGpsIrigClock::FormatAltitude(double altitude, BOOL bShortFormat=FALSE)
//
// Returns a formated string for the given altitude
//
CString CGpsIrigClock::FormatAltitude(double altitude, BOOL bShortFormat)
{
	CString strAltitude;

	if( bShortFormat )
		strAltitude.Format("%0.2fm", altitude);
	else
		strAltitude.Format("%0.2f meters", altitude);

	return strAltitude;
}

//////////////////////////////////////////////////////////////////////////////
// BOOL CGpsIrigClock::SetSystemTime()
//
// Sync the computer's time to the GPS/IRIG time
//
BOOL CGpsIrigClock::SetSystemTime()
{
	if( !InSync() )
		return FALSE;

	SYSTEMTIME curTime;
	if( GetTime(curTime) )
		return ::SetSystemTime(&curTime);

	return FALSE;
}
