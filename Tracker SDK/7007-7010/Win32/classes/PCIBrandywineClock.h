///////////////////////////////////////////////////////////////////////////////
// PCIBrandywineClock.h: interface for the CPCIBrandywineClock class.
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

#if !defined(AFX_PCIBrandywineClock_H__79D2E546_2431_4D20_80EF_093990A118C1__INCLUDED_)
#define AFX_PCIBrandywineClock_H__79D2E546_2431_4D20_80EF_093990A118C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GpsIrigClock.h"

///////////////////////////////////////////////////////////////////////////////
// CPCIBrandywineClock
//
class CPCIBrandywineClock : public CGpsIrigClock
{
protected:
	// general
	HANDLE						m_hPciBoard;
	unsigned long				m_pSharedMem;

protected:
	BOOL	WaitForResponse();
	int		ReadDualPortRAM(unsigned char address);
	int		SetDualPortRAM(unsigned char address, unsigned char value);

public:
	CPCIBrandywineClock();
	virtual ~CPCIBrandywineClock();

	CPCIBrandywineClock(const CPCIBrandywineClock& Src) { ASSERT(FALSE); /*NEVER CALLED!*/}
	const CPCIBrandywineClock& operator=(const CPCIBrandywineClock& Src) { ASSERT(FALSE); return *this; }

public:
	BOOL	InSync();

	// registry archive functions
	BOOL	ReadFromRegistry(LPCTSTR lpszSection);
	BOOL	WriteToRegistry(LPCTSTR lpszSection);

	// open and close the interface
	BOOL	Open();
	BOOL	Close();

	// access functions
	BOOL	GetTime(SYSTEMTIME& CurrentTime);
	BOOL	GetPosition(int& latitude, int& longitude, GpsStatus& status);
	BOOL	GetAltitude(double& altitude);
};

#endif // !defined(AFX_PCIBrandywineClock_H__79D2E546_2431_4D20_80EF_093990A118C1__INCLUDED_)
