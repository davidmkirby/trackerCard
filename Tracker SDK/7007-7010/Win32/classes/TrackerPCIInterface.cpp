///////////////////////////////////////////////////////////////////////////////
// TrackerPCIInterface.cpp - CTrackerPCIInterface class
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
#include "..\TrkrPciApi\TrkrPciApi.h"
#include "TrackerPCIInterface.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


// static functions
static UINT BeginInputThread(LPVOID pParm);
static UINT BeginOutputThread(LPVOID pParm);


///////////////////////////////////////////////////////////////////////////////
// Construction/Destruction
//
CTrackerPCIInterface::CTrackerPCIInterface()
{
	m_hPciBoard = NULL;
	m_pSharedMem = NULL;
	m_hInterruptEvent = NULL;
	m_bInterruptEventReady = FALSE;
	m_BoardNumber = 0;

	m_bInSync = TRUE; // not used!
}

CTrackerPCIInterface::~CTrackerPCIInterface()
{
	Close();
}

//////////////////////////////////////////////////////////////////////////////
// CTrackerPCIInterface::ReadFromRegistry(LPCTSTR lpszSection)
//
// Gets the settings from the registry
//
BOOL CTrackerPCIInterface::ReadFromRegistry(LPCTSTR lpszSection)
{
	CWinApp* pApp = AfxGetApp();
	if( pApp == NULL )
		return FALSE;
	
	m_BoardNumber = pApp->GetProfileInt(lpszSection, "Board Number", 0);

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
// CTrackerPCIInterface::WriteToRegistry(LPCTSTR lpszSection)
//
// Saves the settings to the registry
//
BOOL CTrackerPCIInterface::WriteToRegistry(LPCTSTR lpszSection)
{
	CWinApp* pApp = AfxGetApp();
	if( pApp == NULL )
		return FALSE;

	pApp->WriteProfileInt(lpszSection, "Board Number", m_BoardNumber);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerPCIInterface::Open()
//
// Opens the PCI interface
//
BOOL CTrackerPCIInterface::Open()
{
	// sanity
	ASSERT( !m_IsOpen );
	if( m_IsOpen )
		return TRUE;

	// disabled?
	if( m_BoardNumber < 0 )
		return FALSE;

	// open the board
	m_hPciBoard = TrkrPciOpenBoard(m_BoardNumber);

	if( m_hPciBoard == NULL )
		return FALSE;

	// map the memory
	TrkrPciMapMemory(m_hPciBoard, &m_pSharedMem);

	if( m_pSharedMem == NULL )
	{
		TrkrPciCloseBoard(m_hPciBoard);
		m_hPciBoard = NULL;
		return FALSE;
	}

	// clear status mailbox
	m_pSharedMem[TRKR_STATUS_MAILBOX] = 0;

	// set the open flag
	m_IsOpen = TRUE;

	// start the polling thread
	Start();

	return TRUE;	
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerPCIInterface::Close()
//
// Close the memory interface
//
BOOL CTrackerPCIInterface::Close()
{
	// check if already closed
	if( !m_IsOpen )
		return TRUE;

	// kill polling thread
	Stop();

	// free the shared memory and close the board
	TrkrPciUnMapMemory(m_hPciBoard, m_pSharedMem);
	TrkrPciCloseBoard(m_hPciBoard);

	m_pSharedMem = NULL;
	m_hPciBoard = NULL;

	// call base class and exit
	return CTrackerInterface::Close();
}

/////////////////////////////////////////////////////////////////////////////
// CTrackerPCIInterface::DoNotify(int event = 0)
//
// If a window has asked for async event notification this function will
// send them a message if something happens.
//
void CTrackerPCIInterface::DoNotify(int event)
{
	// release any waiting threads
	m_NotifyEvent.PulseEvent();

	// exit if no window to notify
	if( m_hNotifyWnd == NULL )
		return;

	// check to make sure it is a window
	if( !IsWindow(m_hNotifyWnd) )
	{
		m_hNotifyWnd = NULL;
		return;
	}

	// try to post the message
	PostMessage(m_hNotifyWnd, WM_TRACKER_PCI, (WPARAM)event, (LPARAM)this);
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerPCIInterface::Start()
//
// Starts the polling thread.
//
BOOL CTrackerPCIInterface::Start()
{
	// must be open
	if( !m_IsOpen )
		return FALSE;

	// if the thread is already running, exit
	if( m_bPolling )
		return TRUE;

#ifdef CTRACKERINTERFACE_USE_MMTIMER
	// start multimedia timer
	m_pMMTimer->Start(MMTIMER_INTERVAL);
#endif

	// start up the threads
	m_bAbort = FALSE;
	m_bPolling = TRUE;
	m_InputThreadDone.ResetEvent();
	m_OutputThreadDone.ResetEvent();

	AfxBeginThread(BeginInputThread, this, m_bUseLowPriorityThreads ? THREAD_PRIORITY_NORMAL : THREAD_PRIORITY_TIME_CRITICAL);
	AfxBeginThread(BeginOutputThread, this, m_bUseLowPriorityThreads ? THREAD_PRIORITY_NORMAL : THREAD_PRIORITY_HIGHEST);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerPCIInterface::Stop()
//
// Stop the polling thread
//
BOOL CTrackerPCIInterface::Stop()
{
	// thread not running?
	if( !m_bPolling )
		return FALSE;

	// set abort flag and wait for the threads to stop
	m_bAbort = TRUE;
	m_OutputMessageAvailable.SetEvent();

	CSingleLock l1(&m_InputThreadDone, TRUE);
	CSingleLock l2(&m_OutputThreadDone, TRUE);

	// clear polling flag
	m_bPolling = FALSE;

#ifdef CTRACKERINTERFACE_USE_MMTIMER
	// stop multimedia timer
	m_pMMTimer->Stop();
#endif

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// BeginInputThread(LPVOID pParm)
//
// pParm is a pointer to a CTrackerPCIInterface and this function is a 
// friend which almost makes this a member function of the class
//
static UINT BeginInputThread(LPVOID pParm)
{
	// Get pointer
	ASSERT(pParm);
	CTrackerPCIInterface* pThis = (CTrackerPCIInterface*)pParm;

	pThis->InputThread();

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerPCIInterface::AddIncomingMessageToQueue(CTrackerMessage& message)
//
// Verify checksum and add a received message to the incoming message queue
//
BOOL CTrackerPCIInterface::AddIncomingMessageToQueue(CTrackerMessage& message)
{
	// check the message checksum
	if( !message.VerifyChecksum() )
	{
		TRACE0("Message failed checksum!\n");

		// set checksum fail flag
		CSingleLock checklock(&m_ChecksumCrit, TRUE);
		m_bChecksumFail = TRUE;

		// increment checksum failures
		CSingleLock statslock(&m_StatsCrit, TRUE);
		m_nChecksumFailures++;

		// get next message
		return FALSE;
	}

	// message queue critical section...
	{
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

		// add the message to the queue
		CTrackerMessage* pNewMessage = m_Messages.Add(message);
		ASSERT(pNewMessage);

		if( pNewMessage != NULL )
		{
			// time stamp the message
			pNewMessage->SetTimeStamp();

			// keep track of the last status message
			UpdateLastStatusMessage(*pNewMessage);
		}
	}

	// flag incoming activity indicator
	CSingleLock actlock(&m_ActivityCrit, TRUE);
	m_bInActivity = TRUE;

	// notify the connected window
	DoNotify();

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerPCIInterface::InputThread()
//
// Thread routine to read incoming PCI tracker data
//
void CTrackerPCIInterface::InputThread()
{
	CTrackerMessage StatusMsg;
	CTrackerMessage ResponseMsg;

	m_InputThreadDone.ResetEvent();

	// loop until aborted
	while( !m_bAbort )
	{
		// attach interrupt (if necessary)
		if( !m_bInterruptEventReady )
		{
			m_bInterruptEventReady = TrkrPciAttachMessageInterrupt(m_hPciBoard, &m_hInterruptEvent);

			if( !m_bInterruptEventReady )
			{
				TRACE("TrkrPciAttachMessageInterrupt(): Failed to attach interrupt!\n");
				Sleep(500);
				continue;
			}
		}

		// wait on interrupt (timeout in 1 second)
		DWORD EventStatus = WaitForSingleObject(m_hInterruptEvent, 1000);

		if( EventStatus == WAIT_OBJECT_0 )
		{
			// got the interrupt
			m_bInterruptEventReady = FALSE;
		}
		else if( EventStatus == WAIT_TIMEOUT )
		{
			// timed out without getting interrupt, wait again
			continue;
		}
		else
		{
			// an error occurred
			TRACE("CTrackerPCIInterface: Failed waiting on interrupt!  WaitForSingleObject returned 0x%8x\n", EventStatus);
			Sleep(250);
			continue;
		}

		// try to receive a status message
		if( ReceiveMessage(StatusMsg) )
		{
			// handle adding the message to the queue
			AddIncomingMessageToQueue(StatusMsg);
		}

		// try to receive a response message
		if( ReceiveResponseMessage(ResponseMsg) )
		{
			// handle adding the message to the queue
			AddIncomingMessageToQueue(ResponseMsg);
		}
	}

	// exit the thread, set CEvent
	m_InputThreadDone.SetEvent();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerPCIInterface::ReceiveMessage(CTrackerMessage& message)
//
// We reside in here until we get a message
//
BOOL CTrackerPCIInterface::ReceiveMessage(CTrackerMessage& message)
{
	// get pointer to incoming tracker message and mailbox
	volatile unsigned short* pPCIMsg = m_pSharedMem + TRKR_STATUS_OFFSET;
	volatile unsigned short* pPCIMailbox = m_pSharedMem + TRKR_STATUS_MAILBOX;

	// no message?
	if( *pPCIMailbox == 0 )
		return FALSE;

	// exit if aborted
	if( m_bAbort )
		return FALSE;

	// check for sync word
	USHORT syncword = pPCIMsg[0];

	if( (syncword != GATE0_SYNC_WORD) && (syncword != GATE1_SYNC_WORD) && (syncword != GATE2_SYNC_WORD) )
	{
		// bad sync word
		TRACE("Got PCI message but sync word (0x%0.4X) does not check!\n", (int)syncword);

		// set unknown message flag
		CSingleLock unknownlock(&m_UnknownCrit, TRUE);
		m_bInUnknown = TRUE;

		// increment unknown messages
		CSingleLock statslock(&m_StatsCrit, TRUE);
		m_nInUnknownMessages++;

		// clear mailbox for next message
		*pPCIMailbox = 0;
		return FALSE;
	}

	// get the message type
	unsigned short MsgType = pPCIMsg[1];	
	MsgType = (MsgType >> 8) & 0x00FF;

	// setup the message type
	if( !message.SetType(MsgType, syncword) )
	{
		// unknown message
		TRACE("Failed to set message type to %d (unknown message type?)\n", (int)MsgType);		

		// set unknown message flag
		CSingleLock unknownlock(&m_UnknownCrit, TRUE);
		m_bInUnknown = TRUE;

		// increment unknown messages
		CSingleLock statslock(&m_StatsCrit, TRUE);
		m_nInUnknownMessages++;
		
		// clear mailbox for next message
		*pPCIMailbox = 0;
		return FALSE;
	}

	// get the message raw buffer and size (in words)
	unsigned short* pRaw = (unsigned short*)message.GetRawBuffer();
	int nWords = message.GetRawSize() / 2;

	// copy the message
	for( int i=0; i < nWords; i++ )
		*pRaw++ = *pPCIMsg++;

// DEBUG*** Write over sync word
//m_pSharedMem[TRKR_STATUS_OFFSET] = 0x5555;

	// clear mailbox to allow for next message
	*pPCIMailbox = 0;

/*
// DEBUG*** Show raw message
pRaw = (unsigned short*)message.GetRawBuffer();
CString debugMsg("Raw Message Buffer (before byte swap): ");
CString tmpStr;
for( i=0; i < nWords; i++ )
{
	tmpStr.Format("0x%04X ", *pRaw++);
	debugMsg += tmpStr;
}
debugMsg += "/r/n";
dump_debug(debugMsg);
*/

// DEBUG*** Show frame timer
//dump_debug("Frame Time = %0.6lf ms\r\n", GetFrameTimer());

	// we received a full message!
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerPCIInterface::ReceiveResponseMessage(CTrackerMessage& message)
//
// We reside in here until we get a message
//
BOOL CTrackerPCIInterface::ReceiveResponseMessage(CTrackerMessage& message)
{
	// get pointer to incoming tracker message and mailbox
	volatile unsigned short* pPCIMsg = m_pSharedMem + TRKR_RESPONSE_OFFSET;
	volatile unsigned short* pPCIMailbox = m_pSharedMem + TRKR_RESPONSE_MAILBOX;

	// no message?
	if( *pPCIMailbox == 0 )
		return FALSE;
	
	// exit if aborted
	if( m_bAbort )
		return FALSE;

	// check for sync word
	USHORT syncword = pPCIMsg[0];

	if( (syncword != GATE0_SYNC_WORD) && (syncword != GATE1_SYNC_WORD) && (syncword != GATE2_SYNC_WORD) )
	{
		// bad sync word
		TRACE("Got PCI response message but sync word (0x%0.4X) does not check!\n", (int)syncword);

		// set unknown message flag
		CSingleLock unknownlock(&m_UnknownCrit, TRUE);
		m_bInUnknown = TRUE;

		// increment unknown messages
		CSingleLock statslock(&m_StatsCrit, TRUE);
		m_nInUnknownMessages++;

		// clear mailbox for next message
		*pPCIMailbox = 0;
		return FALSE;
	}

	// get the message type
	unsigned short MsgType = pPCIMsg[1];	
	MsgType = (MsgType >> 8) & 0x00FF;

	// setup the message type
	if( !message.SetType(MsgType, syncword) )
	{
		// unknown message
		TRACE("Failed to set message type to %d (unknown message type?)\n", (int)MsgType);		

		// set unknown message flag
		CSingleLock unknownlock(&m_UnknownCrit, TRUE);
		m_bInUnknown = TRUE;

		// increment unknown messages
		CSingleLock statslock(&m_StatsCrit, TRUE);
		m_nInUnknownMessages++;
		
		// clear mailbox for next message
		*pPCIMailbox = 0;
		return FALSE;
	}

	// get the message raw buffer and size (in words)
	unsigned short* pRaw = (unsigned short*)message.GetRawBuffer();
	int nWords = message.GetRawSize() / 2;

	// copy the message
	for( int i=0; i < nWords; i++ )
		*pRaw++ = *pPCIMsg++;

// DEBUG*** Write over sync word
//m_pSharedMem[TRKR_STATUS_OFFSET] = 0x5555;

	// clear mailbox to allow for next message
	*pPCIMailbox = 0;

// DEBUG*** Show raw message
/*
pRaw = (unsigned short*)message.GetRawBuffer();
CString debugMsg("Raw Message Buffer (before byte swap)\n\n");
CString tmpStr;
for( i=0; i < nWords; i++ )
{
	tmpStr.Format("0x%04X ", *pRaw++);
	debugMsg += tmpStr;
}
AfxMessageBox(debugMsg);
*/

	// we received a full message!
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// BeginOutputThread(LPVOID pParm)
//
// pParm is a pointer to a CTrackerPCIInterface and this function is a 
// friend which almost makes this a member function of the class
//
static UINT BeginOutputThread(LPVOID pParm)
{
	// Get pointer
	ASSERT(pParm);
	CTrackerPCIInterface* pThis = (CTrackerPCIInterface*)pParm;

	pThis->OutputThread();

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerPCIInterface::OutputThread()
//
// Thread routine to send queued data out
//
void CTrackerPCIInterface::OutputThread()
{
	// get pointer to PCI outgoing tracker message and mailbox
	volatile unsigned short* pPCIMsg = m_pSharedMem + TRKR_COMMAND_OFFSET;
	volatile unsigned short* pPCIMailbox = m_pSharedMem + TRKR_COMMAND_MAILBOX;

	m_OutputThreadDone.ResetEvent();

	CSingleLock dataready(&m_OutputMessageAvailable, FALSE);

	CTrackerMessage* pMessage = NULL;

	// loop until aborted
	while( !m_bAbort )
	{
		// send everything in the queue
		for(;;)
		{
			{
				CSingleLock l(&m_OutputQueueCrit, TRUE);

				// nothing in the queue to send?
				if( m_OutputQueue.GetSize() <= 0 )
					break;

				// get a message to send
				pMessage = m_OutputQueue.GetAt(0);
			}

			ASSERT( pMessage );

			// compute the checksum
			pMessage->SetChecksum();

			// get the message raw buffer and size (in words)
			unsigned short* pRaw = (unsigned short*)pMessage->GetRawBuffer();
			int nWords = pMessage->GetRawSize() / 2;

			ASSERT(nWords > 0);

			// wait until tracker is ready
			while( !m_bAbort )
			{
				// check mailbox
				if( *pPCIMailbox == 0 )
					break;

#ifdef CTRACKERINTERFACE_USE_MMTIMER
				CSingleLock lock(&m_MMTimerEvent, TRUE);
#else
				// yield the processor
				Sleep(1);
#endif
			}

			if( m_bAbort )
				break;

			// copy message to PCI tracker memory
			for( int i=0; i < nWords; i++ )
				pPCIMsg[i] = pRaw[i];

			// set mailbox flag
			*pPCIMailbox = 0x5555;

			{
				CSingleLock actlock(&m_ActivityCrit, TRUE);
				m_bOutActivity = TRUE;
			}

			{
				CSingleLock l(&m_OutputQueueCrit, TRUE);

				// remove the message from the queue
				m_OutputQueue.RemoveAt(0);
				pMessage = NULL;
			}

			// increment out messages
			CSingleLock statslock(&m_StatsCrit, TRUE);
			m_nOutMessages++;
		}

		// wait for data
		dataready.Lock();
		dataready.Unlock();
	}

	// exit the thread, set CEvent
	m_OutputThreadDone.SetEvent();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerPCIInterface::GetNumberOfBoards()
//
// Returns the number of PCI boards in the computer system
//
int CTrackerPCIInterface::GetNumberOfBoards()
{
	return TrkrPciGetNumberOfBoards();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerPCIInterface::GetFrameTimer()
//
// Returns the number (in milliseconds with 16 nanosecond precision) since 
// the current video frame's vertical sync (ie-start of field/frame)
//
double CTrackerPCIInterface::GetFrameTimer()
{
	if( m_hPciBoard == NULL )
		return -1;

	unsigned int rawTimer = 0;

	if( !TrkrPciGetFrameTimer(m_hPciBoard, &rawTimer) )
		return -1;

	return (double)rawTimer * 0.000016;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerPCIInterface::SetSMUserString(int nIndex, SM_USER_STRING_MSG* pSMUserString = NULL)
//
// Sets a shared memory user string.  There are four strings (nIndex range: 1 to 4).
// Passing a NULL pointer for the SM_USER_STRING_MSG structure will disable the string.
//
BOOL CTrackerPCIInterface::SetSMUserString(int nIndex, SM_USER_STRING_MSG* pSMUserString)
{
	// must be open
	if( !m_IsOpen || (m_pSharedMem == NULL) )
		return FALSE;

	// get pointer to PCI memory
	volatile unsigned short* pPCIUserString = NULL;

	switch( nIndex )
	{
	case 1:
		pPCIUserString = m_pSharedMem + TRKR_USER_STRING1_OFFSET;
		break;

	case 2:
		pPCIUserString = m_pSharedMem + TRKR_USER_STRING2_OFFSET;
		break;

	case 3:
		pPCIUserString = m_pSharedMem + TRKR_USER_STRING3_OFFSET;
		break;

	case 4:
		pPCIUserString = m_pSharedMem + TRKR_USER_STRING4_OFFSET;
		break;

	default:
		// invalid index
		return FALSE;
	}

	if( pSMUserString == NULL )
	{
		// zero it
		for( int i=0; i < sizeof(SM_USER_STRING_MSG)/2; i++ )
			*pPCIUserString++ = 0;
	}
	else
	{
		// get pointer to user string enable mailbox
		volatile unsigned short* pPCIUserStringEnable = pPCIUserString;

		// make sure the tracker consumed the last message before writing
		// a new one... otherwise you could get odd looking stuff displayed
		if( *pPCIUserStringEnable != 0 )
			return FALSE;

		// get pointer to new user string data
		unsigned short* pUserBuffer = (unsigned short*)pSMUserString;

		// skip first word (the enable mailbox)
		pUserBuffer++;
		pPCIUserString++;

		// write the body of the message
		for( int i=0; i < (sizeof(SM_USER_STRING_MSG)/2) - 1; i++ )
			*pPCIUserString++ = *pUserBuffer++;

		// enable the user string
		*pPCIUserStringEnable = pSMUserString->enable;
	}

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerPCIInterface::GetSMMountPerformanceData(SM_MOUNT_PERFORMANCE_DATA* pData = NULL)
//
// Sets a shared memory user string.  There are four strings (nIndex range: 1 to 4).
// Passing a NULL pointer for the SM_USER_STRING_MSG structure will disable the string.
//
BOOL CTrackerPCIInterface::GetSMMountPerformanceData(SM_MOUNT_PERFORMANCE_DATA* pData)
{
	// must be open
	if( !m_IsOpen || (m_pSharedMem == NULL) )
		return FALSE;

	// get pointers to PCI memory
	volatile unsigned short* pPCIMountMailbox	= m_pSharedMem + TRKR_MOUNT_PERF_MAILBOX;
	volatile unsigned short* pPCIMountData		= m_pSharedMem + TRKR_MOUNT_PERF_OFFSET;

	// check if data is not available
	if( *pPCIMountMailbox != 0x5555 )
		return FALSE;

	// if only reading mailbox status, exit
	if( pData == NULL )
		return TRUE;

	// get pointer to new user string data
	unsigned short* pUserBuffer = (unsigned short*)pData;

	// read the data
	for( int i=0; i < (sizeof(SM_MOUNT_PERFORMANCE_DATA)/2); i++ )
		*pUserBuffer++ = *pPCIMountData++;

	// clear the mailbox
	*pPCIMountMailbox = 0;

	return TRUE;
}
