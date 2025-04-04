///////////////////////////////////////////////////////////////////////////////
// TrackerInterface.h: interface for the CTrackerInterface class.
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

#if !defined(AFX_TRACKERINTERFACE_H__06D1EBE0_F5A7_48FF_98E6_B139BFB460D1__INCLUDED_)
#define AFX_TRACKERINTERFACE_H__06D1EBE0_F5A7_48FF_98E6_B139BFB460D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TrackerMessage.h"

///////////////////////////////////////////////////////////////////////////////
// In order to reduce latency, you can use the Windows multimedia timer
// instead of using the sleep command which is not deterministic in how long
// it waits before returning control.
//
#define CTRACKERINTERFACE_USE_MMTIMER

#ifdef CTRACKERINTERFACE_USE_MMTIMER
	#include "MMTimer.h"
	#define MMTIMER_INTERVAL	4	// 4 millisecond tick
#endif

///////////////////////////////////////////////////////////////////////////////
// defines
//
#define TRK_MAX_STORED_MESSAGES		128
#define TRK_RATE_THRESHOLD			15

// tracker status message rates
#define TRK_RATE_UNKNOWN	-1
#define TRK_RATE_30HZ		30	// progressive RS-170/NTSC (~33ms)
#define TRK_RATE_50HZ		50	// CCIR/PAL (20ms)
#define TRK_RATE_60HZ		60	// RS-170/NTSC (~16ms)


