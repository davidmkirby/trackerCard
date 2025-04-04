///////////////////////////////////////////////////////////////////////////////
// CTrackerSerialPort.cpp - CTrackerSerialPort class
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
#include "TrackerSerialPort.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static UINT BeginInputThread(LPVOID pParm);
static UINT BeginOutputThread(LPVOID pParm);


///////////////////////////////////////////////////////////////////////////////
// Construction/Destruction
//
CTrackerSerialPort::CTrackerSerialPort()
{
	m_Handle = INVALID_HANDLE_VALUE;

	memset(&m_DCB, 0, sizeof(m_DCB));
	m_DCB.DCBlength = sizeof(m_DCB);

	m_bRTSControlEnable = FALSE;
	m_bXonXoff = FALSE;
	m_bNoHandshaking = FALSE;
}

CTrackerSerialPort::~CTrackerSerialPort()
{
	Close();
}

//////////////////////////////////////////////////////////////////////////////
// CTrackerSerialPort::ReadFromRegistry(LPCTSTR lpszSection)
//
// Gets this serial port's settings from the registry
//
BOOL CTrackerSerialPort::ReadFromRegistry(LPCTSTR lpszSection)
{
	CWinApp* pApp = AfxGetApp();
	if( pApp == NULL )
		return FALSE;

	CString str;

	m_Name = pApp->GetProfileString(lpszSection, "Name", "COM1");

	m_ComNumber = pApp->GetProfileInt(lpszSection, "Com Port", 1);
	if( m_ComNumber < 0 )
		m_ComNumber = 0;
	
	m_BaudRate = (DWORD)pApp->GetProfileInt(lpszSection, "Baud Rate", 115200);

	str = pApp->GetProfileString(lpszSection, "Parity", "o");
	m_Parity = str[0];
	
	m_DataBits = pApp->GetProfileInt(lpszSection, "Data Bits", 8);
	m_StopBits = pApp->GetProfileInt(lpszSection, "Stop Bits", 1);

	m_bXonXoff = pApp->GetProfileInt(lpszSection, "Xon Xoff", 0);
	m_bRTSControlEnable = pApp->GetProfileInt(lpszSection, "RTS control", 0);
	m_bNoHandshaking = pApp->GetProfileInt(lpszSection, "No Handshaking", 0);

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
// CTrackerSerialPort::WriteToRegistry(LPCTSTR lpszSection)
//
// Saves this serial port's settings to the registry
//
BOOL CTrackerSerialPort::WriteToRegistry(LPCTSTR lpszSection)
{
	CWinApp* pApp = AfxGetApp();
	if( pApp == NULL )
		return FALSE;

	CString str;

	pApp->WriteProfileString(lpszSection, "Name", m_Name);
	pApp->WriteProfileInt(lpszSection, "Com Port", m_ComNumber);
	pApp->WriteProfileInt(lpszSection, "Baud Rate", (int)m_BaudRate);

	str.Format("%c", m_Parity);
	pApp->WriteProfileString(lpszSection, "Parity", str);

	pApp->WriteProfileInt(lpszSection, "Data Bits", m_DataBits);
	pApp->WriteProfileInt(lpszSection, "Stop Bits", m_StopBits);

	pApp->WriteProfileInt(lpszSection, "Xon Xoff", m_bXonXoff);
	pApp->WriteProfileInt(lpszSection, "RTS control", m_bRTSControlEnable);
	pApp->WriteProfileInt(lpszSection, "No Handshaking", m_bNoHandshaking);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerSerialPort::Open()
//
// Opens the serial port for communication
//
BOOL CTrackerSerialPort::Open()
{
	// sanity
	ASSERT( !m_IsOpen );
	if( m_IsOpen )
		return TRUE;

	// disabled?
	if( m_ComNumber < 1 )
		return FALSE;

	CString FileName;
	FileName.Format(_T("\\\\.\\COM%d"), m_ComNumber);

	m_Handle = CreateFile(
		FileName,						// pointer to name of the file 
		GENERIC_READ | GENERIC_WRITE,	// access (read-write) mode 
		0,								// share mode (ours exclusivley)
		NULL,							// pointer to security descriptor 
		OPEN_EXISTING,					// how to create 
		0,								// file attributes 
		NULL );							// handle to file with attributes to copy  


	// check for error
	if( m_Handle == INVALID_HANDLE_VALUE )
	{
	    TRACE(_T("Failed to open comm port #%d\n"), m_ComNumber);
		return FALSE;
	}

	// setup the communication events to monitor
//	SetCommMask(m_Handle, EV_RXCHAR|EV_TXEMPTY);

	// get the default DCB
	ZeroMemory(&m_DCB, sizeof(m_DCB));

	if( !GetCommState(m_Handle, &m_DCB) )
	{
		TRACE( _T("Failed in call to GetCommState\n") );
		CloseHandle(m_Handle);
		m_Handle = INVALID_HANDLE_VALUE;
		return FALSE;
	}

	// setup the baud rate
	m_DCB.BaudRate = m_BaudRate; 

	// setup parity
	switch( toupper(m_Parity) )
	{
	case 'E':	m_DCB.Parity = EVENPARITY;	break;
	case 'M':	m_DCB.Parity = MARKPARITY;	break;
	case 'N':	m_DCB.Parity = NOPARITY;	break;
	case 'O':	m_DCB.Parity = ODDPARITY;	break;
	case 'S':	m_DCB.Parity = SPACEPARITY;	break;
	default:	ASSERT(FALSE);				break;
	}

	// setup the data bits
	m_DCB.ByteSize = m_DataBits;

	// setup the stop bits
	switch( m_StopBits )
	{
		case 1:		m_DCB.StopBits = ONESTOPBIT;	break;
		case 2:		m_DCB.StopBits = TWOSTOPBITS;	break;
		default:	ASSERT(FALSE);					break;
	}

	// setup handshaking
	if( m_bNoHandshaking )
	{
		m_DCB.fOutxCtsFlow = FALSE;
		m_DCB.fOutxDsrFlow = FALSE;
		m_DCB.fDtrControl = DTR_CONTROL_DISABLE;
		m_DCB.fRtsControl = RTS_CONTROL_ENABLE;
		m_DCB.fTXContinueOnXoff = TRUE;
		m_DCB.fOutX = FALSE;
		m_DCB.fInX = FALSE;
	}
	else
	{
		if( m_bXonXoff )
		{
			m_DCB.XonChar = '\021';
			m_DCB.XoffChar = '\023';
			m_DCB.fOutX = 1;
			m_DCB.fInX = 1;
		}

		if( m_bRTSControlEnable )
			m_DCB.fRtsControl = RTS_CONTROL_ENABLE;
	}

	// Try to set the comm port state
	if( !SetCommState(m_Handle, &m_DCB) )
	{
		TRACE(_T("Failed to set comm port state!\n"));
		CloseHandle(m_Handle);
		m_Handle = INVALID_HANDLE_VALUE;
		return FALSE;
	}

	COMMTIMEOUTS CommTimeouts;
	ZeroMemory(&CommTimeouts, sizeof(COMMTIMEOUTS));

	// get the current timeout values
	if( !GetCommTimeouts(m_Handle, &CommTimeouts) )
	{
		TRACE(_T("Failed to get comm port timouts!\n"));
		CloseHandle(m_Handle);
		m_Handle = INVALID_HANDLE_VALUE;
		return FALSE;
	}

	// zero read timeouts
	CommTimeouts.ReadIntervalTimeout = MAXDWORD;
	CommTimeouts.ReadTotalTimeoutMultiplier = 0;
	CommTimeouts.ReadTotalTimeoutConstant = 0;

	// set read timeouts (THIS GIVES SLOW PERFORMANCE)
//	CommTimeouts.ReadIntervalTimeout = MAXDWORD;
//	CommTimeouts.ReadTotalTimeoutMultiplier = MAXDWORD;
//	CommTimeouts.ReadTotalTimeoutConstant = 250;

	// zero write timeouts
    CommTimeouts.WriteTotalTimeoutMultiplier = 0;
    CommTimeouts.WriteTotalTimeoutConstant = 0;

	// set the new timeout values
	if( !SetCommTimeouts(m_Handle, &CommTimeouts) )
	{
		TRACE(_T("Failed to set comm port timouts!\n"));
		CloseHandle(m_Handle);
		m_Handle = INVALID_HANDLE_VALUE;
		return FALSE;
	}

	if( !PurgeComm(m_Handle, PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR) )	
	{
		TRACE(_T("Failed to purge comm port!\n"));
		CloseHandle(m_Handle);
		m_Handle = INVALID_HANDLE_VALUE;
		return FALSE;
	}

	// set the open flag
	m_IsOpen = TRUE;

	// start the polling thread
	Start();

	return TRUE;	
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerSerialPort::Close()
//
// Close the serial port
//
BOOL CTrackerSerialPort::Close()
{
	// check if already closed
	if( !m_IsOpen )
		return TRUE;

	// kill polling thread
	Stop();

	// close the serial handle	
	if( !CloseHandle(m_Handle) )
		return FALSE; 

	m_Handle = INVALID_HANDLE_VALUE;

	// call base class and exit
	return CTrackerInterface::Close();
}

/////////////////////////////////////////////////////////////////////////////
// CTrackerSerialPort::DoNotify(int event = 0)
//
// If a window has asked for async event notification this function will
// send them a message if something happens.
//
void CTrackerSerialPort::DoNotify(int event)
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
	PostMessage(m_hNotifyWnd, WM_TRACKER_SERIAL, (WPARAM)event, (LPARAM)this);
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerSerialPort::Start()
//
// Starts the polling thread.  Needed if reading from serial port.
//
BOOL CTrackerSerialPort::Start()
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
// CTrackerSerialPort::Stop()
//
// Stop the polling thread
//
BOOL CTrackerSerialPort::Stop()
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
// pParm is a pointer to a CTrackerSerialPort and this function is a 
// friend which almost makes this a member function of the class
//
static UINT BeginInputThread(LPVOID pParm)
{
	// Get pointer
	ASSERT(pParm);
	CTrackerSerialPort* pThis = (CTrackerSerialPort*)pParm;

	pThis->InputThread();

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerSerialPort::InputThread()
//
// Thread routine to read incoming serial data
//
void CTrackerSerialPort::InputThread()
{
	CTrackerMessage msg;
#ifdef _DEBUG_SERIAL_COMM
	char debugstr[1024];
#endif

	m_InputThreadDone.ResetEvent();

	// loop until aborted
	while( !m_bAbort )
	{
		m_bInSync = FALSE;

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

#ifdef _DEBUG_SERIAL_COMM
				msg.GetAsHexString(debugstr, 1023);
				dump_debug("TRK: Bad Checksum: %s\r\n", debugstr);
#endif
				// get next message
				continue;
			}

#ifdef _DEBUG_SERIAL_COMM
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
#ifdef _DEBUG_SERIAL_COMM
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
// CTrackerSerialPort::SyncToMessage()
//
// Try to synchronize to the incoming serial stream and find the start of
// a message (the sync word)
// Returns the sync word if successful or 0 on failure
//
USHORT CTrackerSerialPort::SyncToMessage()
{
	unsigned char currentbyte = 0;
	unsigned char lastbyte = 0;
	DWORD NumberOfBytesRead = 0;

#ifdef _DEBUG
	if( !m_bInSync )
		TRACE0("TRK: Synchronizing serial stream\n");
#endif

#ifdef _DEBUG_SERIAL_COMM
	if( !m_bInSync )
		dump_debug("TRK: Synchronizing serial stream\r\n");
#endif		

	// search for sync word 0xA5A5 or 0xA6A6
	while( TRUE )
	{
		if( !ReadFile(m_Handle, &currentbyte, 1, &NumberOfBytesRead, NULL) )
			break;

		// no data available on the serial port?
		if( NumberOfBytesRead == 0 )
		{
#ifdef CTRACKERINTERFACE_USE_MMTIMER
			CSingleLock lock(&m_MMTimerEvent, TRUE);
#else
			// yield the processor
			Sleep(1);
#endif

			// check if someone has aborted the polling
			if( m_bAbort )
				break;

			// continue reading the serial port
			continue;
		}

		ASSERT( NumberOfBytesRead == 1 );

		// received a good sync byte?
		if( (currentbyte == 0xA5) || (currentbyte == 0xA6) || (currentbyte == 0xA7) )
		{
			// got the full word?
			if( lastbyte == currentbyte )
			{
				// we are in sync!
#ifdef _DEBUG
				if( !m_bInSync )
					TRACE0("TRK: In sync!\n");
#endif
#ifdef _DEBUG_SERIAL_COMM
				if( !m_bInSync )
					dump_debug("TRK: In sync!\r\n");
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
					TRACE1("CTrackerSerialPort: Unknown sync byte 0x%02X!\n", (unsigned int)currentbyte);
					m_bInSync = FALSE;
				}
			}
		}
		else
		{
			// not in sync!
			m_bInSync = FALSE;

			TRACE1("TRK: %02X\n", (unsigned int)currentbyte);
#ifdef _DEBUG_SERIAL_COMM
			dump_debug("TRK: %02X\r\n", (unsigned int)currentbyte);
#endif		
		}

		lastbyte = currentbyte;
		currentbyte = 0;
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerSerialPort::ReceiveMessage(CTrackerMessage& message)
//
// We reside in here until we get a message
//
BOOL CTrackerSerialPort::ReceiveMessage(CTrackerMessage& message)
{
	// sync to a message
	USHORT syncword = SyncToMessage();

	if( syncword == 0 )
		return FALSE;

	DWORD NumberOfBytesRead = 0;

	// get the message type
	unsigned char FirstByte;

	while( !m_bAbort )
	{
		if( !ReadFile(m_Handle, &FirstByte, 1, &NumberOfBytesRead, NULL) )
			return FALSE;

		// did we get the byte?
		if( NumberOfBytesRead == 1 )
			break;

#ifdef CTRACKERINTERFACE_USE_MMTIMER
		CSingleLock lock(&m_MMTimerEvent, TRUE);
#else
		// no data was available, so yield the processor
		Sleep(0);
#endif
	}

	// exit if aborted
	if( m_bAbort )
		return FALSE;

//	Hard code the message type to status.
//	Right now there is no message type on messages coming from the
//	tracker.  If this is fixed in the future, this will allow different
//	message types to be received
//	unsigned int MsgType = STATUS_MSG_TYPE; // hard code type

	unsigned int MsgType = FirstByte;

	// setup the message type
	if( !message.SetType(MsgType, syncword) )
	{
		// unknown message
		TRACE("TRK: Failed to set message type to %d (unknown message type?)\n", (int)MsgType);		
#ifdef _DEBUG_SERIAL_COMM
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

	// skip over sync word
	pRaw += 2;

	// set first byte
	*pRaw++ = FirstByte;

	// loop to read message data
	for( int i=3; i < nBytes; )
	{
		if( !ReadFile(m_Handle, pRaw, 1, &NumberOfBytesRead, NULL) )
			return FALSE;

		// if NumberOfBytesRead is 0 then no data was available
		if( NumberOfBytesRead == 0 )
		{
#ifdef CTRACKERINTERFACE_USE_MMTIMER
			CSingleLock lock(&m_MMTimerEvent, TRUE);
#else
			// yield the processor
			Sleep(0);
#endif
			// check if someone has aborted the polling
			if( m_bAbort )
				return FALSE;

			continue;
		}

		// got a byte
		pRaw++;
		i++;
	}

	// byte swap the message (to Intel byte order)
	message.ByteSwap();

	// we received a full message!
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// BeginOutputThread(LPVOID pParm)
//
// pParm is a pointer to a CTrackerSerialPort and this function is a 
// friend which almost makes this a member function of the class
//
static UINT BeginOutputThread(LPVOID pParm)
{
	// Get pointer
	ASSERT(pParm);
	CTrackerSerialPort* pThis = (CTrackerSerialPort*)pParm;

	pThis->OutputThread();

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerSerialPort::OutputThread()
//
// Thread routine to send queued data out the serial port
//
void CTrackerSerialPort::OutputThread()
{
#ifdef _DEBUG_SERIAL_COMM
	char debugstr[1024];
#endif

	m_OutputThreadDone.ResetEvent();

	CSingleLock dataready(&m_OutputMessageAvailable, FALSE);

	CTrackerMessage* pMessage = NULL;
	DWORD NumberOfBytesWritten = 0;

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

#ifdef _DEBUG_SERIAL_COMM
			pMessage->GetAsHexString(debugstr, 1023);
			dump_debug("GUI: %s\r\n", debugstr);
#endif
			// byte swap the message (to Motorola byte order)
			pMessage->ByteSwap();

			// get the message raw buffer and size
			unsigned char* pBuffer = pMessage->GetRawBuffer();
			int nBytes = pMessage->GetRawSize();

			ASSERT(nBytes > 0);

			// try to write the message
			if( !WriteFile(m_Handle, pBuffer, nBytes, &NumberOfBytesWritten, NULL) )
			{
#ifdef _DEBUG_SERIAL_COMM
				dump_debug("Failed to send message!\r\n");
#endif
				ASSERT(FALSE);
			}

			ASSERT( (int)NumberOfBytesWritten == nBytes );

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
