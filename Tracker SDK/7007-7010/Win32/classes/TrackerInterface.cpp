///////////////////////////////////////////////////////////////////////////////
// TrackerInterface.cpp: implementation of the CTrackerInterface class.
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
#include "TrackerInterface.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

///////////////////////////////////////////////////////////////////////////////
// Construction/Destruction
//
CTrackerInterface::CTrackerInterface()
	: m_InputThreadDone(FALSE, TRUE), m_OutputThreadDone(FALSE, TRUE),
	  m_Messages(64), m_OutputQueue(64), m_NotifyEvent(FALSE, TRUE)
#ifdef CTRACKERINTERFACE_USE_MMTIMER
	  ,m_MMTimerEvent(FALSE, TRUE)
#endif
{
	m_hNotifyWnd = NULL;
	m_NotifyEvent.ResetEvent();

#ifdef CTRACKERINTERFACE_USE_MMTIMER
	m_pMMTimer = new CMultimediaTimer(*this);
	ASSERT(m_pMMTimer);

	m_MMTimerEvent.ResetEvent();
#endif

	m_IsOpen = FALSE;

	m_bInSync = FALSE;
	m_bPolling = FALSE;
	m_bAbort = FALSE;

	m_bInOverflow = FALSE;
	m_bOutOverflow = FALSE;

	m_bInActivity = FALSE;
	m_bOutActivity = FALSE;

	m_bChecksumFail = FALSE;

	m_bInUnknown = FALSE;

	m_bUseLowPriorityThreads = FALSE;

	m_nStatusMessageRate = TRK_RATE_UNKNOWN;
	m_nChecksumFailures = 0;
	m_nOutMessages = m_nOutOverflowMessages = 0;
	m_nInMessages = m_nInOverflowMessages = 0;
	m_nInUnknownMessages = 0;

	m_LastStatusMessage.SetType(STATUS_MSG_TYPE);
	m_nLastStatusMessageRate = TRK_RATE_UNKNOWN;
	m_StatusRateValidCount = 0;

	m_InputThreadDone.SetEvent();
	m_OutputThreadDone.SetEvent();
}

