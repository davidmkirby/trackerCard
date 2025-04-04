///////////////////////////////////////////////////////////////////////////////
// TrackerConfiguration.cpp
//

/*******************************************************************************
* Copyright (c) 2013 Electro-Optical Imaging, Inc. All Rights Reserved
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
#include "TrackerConfiguration.h"


//////////////////////////////////////////////////////////////////////////////
// Main message table for query of entire tracker configuration
//
int MessageQueryTable[] =
{
	CAPABILITIES_MSG_TYPE,				// capabilities first (read only)
	AAQ_ACQUIRE_CTRL_MSG_TYPE,			// do auto-acquire stuff first (it messes up other messages)
	AAQ_TRACK_CTRL_MSG_TYPE,
	AAQ_TGT_SELECT_CTRL_MSG_TYPE,
	RUN_TIME_CTRL_MSG_TYPE,
	SYSTEM_CTRL_MSG_TYPE,
//	LOS_OFFSET_CTRL_MSG_TYPE,
	LOS_OFFSET_CTRL2_MSG_TYPE,			// newer version (if available) will override older version
//	OFFSET_AIM_CTRL_MSG_TYPE,
	OFFSET_AIM_CTRL2_MSG_TYPE,			// newer version (if available) will override older version
	SYMBOLOGY_CTRL_MSG_TYPE,
	CORRELATION_CTRL_MSG_TYPE,
	FILTER_CTRL_MSG_TYPE,
	COAST_CTRL_MSG_TYPE,
	TGT_VALIDATION_CTRL_MSG_TYPE,
	ANNOTATION_MSG_TYPE,
	SCAN_MSG_TYPE,
	CONTROL_BOX_MSG_TYPE,
	LRF_CONTROL_MSG_TYPE,
	GATE_CONTROL_MSG_TYPE,
	TARGET_SIMULATOR_MSG_TYPE,
	STEERED_MIRROR_FILTER_MSG_TYPE,
	MT_GENERAL_MSG_TYPE,
	MT_ACQUIRE_MSG_TYPE,
	MT_TRACK_MSG_TYPE,
	MT_VALIDATION_MSG_TYPE,
	CONFIG_GATE_SIZE_MSG_TYPE,
	CONFIG_GATE_POS_MSG_TYPE,
//	CONFIG_ANNOTATION_MSG_TYPE,
	CONFIG_ANNOTATION2_MSG_TYPE,		// newer version (if available) will override older version
	CONFIG_SYMBOLOGY_MSG_TYPE,
	CONFIG_CORR_REF_POS_MSG_TYPE,
	CONFIG_VIDEO_MSG_TYPE,
//	CONFIG_PRESET_CONFIG_MSG_TYPE,	// SKIP THIS, it will write to FLASH and take over 1 second to complete!
	CONFIG_AUTOSIZE_MSG_TYPE,
	CONFIG_VALIDATION_MSG_TYPE,
	CONFIG_JOYSTICK_MSG_TYPE,
	CONFIG_MOUNT_MSG_TYPE,
	CONFIG_ANALOG_JOYSTICK_MSG_TYPE,
	CONFIG_DIGITAL_IO_MSG_TYPE,
	CONFIG_ZOOM_TO_RANGE_MSG_TYPE,
	CONFIG_GATE_STYLE_MSG_TYPE,
//	CONFIG_GATE_RETICLE_MSG_TYPE,
	CONFIG_GATE_RETICLE2_MSG_TYPE,		// newer version (if available) will override older version
	CONFIG_LOS_RETICLE_MSG_TYPE,
	CONFIG_TRACK_FLAG_MSG_TYPE,
	CONFIG_NORTH_OFFSET_MSG_TYPE,
	CONFIG_DIGITAL_VIDEO_MSG_TYPE,
	CONFIG_SERIAL_PORTS_MSG_TYPE,
	CONFIG_CONTROL_BOX_MSG_TYPE,
	CONFIG_TARGET_SIMULATOR_MSG_TYPE,
	CONFIG_AUTOTHRESHOLD_MSG_TYPE,
	CONFIG_ETHERNET_MSG_TYPE,
//	CONFIG_DIGITAL_VIDEO_EXT_MSG_TYPE,	// Model 6007 ONLY (DEPRECATED)
	CONFIG_DIGITAL_PREPROCESS_MSG_TYPE,
	CONFIG_IFF_TRACK_MSG_TYPE,
	CONFIG_INTRUSION_DETECT_MSG_TYPE,
	CONFIG_POS_TRACK_MSG_TYPE,
	CONFIG_CONTROL_BOX_IO_MSG_TYPE,
	CONFIG_VIDEO_SWITCH_MSG_TYPE,
	CONFIG_GPS_MSG_TYPE,
	LENS_CONFIG_MSG_TYPE,			// must query all connected lenses
//	CAMERA_CONFIG_MSG_TYPE,			// must query all connected cameras (DEPRECATED)
};

const int nMessageQueryTableSize = sizeof(MessageQueryTable)/sizeof(int);


///////////////////////////////////////////////////////////////////////////////
// CTrackerConfiguration constructor/destructor
//
CTrackerConfiguration::CTrackerConfiguration(void)
	: m_MessageArray(8), m_QueryArray(8)
{
	m_QueryIndex = 0;
	m_QueryReceived = 0;
	m_QueryTimedOut = 0;
	m_bQueryRunning = FALSE;
	m_bAbortQueryThread = TRUE;
}

CTrackerConfiguration::~CTrackerConfiguration(void)
{
	// make sure query thread is not running (abort if necessary)
	m_bAbortQueryThread = TRUE;
	CSingleLock lock(&m_QueryThreadCrit, TRUE);
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerConfiguration::HasSubtype(int type) const
//
// Returns TRUE if the message type specified will take a subtype identifier
//
BOOL CTrackerConfiguration::HasSubtype(int type) const
{
	switch( type )
	{
	case LENS_SERIAL_TFOV_MSG_TYPE:
	case LENS_SERIAL_DFOV_MSG_TYPE:
	case LENS_GENERIC_MSG_TYPE:
	case LENS_SERIAL_ZOOM_MSG_TYPE:
	case LENS_SERIAL_IR_ZOOM_MSG_TYPE:
	case LENS_ANALOG_ZOOM_MSG_TYPE:
	case CAMERA_GENERIC_MSG_TYPE:
	case LENS_SERIAL_FIXED_FOV_MSG_TYPE:
	case LENS_SERIAL_IR_DFOV_MSG_TYPE:
	case LENS_MOOG_ZOOM_MSG_TYPE:
		return TRUE;

	default:
		break;
	}

	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerConfiguration::GetSubtype(const CTrackerMessage* pMessage) const
//
// Returns the subtype of the message (or -1 if none)
//
int CTrackerConfiguration::GetSubtype(const CTrackerMessage* pMessage) const
{
	switch( pMessage->GetType() )
	{
	case LENS_SERIAL_TFOV_MSG_TYPE:
		return pMessage->GetLensSerialTfov()->video_source;

	case LENS_SERIAL_DFOV_MSG_TYPE:
		return pMessage->GetLensSerialDfov()->video_source;

	case LENS_GENERIC_MSG_TYPE:
		return pMessage->GetLensGeneric()->video_source;

	case LENS_SERIAL_ZOOM_MSG_TYPE:
		return pMessage->GetLensSerialZoom()->video_source;

	case LENS_SERIAL_IR_ZOOM_MSG_TYPE:
		return pMessage->GetLensSerialIrZoom()->video_source;

	case LENS_ANALOG_ZOOM_MSG_TYPE:
		return pMessage->GetLensAnalogZoom()->video_source;

	case CAMERA_GENERIC_MSG_TYPE:
		return pMessage->GetCameraGeneric()->video_source;

	case LENS_SERIAL_FIXED_FOV_MSG_TYPE:
		return pMessage->GetLensSerialFixedFov()->video_source;

	case LENS_SERIAL_IR_DFOV_MSG_TYPE:
		return pMessage->GetLensSerialIrDfov()->video_source;

	case LENS_MOOG_ZOOM_MSG_TYPE:
		return pMessage->GetLensMoogZoom()->video_source;

	default:
		break;
	}

	return -1;
}


///////////////////////////////////////////////////////////////////////////////
// CTrackerConfiguration::IsSubtype(int nIndex, int subtype) const
//
// Determines if the message is of the specified subtype (message id)
// This is currently used to check if a lens or camera type message is
// connected to the specified video source (subtype=video source)
//
BOOL CTrackerConfiguration::IsSubtype(int nIndex, int subtype) const
{
	if( (nIndex < 0) || (nIndex >= m_MessageArray.GetSize()) )
		return FALSE;

	switch( m_MessageArray[nIndex].GetType() )
	{
	case LENS_SERIAL_TFOV_MSG_TYPE:
		if( m_MessageArray[nIndex].GetLensSerialTfov()->video_source == subtype )
			return TRUE;
		break;

	case LENS_SERIAL_DFOV_MSG_TYPE:
		if( m_MessageArray[nIndex].GetLensSerialDfov()->video_source == subtype )
			return TRUE;
		break;

	case LENS_GENERIC_MSG_TYPE:
		if( m_MessageArray[nIndex].GetLensGeneric()->video_source == subtype )
			return TRUE;
		break;

	case LENS_SERIAL_ZOOM_MSG_TYPE:
		if( m_MessageArray[nIndex].GetLensSerialZoom()->video_source == subtype )
			return TRUE;
		break;

	case LENS_SERIAL_IR_ZOOM_MSG_TYPE:
		if( m_MessageArray[nIndex].GetLensSerialIrZoom()->video_source == subtype )
			return TRUE;
		break;

	case LENS_ANALOG_ZOOM_MSG_TYPE:
		if( m_MessageArray[nIndex].GetLensAnalogZoom()->video_source == subtype )
			return TRUE;
		break;

	case CAMERA_GENERIC_MSG_TYPE:
		if( m_MessageArray[nIndex].GetCameraGeneric()->video_source == subtype )
			return TRUE;
		break;

	case LENS_SERIAL_FIXED_FOV_MSG_TYPE:
		if( m_MessageArray[nIndex].GetLensSerialFixedFov()->video_source == subtype )
			return TRUE;
		break;

	case LENS_SERIAL_IR_DFOV_MSG_TYPE:
		if( m_MessageArray[nIndex].GetLensSerialIrDfov()->video_source == subtype )
			return TRUE;
		break;

	case LENS_MOOG_ZOOM_MSG_TYPE:
		if( m_MessageArray[nIndex].GetLensMoogZoom()->video_source == subtype )
			return TRUE;
		break;

	default:
		break;
	}

	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerConfiguration::IsLensMessageType(int msgType) const
//
// Returns TRUE if the tracker message type is a lens type message
//
BOOL CTrackerConfiguration::IsLensMessageType(int msgType) const
{
	switch( msgType )
	{
	case LENS_SERIAL_TFOV_MSG_TYPE:
	case LENS_SERIAL_DFOV_MSG_TYPE:
	case LENS_GENERIC_MSG_TYPE:
	case LENS_SERIAL_ZOOM_MSG_TYPE:
	case LENS_SERIAL_IR_ZOOM_MSG_TYPE:
	case LENS_ANALOG_ZOOM_MSG_TYPE:
	case LENS_SERIAL_FIXED_FOV_MSG_TYPE:
	case LENS_SERIAL_IR_DFOV_MSG_TYPE:
	case LENS_MOOG_ZOOM_MSG_TYPE:
		return TRUE;

	default:
		break;
	}

	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerConfiguration::IsLensMessageType(const CTrackerMessage* pMessage) const
//
// Returns TRUE if the tracker message type is a lens type message
//
BOOL CTrackerConfiguration::IsLensMessageType(const CTrackerMessage* pMessage) const
{
	if( pMessage == NULL )
		return FALSE;

	return IsLensMessageType(pMessage->GetType());
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerConfiguration::GetLensMessageType(int lensType) const
//
// Returns the tracker message used to configure and control the lens
// type specified.  Returns -1 on error.
//
int	CTrackerConfiguration::GetLensMessageType(int lensType) const
{
	// create the proper type
	switch( lensType )
	{
	case LENS_GRAFLEX:
		return LENS_GRAFLEX_MSG_TYPE;

	case LENS_OOS_TFOV:
	case LENS_SOPHIE_THERMAL_BINOCULARS:
	case LENS_JANOS_ALBA_TFOV:
		return LENS_SERIAL_TFOV_MSG_TYPE;

	case LENS_GENERIC:
		return LENS_GENERIC_MSG_TYPE;

	case LENS_ITS_6125DF:
	case LENS_GRAFLEX_SERIAL:
	case LENS_GRAFLEX_VINTEN:
	case LENS_COHU_MPC:
	case LENS_FUJINON_D60:
	case LENS_GRAFLEX_35X:
	case LENS_FUJINON_C22X23R2DZP1:
	case LENS_PVP_NIGHTHAWK_VIS_ZOOM:
	case LENS_HITACHI_HD2005_D60X16:
	case LENS_HITACHI_HD2005_FH32X15:
	case LENS_SONY_FCB_EX980S:
	case LENS_FUJINON_SX800:
		return LENS_SERIAL_ZOOM_MSG_TYPE;

	case LENS_DIOP_FIELDPRO5X:
	case LENS_FLIR_RANGER_HRC:
	case LENS_STINGRAY_OPTICS_SR2536:
	case LENS_PVP_NIGHTHAWK_IR_ZOOM:
	case LENS_G5_INFRARED_550CZ:
	case LENS_L3_WALRSS_HD:
	case LENS_IRC_QUAZIR_LRSD_RPO_ODEM825:
	case LENS_IRC_QUAZIR_LRSD_RPO_DIAMOND:
	case LENS_FLIR_RANGER_HDC:
	case LENS_G5_INFRARED_785CZ:
	case LENS_FLIR_NEUTRINO_SX12ISR1200:
	case LENS_INVEO_THEIA_HD900M:
		return LENS_SERIAL_IR_ZOOM_MSG_TYPE;

	case LENS_ANALOG_ZOOM:
		return LENS_ANALOG_ZOOM_MSG_TYPE;

	case LENS_JANOS_ASIO_DFOV:
		return LENS_SERIAL_DFOV_MSG_TYPE;

	case LENS_OOS_MULTIBAND_TELESCOPE:
	case LENS_GRAFLEX_FIXED_FOV:
	case LENS_OPTEC_FOCUSER:
	case LENS_OFFICINA_STELLARE_FOCUSER:
		return LENS_SERIAL_FIXED_FOV_MSG_TYPE;

	case LENS_FLIR_MILCAM_DFOV:
	case LENS_FLIR_RS6700_DFOV:
		return LENS_SERIAL_IR_DFOV_MSG_TYPE;

	case LENS_MOOG_ZOOM_1:
	case LENS_MOOG_ZOOM_2:
		return LENS_MOOG_ZOOM_MSG_TYPE;
	}

	return -1;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerConfiguration::GetLensFov(const CTrackerMessage* pMessage) const
//
// Returns the FOV in degrees of the lens (as per the lens message passed).
// Returns -1 on error.
//
double CTrackerConfiguration::GetLensFov(const CTrackerMessage* pMessage) const
{
	if( pMessage == NULL )
		return -1;

	switch( pMessage->GetType() )
	{
	case LENS_SERIAL_TFOV_MSG_TYPE:
		if( pMessage->GetLensSerialTfov()->fov_cmd == FOV_WIDE )
			return (double)pMessage->GetLensSerialTfov()->fov_wide / 100.0;
		else if( pMessage->GetLensSerialTfov()->fov_cmd == FOV_MEDIUM )
			return (double)pMessage->GetLensSerialTfov()->fov_medium / 100.0;
		else if( pMessage->GetLensSerialTfov()->fov_cmd == FOV_NARROW )
			return (double)pMessage->GetLensSerialTfov()->fov_narrow / 100.0;
		break;

	case LENS_SERIAL_DFOV_MSG_TYPE:
		if( pMessage->GetLensSerialDfov()->fov_cmd == FOV_WIDE )
			return (double)pMessage->GetLensSerialDfov()->fov_wide / 100.0;
		else if( pMessage->GetLensSerialDfov()->fov_cmd == FOV_NARROW )
			return (double)pMessage->GetLensSerialDfov()->fov_narrow / 100.0;
		break;

	case LENS_GENERIC_MSG_TYPE:
		if( pMessage->GetLensGeneric()->use_fov )
			return (double)pMessage->GetLensGeneric()->lens_fov / 100.0;
		break;

	case LENS_SERIAL_ZOOM_MSG_TYPE:
		return (double)pMessage->GetLensSerialZoom()->zoom_fov / 100.0;

	case LENS_SERIAL_IR_ZOOM_MSG_TYPE:
		return (double)pMessage->GetLensSerialIrZoom()->zoom_fov / 100.0;

	case LENS_ANALOG_ZOOM_MSG_TYPE:
		return (double)pMessage->GetLensAnalogZoom()->zoom_fov / 100.0;

	case LENS_SERIAL_FIXED_FOV_MSG_TYPE:
		return (double)pMessage->GetLensSerialFixedFov()->lens_fov / 100.0;

	case LENS_SERIAL_IR_DFOV_MSG_TYPE:
		if( pMessage->GetLensSerialIrDfov()->fov_cmd == FOV_WIDE )
			return (double)pMessage->GetLensSerialIrDfov()->fov_wide / 100.0;
		else if( pMessage->GetLensSerialIrDfov()->fov_cmd == FOV_NARROW )
			return (double)pMessage->GetLensSerialIrDfov()->fov_narrow / 100.0;
		break;

	case LENS_MOOG_ZOOM_MSG_TYPE:
		return (double)pMessage->GetLensMoogZoom()->zoom_fov / 100.0;

	default:
		break;
	}

	return -1;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerConfiguration::GetLensMaximumFov(const CTrackerMessage* pMessage) const
//
// Returns the maximum possible FOV in degrees for the lens (as per the lens message passed).
// Returns -1 on error.
//
double CTrackerConfiguration::GetLensMaximumFov(const CTrackerMessage* pMessage) const
{
	if( pMessage == NULL )
		return -1;

	switch( pMessage->GetType() )
	{
	case LENS_SERIAL_TFOV_MSG_TYPE:
		return (double)pMessage->GetLensSerialTfov()->fov_wide / 100.0;

	case LENS_SERIAL_DFOV_MSG_TYPE:
		return (double)pMessage->GetLensSerialDfov()->fov_wide / 100.0;

	case LENS_GENERIC_MSG_TYPE:
		if( pMessage->GetLensGeneric()->use_fov )
			return (double)pMessage->GetLensGeneric()->lens_fov / 100.0;
		break;

	case LENS_SERIAL_ZOOM_MSG_TYPE:
		return (double)pMessage->GetLensSerialZoom()->max_fov / 100.0;

	case LENS_SERIAL_IR_ZOOM_MSG_TYPE:
		return (double)pMessage->GetLensSerialIrZoom()->max_fov / 100.0;

	case LENS_ANALOG_ZOOM_MSG_TYPE:
		return (double)pMessage->GetLensAnalogZoom()->max_fov / 100.0;

	case LENS_SERIAL_FIXED_FOV_MSG_TYPE:
		return (double)pMessage->GetLensSerialFixedFov()->lens_fov / 100.0;

	case LENS_SERIAL_IR_DFOV_MSG_TYPE:
		return (double)pMessage->GetLensSerialIrDfov()->fov_wide / 100.0;

	case LENS_MOOG_ZOOM_MSG_TYPE:
		return (double)pMessage->GetLensMoogZoom()->max_fov / 100.0;

	default:
		break;
	}

	return -1;
}


///////////////////////////////////////////////////////////////////////////////
// CTrackerConfiguration::GetMessageIndex(int type, int subtype=-1) const
//
// Finds a message in the array by type and returns it's index in the array
// or a -1 if not found
//
int	CTrackerConfiguration::GetMessageIndex(int type, int subtype) const
{
	for( int i=0; i < m_MessageArray.GetSize(); i++ )
	{
		if( m_MessageArray[i].GetType() == type )
		{
			if( subtype == -1 )
				return i;
			else
			{
				if( IsSubtype(i, subtype) )
					return i;
			}
		}
	}

	return -1;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerConfiguration::GetMessage(int type, int subtype=-1)
//
// Finds a message in the array by type and returns a pointer to it or
// NULL pointer if not found
//
CTrackerMessage* CTrackerConfiguration::GetMessage(int type, int subtype)
{
	int index = GetMessageIndex(type, subtype);

	if( index >= 0 )
		return m_MessageArray.GetAt(index);

	return NULL;
}

const CTrackerMessage* CTrackerConfiguration::GetMessage(int type, int subtype) const
{
	int index = GetMessageIndex(type, subtype);

	if( index >= 0 )
		return m_MessageArray.GetAt(index);

	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerConfiguration::AddMessage(const CTrackerMessage* pMessage)
//
// Add a new message to the array or update the message if it already
// exists in the array
//
BOOL CTrackerConfiguration::AddMessage(const CTrackerMessage* pMessage)
{
	if( pMessage == NULL )
		return FALSE;

	int subtype = -1;

	if( HasSubtype(pMessage->GetType()) )
		subtype = GetSubtype(pMessage);

	// check to see if the message is already in the array
	CTrackerMessage* pCurMessage = GetMessage(pMessage->GetType(), subtype);

	if( pCurMessage != NULL )
	{
		// replace current message
		*pCurMessage = *pMessage;
	}
	else
	{
		// add a new message to the array
		m_MessageArray.Add(*pMessage);
	}

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerConfiguration::RemoveMessage(int type, int subtype=-1)
//
// Removes a message from the array by type (and subtype)
//
BOOL CTrackerConfiguration::RemoveMessage(int type, int subtype)
{
	int index = GetMessageIndex(type, subtype);

	if( index < 0 )
		return FALSE;

	m_MessageArray.RemoveAt(index);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerConfiguration::RemoveMessage(const CTrackerMessage* pMessage)
//
// Removes a message from the array by type (and subtype)
//
BOOL CTrackerConfiguration::RemoveMessage(const CTrackerMessage* pMessage)
{
	if( pMessage == NULL )
		return FALSE;

	// get subtype (if any)
	int subtype = GetSubtype(pMessage);

	return RemoveMessage(pMessage->GetType(), subtype);
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerConfiguration::RemoveAllLensMessages()
//
// Removes all the lens type messages from the array.
// Useful before query of all connected lenses.
//
void CTrackerConfiguration::RemoveAllLensMessages()
{
	for( int i=0; i < m_MessageArray.GetSize(); i++ )
	{
		switch( m_MessageArray[i].GetType() )
		{
		case LENS_SERIAL_TFOV_MSG_TYPE:
		case LENS_SERIAL_DFOV_MSG_TYPE:
		case LENS_GENERIC_MSG_TYPE:
		case LENS_SERIAL_ZOOM_MSG_TYPE:
		case LENS_SERIAL_IR_ZOOM_MSG_TYPE:
		case LENS_ANALOG_ZOOM_MSG_TYPE:
		case LENS_SERIAL_FIXED_FOV_MSG_TYPE:
		case LENS_SERIAL_IR_DFOV_MSG_TYPE:
		case LENS_MOOG_ZOOM_MSG_TYPE:
			m_MessageArray.RemoveAt(i);
			i--;
			break;

		default:
			break;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerConfiguration::RemoveAllCameraMessages()
//
// Removes all the camera type messages from the array.
// Useful before query of all connected cameras.
//
void CTrackerConfiguration::RemoveAllCameraMessages()
{
	for( int i=0; i < m_MessageArray.GetSize(); i++ )
	{
		switch( m_MessageArray[i].GetType() )
		{
		case CAMERA_GENERIC_MSG_TYPE:
			m_MessageArray.RemoveAt(i);
			i--;
			break;

		default:
			break;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerConfiguration::QueryAllMessages(CTrackerInterface* pTrackerInterface)
//
// Wipe out current tracker configuration and then query the entire
// tracker configuration.
//
BOOL CTrackerConfiguration::QueryAllMessages(CTrackerInterface* pTrackerInterface)
{
	// sanity
	ASSERT(pTrackerInterface);
	if( pTrackerInterface == NULL )
		return FALSE;

	// if already in the middle of a query, abort and restart
	AbortQuery();

	ASSERT(!m_bQueryRunning);

	// set tracker interface pointer
	m_pTrackerInterface = pTrackerInterface;

	// wipe out current message arrays
	m_MessageArray.RemoveAll();
	m_QueryArray.RemoveAll();

	// Add query messages to array
	CTrackerMessage queryMsg;
	queryMsg.SetDefaultQueryConfig();

	for( int i=0; i < nMessageQueryTableSize; i++ )
	{
		queryMsg.GetQueryConfig()->get_msg_type = MessageQueryTable[i];
		m_QueryArray.Add(queryMsg);
	}

	// kick off the query thread
	m_QueryIndex = 0;
	m_QueryReceived = 0;
	m_QueryTimedOut = 0;
	m_bAbortQueryThread = FALSE;
	m_bQueryRunning = TRUE;

	if( AfxBeginThread(BeginQueryThread, this) == NULL )
	{
		AbortQuery();
	}

	return m_bQueryRunning;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerConfiguration::AbortQuery()
//
// Abort the current query and wait for the query thread to stop
//
void CTrackerConfiguration::AbortQuery()
{
	// set abort flag and wait for the thread to stop
	m_bAbortQueryThread = TRUE;
	CSingleLock lock(&m_QueryThreadCrit, TRUE);
	m_bQueryRunning = FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// BeginQueryThread(LPVOID pParm)
//
// pParm is a pointer to a CTrackerConfiguration and this function is a 
// friend which almost makes this a member function of the class
//
static UINT BeginQueryThread(LPVOID pParm)
{
	// Get pointer
	ASSERT(pParm);
	CTrackerConfiguration* pThis = (CTrackerConfiguration*)pParm;

	pThis->QueryThread();

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerConfiguration::QueryThread()
//
// Thread routine to get the tracker configuration
//
void CTrackerConfiguration::QueryThread()
{
	ASSERT(m_pTrackerInterface);

	// lock thread running
	CSingleLock lock(&m_QueryThreadCrit, TRUE);

	// setup variables
	m_QueryIndex = 0;
	m_QueryReceived = 0;
	m_QueryTimedOut = 0;

	int nTimeOutSecs = 1;	// 1 second timeout

	TRACE("CTrackerConfiguration: Start configuration query\n");

	// loop until aborted or we have received the last message
	while( (!m_bAbortQueryThread) && (m_QueryIndex < m_QueryArray.GetSize()) )
	{
		// don't allow the tracker interface message output queue to fill up
		// wait for everything to be connected and data to be flowing before we query
		// this also keeps this background query out of the way of the standard GUI messaging
		if( m_pTrackerInterface->GetSendQueueSize() > 0 )
		{
			// yield CPU and loop
			Sleep(10);
			continue;
		}

		// send query to tracker
		m_pTrackerInterface->SendMessage(m_QueryArray[m_QueryIndex]);

		// get message type and subtype (if it has one)
		int msgType = m_QueryArray[m_QueryIndex].GetQueryConfig()->get_msg_type;
		int msgSubType = -1;
		if( HasSubtype(msgType) )
			msgSubType = m_QueryArray[m_QueryIndex].GetQueryConfig()->get_msg_id;

		// get start time
		CTime StartTime = CTime::GetCurrentTime();
		BOOL bMessageTimedOut = FALSE;

		// wait to receive the message
		while( (!m_bAbortQueryThread) && (!bMessageTimedOut) )
		{
			// yield CPU
			Sleep(10);

			// did we get it?
			if( GetMessageIndex(msgType, msgSubType) >= 0 )
				break;

			// check for time out
			CTimeSpan CurrentSpan = CTime::GetCurrentTime() - StartTime;
			int secs = (int)CurrentSpan.GetTotalSeconds();

			if( secs > nTimeOutSecs )
				bMessageTimedOut = TRUE;
		}

		// was the message timed out?
		if( bMessageTimedOut )
		{
			// if this is the first query in the list, then keep trying until we get a connection to the tracker
			if( m_QueryIndex == 0 )
				continue;

			TRACE("CTrackerConfiguration: Timed out waiting for message type %d! Skipping this message.\n", msgType);
#ifdef _DEBUG_SAVE_CONFIG
			dump_debug("CTrackerConfiguration: Timed out waiting for message type %d! Skipping this message.\r\n", msgType);
#endif
			// skip this message (the tracker is not responding to the query)
			m_QueryTimedOut++;
			m_QueryIndex++;

			// try the next message
			continue;
		}

		// check for LensConfig of CameraConfig types
		if( msgType == LENS_CONFIG_MSG_TYPE )
		{
			RemoveAllLensMessages();	// remove any old lens type messages
			AddLensQueriesToArray();
		}
/*		else if( msgType == CAMERA_CONFIG_MSG_TYPE )
		{
			RemoveAllCameraMessages();	// remove any old camera type messages
			AddCameraQueriesToArray();
		}
*/
		m_QueryReceived++;
		m_QueryIndex++;
	}

	TRACE("CTrackerConfiguration: End configuration query (%d of %d messages)\n", GetSize(), m_QueryArray.GetSize());
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerConfiguration::AddLensQueriesToArray()
//
// Add queries for all configured lenses in the LENS_CONFIG_MSG
//
BOOL CTrackerConfiguration::AddLensQueriesToArray()
{
	CTrackerMessage* pLensConfig = GetMessage(LENS_CONFIG_MSG_TYPE);

	if( pLensConfig == NULL )
		return FALSE;

	// setup query message
	CTrackerMessage queryMsg;
	queryMsg.SetDefaultQueryConfig();

	const LENS_CONFIG_MSG* pMsg = pLensConfig->GetLensConfig();

	if( pMsg->analog1 != LENS_NONE )
	{
		queryMsg.GetQueryConfig()->get_msg_type = GetLensMessageType(pMsg->analog1);
		queryMsg.GetQueryConfig()->get_msg_id   = VS_ANALOG1;
		m_QueryArray.Add(queryMsg);
	}

	if( pMsg->analog2 != LENS_NONE )
	{
		queryMsg.GetQueryConfig()->get_msg_type = GetLensMessageType(pMsg->analog2);
		queryMsg.GetQueryConfig()->get_msg_id   = VS_ANALOG2;
		m_QueryArray.Add(queryMsg);
	}

	if( pMsg->analog3 != LENS_NONE )
	{
		queryMsg.GetQueryConfig()->get_msg_type = GetLensMessageType(pMsg->analog3);
		queryMsg.GetQueryConfig()->get_msg_id   = VS_ANALOG3;
		m_QueryArray.Add(queryMsg);
	}

	if( pMsg->analog4 != LENS_NONE )
	{
		queryMsg.GetQueryConfig()->get_msg_type = GetLensMessageType(pMsg->analog4);
		queryMsg.GetQueryConfig()->get_msg_id   = VS_ANALOG4;
		m_QueryArray.Add(queryMsg);
	}

	if( pMsg->digital1 != LENS_NONE )
	{
		queryMsg.GetQueryConfig()->get_msg_type = GetLensMessageType(pMsg->digital1);
		queryMsg.GetQueryConfig()->get_msg_id   = VS_DIGITAL1;
		m_QueryArray.Add(queryMsg);
	}

	if( pMsg->digital2 != LENS_NONE )
	{
		queryMsg.GetQueryConfig()->get_msg_type = GetLensMessageType(pMsg->digital2);
		queryMsg.GetQueryConfig()->get_msg_id   = VS_DIGITAL2;
		m_QueryArray.Add(queryMsg);
	}

	return TRUE;
}