///////////////////////////////////////////////////////////////////////////////
// CTrackerInterface - a base class for the different tracker interfaces
//
#ifdef CTRACKERINTERFACE_USE_MMTIMER
class CTrackerInterface : public CMultimediaTimerCallback
#else
class CTrackerInterface
#endif
{
protected:
	// general
	HWND					m_hNotifyWnd;
	CEvent					m_NotifyEvent;

#ifdef CTRACKERINTERFACE_USE_MMTIMER
	CMultimediaTimer*		m_pMMTimer;
	CEvent					m_MMTimerEvent;
#endif

	CTrackerMessageArray	m_Messages;		// messages received
	CTrackerMessageArray	m_OutputQueue;	// messages to send

	BOOL					m_IsOpen;
	BOOL					m_bPolling;
	BOOL					m_bInSync;
	BOOL					m_bAbort;
	BOOL					m_bUseLowPriorityThreads;

	BOOL					m_bInOverflow;
	BOOL					m_bOutOverflow;
	BOOL					m_bInActivity;
	BOOL					m_bOutActivity;
	BOOL					m_bChecksumFail;
	BOOL					m_bInUnknown;

	CEvent					m_InputThreadDone;
	CEvent					m_OutputThreadDone;
	CEvent					m_OutputMessageAvailable;
	CCriticalSection		m_OutputQueueCrit;
	CCriticalSection		m_MessageBufferCrit;
	CCriticalSection		m_ActivityCrit;
	CCriticalSection		m_OverflowCrit;
	CCriticalSection		m_ChecksumCrit;
	CCriticalSection		m_UnknownCrit;

	int						m_nStatusMessageRate;
	unsigned long			m_nChecksumFailures;
	unsigned long			m_nOutMessages;
	unsigned long			m_nOutOverflowMessages;
	unsigned long			m_nInMessages;
	unsigned long			m_nInOverflowMessages;
	unsigned long			m_nInUnknownMessages;
	CCriticalSection		m_StatsCrit;

	CTrackerMessage			m_LastStatusMessage;
	int						m_nLastStatusMessageRate;
	int						m_StatusRateValidCount;

protected:
	virtual	void DoNotify(int event=0) = 0;

	virtual BOOL ReceiveMessage(CTrackerMessage& message) = 0;

	virtual void InputThread() = 0;
	virtual void OutputThread() = 0;

	virtual void UpdateLastStatusMessage(CTrackerMessage& message);
	virtual void UpdateStatusMessageRate(CTrackerMessage& message);

#ifdef CTRACKERINTERFACE_USE_MMTIMER
protected:
	// multimedia timer callback
	virtual	bool	OnLoop() { m_MMTimerEvent.PulseEvent(); return true; }
#endif

public:
	CTrackerInterface();
	virtual ~CTrackerInterface();

	CTrackerInterface(const CTrackerInterface& Src) { ASSERT(FALSE); /*NEVER CALLED!*/}
	const CTrackerInterface& operator=(const CTrackerInterface& Src) { ASSERT(FALSE); return *this; }

	virtual	void SetNotifyWindow(HWND hWnd) { m_hNotifyWnd = hWnd; }

	// registry archive functions
	virtual BOOL	ReadFromRegistry(LPCTSTR lpszSection) = 0;
	virtual BOOL	WriteToRegistry(LPCTSTR lpszSection) = 0;

	// open and close the interface
	virtual BOOL	Open() = 0;
	virtual BOOL	Close();

	virtual BOOL	IsOpen() { return m_IsOpen; }
	virtual BOOL	IsPolling() { return m_bPolling; }
	virtual BOOL	IsSyncronized() { return m_bInSync; }

	// overflow, checksum fail, and activity indication
	virtual BOOL	IncomingMessageOverflow() { return m_bInOverflow; }
	virtual BOOL	OutgoingMessageOverflow() { return m_bOutOverflow; }
	virtual void	ClearOverflow()
					{
						CSingleLock lock(&m_OverflowCrit, TRUE);
						m_bInOverflow = m_bOutOverflow = FALSE;
					}

	virtual BOOL	IncomingActivity() { return m_bInActivity; }
	virtual BOOL	OutgoingActivity() { return m_bOutActivity; }
	virtual void	ClearActivity()
					{
						CSingleLock lock(&m_ActivityCrit, TRUE);
						m_bInActivity = m_bOutActivity = FALSE;
					}

	virtual BOOL	ChecksumFailure() { return m_bChecksumFail; }
	virtual void	ClearChecksumFailure()
					{
						CSingleLock lock(&m_ChecksumCrit, TRUE);
						m_bChecksumFail = FALSE;
					}

	virtual BOOL	InUnknownMessage() { return m_bInUnknown; }
	virtual void	ClearUnknown()
					{
						CSingleLock lock(&m_UnknownCrit, TRUE);
						m_bInUnknown = FALSE;
					}

	// statistics
	virtual int			  GetStatusMessageRate() const { return m_nStatusMessageRate; }
	virtual unsigned long GetNumberOfChecksumFailures() const { return m_nChecksumFailures; }
	virtual unsigned long GetOutMessageQueueSize() const { return m_OutputQueue.GetSize();	}
	virtual unsigned long GetNumberOfOutMessages() const { return m_nOutMessages;	}
	virtual unsigned long GetNumberOfOutOverflowMessages() const { return m_nOutOverflowMessages;	}
	virtual unsigned long GetInMessageQueueSize() const { return m_Messages.GetSize();	}
	virtual unsigned long GetNumberOfInMessages() const { return m_nInMessages; }
	virtual unsigned long GetNumberOfInOverflowMessages() const { return m_nInOverflowMessages; }
	virtual unsigned long GetNumberOfInUnknownMessages() const { return m_nInUnknownMessages; }

	virtual void	ClearStatistics()
					{
						CSingleLock lock(&m_StatsCrit, TRUE);
						m_nChecksumFailures = 0;
						m_nOutMessages = m_nOutOverflowMessages = 0;
						m_nInMessages = m_nInOverflowMessages = 0;
						m_nInUnknownMessages = 0;
					}

	// send a message
	virtual BOOL SendMessage(const CTrackerMessage& message, int nTimes=1);

	virtual int	 GetSendQueueSize() const { return m_OutputQueue.GetSize();	}

	// access to messages received
	virtual BOOL GetMessage(CTrackerMessage& message);

	virtual const STATUS_MSG* GetLastStatusMessage() const { return m_LastStatusMessage.GetStatus(); }
	virtual const CTimeStamp& GetLastStatusTime() const { return m_LastStatusMessage.GetTimeStamp(); }

	virtual void WaitForMessage() { CSingleLock lock(&m_NotifyEvent, TRUE); }
	virtual int	 GetReceiveQueueSize() const { return m_Messages.GetSize();	}

	// access to shared memory user strings (only for bus level communication)
	virtual BOOL SetSMUserString(int nIndex, SM_USER_STRING_MSG* pSMUserString = NULL) { return FALSE; }

	// access to shared memory mount performance data (only for bus level communication)
	virtual BOOL GetSMMountPerformanceData(SM_MOUNT_PERFORMANCE_DATA* pData = NULL) { return FALSE; }

	// polling thread start/stop functions
	virtual BOOL Start() = 0;
	virtual BOOL Stop() = 0;

	virtual void SetUseLowPriorityThreads(BOOL bLow=TRUE) { m_bUseLowPriorityThreads = bLow; }
	virtual BOOL GetUseLowPriorityThreads() const { return m_bUseLowPriorityThreads; }

	// fake receive function (for debug testing)
	virtual void FakeMessageReceive(const CTrackerMessage& message);
};

#endif // !defined(AFX_TRACKERINTERFACE_H__06D1EBE0_F5A7_48FF_98E6_B139BFB460D1__INCLUDED_)
