///////////////////////////////////////////////////////////////////////////////
// TrackerTcpInterface.h - CTrackerTcpInterface class header file
//

/*******************************************************************************
* Copyright (c) 2008 Electro-Optical Imaging, Inc. All Rights Reserved
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

#pragma once

#include "TrackerInterface.h"
#include "SocMFC.h"

#define WM_TRACKER_TCP	(WM_USER + 100 + 90)


///////////////////////////////////////////////////////////////////////////////
// CTrackerTcpInterface
//
class CTrackerTcpInterface : public CTrackerInterface
{
	friend UINT BeginInputThread(LPVOID pParm);
	friend UINT BeginOutputThread(LPVOID pParm);

protected:
	// general
	CWSocket		m_Socket;
	BOOL			m_bConnected;

	CEvent			m_AckEvent;

	// emulate bus level shared memory user strings
	SM_USER_STRING_MSG	m_SMUserStrings[4];

public:
	// general
	CString			m_HostAddress;
	UINT			m_HostPort;

	BOOL			m_bWaitForAck;

protected:
	virtual	void DoNotify(int event=0);

	BOOL	ConnectSocket();
	USHORT	SyncToMessage();
	virtual BOOL ReceiveMessage(CTrackerMessage& message);

	virtual void InputThread();
	virtual void OutputThread();

public:
	CTrackerTcpInterface(void);
	virtual ~CTrackerTcpInterface(void);

	CTrackerTcpInterface(const CTrackerTcpInterface& Src) { ASSERT(FALSE); /*NEVER CALLED!*/}
	const CTrackerTcpInterface& operator=(const CTrackerTcpInterface& Src) { ASSERT(FALSE); return *this; }

	const CString&	GetHostAddress() const { return m_HostAddress; }
	UINT			GetHostPort() const { return m_HostPort; }
	BOOL			IsConnected() const { return m_bConnected; }

	// emulate bus level shared memory user strings
	BOOL	SetSMUserString(int nIndex, SM_USER_STRING_MSG* pSMUserString = NULL);

	// registry archive functions
	BOOL	ReadFromRegistry(LPCTSTR lpszSection);
	BOOL	WriteToRegistry(LPCTSTR lpszSection);

	// open and close the serial port
	BOOL	Open();
	BOOL	Close();

	// polling thread start/stop functions
	BOOL	Start();
	BOOL	Stop();
};
