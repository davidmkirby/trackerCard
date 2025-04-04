// Status.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../../TrkrPciApi/TrkrPciApi.h"
#include "../../classes/MSG_FMT.h"

PING_MSG			TrkrPingMsg;
SYSTEM_CTRL_MSG		TrkrSystemMsg;
STATUS_MSG			TrkrStatusMsg;
HANDLE				hTrackerBoard;


char StateStrings[][20] =
	{
	"Initialization",
	"Acquire",
	"Pending Track",
	"On Track",
	"Coast",
	"Off Track",
	"Auto Acquire"
	};

///////////////////////////////////////////////////////////////////////////////
// Set the checksum on a message
//
void SetChecksum(void* pMsg, size_t MsgSize)
{
	const unsigned char* pBuffer;
	short sum;
	int nBytes, i;

	// get length to add up
	nBytes = MsgSize - 2;

	// sum up all the data bytes
	pBuffer = (unsigned char*)pMsg;
	sum = 0;

	for( i=0; i < nBytes; i++ )
	{
		sum += *pBuffer;
		pBuffer++;
	}

	// set the message checksum
	*((short*)pBuffer) = -sum;
}

///////////////////////////////////////////////////////////////////////////////
// Verify the checksum on a message
//
BOOL VerifyChecksum(void* pMsg, size_t MsgSize)
{
	const unsigned char* pBuffer;
	short sum;
	int nBytes, i;

	// sanity
	if( pMsg == NULL )
		return FALSE;

	// get length to add up
	nBytes = MsgSize - 2;

	// sum up all the data bytes
	pBuffer = (unsigned char*)pMsg;
	sum = 0;

	for( i=0; i < nBytes; i++ )
	{
		sum += *pBuffer;
		pBuffer++;
	}

	// add to message checksum
	sum += *((short*)pBuffer);

	// sum should be zero
	return (sum == 0);
}

///////////////////////////////////////////////////////////////////////////////
// Initialize tracker messages
//
void InitMessages()
{
	memset(&TrkrStatusMsg, 0, sizeof(STATUS_MSG));

	memset(&TrkrPingMsg, 0, sizeof(PING_MSG));
	TrkrPingMsg.sync = GATE0_SYNC_WORD;
	TrkrPingMsg.msg_type = PING_MSG_TYPE;

	memset(&TrkrSystemMsg, 0, sizeof(SYSTEM_CTRL_MSG));
	TrkrSystemMsg.sync				= GATE0_SYNC_WORD;
	TrkrSystemMsg.msg_type			= SYSTEM_CTRL_MSG_TYPE;
	TrkrSystemMsg.vid_src			= VS_ANALOG1;
	TrkrSystemMsg.out_60hz			= OFF;
	TrkrSystemMsg.dualgates			= DISABLE;
	TrkrSystemMsg.auto_size_ratio	= 150;	// 1.50:1 gate to target ratio
	TrkrSystemMsg.vec_trans_time	= 4;
	TrkrSystemMsg.acquire_val_time	= 1;
}

///////////////////////////////////////////////////////////////////////////////
// Send the tracker a message
//
BOOL SendTrackerMessage(void* pMsg, size_t MsgSize)
{
	int nSleepCount;

	// set message checksum
	SetChecksum(pMsg, MsgSize);

	// wait until the tracker is ready
	nSleepCount = 0;
	while( !TrkrPciReadyToSendCommandMessage(hTrackerBoard) )
	{
		// sleep 10ms
		Sleep(10);
		nSleepCount++;

		// timeout after 1 second
		if( nSleepCount > 100 )
		{
			printf("Timed out trying to send the tracker a message!\n");
			return FALSE;
		}
	}

	// send the message
	return TrkrPciSendCommandMessage(hTrackerBoard, pMsg, MsgSize);
}

