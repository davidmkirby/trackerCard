///////////////////////////////////////////////////////////////////////////////
// PCIBrandywineClock.cpp - CPCIBrandywineClock class
//

/*******************************************************************************
 * Copyright (c) 2003 Electro-Optical Imaging, Inc. All Rights Reserved
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
#include "PCIBrandywineClock.h"

#include "brandywine/pci/RegDef.h"
#include "brandywine/pci/DPDef.h"
#include "brandywine/pci/GPSDef.h"

#include "..\TrkrPciApi\TrkrPciApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


///////////////////////////////////////////////////////////////////////////////
// Construction/Destruction
//
CPCIBrandywineClock::CPCIBrandywineClock()
{
	m_hPciBoard = NULL;
	m_pSharedMem = 0;

	m_bEnabled = TRUE; // PCI always enabled (smarter than VMEbus)
}

CPCIBrandywineClock::~CPCIBrandywineClock()
{
	Close();
}

//////////////////////////////////////////////////////////////////////////////
// CPCIBrandywineClock::ReadFromRegistry(LPCTSTR lpszSection)
//
// Gets the PCI settings from the registry
//
BOOL CPCIBrandywineClock::ReadFromRegistry(LPCTSTR lpszSection)
{
	// call base class
	CGpsIrigClock::ReadFromRegistry(lpszSection);

	// get our specific stuff
	CWinApp* pApp = AfxGetApp();
	if( pApp == NULL )
		return FALSE;

	m_bEnabled = TRUE; // PCI always enabled (smarter than VMEbus)

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
// CPCIBrandywineClock::WriteToRegistry(LPCTSTR lpszSection)
//
// Saves the PCI settings to the registry
//
BOOL CPCIBrandywineClock::WriteToRegistry(LPCTSTR lpszSection)
{
	// call base class
	CGpsIrigClock::WriteToRegistry(lpszSection);

	// write our specific stuff
	CWinApp* pApp = AfxGetApp();
	if( pApp == NULL )
		return FALSE;

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// CPCIBrandywineClock::Open()
//
// Opens the PCI memory interface
//
BOOL CPCIBrandywineClock::Open()
{
	// sanity
	ASSERT( !m_bIsOpen );
	if( m_bIsOpen )
		return TRUE;

	// open the board
	m_hPciBoard = GenericPciOpenBoard(0, 0x10B5, 0x9030);		// PCI board

	if( m_hPciBoard == NULL )
		m_hPciBoard = GenericPciOpenBoard(0, 0x10B5, 0x9056);	// PCIe board

	// no boards found?
	if( m_hPciBoard == NULL )
		return FALSE;

	// map the memory
	GenericPciMapMemory(m_hPciBoard, 2, (volatile unsigned long**)(&m_pSharedMem));

	ASSERT(m_pSharedMem);
	if( m_pSharedMem == NULL )
	{
		GenericPciCloseBoard(m_hPciBoard);
		m_hPciBoard = NULL;

		return FALSE;
	}

	// set the open flag
	m_bIsOpen = TRUE;

/*** DEBUG dump for Brandywine tech support
	CString strDump, strTemp;
	strDump = "Brandywine DP RAM Dump\n";

	for( int i=0x20; i <= 0x51; i++ )
	{
		if( i % 4 == 0 )
		{
			strTemp.Format("\n0x%02X: ", i);
			strDump += strTemp;
		}

		strTemp.Format("%02X ", ReadDualPortRAM(i));
		strDump += strTemp;
	}

	strDump += "\n";

	AfxMessageBox(strDump);
***/
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// CPCIBrandywineClock::Close()
//
// Close the PCI memory interface
//
BOOL CPCIBrandywineClock::Close()
{
	// check if already closed
	if( !m_bIsOpen )
		return TRUE;

	// unmap memory
	GenericPciUnMapMemory(m_hPciBoard, (volatile unsigned long*)m_pSharedMem);
	m_pSharedMem = NULL;

	// close board
	GenericPciCloseBoard(m_hPciBoard);
	m_hPciBoard = NULL;

	m_bIsOpen = FALSE;

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// CPCIBrandywineClock::InSync()
//
// Returns TRUE if the clock is in sync and the time/position is good
//
BOOL CPCIBrandywineClock::InSync()
{
	if( !m_bIsOpen )
		return FALSE;

	unsigned char status = *(volatile unsigned char*)(m_pSharedMem+Status_Port);

	return ((status & Sync_OK) != 0);
}

///////////////////////////////////////////////////////////////////////////////
// CPCIBrandywineClock::GetTime(SYSTEMTIME& CurrentTime)
//
// Get the current system time and date (as a SYSTEMTIME structure)
//
BOOL CPCIBrandywineClock::GetTime(SYSTEMTIME& CurrentTime)
{
	static WORD	leapfirstdayofmonth[13]    = {1,32,61,92,122,153,183,214,245,275,306,336,367};
	static WORD	nonleapfirstdayofmonth[13] = {1,32,60,91,121,152,182,213,244,274,305,335,366};

	// sanity
	if( !m_bIsOpen )
		return FALSE;

	// not in sync?
//	if( !InSync() )
//		return FALSE;

	// get the Brandywine time
	unsigned long timelo = *(volatile unsigned long*)(m_pSharedMem+Sec10_Usec1_Port);
	unsigned long timehi = *(volatile unsigned long*)(m_pSharedMem+Year1_Min1_Port);

	// get system time from operating system
	::GetSystemTime(&CurrentTime);

	// make sure the current year is set in the Brandywine board
	WORD year = CurrentTime.wYear;
	if( (timehi&0xf0000000) != ((((unsigned long)(year%10))<<28)&0xf0000000) )
	{
		TRACE("Setting Brandywine board year to %d\n", year);

		// set the year in the Brandywine board
		WORD yearofcenturybin = year % 100;
		unsigned char yearofcenturybcd = ((yearofcenturybin/10)*16) + yearofcenturybin%10;
		
		WORD centurybin= year / 100;
		unsigned char centurybcd = ((centurybin/10)*16) + centurybin%10;

		SetDualPortRAM(DP_Year10Year1, yearofcenturybcd);
		SetDualPortRAM(DP_Year1000Year100, centurybcd);
		SetDualPortRAM(DP_Command, Command_Set_Years);

		return FALSE;
	}

	WORD bcddays= (WORD)((timehi&0x0fff0000)>>16);
	WORD bindays= (WORD)((((bcddays&0x0f00)>>8)*100) + (((bcddays&0x0f0)>>4)*10) + (bcddays&0x0f));

	WORD bcdhours= (WORD)((timehi&0x0000ff00)>>8);
	WORD binhours= (((bcdhours&0x0f0)>>4)*10)+(bcdhours&0x0f);

	WORD bcdminutes= (WORD)(timehi&0x000000ff);
	WORD binminutes= (((bcdminutes&0x0f0)>>4)*10) +(bcdminutes&0x0f);

	WORD bcdseconds= (WORD)((timelo&0xff000000)>>24);
	WORD binseconds= (((bcdseconds&0x0f0)>>4)*10) + (bcdseconds&0x0f);

	WORD bcdmilliseconds= (WORD)((timelo&0x00fff000)>>12);
	WORD binmilliseconds= (((bcdmilliseconds&0x0f00)>>8)*100) +
						  (((bcdmilliseconds&0x0f0)>>4)*10) + (bcdmilliseconds&0x0f);
	
	WORD binmonth=0;
	WORD firstdayofmonth = 1;

	BOOL IsLeapYear = (((year % 4) == 0) && (((year % 100) != 0) || ((year % 400) == 0))) ? TRUE : FALSE;

	if( IsLeapYear )
	{
		do
		{
			firstdayofmonth = leapfirstdayofmonth[binmonth];
			binmonth++;

		} while( bindays >= leapfirstdayofmonth[binmonth] );
	}
	else
	{
		do
		{
			firstdayofmonth = nonleapfirstdayofmonth[binmonth];
			binmonth++;

		} while( bindays >= nonleapfirstdayofmonth[binmonth] );
	}

	CurrentTime.wMonth = binmonth;
	CurrentTime.wDay = bindays-firstdayofmonth+1;
	CurrentTime.wHour = binhours;
	CurrentTime.wMinute = binminutes;
	CurrentTime.wSecond = binseconds;
	CurrentTime.wMilliseconds = binmilliseconds;

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// CPCIBrandywineClock::GetPosition(int& latitude, int& longitude, GpsStatus& status)
//
// Get the current GPS position
//
BOOL CPCIBrandywineClock::GetPosition(int& latitude, int& longitude, GpsStatus& status)
{
	// sanity
	if( !m_bIsOpen )
		return FALSE;

	// not in sync?
//	if( !InSync() )
//		return FALSE;

	int statreg = ReadDualPortRAM(DP_GPS_Status);

	if( statreg & DP_GPS_Status_Nav)
		status = Navigate;
	else
		status = Acquiring;

	// read latitude
	latitude = ReadDualPortRAM(DP_GPS_Latbin0700);
	latitude |= ReadDualPortRAM(DP_GPS_Latbin1508) << 8;
	latitude |= ReadDualPortRAM(DP_GPS_Latbin2316) << 16;
	latitude |= ReadDualPortRAM(DP_GPS_Latbin3124) << 24;

	// read longitude
	longitude = ReadDualPortRAM(DP_GPS_Lonbin0700);
	longitude |= ReadDualPortRAM(DP_GPS_Lonbin1508) << 8;
	longitude |= ReadDualPortRAM(DP_GPS_Lonbin2316) << 16;
	longitude |= ReadDualPortRAM(DP_GPS_Lonbin3124) << 24;

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// CPCIBrandywineClock::GetAltitude()
//
// Get the altitude above geoid in meters (centimeter resolution)
//
BOOL CPCIBrandywineClock::GetAltitude(double& altitude)
{
	// sanity
	if( !m_bIsOpen )
		return FALSE;

	// not in sync?
//	if( !InSync() )
//		return FALSE;

	// read altitude
	int altbin = ReadDualPortRAM(DP_GPS_Altbin0700);
	altbin |= ReadDualPortRAM(DP_GPS_Altbin1508) << 8;
	altbin |= ReadDualPortRAM(DP_GPS_Altbin2316) << 16;
	altbin |= ReadDualPortRAM(DP_GPS_Altbin3124) << 24;

	altitude = (double)altbin / 100.0;

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// CPCIBrandywineClock::WaitForResponse()
//
// Waits until a response is available on the dual port RAM
// returns FALSE on timeout
//
BOOL CPCIBrandywineClock::WaitForResponse()
{
	// wait until ready
	for( int i=0; i < 10000; i++ )
	{
		unsigned char status = *(volatile unsigned char*)(m_pSharedMem+Status_Port);

		if( (status & Response_Ready) != 0 )
			return TRUE;
	}

	// timeout!
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// CPCIBrandywineClock::ReadDualPortRAM(unsigned char address)
//
// Read from the dual port RAM on the board
// returns -1 if there is an error
//
int CPCIBrandywineClock::ReadDualPortRAM(unsigned char address)
{
	unsigned char response;

	// set dual port address
	*(volatile unsigned char*)(m_pSharedMem+Dual_Port_Address_Port) = address;

	// wait until ready
	response = *(volatile unsigned char*)(m_pSharedMem+Status_Port); // short delay for data read
	response = *(volatile unsigned char*)(m_pSharedMem+Status_Port); // doing DMA inside PCI-SYNCCLOCK

	// read response data
	response = *(volatile unsigned char*)(m_pSharedMem+Dual_Port_Data_Port);

	return (int)response;
}

///////////////////////////////////////////////////////////////////////////////
// CPCIBrandywineClock::SetDualPortRAM(unsigned char address, unsigned char value)
//
// Sets the dual port RAM on the board to the value specified
// returns -1 if there is an error
//
int CPCIBrandywineClock::SetDualPortRAM(unsigned char address, unsigned char value)
{
	unsigned char response;

	// set dual port address
	*(volatile unsigned char*)(m_pSharedMem+Dual_Port_Address_Port) = address;

	// wait until ready
	response = *(volatile unsigned char*)(m_pSharedMem+Status_Port); // short delay for data read
	response = *(volatile unsigned char*)(m_pSharedMem+Status_Port); // doing DMA inside PCI-SYNCCLOCK
	response = *(volatile unsigned char*)(m_pSharedMem+Status_Port); // doing DMA inside PCI-SYNCCLOCK

	// set data
	*(volatile unsigned char*)(m_pSharedMem+Dual_Port_Data_Port) = value;

	// wait until ready
	response = *(volatile unsigned char*)(m_pSharedMem+Status_Port); // short delay for data write
	response = *(volatile unsigned char*)(m_pSharedMem+Status_Port); // doing DMA inside PCI-SYNCCLOCK
	response = *(volatile unsigned char*)(m_pSharedMem+Status_Port); // doing DMA inside PCI-SYNCCLOCK

	return (int)response;
}
