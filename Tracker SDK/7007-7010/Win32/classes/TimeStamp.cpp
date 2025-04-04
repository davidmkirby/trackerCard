// TimeStamp.cpp: implementation of the CTimeStamp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TimeStamp.h"

CGpsIrigClock*	CTimeStamp::m_pGpsIrigClock = NULL;

static const char strMonths[13][4] =
{
	"", "Jan", "Feb", "Mar", "Apr", "May", "Jun",
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};
	
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTimeStamp::CTimeStamp(BOOL bSetNow)
{
	if( bSetNow )
		SetTimeStamp();
	else
		Clear();
}

CTimeStamp::~CTimeStamp()
{
}

CTimeStamp& CTimeStamp::Copy(const CTimeStamp& src)
{
	m_TimeSource = src.m_TimeSource;
	memcpy(&m_TimeStamp, &src.m_TimeStamp, sizeof(m_TimeStamp));

	return *this;
}

///////////////////////////////////////////////////////////////////////////////
// CTimeStamp::IsEqual(const CTimeStamp& ts2) const
//
// Compare this time stamp to another
//
BOOL CTimeStamp::IsEqual(const CTimeStamp& ts2) const
{
	// compare the data of the two time stamps
	if( memcmp(&m_TimeStamp, &ts2.m_TimeStamp, sizeof(m_TimeStamp)) == 0 )
		return TRUE;

	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// operator ==(const CTimeStamp& ts1, const CTimeStamp& ts2)
//
// Compare one message to another message
//
BOOL operator ==(const CTimeStamp& ts1, const CTimeStamp& ts2)
{
	return ts1.IsEqual(ts2);
}

//////////////////////////////////////////////////////////////////////////////
// CTimeStamp::SetTimeStamp()
//
// Set the time stamp to the current time
//
void CTimeStamp::SetTimeStamp()
{
	if( m_pGpsIrigClock != NULL )
	{
		if( m_pGpsIrigClock->GetTime(m_TimeStamp) )
		{
			// got IRIG time
			m_TimeSource = IrigTime;
			return;
		}
	}

	// use PC clock	(if nothing else is available)
	::GetSystemTime(&m_TimeStamp);
	m_TimeSource = PCTime;
}

//////////////////////////////////////////////////////////////////////////////
// CTimeStamp::SetTimeStamp(double timet, TimeSource source=IrigTime)
//
// Set from time_t value including sub-seconds
//
void CTimeStamp::SetTimeStamp(double timet, TimeSource source)
{
	ASSERT(timet >= 0);

	double milliseconds = (timet - ((long)timet)) * 1000;

	time_t inTime = (time_t)timet;

	struct tm* ptm = gmtime(&inTime);
	ASSERT(ptm);

	m_TimeStamp.wYear = (WORD) (1900 + ptm->tm_year);
	m_TimeStamp.wMonth = (WORD) (1 + ptm->tm_mon);
	m_TimeStamp.wDayOfWeek = (WORD) ptm->tm_wday;
	m_TimeStamp.wDay = (WORD) ptm->tm_mday;
	m_TimeStamp.wHour = (WORD) ptm->tm_hour;
	m_TimeStamp.wMinute = (WORD) ptm->tm_min;
	m_TimeStamp.wSecond = (WORD) ptm->tm_sec;
	m_TimeStamp.wMilliseconds = (WORD)milliseconds;

	m_TimeSource = source;
}

//////////////////////////////////////////////////////////////////////////////
// CTimeStamp::SetTimeStamp(const char* pTimeStr, TimeSource source=IrigTime)
//
// Set from IRIG time string in the format
// "%02d%c%02d%c%02d.%03d" as "hour:minute:second.msec" 
//
void CTimeStamp::SetTimeStamp(const char* pTimeStr, TimeSource source)
{
	// use built-in clock to get year/month/day info
	SetTimeStamp();

	char tmpStr[4];
	memset(tmpStr, 0, sizeof(tmpStr));

	// hour
	tmpStr[0] = pTimeStr[0];
	tmpStr[1] = pTimeStr[1];
	tmpStr[2] = '\0';

	m_TimeStamp.wHour = (WORD) atoi(tmpStr);

	// minute
	tmpStr[0] = pTimeStr[3];
	tmpStr[1] = pTimeStr[4];
	tmpStr[2] = '\0';

	m_TimeStamp.wMinute = (WORD) atoi(tmpStr);

	// second
	tmpStr[0] = pTimeStr[6];
	tmpStr[1] = pTimeStr[7];
	tmpStr[2] = '\0';

	m_TimeStamp.wSecond = (WORD) atoi(tmpStr);

	// millisecond
	if( pTimeStr[8] == '.' )
	{
		tmpStr[0] = pTimeStr[9];
		tmpStr[1] = pTimeStr[10];
		tmpStr[2] = pTimeStr[11];
		tmpStr[3] = '\0';

		m_TimeStamp.wMilliseconds = (WORD) atoi(tmpStr);
	}
	else
		m_TimeStamp.wMilliseconds = 0;

	m_TimeSource = source;
}

//////////////////////////////////////////////////////////////////////////////
// CTimeStamp::GetAsVariantTime() const
//
// Get the time as a variant time in seconds
//
// A variant time is stored as an 8-byte real value (double), representing a
// date between January 1, 100 and December 31, 9999, inclusive. The value 2.0
// represents January 1, 1900; 3.0 represents January 2, 1900, and so on. Adding 1
// to the value increments the date by a day. The fractional part of the value
// represents the time of day. Therefore, 2.5 represents noon on January 1, 1900;
// 3.25 represents 6:00 A.M. on January 2, 1900, and so on. Negative numbers
// represent dates prior to December 30, 1899.  However, this function uses
// -1 as an error condition on return.
// 1 second = 0.5/(12*60*60) = .0000115740740740
//
double CTimeStamp::GetAsVariantTime() const
{
	SYSTEMTIME timestamp = m_TimeStamp;

	// zero milliseconds before function call
	timestamp.wMilliseconds = 0;

	double variantTime;

	// get variant time
	if( SystemTimeToVariantTime(&timestamp, &variantTime) == 0 )
	{
		// failed, so exit
		return -1;
	}

	// add in milliseconds
	double OneMilliSecond = (0.5 / (12*60*60)) / 1000.0;

	variantTime += OneMilliSecond * m_TimeStamp.wMilliseconds;

	return variantTime;
}

//////////////////////////////////////////////////////////////////////////////
// CTimeStamp::GetAsTimet()
//
// Get the current UTC time in the time_t form (including sub-seconds)
//
double CTimeStamp::GetAsTimet() const
{
	struct tm atm;
	atm.tm_sec = m_TimeStamp.wSecond;
	atm.tm_min = m_TimeStamp.wMinute;
	atm.tm_hour = m_TimeStamp.wHour;
	atm.tm_mday = m_TimeStamp.wDay;
	atm.tm_mon = m_TimeStamp.wMonth - 1;        // tm_mon is 0 based
	atm.tm_year = m_TimeStamp.wYear - 1900;     // tm_year is 1900 based
	atm.tm_isdst = 0;

	// get computer's UTC time_t seconds
	double seconds = (double)_mkgmtime(&atm);

	// add milliseconds
	seconds += (double)m_TimeStamp.wMilliseconds / 1000.0;

	return seconds;
}

//////////////////////////////////////////////////////////////////////////////
// CTimeStamp::GetTimeString(BOOL bNoMilliseconds=FALSE, char seperator=':') const
//
// Returns a formatted time string
//
CString	CTimeStamp::GetTimeString(BOOL bNoMilliseconds, char seperator) const
{
	CString strTime;

	if( m_TimeSource == Invalid )
	{
		strTime = "INVALID";
	}
	else if( bNoMilliseconds )
	{
		// format hour:minute:second (skip milliseconds)
		strTime.Format("%02d%c%02d%c%02d", m_TimeStamp.wHour, seperator, m_TimeStamp.wMinute,
						seperator, m_TimeStamp.wSecond);
	}
	else
	{
		// format hour:minute:second.msec
		strTime.Format("%02d%c%02d%c%02d.%03d", m_TimeStamp.wHour, seperator, m_TimeStamp.wMinute,
						seperator, m_TimeStamp.wSecond, m_TimeStamp.wMilliseconds);
	}

	return strTime;
}

//////////////////////////////////////////////////////////////////////////////
// CTimeStamp::GetDateString(BOOL bYearFirst=TRUE, char seperator='-') const
//
// Returns a formatted date string
//
CString	CTimeStamp::GetDateString(BOOL bYearFirst, char seperator) const
{
	CString strDate;

	if( bYearFirst )
	{
		// format date as: year-month-day
		strDate.Format("%04d%c%02d%c%02d", m_TimeStamp.wYear, seperator, m_TimeStamp.wMonth, 
						seperator, m_TimeStamp.wDay);
	}
	else
	{
		// format date as: day-month-year
		strDate.Format("%02d%c%02d%c%04d", m_TimeStamp.wDay, seperator, m_TimeStamp.wMonth, 
						seperator, m_TimeStamp.wYear);
	}

	return strDate;
}

//////////////////////////////////////////////////////////////////////////////
// CTimeStamp::GetAlphaDateString() const
//
// Returns a formatted date string
//
CString	CTimeStamp::GetAlphaDateString() const
{
	CString strDate;
	strDate.Format("%02d%s%04d", m_TimeStamp.wDay, strMonths[m_TimeStamp.wMonth], m_TimeStamp.wYear);
	return strDate;
}