CTrackerInterface::~CTrackerInterface()
{
	// make sure to close the interface (if open)
	if( m_IsOpen )
		Close();

	// release anybody waiting
	m_NotifyEvent.SetEvent();

#ifdef CTRACKERINTERFACE_USE_MMTIMER
	// stop multimedia timer and free memory
	if( m_pMMTimer != NULL )
	{
		m_pMMTimer->Stop();
		delete m_pMMTimer;
		m_pMMTimer = NULL;
	}
	m_MMTimerEvent.SetEvent();
#endif
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerInterface::Close()
//
// Close the tracker interface
//
// MAKE SURE TO OVERLOAD THIS FUNCTION AND CALL THE BASE CLASS IN YOUR IMPLEMENTATION
//
BOOL CTrackerInterface::Close()
{
	// wait to make sure the threads are done,
	// this should be done in the derived class
	// but is done here just to make sure
	CSingleLock l1(&m_InputThreadDone, TRUE);
	CSingleLock l2(&m_OutputThreadDone, TRUE);

	m_IsOpen = FALSE;

	m_nStatusMessageRate = TRK_RATE_UNKNOWN;
	m_nLastStatusMessageRate = TRK_RATE_UNKNOWN;
	m_StatusRateValidCount = 0;

	m_Messages.RemoveAll();
	m_OutputQueue.RemoveAll();

	ClearActivity();

#ifdef CTRACKERINTERFACE_USE_MMTIMER
	// stop multimedia timer
	if( m_pMMTimer != NULL )
		m_pMMTimer->Stop();
	m_MMTimerEvent.SetEvent();
#endif

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerInterface::SendMessage(const CTrackerMessage& message, int nTimes=1)
//
// Send a message to the tracker (add to output queue)
//
BOOL CTrackerInterface::SendMessage(const CTrackerMessage& message, int nTimes)
{
	// must be opened
	ASSERT( m_IsOpen );
	if( !m_IsOpen )
		return FALSE;

	CSingleLock l(&m_OutputQueueCrit, TRUE);

	for( int i=0; i < nTimes; i++ )
	{
		// if we have too many messages, dump the head
		if( m_OutputQueue.GetSize() > TRK_MAX_STORED_MESSAGES-1 )
		{
			TRACE0("CTrackerInterface::SendMessage, Outgoing message overflow!\n");

			// set outgoing overflow flag
			CSingleLock overlock(&m_OverflowCrit, TRUE);
			m_bOutOverflow = TRUE;

			// remove the oldest message
			m_OutputQueue.RemoveAt(0);

			// increment output overflow
			CSingleLock statslock(&m_StatsCrit, TRUE);
			m_nOutOverflowMessages++;
		}

		// add the message to the queue
		CTrackerMessage* pNewMessage = m_OutputQueue.Add(message);

		ASSERT( pNewMessage );
		if( pNewMessage == NULL )
			return FALSE;

		// time stamp the message
		pNewMessage->SetTimeStamp();
	}

	// notify thread that data is available
	m_OutputMessageAvailable.SetEvent();

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerInterface::GetMessage(CTrackerMessage& message)
//
// This is the users access to received tracker messages
// this should be called when the WM_TRACKER_SERIAL message is received
//
BOOL CTrackerInterface::GetMessage(CTrackerMessage& message)
{
	// critical section
	CSingleLock Lock(&m_MessageBufferCrit, TRUE);

	// sanity check
	if( m_Messages.GetSize() == 0 )
		return FALSE;

	message.SwapContents( m_Messages[0] );
	m_Messages.RemoveAt(0);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerInterface::UpdateLastStatusMessage(CTrackerMessage& message)
//
// Keep track of the last incoming status messages and stats
// This is the status message for the last PRIMARY track gate only.
//
void CTrackerInterface::UpdateLastStatusMessage(CTrackerMessage& message)
{
	// only work on status messages
	if( message.GetType() != STATUS_MSG_TYPE )
		return;

	// only work on the primary gate
	if( message.GetStatus()->gate != 0 )
		return;

	// update last status message
	m_LastStatusMessage = message;

	// keep track of the incoming status message rate
//	UpdateStatusMessageRate(message);
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerInterface::UpdateStatusMessageRate(CTrackerMessage& message)
//
// Keep track of the incoming status message rate
//
// NOTE: The timers on PCs are very inaccurate.  Only trust this function
// when using a GPS/IRIG time board as your time source.  In fact, it's
// so bad, I'm commenting it out of the code for now.
//
void CTrackerInterface::UpdateStatusMessageRate(CTrackerMessage& message)
{
/*
	// calculate time difference (in milliseconds)
	FILETIME CurrentTime, LastTime;
	SystemTimeToFileTime(&message.GetTimeStamp().GetTimeStamp(), &CurrentTime);
	SystemTimeToFileTime(&m_LastStatusTime.GetTimeStamp(), &LastTime);
	int msecs = (int)((*((__int64*)&CurrentTime) - *((__int64*)&LastTime)) / 10000);

	// find current rate
	int rate = TRK_RATE_UNKNOWN;

	if( (msecs < 35) && (msecs > 31) )
		rate = TRK_RATE_30HZ;
	else if( (msecs < 22) && (msecs > 18) )
		rate = TRK_RATE_50HZ;
	else if( (msecs < 18) && (msecs > 14) )
		rate = TRK_RATE_60HZ;

#ifdef _DEBUG_STATUS_RATE
	dump_debug(message.GetTimeStamp().GetTimeString());
	dump_debug("\r\n");
#endif

	// are we at zero (rate is unknown)?
	if( m_StatusRateValidCount <= 0 )
	{
		// did we have a previous rate?
		if( m_nStatusMessageRate != TRK_RATE_UNKNOWN )
		{
			// set it to unknown
			m_nStatusMessageRate = TRK_RATE_UNKNOWN;
#ifdef _DEBUG_STATUS_RATE
			dump_debug("Setting incoming status message rate to UNKNOWN\r\n");
#endif
		}
		// got a first match?
		else if( (rate != TRK_RATE_UNKNOWN) && (m_nLastStatusMessageRate == rate) )
		{
			m_StatusRateValidCount++;
#ifdef _DEBUG_STATUS_RATE
			dump_debug("Got first rate match at %d ms (%dHz)\r\n", msecs, rate);
#endif
		}
	}
	// do we have a locked in rate?
	else if( m_nStatusMessageRate != TRK_RATE_UNKNOWN )
	{
		// match with current rate?
		if( m_nStatusMessageRate == rate )
		{
			// increment the valid count if necessary
			if( m_StatusRateValidCount < TRK_RATE_THRESHOLD )
			{
				m_StatusRateValidCount++;
#ifdef _DEBUG_STATUS_RATE
				dump_debug("Locked rate match: count %d at %d ms (%dHz)\r\n", m_StatusRateValidCount, msecs, rate);
#endif
			}
		}
		else
		{
			m_StatusRateValidCount--; // mismatch
#ifdef _DEBUG_STATUS_RATE
			dump_debug("Locked rate mismatch: count %d for %d ms\r\n", m_StatusRateValidCount, msecs);
#endif
		}
	}
	// we are looking for a new rate
	else
	{
		// same as last time?
		if( m_nLastStatusMessageRate == rate )
		{
			if( m_StatusRateValidCount < TRK_RATE_THRESHOLD )
				m_StatusRateValidCount++;
			else
			{
				m_nStatusMessageRate = rate; // got a new rate!
#ifdef _DEBUG_STATUS_RATE
				dump_debug("Incoming status message rate locked at %dHz\r\n", rate);
#endif
			}

		}
		else
		{
			m_StatusRateValidCount--;  // mismatch
#ifdef _DEBUG_STATUS_RATE
			dump_debug("Unlocked rate mismatch: count %d for %d ms\r\n", m_StatusRateValidCount, msecs);
#endif
		}
	}

	// update last sample data
	m_nLastStatusMessageRate = rate;
	m_LastStatusTime = message.GetTimeStamp();
*/
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerInterface::FakeMessageReceive(const CTrackerMessage& message)
//
// DEBUG FUNCTION
// Use this function to simulate receiving a message
//
void CTrackerInterface::FakeMessageReceive(const CTrackerMessage& message)
{
	// check the message checksum
	if( !message.VerifyChecksum() )
	{
		TRACE0("Fake message failed checksum!\n");

		// set checksum fail flag
		CSingleLock checklock(&m_ChecksumCrit, TRUE);
		m_bChecksumFail = TRUE;

		return;
	}

	// critical section...
	{
		// critical section
		CSingleLock Lock(&m_MessageBufferCrit, TRUE);

		// if we have too many messages, dump the head
		if( m_Messages.GetSize() > TRK_MAX_STORED_MESSAGES-1 )
		{
			TRACE0("Incoming message overflow!\n");

			// set incoming overflow flag
			CSingleLock overlock(&m_OverflowCrit, TRUE);
			m_bInOverflow = TRUE;

			// remove the oldest message
			m_Messages.RemoveAt(0);

			// increment in message overflow
			CSingleLock statslock(&m_StatsCrit, TRUE);
			m_nInOverflowMessages++;
		}

		// increment in messages
		CSingleLock statslock(&m_StatsCrit, TRUE);
		m_nInMessages++;

		// add this message to the queue
		CTrackerMessage* pNewMessage = m_Messages.Add(message);
		ASSERT(pNewMessage);

		if( pNewMessage != NULL )
		{
			// time stamp the message
			pNewMessage->SetTimeStamp();

			// keep track of status message rate
			UpdateStatusMessageRate(*pNewMessage);
		}
	}

	// flag incoming activity indicator
	CSingleLock actlock(&m_ActivityCrit, TRUE);
	m_bInActivity = TRUE;

	// notify the connected window
	DoNotify();
}
