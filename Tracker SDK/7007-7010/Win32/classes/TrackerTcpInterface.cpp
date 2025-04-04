///////////////////////////////////////////////////////////////////////////////
// TrackerTcpInterface.cpp - CTrackerTcpInterface class
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

#include "stdafx.h"
#include "TrackerTcpInterface.h"

#define TRACKER_TCP_DEFAULT_PORT		30000
#define TRACKER_TCP_CONNECT_TIMEOUT		5000	// 5 seconds


//////////////////////////////////////////////////////////////////////////////
// Constructor / Destructor
//
CTrackerTcpInterface::CTrackerTcpInterface(void)
{
	m_HostPort = TRACKER_TCP_DEFAULT_PORT;
	m_bConnected = FALSE;
	m_bWaitForAck = FALSE;

	// blank user strings
	for( int i=0; i < 4; i++ )
		memset(&m_SMUserStrings[i], 0, sizeof(SM_USER_STRING_MSG));
}

CTrackerTcpInterface::~CTrackerTcpInterface(void)
{
	Close();
}

//////////////////////////////////////////////////////////////////////////////
// CTrackerTcpInterface::ReadFromRegistry(LPCTSTR lpszSection)
//
// Gets settings from the registry
//
BOOL CTrackerTcpInterface::ReadFromRegistry(LPCTSTR lpszSection)
{
	CWinApp* pApp = AfxGetApp();
	if( pApp == NULL )
		return FALSE;

	m_HostAddress = pApp->GetProfileString(lpszSection, "Host Address", "192.168.1.100");
	m_HostPort = pApp->GetProfileInt(lpszSection, "Host Port", TRACKER_TCP_DEFAULT_PORT);

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
// CTrackerTcpInterface::WriteToRegistry(LPCTSTR lpszSection)
//
// Save settings to the registry
//
BOOL CTrackerTcpInterface::WriteToRegistry(LPCTSTR lpszSection)
{
	CWinApp* pApp = AfxGetApp();
	if( pApp == NULL )
		return FALSE;

	pApp->WriteProfileString(lpszSection, "Host Address", m_HostAddress);
	pApp->WriteProfileInt(lpszSection, "Host Port", m_HostPort);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerTcpInterface::Open()
//
// Opens the socket for communication
//
BOOL CTrackerTcpInterface::Open()
{
	// sanity
	ASSERT( !m_IsOpen );
	if( m_IsOpen )
		return TRUE;

	// make sure the socked is closed
	m_bConnected = FALSE;
	m_Socket.Close();

	// set the open flag
	m_IsOpen = TRUE;

	// start the polling thread
	Start();

	return TRUE;	
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerTcpInterface::Close()
//
// Close the socket connection
//
BOOL CTrackerTcpInterface::Close()
{
	// check if already closed
	if( !m_IsOpen )
		return TRUE;

	// kill polling thread
	Stop();

	// make sure the socket is closed
	m_bConnected = FALSE;
	m_Socket.Close();

	// call base class and exit
	return CTrackerInterface::Close();
}

/////////////////////////////////////////////////////////////////////////////
// CTrackerTcpInterface::DoNotify(int event = 0)
//
// If a window has asked for async event notification this function will
// send them a message if something happens.
//
void CTrackerTcpInterface::DoNotify(int event)
{
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
	PostMessage(m_hNotifyWnd, WM_TRACKER_TCP, (WPARAM)event, (LPARAM)this);
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerTcpInterface::Start()
//
// Starts the polling thread.  Needed if reading from serial port.
//
BOOL CTrackerTcpInterface::Start()
{
	// must be open
	if( !m_IsOpen )
		return FALSE;

	// if the thread is already running, exit
	if( m_bPolling )
		return TRUE;

	// start up the thread
	m_bAbort = FALSE;
	m_bPolling = TRUE;
	m_InputThreadDone.ResetEvent();
	m_OutputThreadDone.ResetEvent();

	AfxBeginThread(BeginInputThread, this, m_bUseLowPriorityThreads ? THREAD_PRIORITY_NORMAL : THREAD_PRIORITY_TIME_CRITICAL);
	AfxBeginThread(BeginOutputThread, this, m_bUseLowPriorityThreads ? THREAD_PRIORITY_NORMAL : THREAD_PRIORITY_HIGHEST);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerTcpInterface::Stop()
//
// Stop the polling thread
//
BOOL CTrackerTcpInterface::Stop()
{
	// thread not running?
	if( !m_bPolling )
		return FALSE;

	// set abort flag, close the socket and wait for the threads to stop
	m_bAbort = TRUE;
	m_bConnected = FALSE;
	m_Socket.Close();
	m_OutputMessageAvailable.SetEvent();

	CSingleLock l1(&m_InputThreadDone, TRUE);
	CSingleLock l2(&m_OutputThreadDone, TRUE);

	// clear polling flag
	m_bPolling = FALSE;

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// BeginInputThread(LPVOID pParm)
//
// pParm is a pointer to a CTrackerTcpInterface and this function is a 
// friend which almost makes this a member function of the class
//
static UINT BeginInputThread(LPVOID pParm)
{
	// Get pointer
	ASSERT(pParm);
	CTrackerTcpInterface* pThis = (CTrackerTcpInterface*)pParm;

	pThis->InputThread();

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerTcpInterface::InputThread()
//
// Thread routine to read incoming data
//
void CTrackerTcpInterface::InputThread()
{
	CTrackerMessage msg;
#ifdef _DEBUG_SOCKET_COMM
	char debugstr[1024];
#endif

	m_InputThreadDone.ResetEvent();

	// loop until aborted
	while( !m_bAbort )
	{
		m_bInSync = FALSE;

		// make the connection
		if( !ConnectSocket() )
			continue; // keep waiting on a connection

		// try to receive data
		while( ReceiveMessage(msg) )
		{
			// check the message checksum
			if( !msg.VerifyChecksum() )
			{
				TRACE0("TRK: Message failed checksum!\n");

				// set checksum fail flag
				CSingleLock checklock(&m_ChecksumCrit, TRUE);
				m_bChecksumFail = TRUE;

				// increment checksum failures
				CSingleLock statslock(&m_StatsCrit, TRUE);
				m_nChecksumFailures++;

#ifdef _DEBUG_SOCKET_COMM
				msg.GetAsHexString(debugstr, 1023);
				dump_debug("TRK: Bad Checksum: %s\r\n", debugstr);
#endif
				// get next message
				continue;
			}

			// check for message acknowledgment
			if( msg.GetType() == MESSAGE_ACK_MSG_TYPE )
				m_AckEvent.SetEvent();

#ifdef _DEBUG_SOCKET_COMM
			msg.GetAsHexString(debugstr, 1023);
			dump_debug("TRK: %s\r\n", debugstr);
#endif
			// message queue critical section...
			{
				CSingleLock Lock(&m_MessageBufferCrit, TRUE);

				// if we have too many messages, dump the head
				if( m_Messages.GetSize() > TRK_MAX_STORED_MESSAGES-1 )
				{
					TRACE0("TRK: Incoming message overflow!\n");
#ifdef _DEBUG_SOCKET_COMM
					dump_debug("TRK: Incoming message queue overflow!  Dumping oldest.\r\n");
#endif		

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
				CTrackerMessage* pNewMessage = m_Messages.Add(msg);
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
		}
	}

	// exit the thread, set CEvent
	m_InputThreadDone.SetEvent();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerTcpInterface::ConnectSocket()
//
// Connect to the host if not already connected
//
BOOL CTrackerTcpInterface::ConnectSocket()
{
	// socket already connected?
	if( m_bConnected && m_Socket.IsCreated() )
		return TRUE;

	TRACE("GUI: Trying to connect...\n");
#ifdef _DEBUG_SOCKET_COMM
	dump_debug("GUI: Trying to connect...\r\n");
#endif

	// destroy socket (if necessary)
	m_Socket.Close();

	// create the socket
	try
	{
		m_Socket.Create();
	}
	catch(CWSocketException* pEx)
	{
		TRACE(_T("CTrackerTcpInterface::ConnectSocket(), create socket failed: Error:%d\n"), pEx->m_nError);
		pEx->Delete();

		Sleep(100);
		return FALSE;
	}

	// try to connect
	try
	{
		m_Socket.Connect(m_HostAddress, m_HostPort, TRACKER_TCP_CONNECT_TIMEOUT);
	}
	catch(CWSocketException* pEx)
	{
		TRACE(_T("CTrackerTcpInterface::ConnectSocket(), connect socket failed: Error:%d\n"), pEx->m_nError);
		pEx->Delete();

		m_Socket.Close();
		return FALSE;
	}

	TRACE("GUI: Socket connected\n");
#ifdef _DEBUG_SOCKET_COMM
	dump_debug("GUI: Socket connected\r\n");
#endif

	// set connected flag;
	m_bConnected = TRUE;

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerTcpInterface::SyncToMessage()
//
// Try to synchronize to the incoming data stream and find the start of
// a message (the sync word)
// Returns the sync word if successful or 0 on failure
//
USHORT CTrackerTcpInterface::SyncToMessage()
{
	unsigned char currentbyte = 0;
	unsigned char lastbyte = 0;

#ifdef _DEBUG
	if( !m_bInSync )
		TRACE0("GUI: Synchronizing socket stream\n");
#endif

#ifdef _DEBUG_SOCKET_COMM
	if( !m_bInSync )
		dump_debug("GUI: Synchronizing socket stream\r\n");
#endif		

	// search for sync words 0xA5A5, 0xA6A6 or 0xA7A7
	while( TRUE )
	{
		try
		{
			if( m_Socket.Receive(&currentbyte, 1) != 1 )
				return 0;
		}
		catch(CWSocketException* pEx)
		{
			TRACE(_T("CTrackerTcpInterface::SyncToMessage(), receive socket failed: Error:%d\n"), pEx->m_nError);
			pEx->Delete();

			m_bConnected = FALSE;
			return 0;
		}

		// received a good sync byte?
		if( (currentbyte == 0xA5) || (currentbyte == 0xA6) || (currentbyte == 0xA7) )
		{
			// got the full word?
			if( lastbyte == currentbyte )
			{
				// we are in sync!
#ifdef _DEBUG
				if( !m_bInSync )
					TRACE0("GUI: In sync!\n");
#endif
#ifdef _DEBUG_SOCKET_COMM
				if( !m_bInSync )
					dump_debug("GUI: In sync!\r\n");
#endif		
				// set flag
				m_bInSync = TRUE;

				if( currentbyte == 0xA5 )
					return GATE0_SYNC_WORD;
				else if( currentbyte == 0xA6 )
					return GATE1_SYNC_WORD;
				else if( currentbyte == 0xA7 )
					return GATE2_SYNC_WORD;
				else
				{
					TRACE1("CTrackerTcpInterface: Unknown sync byte 0x%02X!\n", (unsigned int)currentbyte);
					m_bInSync = FALSE;
				}
			}
		}
		else
		{
			// not in sync!
			m_bInSync = FALSE;

			TRACE1("TRK: %02X\n", (unsigned int)currentbyte);
#ifdef _DEBUG_SOCKET_COMM
			dump_debug("TRK: %02X\r\n", (unsigned int)currentbyte);
#endif		
		}

		lastbyte = currentbyte;
		currentbyte = 0;
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerTcpInterface::ReceiveMessage(CTrackerMessage& message)
//
// We reside in here until we get a message
//
BOOL CTrackerTcpInterface::ReceiveMessage(CTrackerMessage& message)
{
	// sync to a message
	USHORT syncword = SyncToMessage();

	if( syncword == 0 )
		return FALSE;

	// get the message type
	unsigned char FirstByte;
	unsigned char SecondByte;

	try
	{
		if( m_Socket.Receive(&FirstByte, 1) != 1 )
		{
			m_bConnected = FALSE;
			return FALSE;
		}

		if( m_Socket.Receive(&SecondByte, 1) != 1 )
		{
			m_bConnected = FALSE;
			return FALSE;
		}
	}
	catch(CWSocketException* pEx)
	{
		TRACE(_T("CTrackerTcpInterface::ReceiveMessage(), receive socket failed: Error:%d\n"), pEx->m_nError);
		pEx->Delete();

		m_bConnected = FALSE;
		return FALSE;
	}

	// exit if aborted
	if( m_bAbort )
		return FALSE;

	unsigned int MsgType = SecondByte;

	// setup the message type
	if( !message.SetType(MsgType, syncword) )
	{
		// unknown message
		TRACE("TRK: Failed to set message type to %d (unknown message type?)\n", (int)MsgType);		
#ifdef _DEBUG_SOCKET_COMM
		dump_debug("TRK: Failed to set message type to %d (unknown message type?)\r\n", (int)MsgType);
#endif		

		// set unknown message flag
		CSingleLock unknownlock(&m_UnknownCrit, TRUE);
		m_bInUnknown = TRUE;

		// increment unknown messages
		CSingleLock statslock(&m_StatsCrit, TRUE);
		m_nInUnknownMessages++;
		return FALSE;
	}

	// get the message raw buffer and size
	unsigned char* pRaw = message.GetRawBuffer();
	int nBytes = message.GetRawSize();

	ASSERT(pRaw);

	// skip over sync word which has already been set
	pRaw += 2;

	// set first and second byte
	*pRaw++ = FirstByte;
	*pRaw++ = SecondByte;

	// read the message data
	try
	{
		int nReadSize = nBytes-4;
		if( m_Socket.Receive(pRaw, nReadSize) != nReadSize )
		{
			m_bConnected = FALSE;
			return FALSE;
		}
	}
	catch(CWSocketException* pEx)
	{
		TRACE(_T("CTrackerTcpInterface::ReceiveMessage(), receive socket failed: Error:%d\n"), pEx->m_nError);
		pEx->Delete();

		m_bConnected = FALSE;
		return FALSE;
	}

	// exit if aborted
	if( m_bAbort )
		return FALSE;

	// we received a full message!
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// BeginOutputThread(LPVOID pParm)
//
// pParm is a pointer to a CTrackerTcpInterface and this function is a 
// friend which almost makes this a member function of the class
//
static UINT BeginOutputThread(LPVOID pParm)
{
	// Get pointer
	ASSERT(pParm);
	CTrackerTcpInterface* pThis = (CTrackerTcpInterface*)pParm;

	pThis->OutputThread();

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerTcpInterface::OutputThread()
//
// Thread routine to send queued data out
//
void CTrackerTcpInterface::OutputThread()
{
#ifdef _DEBUG_SOCKET_COMM
	char debugstr[1024];
#endif

	m_OutputThreadDone.ResetEvent();

	CSingleLock dataready(&m_OutputMessageAvailable, FALSE);

	CTrackerMessage* pMessage = NULL;
	DWORD NumberOfBytesWritten = 0;

	// loop until aborted
	while( !m_bAbort )
	{
		// wait until connected
		while( !m_bAbort && !m_bConnected )
			Sleep(50);

		if( m_bAbort )
			break;

		// send everything in the queue
		for(;;)
		{
			{
				CSingleLock l(&m_OutputQueueCrit, TRUE);

				// nothing in the queue to send?
				if( m_OutputQueue.GetSize() <= 0 )
					break;

				// wait for last message acknowledgment?
				if( m_bWaitForAck )
				{
					CSingleLock ackLock(&m_AckEvent);
					if( !ackLock.Lock(100) ) // 100ms timeout
						TRACE("Failed lock on message ack!\n");
				}

				// get a message to send
				pMessage = m_OutputQueue.GetAt(0);
			}

			ASSERT( pMessage );

			// compute the checksum
			pMessage->SetChecksum();

#ifdef _DEBUG_SOCKET_COMM
			pMessage->GetAsHexString(debugstr, 1023);
			dump_debug("GUI: %s\r\n", debugstr);
#endif
			// get the message raw buffer and size
			unsigned char* pBuffer = pMessage->GetRawBuffer();
			int nBytes = pMessage->GetRawSize();

			ASSERT(nBytes > 0);

			// try to write the message
			try
			{
				m_Socket.Send(pBuffer, nBytes);
			}
			catch(CWSocketException* pEx)
			{
#ifdef _DEBUG_SOCKET_COMM
				dump_debug("GUI: Failed to send message!\r\n");
#endif
				TRACE(_T("CTrackerTcpInterface::OutputThread(), send socket failed: Error:%d\n"), pEx->m_nError);
				pEx->Delete();
				break;
			}

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
// CTrackerTcpInterface::SetSMUserString(int nIndex, SM_USER_STRING_MSG* pSMUserString = NULL)
//
// Emulates bus level shared memory strings by sending normal
// user string messages over Ethernet.
//
// There are four strings (nIndex range: 1 to 4).
// The nIndex parameter is used the cache strings (for erasing them later).
// Passing a NULL pointer for the SM_USER_STRING_MSG structure will erase the string.
//
BOOL CTrackerTcpInterface::SetSMUserString(int nIndex, SM_USER_STRING_MSG* pSMUserString)
{
	// must be open with valid index parameter
	if( !m_IsOpen || (nIndex < 1) || (nIndex > 4) )
		return FALSE;

	// flags
	BOOL bEraseMessage = FALSE;
	BOOL bSendMessage = FALSE;

	// get pointer to the cached user string
	SM_USER_STRING_MSG* pCachedUserString = &m_SMUserStrings[nIndex-1];

	// no structure passed?
	if( pSMUserString == NULL )
	{
		// erase it
		bEraseMessage = TRUE;
	}
	else
	{
		// any change?
		if( memcmp(pCachedUserString, pSMUserString, sizeof(SM_USER_STRING_MSG)) != 0 )
		{
			// copy it to the cache
			*pCachedUserString = *pSMUserString;

			// set the send message flag
			bSendMessage = TRUE;
		}
	}

	// make sure we do not exceed the user string length message
	// payload or the shared memory string length
	// use smallest string length of the two
	int maxLength = (MAX_SM_USER_STRING_LEN < MAX_USER_STRING_LEN) ? MAX_SM_USER_STRING_LEN : MAX_USER_STRING_LEN;

	// erase it?
	if( bEraseMessage )
	{
		// anything in the string?
		if( pCachedUserString->string[0] != NULL )
		{
			// erase the text with spaces
			for( int i=0; i < maxLength; i++ )
			{
				if( pCachedUserString->string[i] != NULL )
					pCachedUserString->string[i] = ' ';
			}
			pCachedUserString->string[maxLength] = NULL;

			bSendMessage = TRUE;
		}
	}

	// send user string message to tracker?
	if( bSendMessage )
	{
		// create message
		CTrackerMessage msg;
		msg.SetDefaultUserString2();
		USER_STRING2_MSG* pUserStringMsg = msg.GetUserString2();

		pUserStringMsg->row = pCachedUserString->row;
		pUserStringMsg->col = pCachedUserString->col;

		for( int i=0; i < maxLength; i++ )
			pUserStringMsg->string[i] = pCachedUserString->string[i];
		pUserStringMsg->string[maxLength] = NULL;

		// add to output queue
		SendMessage(msg);
	}

	return TRUE;
}