/********* DEPRECATED
///////////////////////////////////////////////////////////////////////////////
// CTrackerConfiguration::AddCameraQueriesToArray()
//
// Add queries for all configured cameras in the CAMERA_CONFIG_MSG
//
BOOL CTrackerConfiguration::AddCameraQueriesToArray()
{
	CTrackerMessage* pCameraConfig = GetMessage(CAMERA_CONFIG_MSG_TYPE);

	if( pCameraConfig == NULL )
		return FALSE;

	// setup query message
	CTrackerMessage queryMsg;
	queryMsg.SetDefaultQueryConfig();

	const CAMERA_CONFIG_MSG* pMsg = pCameraConfig->GetCameraConfig();

	if( pMsg->analog1 != CAMERA_NONE )
	{
		queryMsg.GetQueryConfig()->get_msg_type = CAMERA_GENERIC_MSG_TYPE;
		queryMsg.GetQueryConfig()->get_msg_id   = VS_ANALOG1;
		m_QueryArray.Add(queryMsg);
	}

	if( pMsg->analog2 != CAMERA_NONE )
	{
		queryMsg.GetQueryConfig()->get_msg_type = CAMERA_GENERIC_MSG_TYPE;
		queryMsg.GetQueryConfig()->get_msg_id   = VS_ANALOG2;
		m_QueryArray.Add(queryMsg);
	}

	if( pMsg->analog3 != CAMERA_NONE )
	{
		queryMsg.GetQueryConfig()->get_msg_type = CAMERA_GENERIC_MSG_TYPE;
		queryMsg.GetQueryConfig()->get_msg_id   = VS_ANALOG3;
		m_QueryArray.Add(queryMsg);
	}

	if( pMsg->analog4 != CAMERA_NONE )
	{
		queryMsg.GetQueryConfig()->get_msg_type = CAMERA_GENERIC_MSG_TYPE;
		queryMsg.GetQueryConfig()->get_msg_id   = VS_ANALOG4;
		m_QueryArray.Add(queryMsg);
	}

	if( pMsg->digital1 != CAMERA_NONE )
	{
		queryMsg.GetQueryConfig()->get_msg_type = CAMERA_GENERIC_MSG_TYPE;
		queryMsg.GetQueryConfig()->get_msg_id   = VS_DIGITAL1;
		m_QueryArray.Add(queryMsg);
	}

	if( pMsg->digital2 != CAMERA_NONE )
	{
		queryMsg.GetQueryConfig()->get_msg_type = CAMERA_GENERIC_MSG_TYPE;
		queryMsg.GetQueryConfig()->get_msg_id   = VS_DIGITAL2;
		m_QueryArray.Add(queryMsg);
	}

	return TRUE;
}
************/

