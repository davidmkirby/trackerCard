///////////////////////////////////////////////////////////////////////////////
// TrackerSerialPort.h - CTrackerSerialPort class header file
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

#if !defined(AFX_TrackerSerialPort_H__BA280D53_1B1D_11D1_BAAE_000000000000__INCLUDED_)
#define AFX_TrackerSerialPort_H__BA280D53_1B1D_11D1_BAAE_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TrackerInterface.h"

#define WM_TRACKER_SERIAL	(WM_USER + 100 + 87)


///////////////////////////////////////////////////////////////////////////////
// CTrackerSerialPort
//
class CTrackerSerialPort : public CTrackerInterface
{
	friend UINT BeginInputThread(LPVOID pParm);
	friend UINT BeginOutputThread(LPVOID pParm);

protected:
	// general
	HANDLE					m_Handle;
	DCB						m_DCB;

public:
	// general
	CString			m_Name;

	// serial port parameters
	int 			m_ComNumber;
	DWORD 			m_BaudRate;
	char			m_Parity;
	int 			m_DataBits;
	int				m_StopBits;
	BOOL			m_bRTSControlEnable;
	BOOL			m_bXonXoff;
	BOOL			m_bNoHandshaking;

protected:
	virtual	void DoNotify(int event=0);

	virtual BOOL ReceiveMessage(CTrackerMessage& message);
	USHORT SyncToMessage();

	virtual void InputThread();
	virtual void OutputThread();

public:
	CTrackerSerialPort();
	virtual ~CTrackerSerialPort();

	CTrackerSerialPort(const CTrackerSerialPort& Src) { ASSERT(FALSE); /*NEVER CALLED!*/}
	const CTrackerSerialPort& operator=(const CTrackerSerialPort& Src) { ASSERT(FALSE); return *this; }

	const CString& GetName() const { return m_Name; }

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

#endif // !defined(AFX_TrackerSerialPort_H__BA280D53_1B1D_11D1_BAAE_000000000000__INCLUDED_)