///////////////////////////////////////////////////////////////////////////////
// Get a tracker status message
//
BOOL GetStatusMessage(void* pMsg, size_t MsgSize)
{
	int nSleepCount;

	// wait until the tracker is ready
	nSleepCount = 0;
	while( !TrkrPciGetStatusMessage(hTrackerBoard, pMsg, MsgSize) )
	{
		// sleep 10ms
		Sleep(10);
		nSleepCount++;

		// timeout after 1 second
		if( nSleepCount > 100 )
		{
			printf("Timed out trying to get a tracker STATUS message!\n");
			return FALSE;
		}
	}

	// verify checksum
	if( !VerifyChecksum(pMsg, MsgSize) )
	{
		printf("Checksum of received STATUS message was invalid!\n");
		return FALSE;
	}

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Format a status message as a text string
//
void FormatStatusMessage(char* pBuffer, const STATUS_MSG* pMsg)
{
	sprintf(pBuffer, "State = %14s, ErrX = %8.3f, ErrY = %8.3f", StateStrings[pMsg->trk_state],
		    pMsg->txerr/32.0, pMsg->tyerr/32.0);
}


int main(int argc, char* argv[])
{
	int nBoards, i;
	char TextBuffer[100];
	time_t StartTime, StopTime;

	printf("-----------------------------------\n");
	printf("   Electro-Optical Imaging, Inc.\n");
	printf("    Model 6007/6008 PCI Tracker\n");
	printf(" Status Message Sample Application\n");
	printf("-----------------------------------\n");
	printf("\n");

	// init tracker messages
	InitMessages();

	// verify tracker
	nBoards = TrkrPciGetNumberOfBoards();
	if( nBoards < 1 )
	{
		printf("No tracker boards found on the PCI bus!\n");
		return 1;
	}

	printf("Found %d tracker boards on the PCI bus.\n", nBoards);

	// open the tracker board
	hTrackerBoard = TrkrPciOpenBoard(0);
	if( hTrackerBoard == NULL )
	{
		printf("Failed to open the tracker board!\n");
		return 1;
	}

	printf("Opened tracker board #0 successfully.\n");

	// configure tracker to only send status messages when polled
	TrkrSystemMsg.out_60hz = DISABLE;
	if( !SendTrackerMessage(&TrkrSystemMsg, sizeof(SYSTEM_CTRL_MSG) ) )
	{
		printf("Failed to send the tracker a SYSTEM message!\n");
		return 1;
	}
	
	// wait for command message to be processed by tracker
	Sleep(250);

	printf("Tracker configured for status polling.\n");

	printf("\n--- Start tracker polling demo ---\n");

	// remove stale status message (if it exists)
	TrkrPciGetStatusMessage(hTrackerBoard, &TrkrStatusMsg, sizeof(STATUS_MSG));

	for( i=1; i < 6; i++ )
	{
		// try to get a STATUS message
		if( GetStatusMessage(&TrkrStatusMsg, sizeof(STATUS_MSG)) )
		{
			// this code should not run!
			printf("OOPS!  We got a tracker status message!\n");
			printf("This should not happen when polling is disabled.\n\n");
		}
		else // we should get here
			printf("Waited %i second(s) with no status messages available (all is well).\n\n", i);
	}

	for( i=0; i < 4; i++ )
	{
		printf("Press a key to poll the tracker for status: ");
		_getch();
		printf("\n");

		// send PING message
		if( !SendTrackerMessage(&TrkrPingMsg, sizeof(PING_MSG)) )
		{
			printf("Failed to send the tracker a PING message!\n");
			break;
		}

		// get STATUS message
		if( !GetStatusMessage(&TrkrStatusMsg, sizeof(STATUS_MSG)) )
		{
			printf("Failed to get the tracker status message!\n");
			break;
		}

		// format STATUS message for print
		FormatStatusMessage(TextBuffer, &TrkrStatusMsg);

		printf(TextBuffer);
		printf("\n\n");
	}

	printf("\n--- Start tracker field rate status demo ---\n");

	// configure tracker for real time status updates
	TrkrSystemMsg.out_60hz = ENABLE;
	if( !SendTrackerMessage(&TrkrSystemMsg, sizeof(SYSTEM_CTRL_MSG) ) )
	{
		printf("Failed to send the tracker a SYSTEM message!\n");
		return 1;
	}

	// wait for command message to be processed by tracker
	Sleep(250);

	printf("Tracker configured for real time status updates.\n\n");

	// display messages for 5 seconds (assuming 60Hz video)
	StartTime = time(NULL);
	for( i=0; i < 60*5; i++ )
	{
		// get STATUS message
		if( !GetStatusMessage(&TrkrStatusMsg, sizeof(STATUS_MSG)) )
		{
			printf("Failed to get the tracker status message!\n");
			break;
		}

		// format STATUS message for print
		FormatStatusMessage(TextBuffer, &TrkrStatusMsg);

		printf(TextBuffer);
		printf("\r");
	}
	StopTime = time(NULL);

	printf("\n\n");

	printf("Processed real time updates for about %d seconds.\n\n", StopTime-StartTime);

	// clean up
	TrkrPciCloseBoard(hTrackerBoard);

	printf("DONE!\n");

	return 0;
}

