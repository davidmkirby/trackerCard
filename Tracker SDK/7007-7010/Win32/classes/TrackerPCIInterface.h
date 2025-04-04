///////////////////////////////////////////////////////////////////////////////
// TrackerPCIInterface.h - CTrackerPCIInterface class header file
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

#if !defined(AFX_TrackerPCIInterface_H__BB280D53_1B1D_11D1_BAAE_000000000000__INCLUDED_)
#define AFX_TrackerPCIInterface_H__BB280D53_1B1D_11D1_BAAE_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TrackerInterface.h"

#define WM_TRACKER_PCI	(WM_USER + 100 + 89)


///////////////////////////////////////////////////////////////////////////////
// CTrackerPCIInterface
//
class CTrackerPCIInterface : public CTrackerInterface
{
	friend UINT BeginInputThread(LPVOID pParm);
	friend UINT BeginOutputThread(LPVOID pParm);


protected:
	// general
	HANDLE						m_hPciBoard;
	volatile unsigned short*	m_pSharedMem;
	HANDLE						m_hInterruptEvent;
	BOOL						m_bInterruptEventReady;

public:
	int							m_BoardNumber;

protected:
	virtual	void DoNotify(int event=0);

	virtual BOOL AddIncomingMessageToQueue(CTrackerMessage& message);
	virtual BOOL ReceiveMessage(CTrackerMessage& message);
	virtual BOOL ReceiveResponseMessage(CTrackerMessage& message);

	virtual void InputThread();
	virtual void OutputThread();

public:
	CTrackerPCIInterface();
	virtual ~CTrackerPCIInterface();

	CTrackerPCIInterface(const CTrackerPCIInterface& Src) { ASSERT(FALSE); /*NEVER CALLED!*/}
	const CTrackerPCIInterface& operator=(const CTrackerPCIInterface& Src) { ASSERT(FALSE); return *this; }

	// PCI API access functions
	int		GetNumberOfBoards();	// number of boards detected on bus
	double	GetFrameTimer();		// in milliseconds since vertical sync

	// access to fast user strings
	BOOL	SetSMUserString(int nIndex, SM_USER_STRING_MSG* pSMUserString = NULL);

	// access to mount performance data
	BOOL	GetSMMountPerformanceData(SM_MOUNT_PERFORMANCE_DATA* pData = NULL);

	// registry archive functions
	BOOL	ReadFromRegistry(LPCTSTR lpszSection);
	BOOL	WriteToRegistry(LPCTSTR lpszSection);

	// open and close the interface
	BOOL	Open();
	BOOL	Close();

	// polling thread start/stop functions
	BOOL	Start();
	BOOL	Stop();
};

#endif // !defined(AFX_TrackerPCIInterface_H__BB280D53_1B1D_11D1_BAAE_000000000000__INCLUDED_)
