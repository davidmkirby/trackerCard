///////////////////////////////////////////////////////////////////////////////
// TrkrPciApi.h
//
// API for Model 6007 PCI Tracker
// API for Model 7007 PCI Tracker
// API for Model 7010 PCI Express Tracker
// API for Model 7410 PCI Express Tracker

/*******************************************************************************
 * Copyright (c) 2014 Electro-Optical Imaging, Inc. All Rights Reserved
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

#ifndef __TrkrPciApi_H__
#define __TrkrPciApi_H__

#ifdef __cplusplus
extern "C" {
#endif

// DLL support
#ifndef EXPORT
    #if defined(_WIN32)
        #define EXPORT __declspec(dllexport)
    #else
        #define EXPORT
    #endif
#endif

#ifndef USHORT
	typedef unsigned short	USHORT;
#endif

///////////////////////////////////////////////////////////////////////////////
// tracker memory access defines
//
#define TRKR_COMMAND_OFFSET			0x0000	// Command messages
#define TRKR_COMMAND_MAILBOX		0x01FF

#define TRKR_USER_STRING1_OFFSET	0x0100	// Fast user annotation string
#define TRKR_USER_STRING2_OFFSET	0x0116	// Fast user annotation string
#define TRKR_USER_STRING3_OFFSET	0x012C	// Fast user annotation string
#define TRKR_USER_STRING4_OFFSET	0x0142	// Fast user annotation string

#define TRKR_STATUS_OFFSET			0x0200	// Status messages (field/frame rate)
#define TRKR_STATUS_MAILBOX			0x03FF

#define TRKR_RESPONSE_OFFSET		0x0240	// Query response messages
#define TRKR_RESPONSE_MAILBOX		0x03FE

#define TRKR_MOUNT_PERF_OFFSET		0x0280	// Mount performance data
#define TRKR_MOUNT_PERF_MAILBOX		0x03FD

#define TRKR_FRAME_TIMER_OFFSET		0x0300	// Video field/frame time as measured
											//   from vertical sync (LSB is 16ns)


///////////////////////////////////////////////////////////////////////////////
// TrkrPciGetLibraryVersion(char* pLibraryVersion)
//
// Copies the library version string into the string buffer supplied.
// The user supplied buffer should be AT LEAST 8 characters.
//
void EXPORT TrkrPciGetLibraryVersion(char* pLibraryVersion);


///////////////////////////////////////////////////////////////////////////////
// TrkrPciGetNumberOfBoards(void)
//
// Get number of tracker boards on the PCI bus
//
int EXPORT TrkrPciGetNumberOfBoards(void);


///////////////////////////////////////////////////////////////////////////////
// TrkrPciOpenBoard(int BoardNumber)
//
// Open a connection to a tracker board.  If TrkrPciGetNumberOfBoards returns
// 4, then you can pass 0 to 3 to this function to select the appropriate board.
// Multiple tracker boards in a system are enumerated by the PCI bus.  This
// enumeration will stay constant until boards are moved to different PCI
// slots or new boards are added or removed from the computer.
//
// This function returns NULL if it fails to find or open a connection to
// the tracker board.
//
HANDLE EXPORT TrkrPciOpenBoard(int BoardNumber);


///////////////////////////////////////////////////////////////////////////////
// TrkrPciCloseBoard(HANDLE hBoard)
//
// Close a connection to a tracker board.
//
void EXPORT TrkrPciCloseBoard(HANDLE hBoard);


///////////////////////////////////////////////////////////////////////////////
// TrkrPciMapMemory(HANDLE hBoard, volatile unsigned short** ppVirtualAddress)
//
// Map the tracker's communication memory into virtual address space.
// This function returns a pointer which can be used to read and write
// data to the tracker's communication memory (16-bit reads/writes ONLY).
//
// Pointer will be NULL on failure.
//
// NOTE: THIS IS A LOWER LEVEL FUNCTION AND IT IS NOT NECESSARY TO USE
//       IT WHEN WRITING A TYPICAL APPLICATION
//
void EXPORT TrkrPciMapMemory(HANDLE hBoard, volatile unsigned short** ppVirtualAddress);


///////////////////////////////////////////////////////////////////////////////
// TrkrPciUnMapMemory(unsigned short* pVirtualAddress)
//
// Releases a previously mapped virtual address space.
//
// NOTE: THIS IS A LOWER LEVEL FUNCTION AND IT IS NOT NECESSARY TO USE
//       IT WHEN WRITING A TYPICAL APPLICATION
//
void EXPORT TrkrPciUnMapMemory(HANDLE hBoard, volatile unsigned short* pVirtualAddress);


///////////////////////////////////////////////////////////////////////////////
// TrkrPciAttachMessageInterrupt(HANDLE hBoard, HANDLE* pInterruptEvent)
//
// Attach incoming message interrupt event handle and enable the interrupt.
//
// NOTE: BE SURE TO OBSERVE THE FOLLOWING GUIDELINES
//
// - Never call CloseHandle() to release the handle created by this function.
//   When an application terminates, the API will release all memory created
//   as a result of use of this function.
//
// - Memory for the event handle pointer must remain persistent. The handle
//   pointer should either be declared as static or should be allocated manually
//   with a call to malloc(). If not, the API function will continue to allocate
//   resources and the system may crash.
//
// - To make the best use of memory, applications should re-use an event handle,
//   if possible, when re-attaching, provided the event has been signaled already.
//
// - Both the status and response incoming message mailboxes assert this interrupt.
//   They both must be serviced and cleared before calling this function again. 
//
BOOL EXPORT TrkrPciAttachMessageInterrupt(HANDLE hBoard, HANDLE* pInterruptEvent);


///////////////////////////////////////////////////////////////////////////////
// TrkrPciGetStatusMessage(HANDLE hBoard, void* pStatusMessage, size_t StatusMessageSize)
//
// Returns TRUE if a status message is available.  If a non-NULL pointer
// was supplied for pStatusMessage, then the status message is copied into
// the user supplied buffer and the status mailbox is cleared (allowing
// the tracker to send another message when available).
//
// Returns FALSE (=0) if a status message is not available or the board
// handle is invalid.
//
// IMPORTANT NOTE: IF YOU PLAN ON ISSUING QUERIES TO THE TRACKER, YOU MUST
//                 SERVICE BOTH TYPES OF MESSAGES (IF PENDING) IN ORDER
//                 TO CLEAR THE INTERRUPT.  ALSO, WHEN USING INERRUPT
//				   TRIGGERED WINDOWS MESSAGE POSTING, YOU MUST SERVICE
//				   THE RESPONSE MESSAGE BEFORE THE STATUS MESSAGE.  IN
//				   THIS CASE, SERVICING THE STATUS MESSAGE WILL RE-ENABLE
//				   THE INTERRUPT.
//
BOOL EXPORT TrkrPciGetStatusMessage(HANDLE hBoard, void* pStatusMessage, size_t StatusMessageSize);


///////////////////////////////////////////////////////////////////////////////
// TrkrPciGetResponseMessageType(HANDLE hBoard, USHORT* pResponseMessageType)
//
// Returns TRUE if a response message is available.  If a non-NULL pointer
// was supplied for pResponseMessageType, then pResponseMessageType is set
// to the response message type available.
//
// Returns FALSE (=0) if a response message is not available or the board
// handle is invalid.
//
BOOL EXPORT TrkrPciGetResponseMessageType(HANDLE hBoard, USHORT* pResponseMessageType);


///////////////////////////////////////////////////////////////////////////////
// TrkrPciGetResponseMessage(HANDLE hBoard, void* pResponseMessage, size_t ResponseMessageSize)
//
// Returns TRUE if a response message is available.  If a non-NULL pointer
// was supplied for pResponseMessage, then the response message is copied into
// the user supplied buffer and the response mailbox is cleared (allowing
// the tracker to send another message when available).
//
// Returns FALSE (=0) if a response message is not available or the board
// handle is invalid.
//
// IMPORTANT NOTE: IF YOU PLAN ON ISSUING QUERIES TO THE TRACKER, YOU MUST
//                 SERVICE BOTH TYPES OF MESSAGES (IF PENDING) IN ORDER
//                 TO CLEAR THE INTERRUPT.  ALSO, WHEN USING INERRUPT
//				   TRIGGERED WINDOWS MESSAGE POSTING, YOU MUST SERVICE
//				   THE RESPONSE MESSAGE BEFORE THE STATUS MESSAGE.  IN
//				   THIS CASE, SERVICING THE STATUS MESSAGE WILL RE-ENABLE
//				   THE INTERRUPT.
//
BOOL EXPORT TrkrPciGetResponseMessage(HANDLE hBoard, void* pResponseMessage, size_t ResponseMessageSize);


///////////////////////////////////////////////////////////////////////////////
// TrkrPciReadyToSendCommandMessage(HANDLE hBoard)
//
// Returns TRUE if the tracker is ready to accept a command message
// (ie-the command mailbox is equal to zero)
//
// Returns FALSE (=0) if not clear to send a command message or the board
// handle is invalid.
//
BOOL EXPORT TrkrPciReadyToSendCommandMessage(HANDLE hBoard);


///////////////////////////////////////////////////////////////////////////////
// TrkrPciSendCommandMessage(HANDLE hBoard, void* pCommandMessage, size_t CommandMessageSize)
//
// Returns TRUE if the command message was sent.  If a non-NULL pointer
// was supplied for pCommandMessage, then the command message is sent to
// the tracker and the command mailbox is set (signaling the tracker to
// process the message).
//
// Returns FALSE (=0) if not clear to send a command message, the board
// handle is invalid or a NULL pointer was supplied for pCommandMessage.
//
BOOL EXPORT TrkrPciSendCommandMessage(HANDLE hBoard, void* pCommandMessage, size_t CommandMessageSize);


///////////////////////////////////////////////////////////////////////////////
// TrkrPciGetFrameTimer(HANDLE hBoard, unsigned int* pTimer)
//
// Reads the tracker's field/frame hardware timer, which is the time in 16ns
// increments since the start (vertical sync) of the current field/frame.
// NOTE: *pTimer * 0.000016 = milliseconds since last vertical sync
//
// Returns FALSE (=0) if the board handle is invalid or pTimer is NULL.
//
BOOL EXPORT TrkrPciGetFrameTimer(HANDLE hBoard, unsigned int* pTimer);


///////////////////////////////////////////////////////////////////////////////
// TrkrPciAttachWindowsMessage(HANDLE hBoard, HWND hWnd, UINT Msg)
//
// Attach a window handle and message ID to the interrupt event handler
// thread.  This will post a callback message to a given window to handle
// received messages (both status and response).
//
// The LPARAM of the callback message will be the handle to the tracker board.
//
BOOL EXPORT TrkrPciAttachWindowsMessage(HANDLE hBoard, HWND hWnd, UINT Msg);


///////////////////////////////////////////////////////////////////////////////
// TrkrPciDetachWindowsMessage(HANDLE hBoard, HWND hWnd)
//
// Removes a previously attached window handle (and message ID) from the
// interrupt event handler thread.  This will not cancel any previously
// queued messages to the window.
//
BOOL EXPORT TrkrPciDetachWindowsMessage(HANDLE hBoard, HWND hWnd);



///////////////////////////////////////////////////////////////////////////////
//
// Generic PCI bus access functions to support other boards
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// GenericPciGetNumberOfBoards(USHORT VendorId, USHORT DeviceId)
//
// Get the number of a certain type of boards on the PCI bus
//
int EXPORT GenericPciGetNumberOfBoards(USHORT VendorId, USHORT DeviceId);


///////////////////////////////////////////////////////////////////////////////
// GenericPciOpenBoard(int BoardNumber, USHORT VendorId, USHORT DeviceId)
//
// Open a connection to a PCI board.  If GenericPciGetNumberOfBoards returns
// 4, then you can pass 0 to 3 to this function to select the appropriate board.
//
// This function returns NULL if it fails to find or open a connection to
// the tracker board.
//
HANDLE EXPORT GenericPciOpenBoard(int BoardNumber, USHORT VendorId, USHORT DeviceId);


///////////////////////////////////////////////////////////////////////////////
// GenericPciCloseBoard(HANDLE hBoard)
//
// Close a connection to a PCI board.
//
void EXPORT GenericPciCloseBoard(HANDLE hBoard);


///////////////////////////////////////////////////////////////////////////////
// GenericPciMapMemory(HANDLE hBoard, int BarIndex, volatile unsigned long** ppVirtualAddress)
//
// Maps a PCI board's local memory into virtual address space.
// This function returns a pointer which can be used to read and write
// data to the PCI board's shared memory.
//
// Pointer will be NULL on failure.
//
void EXPORT GenericPciMapMemory(HANDLE hBoard, int BarIndex, volatile unsigned long** ppVirtualAddress);


///////////////////////////////////////////////////////////////////////////////
// GenericPciUnMapMemory(HANDLE hBoard, volatile unsigned long* pVirtualAddress)
//
// Releases a previously mapped virtual address space.
//
void EXPORT GenericPciUnMapMemory(HANDLE hBoard, volatile unsigned long* pVirtualAddress);


#ifdef __cplusplus
}
#endif

#endif // __TrkrPciApi_H__