///////////////////////////////////////////////////////////////////////////////
// CTrackerConfiguration::QueryActiveLens(CTrackerInterface* pTrackerInterface)
//
// Query the lens for the currently selected video source.
//
BOOL CTrackerConfiguration::QueryActiveLens(CTrackerInterface* pTrackerInterface)
{
	// sanity
	ASSERT(pTrackerInterface);
	if( pTrackerInterface == NULL )
		return FALSE;

	// get system control message
	CTrackerMessage* pSystem = GetMessage(SYSTEM_CTRL_MSG_TYPE);
	if( pSystem == NULL )
		return FALSE;

	// get lens config message
	CTrackerMessage* pLensConfig = GetMessage(LENS_CONFIG_MSG_TYPE);
	if( pLensConfig == NULL )
		return FALSE;

	// get currently selected video source
	int vidsrc = pSystem->GetSystem()->vid_src;

	// get configured lens type
	int lensType = LENS_NONE;

	switch( vidsrc )
	{
	case VS_ANALOG1:
		lensType = pLensConfig->GetLensConfig()->analog1;
		break;

	case VS_ANALOG2:
		lensType = pLensConfig->GetLensConfig()->analog2;
		break;

	case VS_ANALOG3:
		lensType = pLensConfig->GetLensConfig()->analog3;
		break;

	case VS_ANALOG4:
		lensType = pLensConfig->GetLensConfig()->analog4;
		break;

	case VS_DIGITAL1:
		lensType = pLensConfig->GetLensConfig()->digital1;
		break;

	case VS_DIGITAL2:
		lensType = pLensConfig->GetLensConfig()->digital2;
		break;
	}

	// if no lens configured for the current video source,
	// then exit without doing anything
	if( lensType == LENS_NONE )
		return FALSE;

	// do the query
	CTrackerMessage queryMsg;
	queryMsg.SetDefaultQueryConfig();
	queryMsg.GetQueryConfig()->get_msg_type = GetLensMessageType(lensType);
	queryMsg.GetQueryConfig()->get_msg_id = vidsrc;

	m_pTrackerInterface->SendMessage(queryMsg);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerConfiguration::GetSystemMaximumFov() const
//
// Returns the maximum field of view (FOV) for all the configured lenses.
// Returns -1 on error or if there are no configured lenses
//
double CTrackerConfiguration::GetSystemMaximumFov() const
{
	double maxFov = -1;

	for( int i=0; i < m_MessageArray.GetSize(); i++ )
	{
		const CTrackerMessage* pMessage = m_MessageArray.GetAt(i);

		if( IsLensMessageType(pMessage) )
		{
			double fov = GetLensMaximumFov(pMessage);
			
			if( fov > maxFov )
				maxFov = fov;
		}
	}

	return maxFov;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerConfiguration::GetActiveVideoSource() const
//
// Returns the currently selected video input for the tracker
// Returns -1 on error
//
int CTrackerConfiguration::GetActiveVideoSource() const
{
	// get system control message
	const CTrackerMessage* pSystem = GetMessage(SYSTEM_CTRL_MSG_TYPE);
	if( pSystem == NULL )
		return -1;

	// return currently selected video source
	return pSystem->GetSystem()->vid_src;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerConfiguration::GetActiveLensFov() const
//
// Returns the current field of view (FOV) in degrees for the lens connected
// to the currently selected video source.
// Returns -1 on error or if there are no configured lenses
//
double CTrackerConfiguration::GetActiveLensFov() const
{
	// get system control message
	const CTrackerMessage* pSystem = GetMessage(SYSTEM_CTRL_MSG_TYPE);
	if( pSystem == NULL )
		return -1;

	// get currently selected video source
	int vidsrc = pSystem->GetSystem()->vid_src;

	// loop through messages, looking for the active lens
	for( int i=0; i < m_MessageArray.GetSize(); i++ )
	{
		const CTrackerMessage* pMessage = m_MessageArray.GetAt(i);

		// lens type message?
		if( IsLensMessageType(pMessage) )
		{
			// found it?
			if( GetSubtype(pMessage) == vidsrc )
				return GetLensFov(pMessage);
		}
	}

	return -1;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerConfiguration::GetActiveLensMessage(CTrackerMessage& message) const
//
// Returns the configuration message for the lens connected
// to the currently selected video source.
// Returns FALSE on error or if there is no configured lens
//
BOOL CTrackerConfiguration::GetActiveLensMessage(CTrackerMessage& message) const
{
	// get system control message
	const CTrackerMessage* pSystem = GetMessage(SYSTEM_CTRL_MSG_TYPE);
	if( pSystem == NULL )
		return FALSE;

	// get currently selected video source
	int vidsrc = pSystem->GetSystem()->vid_src;

	// loop through messages, looking for the active lens
	for( int i=0; i < m_MessageArray.GetSize(); i++ )
	{
		const CTrackerMessage* pMessage = m_MessageArray.GetAt(i);

		// lens type message?
		if( IsLensMessageType(pMessage) )
		{
			// found it?
			if( GetSubtype(pMessage) == vidsrc )
			{
				message.Copy(*pMessage);
				return TRUE;
			}
		}
	}

	return FALSE;
}
