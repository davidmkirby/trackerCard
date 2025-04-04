///////////////////////////////////////////////////////////////////////////////
// TrackerMessage.cpp: implementation of the CTrackerMessage class.
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
#include "TrackerMessage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

///////////////////////////////////////////////////////////////////////////////
// statics
//

MSG_TBL CTrackerMessage::MessageTable[MSG_TBL_LEN] =
	{
		{ PING_MSG_TYPE,						sizeof(PING_MSG) },
		{ RUN_TIME_CTRL_MSG_TYPE,				sizeof(RUN_TIME_CTRL_MSG) },
		{ SYSTEM_CTRL_MSG_TYPE,					sizeof(SYSTEM_CTRL_MSG) },	
		{ LOS_OFFSET_CTRL_MSG_TYPE,				sizeof(LOS_OFFSET_CTRL_MSG) },	
		{ OFFSET_AIM_CTRL_MSG_TYPE,				sizeof(OFFSET_AIM_CTRL_MSG) },
		{ SYMBOLOGY_CTRL_MSG_TYPE,				sizeof(SYMBOLOGY_CTRL_MSG) },
		{ CORRELATION_CTRL_MSG_TYPE,			sizeof(CORRELATION_CTRL_MSG) },
		{ RESERVED_MSG_TYPE,					sizeof(RESERVED_MSG) },
		{ FILTER_CTRL_MSG_TYPE,					sizeof(FILTER_CTRL_MSG) },
		{ COAST_CTRL_MSG_TYPE,					sizeof(COAST_CTRL_MSG) },
		{ TGT_VALIDATION_CTRL_MSG_TYPE,			sizeof(TGT_VALIDATION_CTRL_MSG) },
		{ AAQ_ACQUIRE_CTRL_MSG_TYPE,			sizeof(AAQ_ACQUIRE_CTRL_MSG) },
		{ AAQ_TRACK_CTRL_MSG_TYPE,				sizeof(AAQ_TRACK_CTRL_MSG) },
		{ AAQ_TGT_SELECT_CTRL_MSG_TYPE,			sizeof(AAQ_TGT_SELECT_CTRL_MSG) },
		{ ANNOTATION_MSG_TYPE,					sizeof(ANNOTATION_MSG) },
		{ USER_STRING_MSG_TYPE,					sizeof(USER_STRING_MSG) },
		{ SCAN_MSG_TYPE,						sizeof(SCAN_MSG) },
		{ MOUNT_RATE_DRIVE_MSG_TYPE,			sizeof(MOUNT_RATE_DRIVE_MSG) },
		{ MOUNT_CONTROL_MSG_TYPE,				sizeof(MOUNT_CONTROL_MSG) },
		{ CONTROL_BOX_MSG_TYPE,					sizeof(CONTROL_BOX_MSG) },
		{ QUERY_CONFIG_MSG_TYPE,				sizeof(QUERY_CONFIG_MSG) },
		{ PRESET_CONFIG_MSG_TYPE,				sizeof(PRESET_CONFIG_MSG) },
		{ LENS_CONFIG_MSG_TYPE,					sizeof(LENS_CONFIG_MSG) },
		{ LENS_GRAFLEX_MSG_TYPE,				sizeof(LENS_GRAFLEX_MSG) },
		{ LENS_SERIAL_TFOV_MSG_TYPE,			sizeof(LENS_SERIAL_TFOV_MSG) },
		{ LENS_SERIAL_DFOV_MSG_TYPE,			sizeof(LENS_SERIAL_DFOV_MSG) },
		{ LENS_GENERIC_MSG_TYPE,				sizeof(LENS_GENERIC_MSG) },
		{ LENS_SERIAL_ZOOM_MSG_TYPE,			sizeof(LENS_SERIAL_ZOOM_MSG) },
		{ LENS_SERIAL_IR_ZOOM_MSG_TYPE,			sizeof(LENS_SERIAL_IR_ZOOM_MSG) },
		{ LENS_ANALOG_ZOOM_MSG_TYPE,			sizeof(LENS_ANALOG_ZOOM_MSG) },
		{ CAMERA_CONFIG_MSG_TYPE,				sizeof(CAMERA_CONFIG_MSG) },
		{ CAMERA_GENERIC_MSG_TYPE,				sizeof(CAMERA_GENERIC_MSG) },
		{ LENS_SERIAL_FIXED_FOV_MSG_TYPE,		sizeof(LENS_SERIAL_FIXED_FOV_MSG) },
		{ LENS_SERIAL_IR_DFOV_MSG_TYPE,			sizeof(LENS_SERIAL_IR_DFOV_MSG) },
		{ LENS_MOOG_ZOOM_MSG_TYPE,				sizeof(LENS_MOOG_ZOOM_MSG) },
		{ ANALOG_INPUT_MSG_TYPE,				sizeof(ANALOG_INPUT_MSG) },
		{ CAPABILITIES_MSG_TYPE,				sizeof(CAPABILITIES_MSG) },
		{ BUILT_IN_TEST_MSG_TYPE,				sizeof(BUILT_IN_TEST_MSG) },
		{ MOUNT_STATUS_MSG_TYPE,				sizeof(MOUNT_STATUS_MSG) },
		{ LRF_CONTROL_MSG_TYPE	,				sizeof(LRF_CONTROL_MSG) },
		{ TARGET_RANGE_MSG_TYPE,				sizeof(TARGET_RANGE_MSG) },
		{ TARGET_GENERATOR_MSG_TYPE,			sizeof(TARGET_GENERATOR_MSG) },
		{ GATE_CONTROL_MSG_TYPE,				sizeof(GATE_CONTROL_MSG) },
		{ MOUNT_FEEDBACK_MSG_TYPE,				sizeof(MOUNT_FEEDBACK_MSG) },
		{ DIGITAL_IO_MSG_TYPE,					sizeof(DIGITAL_IO_MSG) },
		{ DL_CODE_RECEIVE_MSG_TYPE,				sizeof(DL_CODE_RECEIVE_MSG) },
		{ DL_CODE_STATUS_MSG_TYPE,				sizeof(DL_CODE_STATUS_MSG) },
		{ DL_LICENSE_MSG_TYPE,					sizeof(DL_LICENSE_MSG) },
		{ DL_CODE_STATUS2_MSG_TYPE,				sizeof(DL_CODE_STATUS2_MSG) },
		{ GATE_STATISTICS_MSG_TYPE,				sizeof(GATE_STATISTICS_MSG) },
		{ DIGITAL_VIDEO_STATUS_MSG_TYPE,		sizeof(DIGITAL_VIDEO_STATUS_MSG) },
		{ USER_STRING2_MSG_TYPE,				sizeof(USER_STRING2_MSG) },
		{ TARGET_SIMULATOR_MSG_TYPE,			sizeof(TARGET_SIMULATOR_MSG) },
		{ CRP_CONTROL_MSG_TYPE,					sizeof(CRP_CONTROL_MSG) },
		{ STEERED_MIRROR_FILTER_MSG_TYPE,		sizeof(STEERED_MIRROR_FILTER_MSG) },
		{ IFF_TRACK_STATUS_MSG_TYPE,			sizeof(IFF_TRACK_STATUS_MSG) },
		{ STEERED_MIRROR_CALIBRATION_MSG_TYPE,	sizeof(STEERED_MIRROR_CALIBRATION_MSG) },
		{ OVERLAY_CONTROL_MSG_TYPE,				sizeof(OVERLAY_CONTROL_MSG) },
		{ OVERLAY_STATUS_MSG_TYPE,				sizeof(OVERLAY_STATUS_MSG) },
		{ LOS_OFFSET_CTRL2_MSG_TYPE,			sizeof(LOS_OFFSET_CTRL2_MSG) },	
		{ OFFSET_AIM_CTRL2_MSG_TYPE,			sizeof(OFFSET_AIM_CTRL2_MSG) },
		{ POS_TRACK_STATUS_MSG_TYPE,			sizeof(POS_TRACK_STATUS_MSG) },
		{ CONTROL_BOX_CONTROL_MSG_TYPE,			sizeof(CONTROL_BOX_CONTROL_MSG) },
		{ CONTROL_BOX_STATUS_MSG_TYPE,			sizeof(CONTROL_BOX_STATUS_MSG) },
		{ THRESHOLD_STATISTICS_MSG_TYPE,		sizeof(THRESHOLD_STATISTICS_MSG) },
		{ OVERLAY_STATUS_EXT_MSG_TYPE,			sizeof(OVERLAY_STATUS_EXT_MSG) },
		{ CAMERA_CONTROL_MSG_TYPE,				sizeof(CAMERA_CONTROL_MSG) },
		{ GPS_DATA_MSG_TYPE,					sizeof(GPS_DATA_MSG) },
		{ SYSTEM_STATUS_MSG_TYPE,				sizeof(SYSTEM_STATUS_MSG) },
		{ FPGA_VIDEO_STATUS_MSG_TYPE,			sizeof(FPGA_VIDEO_STATUS_MSG) },
		{ ETHERNET_STATUS_MSG_TYPE,				sizeof(ETHERNET_STATUS_MSG) },
		{ MT_GENERAL_MSG_TYPE,					sizeof(MT_GENERAL_MSG) },
		{ MT_ACQUIRE_MSG_TYPE,					sizeof(MT_ACQUIRE_MSG) },
		{ MT_TRACK_MSG_TYPE,					sizeof(MT_TRACK_MSG) },
		{ MT_DATA_MSG_TYPE,						sizeof(MT_DATA_MSG) },
		{ MT_VALIDATION_MSG_TYPE,				sizeof(MT_VALIDATION_MSG) },
		{ CONFIG_GATE_SIZE_MSG_TYPE,			sizeof(CONFIG_GATE_SIZE_MSG) },
		{ CONFIG_GATE_POS_MSG_TYPE,				sizeof(CONFIG_GATE_POS_MSG) },
		{ CONFIG_ANNOTATION_MSG_TYPE,			sizeof(CONFIG_ANNOTATION_MSG) },
		{ CONFIG_SYMBOLOGY_MSG_TYPE,			sizeof(CONFIG_SYMBOLOGY_MSG) },
		{ CONFIG_CORR_REF_POS_MSG_TYPE,			sizeof(CONFIG_CORR_REF_POS_MSG) },
		{ CONFIG_VIDEO_MSG_TYPE,				sizeof(CONFIG_VIDEO_MSG) },
		{ CONFIG_PRESET_CONFIG_MSG_TYPE,		sizeof(CONFIG_PRESET_CONFIG_MSG) },
		{ CONFIG_AUTOSIZE_MSG_TYPE,				sizeof(CONFIG_AUTOSIZE_MSG) },
		{ CONFIG_VALIDATION_MSG_TYPE,			sizeof(CONFIG_VALIDATION_MSG) },
		{ CONFIG_JOYSTICK_MSG_TYPE,				sizeof(CONFIG_JOYSTICK_MSG) },
		{ CONFIG_LENS_FOV_MSG_TYPE,				sizeof(CONFIG_LENS_FOV_MSG) },
		{ CONFIG_MOUNT_MSG_TYPE,				sizeof(CONFIG_MOUNT_MSG) },
		{ CONFIG_ANALOG_JOYSTICK_MSG_TYPE,		sizeof(CONFIG_ANALOG_JOYSTICK_MSG) },
		{ CONFIG_DIGITAL_IO_MSG_TYPE,			sizeof(CONFIG_DIGITAL_IO_MSG) },
		{ CONFIG_ZOOM_TO_RANGE_MSG_TYPE,		sizeof(CONFIG_ZOOM_TO_RANGE_MSG) },
		{ CONFIG_GATE_STYLE_MSG_TYPE,			sizeof(CONFIG_GATE_STYLE_MSG) },
		{ CONFIG_GATE_RETICLE_MSG_TYPE,			sizeof(CONFIG_GATE_RETICLE_MSG) },
		{ CONFIG_LOS_RETICLE_MSG_TYPE,			sizeof(CONFIG_LOS_RETICLE_MSG) },
		{ CONFIG_TRACK_FLAG_MSG_TYPE,			sizeof(CONFIG_TRACK_FLAG_MSG) },
		{ CONFIG_NORTH_OFFSET_MSG_TYPE,			sizeof(CONFIG_NORTH_OFFSET_MSG) },
		{ CONFIG_DIGITAL_VIDEO_MSG_TYPE,		sizeof(CONFIG_DIGITAL_VIDEO_MSG) },
		{ CONFIG_ANNOTATION2_MSG_TYPE,			sizeof(CONFIG_ANNOTATION2_MSG) },
		{ CONFIG_SERIAL_PORTS_MSG_TYPE,			sizeof(CONFIG_SERIAL_PORTS_MSG) },
		{ CONFIG_CONTROL_BOX_MSG_TYPE,			sizeof(CONFIG_CONTROL_BOX_MSG) },
		{ CONFIG_TARGET_SIMULATOR_MSG_TYPE,		sizeof(CONFIG_TARGET_SIMULATOR_MSG) },
		{ CONFIG_CRP_MSG_TYPE,					sizeof(CONFIG_CRP_MSG) },
		{ CONFIG_AUTOTHRESHOLD_MSG_TYPE,		sizeof(CONFIG_AUTOTHRESHOLD_MSG) },
		{ CONFIG_ETHERNET_MSG_TYPE,				sizeof(CONFIG_ETHERNET_MSG) },
		{ CONFIG_DIGITAL_VIDEO_EXT_MSG_TYPE,	sizeof(CONFIG_DIGITAL_VIDEO_EXT_MSG) },
		{ CONFIG_DIGITAL_PREPROCESS_MSG_TYPE,	sizeof(CONFIG_DIGITAL_PREPROCESS_MSG) },
		{ CONFIG_IFF_TRACK_MSG_TYPE,			sizeof(CONFIG_IFF_TRACK_MSG) },
		{ CONFIG_INTRUSION_DETECT_MSG_TYPE,		sizeof(CONFIG_INTRUSION_DETECT_MSG) },
		{ CONFIG_POS_TRACK_MSG_TYPE,			sizeof(CONFIG_POS_TRACK_MSG) },
		{ CONFIG_CONTROL_BOX_IO_MSG_TYPE,		sizeof(CONFIG_CONTROL_BOX_IO_MSG) },
		{ CONFIG_VIDEO_SWITCH_MSG_TYPE,			sizeof(CONFIG_VIDEO_SWITCH_MSG) },
		{ CONFIG_GATE_RETICLE2_MSG_TYPE,		sizeof(CONFIG_GATE_RETICLE2_MSG) },
		{ CONFIG_GPS_MSG_TYPE,					sizeof(CONFIG_GPS_MSG) },
		{ MESSAGE_ACK_MSG_TYPE,					sizeof(MESSAGE_ACK_MSG) },
		{ STATUS_MSG_TYPE,						sizeof(STATUS_MSG) }
	};

USHORT CTrackerMessage::CurrentSyncWord = GATE0_SYNC_WORD;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTrackerMessage::CTrackerMessage()
{
	m_Type = -1;
	m_nRawSize = 0;
	m_Data.m_pRaw = NULL;
}

CTrackerMessage::~CTrackerMessage()
{
	if( m_Data.m_pRaw != NULL )
		delete[] m_Data.m_pRaw;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::Copy(const CTrackerMessage& src)
//
// Copy function
//
CTrackerMessage& CTrackerMessage::Copy(const CTrackerMessage& src)
{
	m_Type = src.m_Type;
	m_TimeStamp = src.m_TimeStamp;

	if( m_Data.m_pRaw != NULL )
	{
		// different buffer sizes?
		if( m_nRawSize != src.m_nRawSize )
		{
			// delete this objects data
			delete[] m_Data.m_pRaw;
			m_Data.m_pRaw = NULL;
		}
	}

	m_nRawSize = src.m_nRawSize;

	// copy the source's data
	if( src.m_Data.m_pRaw != NULL )
	{
		// allocate buffer if necessary
		if( m_Data.m_pRaw == NULL )
		{
			m_Data.m_pRaw = new unsigned char[m_nRawSize];
			ASSERT( m_Data.m_pRaw );
		}

		// copy it (if buffer is allocated)
		if( m_Data.m_pRaw != NULL )
			memcpy(m_Data.m_pRaw, src.m_Data.m_pRaw, m_nRawSize);
	}

	return *this;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::GetAsHexString(char* pString, int nBufferLen)
//
// Format the binary message buffer as a text string of hexadecimal words.
// pString is a user supplied buffer and nBufferLen is the maximum length
// string the supplied buffer can contain.
//
BOOL CTrackerMessage::GetAsHexString(char* pString, int nBufferLen)
{
	if( m_Data.m_pRaw == NULL )
	{
		*pString = '\0';
		return FALSE;
	}

	int nRawWords = m_nRawSize/2;
	int nSize = nRawWords * 5;

	if( (nSize > nBufferLen) || (nRawWords < 1) )
	{
		*pString = '\0';
		return FALSE;
	}

	unsigned short* pRawWords = (unsigned short*)m_Data.m_pRaw;

	sprintf(pString, "%04X", *pRawWords);
	pRawWords++;
	pString += 4;

	for( int i=1; i < nRawWords; i++ )
	{
		sprintf(pString, " %04X", *pRawWords);

		pRawWords++;
		pString += 5;
	}

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetType(int type, USHORT syncword = CTrackerMessage::CurrentSyncWord)
//
// Set the message type and allocate the appropriate buffer
//
BOOL CTrackerMessage::SetType(int type, USHORT syncword)
{
	// already set?
	if( (m_Type == type) && (m_Data.m_pRaw != NULL) )
	{
		// set sync word and exit
		m_Data.m_pControl->sync = syncword;
		return TRUE;
	}

	// check if this is a valid type
	int index=0;
	for( ; index < MSG_TBL_LEN; index++ )
	{
		if( MessageTable[index].type == type )
			break;
	}

	// type not found?
	if( index >= MSG_TBL_LEN )
		return FALSE;

	// delete this objects data (if any)
	if( m_Data.m_pRaw != NULL )
	{
		delete[] m_Data.m_pRaw;
		m_Data.m_pRaw = NULL;
	}

	// set the type and raw size
	m_Type = type;
	m_nRawSize = MessageTable[index].byte_count;

	// allocate a data buffer
	m_Data.m_pRaw = new unsigned char[m_nRawSize];
	ASSERT( m_Data.m_pRaw );

	// set sync word, message type, and zero buffer
	if( m_Data.m_pRaw != NULL )
	{
		// set sync word
		m_Data.m_pControl->sync = syncword;

		// zero buffer
		memset(m_Data.m_pRaw+2, 0, m_nRawSize-2);

		// set type 
		m_Data.m_pControl->msg_type = m_Type;
	}

	return (m_Data.m_pRaw != NULL);
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetTypeOrClear(int type, USHORT syncword = CTrackerMessage::CurrentSyncWord)
//
// Set the message type and allocate the appropriate buffer or just
// clear the existing buffer if the message is the same
//
BOOL CTrackerMessage::SetTypeOrClear(int type, USHORT syncword)
{
	// already setup (ie-same type and buffer allocated)?
	if( m_Type == type && (m_Data.m_pRaw != NULL) )
	{
		// set sync word
		m_Data.m_pControl->sync = syncword;

		// zero buffer
		memset(m_Data.m_pRaw+2, 0, m_nRawSize-2);

		// set type 
		m_Data.m_pControl->msg_type = m_Type;

		return TRUE;
	}

	return SetType(type, syncword);
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::GetGateNumber() const
//
// Returns the gate number this message is from/to (by looking at the sync word)
// -1=Unknown, 0=Gate0, 1=Gate1
//
int	CTrackerMessage::GetGateNumber() const
{
	if( m_Data.m_pRaw == NULL )
		return -1;

	if( m_Data.m_pControl->sync == GATE0_SYNC_WORD )
		return 0;

	if( m_Data.m_pControl->sync == GATE1_SYNC_WORD )
		return 1;

	if( m_Data.m_pControl->sync == GATE2_SYNC_WORD )
		return 2;

	return -1;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::ByteSwap()
//
// Byte swap the message data
//
BOOL CTrackerMessage::ByteSwap()
{
	// sanity
	ASSERT( m_Data.m_pRaw );
	if( m_Data.m_pRaw == NULL )
		return FALSE;

	// buffer size MUST be even number of bytes
	ASSERT( (m_nRawSize & 1) == 0 );
	if( (m_nRawSize & 1) != 0 )
		return FALSE;

	unsigned char temp;
	unsigned char* pBuffer = m_Data.m_pRaw;

	for( int i=0; i < m_nRawSize-1; i+=2 )
	{
		temp = pBuffer[i+1];
		pBuffer[i+1] = pBuffer[i];
		pBuffer[i] = temp;
	}

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::VerifyChecksum() const
//
// Verify the checksum on a message
//
BOOL CTrackerMessage::VerifyChecksum() const
{
	// sanity
	ASSERT( m_Data.m_pRaw );
	if( m_Data.m_pRaw == NULL )
		return FALSE;

	// get length to add up
	int nBytes;

//	if( m_Type == USER_STR_MSG_TYPE )
//		nBytes = (m_Data.m_pString->msg_len - 1) * 2;
//	else
		nBytes = m_nRawSize - 2;

	// sum up all the data bytes
	const unsigned char* pBuffer = m_Data.m_pRaw;
	short sum = 0;

	for( int i=0; i < nBytes; i++ )
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
// CTrackerMessage::SetChecksum()
//
// Set the checksum on a message
//
BOOL CTrackerMessage::SetChecksum()
{
	// sanity
	ASSERT( m_Data.m_pRaw );
	if( m_Data.m_pRaw == NULL )
		return FALSE;

	// get length to add up
	int nBytes;

//	if( m_Type == USER_STR_MSG_TYPE )
//		nBytes = (m_Data.m_pString->msg_len - 1) * 2;
//	else
		nBytes = m_nRawSize - 2;

	// sum up all the data bytes
	unsigned char* pBuffer = m_Data.m_pRaw;
	short sum = 0;

	for( int i=0; i < nBytes; i++ )
	{
		sum += *pBuffer;
		pBuffer++;
	}

	// set the message checksum
	*((short*)pBuffer) = -sum;

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SwapContents(CTrackerMessage& src)
//
// Swap the contents of two CTrackerMessage objects
//
CTrackerMessage& CTrackerMessage::SwapContents(CTrackerMessage& src)
{
	int type = m_Type;
	m_Type = src.m_Type;
	src.m_Type = type;

	int size = m_nRawSize;
	m_nRawSize = src.m_nRawSize;
	src.m_nRawSize = size;

	CTimeStamp TimeStamp = m_TimeStamp;
	m_TimeStamp = src.m_TimeStamp;
	src.m_TimeStamp = TimeStamp;

	unsigned char* pRaw = m_Data.m_pRaw;
	m_Data.m_pRaw = src.m_Data.m_pRaw;
	src.m_Data.m_pRaw = pRaw;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::IsEqual(const CTrackerMessage& msg2) const
//
// Compare this message to another message
//
BOOL CTrackerMessage::IsEqual(const CTrackerMessage& msg2) const
{
	// not same type?
	if( m_Type != msg2.m_Type )
		return FALSE;

	// not same size?
	if( m_nRawSize != msg2.m_nRawSize )
		return FALSE;

	// both have no data?
	if( m_nRawSize == 0 )
		return TRUE;

	// both must have good data!
	if( (m_Data.m_pRaw == NULL) || 
		(msg2.m_Data.m_pRaw == NULL) )
		return FALSE;

	// compare the data of the two message
	if( memcmp(m_Data.m_pRaw, msg2.m_Data.m_pRaw, m_nRawSize) == 0 )
		return TRUE;

	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// operator ==(const CTrackerMessage& msg1, const CTrackerMessage& msg2)
// operator !=(const CTrackerMessage& msg1, const CTrackerMessage& msg2)
//
// Compare one message to another message
//
BOOL operator ==(const CTrackerMessage& msg1, const CTrackerMessage& msg2)
{
	return msg1.IsEqual(msg2);
}

BOOL operator !=(const CTrackerMessage& msg1, const CTrackerMessage& msg2)
{
	return !msg1.IsEqual(msg2);
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultControl()
//
// Set the message type to control and setup default values
//
BOOL CTrackerMessage::SetDefaultControl()
{
	// setup as a control message
	if( !SetTypeOrClear(RUN_TIME_CTRL_MSG_TYPE) )
		return FALSE;

	// set defaults
	RUN_TIME_CTRL_MSG* pMsg = m_Data.m_pControl;
	ASSERT( pMsg );

	pMsg->act_qui		= ON;
	pMsg->reset			= OFF;

	pMsg->force_trk_acq	= DISABLE;
	pMsg->rmouse_button	= RMOUSE_BUTTON_IDLE;
	pMsg->ath			= OFF;
	pMsg->awp			= OFF;
	pMsg->aws			= OFF;
	pMsg->auto_trk		= OFF;
	pMsg->polarity		= POLARITY_WHITE;
	pMsg->mode			= CENTROID;
	pMsg->trk_acq		= ACQUIRE;

	pMsg->gtposx		= 0;
	pMsg->gtposy		= 0;

	pMsg->gtsizx		= 200/4;
	pMsg->gtsizy		= 50;

	pMsg->bkthrs		= 511;	// 50%
	pMsg->whthrs		= 511;	// 50%

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultSystem()
//
// Set the message type to system and setup default values
//
BOOL CTrackerMessage::SetDefaultSystem()
{
	// setup as a system message
	if( !SetTypeOrClear(SYSTEM_CTRL_MSG_TYPE) )
		return FALSE;

	// set defaults
	SYSTEM_CTRL_MSG* pMsg = m_Data.m_pSystem;
	ASSERT( pMsg );

	pMsg->vid_src			= VS_ANALOG1;
	pMsg->out_60hz			= OFF;
	pMsg->dualgates			= DISABLE;
	pMsg->auto_size_ratio	= 150;	// 1.5 to 1 (gate to target ratio)
	pMsg->vec_trans_time	= 4;
	pMsg->acquire_val_time	= 1;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultLOSOffset()
//
// Set the message type to line-of-sight offset and setup default values
//
BOOL CTrackerMessage::SetDefaultLOSOffset()
{
	// setup as a line-of-sight offset message
	if( !SetTypeOrClear(LOS_OFFSET_CTRL_MSG_TYPE) )
		return FALSE;

	// set defaults
	LOS_OFFSET_CTRL_MSG* pMsg = m_Data.m_pLOSOffset;
	ASSERT( pMsg );

	pMsg->posx		= 0;
	pMsg->posy		= 0;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultOffsetAim()
//
// Set the message type to offset aim and setup default values
//
BOOL CTrackerMessage::SetDefaultOffsetAim()
{
	// setup as a offset aim message
	if( !SetTypeOrClear(OFFSET_AIM_CTRL_MSG_TYPE) )
		return FALSE;

	// set defaults
	OFFSET_AIM_CTRL_MSG* pMsg = m_Data.m_pOffsetAim;
	ASSERT( pMsg );

	pMsg->ofaim_ena	= OFF;
	pMsg->posx		= 0;
	pMsg->posy		= 0;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultSymbology()
//
// Set the message type to symbology and setup default values
//
BOOL CTrackerMessage::SetDefaultSymbology()
{
	// setup as a symbology message
	if( !SetTypeOrClear(SYMBOLOGY_CTRL_MSG_TYPE) )
		return FALSE;

	// set defaults
	SYMBOLOGY_CTRL_MSG* pMsg = m_Data.m_pSymbology;
	ASSERT( pMsg );

	pMsg->los2_ena	= OFF;
	pMsg->enh_data	= ON;
	pMsg->symb_pol	= WHITE;
	pMsg->trk_flag	= ON;
	pMsg->trk_wind	= ON;
	pMsg->los_ena	= OFF;
	pMsg->ofaim_ena	= OFF;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultCorrelation()
//
// Set the message type to correlation and setup default values
//
BOOL CTrackerMessage::SetDefaultCorrelation()
{
	// setup as a correlation message
	if( !SetTypeOrClear(CORRELATION_CTRL_MSG_TYPE) )
		return FALSE;

	// set defaults
	CORRELATION_CTRL_MSG* pMsg = m_Data.m_pCorrelation;
	ASSERT( pMsg );

	pMsg->ref_window	= ON;
	pMsg->ref_image		= ON;

	pMsg->ref_left		= DISABLE;
	pMsg->ref_right		= DISABLE;
	pMsg->ref_up		= DISABLE;
	pMsg->ref_down		= DISABLE;
	pMsg->ref_speed		= 1;

	pMsg->ref_sizex		= 32;
	pMsg->ref_sizey		= 32;

	pMsg->match_percent	= 0; // auto
	pMsg->update_rate	= 1; // every frame

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultFilter()
//
// Set the message type to filter and setup default values
//
BOOL CTrackerMessage::SetDefaultFilter()
{
	// setup as a filter message
	if( !SetTypeOrClear(FILTER_CTRL_MSG_TYPE) )
		return FALSE;

	// set defaults
	FILTER_CTRL_MSG* pMsg = m_Data.m_pFilter;
	ASSERT( pMsg );

	pMsg->pid_enable		= OFF;
	pMsg->dig_fltr			= OFF;
	pMsg->invert_el			= OFF;
	pMsg->invert_az			= OFF;
	pMsg->fir_enable		= OFF;

	pMsg->gain_x			= 1000;
	pMsg->gain_y			= 1000;

	pMsg->propor_x			= 1000;
	pMsg->propor_y			= 1000;

	pMsg->integ_x			= 0;
	pMsg->integ_y			= 0;

	pMsg->deriv_x			= 0;
	pMsg->deriv_y			= 0;

	pMsg->integ_clip_x		= 0;
	pMsg->integ_clip_y		= 0;

	pMsg->vff_x				= 0;
	pMsg->vff_y				= 0;

	pMsg->aff_x				= 0;
	pMsg->aff_y				= 0;

	pMsg->fir_x				= 0;
	pMsg->fir_y				= 0;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultCoast()
//
// Set the message type to coast and setup default values
//
BOOL CTrackerMessage::SetDefaultCoast()
{
	// setup as a coast message
	if( !SetTypeOrClear(COAST_CTRL_MSG_TYPE) )
		return FALSE;

	// set defaults
	COAST_CTRL_MSG* pMsg = m_Data.m_pCoast;
	ASSERT( pMsg );

	pMsg->grow_rate		= COAST_GATE_GROW0;
	pMsg->mode			= COAST_ZERO_OUTPUT;
	pMsg->cst_ena		= OFF;
	pMsg->loop_mode		= COAST_LOOP_CLOSED;
	pMsg->duration		= 30;
	pMsg->search		= SEARCH_RETURN_BORESIGHT;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultTargetValidation()
//
// Set the message type to target validation and setup default values
//
BOOL CTrackerMessage::SetDefaultTargetValidation()
{
	// setup as a target validation message
	if( !SetTypeOrClear(TGT_VALIDATION_CTRL_MSG_TYPE) )
		return FALSE;

	// set defaults
	TGT_VALIDATION_CTRL_MSG* pMsg = m_Data.m_pTargetValidation;
	ASSERT( pMsg );

	pMsg->tql		= OFF;
	pMsg->sze		= OFF;
	pMsg->pse		= OFF;
	pMsg->nce		= OFF;
	pMsg->gte		= OFF;

	pMsg->size_x	= 10;  // 1% tolerance
	pMsg->size_y	= 10;

	pMsg->pos_x		= 10;  // 1 pixel tolerance
	pMsg->pos_y		= 10;

	pMsg->ncount	= 10;  // 1% tolerance

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultAutoAcquire()
//
// Set the message type to auto-acquire and setup default values
//
BOOL CTrackerMessage::SetDefaultAutoAcquire()
{
	// setup as an auto acquire message
	if( !SetTypeOrClear(AAQ_ACQUIRE_CTRL_MSG_TYPE) )
		return FALSE;

	// set defaults
	AAQ_ACQUIRE_CTRL_MSG* pMsg = m_Data.m_pAutoAcquire;
	ASSERT( pMsg );

	pMsg->gtsizx		= 200/4;
	pMsg->gtsizy		= 50;

//	pMsg->auto_acquire	= OFF;
	pMsg->ath			= OFF;
	pMsg->polarity		= POLARITY_WHITE;

	pMsg->gtposx		= 0;
	pMsg->gtposy		= 0;

	pMsg->bkthrs		= 511;	// 50%
	pMsg->whthrs		= 511;	// 50%

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultAutoAcquireTrack()
//
// Set the message type to auto-acquire track and setup default values
//
BOOL CTrackerMessage::SetDefaultAutoAcquireTrack()
{
	// setup as an auto acquire track message
	if( !SetTypeOrClear(AAQ_TRACK_CTRL_MSG_TYPE) )
		return FALSE;

	// set defaults
	AAQ_TRACK_CTRL_MSG* pMsg = m_Data.m_pAutoAcquireTrack;
	ASSERT( pMsg );

	pMsg->gtsizx		= 200/4;
	pMsg->gtsizy		= 50;

	pMsg->unique_track	= OFF;
	pMsg->awp			= OFF;
	pMsg->ath			= OFF;
	pMsg->aws			= OFF;
	pMsg->polarity		= POLARITY_WHITE;

	pMsg->gtposx		= 0;
	pMsg->gtposy		= 0;

	pMsg->bkthrs		= 511;	// 50%
	pMsg->whthrs		= 511;	// 50%

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultTargetSelect()
//
// Set the message type to auto-acquire target select and setup default values
//
BOOL CTrackerMessage::SetDefaultTargetSelect()
{
	// setup as an auto-acquire target select message
	if( !SetTypeOrClear(AAQ_TGT_SELECT_CTRL_MSG_TYPE) )
		return FALSE;

	// set defaults
	AAQ_TGT_SELECT_CTRL_MSG* pMsg = m_Data.m_pTargetSelect;
	ASSERT( pMsg );

	pMsg->tsel_ena		= OFF;

	pMsg->tsel_sizex	= 0;
	pMsg->tsel_sizey	= 0;

	pMsg->size_ena		= OFF;
	pMsg->aspect_ena	= ON;
	pMsg->direct_ena	= OFF;
	pMsg->speed_ena		= OFF;

	pMsg->tsel_ratio	= TARSEL_RATIO_SQUARE;
	pMsg->start_dir		= TARSEL_DIR_TOPCENTER;
	pMsg->end_dir		= TARSEL_DIR_TOPCENTER;

	pMsg->size_tol		= 10;	// 10%
	pMsg->tsel_speed	= 5;	// 5 pixels/field

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultAnnotation()
//
// Set the message type to annotation and setup default values
//
BOOL CTrackerMessage::SetDefaultAnnotation()
{
	// setup as an annotation message
	if( !SetTypeOrClear(ANNOTATION_MSG_TYPE) )
		return FALSE;

	// set defaults
	ANNOTATION_MSG* pMsg = m_Data.m_pAnnotation;
	ASSERT( pMsg );

	pMsg->anno_en		= ON;
	pMsg->anno_color	= WHITE;

	pMsg->show_mode		= ON;
	pMsg->show_pol		= ON;
	pMsg->show_state	= ON;
	pMsg->show_status	= ON;
	pMsg->show_auto		= ON;
	pMsg->show_az		= ON;
	pMsg->show_el		= ON;
	pMsg->show_tval		= ON;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultUserString()
//
// Set the message type to user string and setup default values
//
BOOL CTrackerMessage::SetDefaultUserString()
{
	// setup as an user string message
	if( !SetTypeOrClear(USER_STRING_MSG_TYPE) )
		return FALSE;

	// set defaults
	USER_STRING_MSG* pMsg = m_Data.m_pUserString;
	ASSERT( pMsg );

	pMsg->col		= 0;
	pMsg->row		= 0;

	pMsg->string[0] = '\0';

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultUserString2()
//
// Set the message type to user string and setup default values
//
BOOL CTrackerMessage::SetDefaultUserString2()
{
	// setup as an user string message
	if( !SetTypeOrClear(USER_STRING2_MSG_TYPE) )
		return FALSE;

	// set defaults
	USER_STRING2_MSG* pMsg = m_Data.m_pUserString2;
	ASSERT( pMsg );

	pMsg->col		= 0;
	pMsg->row		= 0;

	pMsg->string[0] = '\0';

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultTargetSimulator()
//
// Set the message type and setup default values
//
BOOL CTrackerMessage::SetDefaultTargetSimulator()
{
	// setup as an user string message
	if( !SetTypeOrClear(TARGET_SIMULATOR_MSG_TYPE) )
		return FALSE;

	// set defaults
	TARGET_SIMULATOR_MSG* pMsg = m_Data.m_pTargetSimulator;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultCrpControl()
//
// Set the message type and setup default values
//
BOOL CTrackerMessage::SetDefaultCrpControl()
{
	// setup as an user string message
	if( !SetTypeOrClear(CRP_CONTROL_MSG_TYPE) )
		return FALSE;

	// set defaults
	CRP_CONTROL_MSG* pMsg = m_Data.m_pCrpControl;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultSteeredMirrorFilter()
//
// Set the message type and setup default values
//
BOOL CTrackerMessage::SetDefaultSteeredMirrorFilter()
{
	// setup as an user string message
	if( !SetTypeOrClear(STEERED_MIRROR_FILTER_MSG_TYPE) )
		return FALSE;

	// set defaults
	STEERED_MIRROR_FILTER_MSG* pMsg = m_Data.m_pSteeredMirrorFilter;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultIffTrackStatus()
//
// Set the message type and setup default values
//
BOOL CTrackerMessage::SetDefaultIffTrackStatus()
{
	// setup as an user string message
	if( !SetTypeOrClear(IFF_TRACK_STATUS_MSG_TYPE) )
		return FALSE;

	// set defaults
	IFF_TRACK_STATUS_MSG* pMsg = m_Data.m_pIffTrackStatus;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultSteeredMirrorCalibration()
//
// Set the message type and setup default values
//
BOOL CTrackerMessage::SetDefaultSteeredMirrorCalibration()
{
	// setup as an user string message
	if( !SetTypeOrClear(STEERED_MIRROR_CALIBRATION_MSG_TYPE) )
		return FALSE;

	// set defaults
	STEERED_MIRROR_CALIBRATION_MSG* pMsg = m_Data.m_pSteeredMirrorCalibration;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultOverlayControl()
//
// Set the message type and setup default values
//
BOOL CTrackerMessage::SetDefaultOverlayControl()
{
	// setup as an user string message
	if( !SetTypeOrClear(OVERLAY_CONTROL_MSG_TYPE) )
		return FALSE;

	// set defaults
	OVERLAY_CONTROL_MSG* pMsg = m_Data.m_pOverlayControl;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultOverlayStatus()
//
// Set the message type and setup default values
//
BOOL CTrackerMessage::SetDefaultOverlayStatus()
{
	// setup as an user string message
	if( !SetTypeOrClear(OVERLAY_STATUS_MSG_TYPE) )
		return FALSE;

	// set defaults
	OVERLAY_STATUS_MSG* pMsg = m_Data.m_pOverlayStatus;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultOverlayStatusExt()
//
// Set the message type and setup default values
//
BOOL CTrackerMessage::SetDefaultOverlayStatusExt()
{
	// setup as an user string message
	if( !SetTypeOrClear(OVERLAY_STATUS_EXT_MSG_TYPE) )
		return FALSE;

	// set defaults
	OVERLAY_STATUS_EXT_MSG* pMsg = m_Data.m_pOverlayStatusExt;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultLOSOffset2()
//
// Set the message type to line-of-sight offset and setup default values
//
BOOL CTrackerMessage::SetDefaultLOSOffset2()
{
	// setup as a line-of-sight offset message
	if( !SetTypeOrClear(LOS_OFFSET_CTRL2_MSG_TYPE) )
		return FALSE;

	// set defaults
	LOS_OFFSET_CTRL2_MSG* pMsg = m_Data.m_pLOSOffset2;
	ASSERT( pMsg );

	pMsg->posx		= 0;
	pMsg->posy		= 0;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultOffsetAim2()
//
// Set the message type to offset aim and setup default values
//
BOOL CTrackerMessage::SetDefaultOffsetAim2()
{
	// setup as a offset aim message
	if( !SetTypeOrClear(OFFSET_AIM_CTRL2_MSG_TYPE) )
		return FALSE;

	// set defaults
	OFFSET_AIM_CTRL2_MSG* pMsg = m_Data.m_pOffsetAim2;
	ASSERT( pMsg );

	pMsg->ofaim_ena	= OFF;
	pMsg->posx		= 0;
	pMsg->posy		= 0;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultPosTrackStatus()
//
// Set the message type and setup default values
//
BOOL CTrackerMessage::SetDefaultPosTrackStatus()
{
	// setup as a offset aim message
	if( !SetTypeOrClear(POS_TRACK_STATUS_MSG_TYPE) )
		return FALSE;

	// set defaults
	POS_TRACK_STATUS_MSG* pMsg = m_Data.m_pPosTrackStatus;
	ASSERT( pMsg );

	pMsg->az_tracking	= 0;
	pMsg->el_tracking	= 0;
	pMsg->az_estimating	= 0;
	pMsg->el_estimating	= 0;
	pMsg->az_drive_lsw	= 0;
	pMsg->az_drive_msw	= 0;
	pMsg->el_drive_lsw	= 0;
	pMsg->el_drive_msw	= 0;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultCameraControl()
//
// Set the message type and setup default values
//
BOOL CTrackerMessage::SetDefaultCameraControl()
{
	// setup as an user string message
	if( !SetTypeOrClear(CAMERA_CONTROL_MSG_TYPE) )
		return FALSE;

	// set defaults
	CAMERA_CONTROL_MSG* pMsg = m_Data.m_pCameraControl;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultGpsData()
//
// Set the message type and setup default values
//
BOOL CTrackerMessage::SetDefaultGpsData()
{
	// setup as an user string message
	if( !SetTypeOrClear(GPS_DATA_MSG_TYPE) )
		return FALSE;

	// set defaults
	GPS_DATA_MSG* pMsg = m_Data.m_pGpsData;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultSystemStatus()
//
// Set the message type and setup default values
//
BOOL CTrackerMessage::SetDefaultSystemStatus()
{
	// setup as an user string message
	if (!SetTypeOrClear(SYSTEM_STATUS_MSG_TYPE))
		return FALSE;

	// set defaults
	SYSTEM_STATUS_MSG* pMsg = m_Data.m_pSystemStatus;
	ASSERT(pMsg);

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultFpgaVideoStatus()
//
// Set the message type and setup default values
//
BOOL CTrackerMessage::SetDefaultFpgaVideoStatus()
{
	// setup as an user string message
	if (!SetTypeOrClear(FPGA_VIDEO_STATUS_MSG_TYPE))
		return FALSE;

	// set defaults
	FPGA_VIDEO_STATUS_MSG* pMsg = m_Data.m_pFpgaVideoStatus;
	ASSERT(pMsg);

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultEthernetStatus()
//
// Set the message type and setup default values
//
BOOL CTrackerMessage::SetDefaultEthernetStatus()
{
	// setup as an user string message
	if (!SetTypeOrClear(ETHERNET_STATUS_MSG_TYPE))
		return FALSE;

	// set defaults
	ETHERNET_STATUS_MSG* pMsg = m_Data.m_pEthernetStatus;
	ASSERT(pMsg);

	// set checksum and exit
	return SetChecksum();
}


///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultMtGeneral()
//
// Set the message type and setup default values
//
BOOL CTrackerMessage::SetDefaultMtGeneral()
{
	// setup as an user string message
	if( !SetTypeOrClear(MT_GENERAL_MSG_TYPE) )
		return FALSE;

	// set defaults
	MT_GENERAL_MSG* pMsg = m_Data.m_pMtGeneral;
	ASSERT( pMsg );

	pMsg->min_count_msw = 0;
	pMsg->min_count_lsw = 1;

	pMsg->max_percent = 75;

	pMsg->enable_output = FALSE;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultMtAcquire()
//
// Set the message type and setup default values
//
BOOL CTrackerMessage::SetDefaultMtAcquire()
{
	// setup as an user string message
	if( !SetTypeOrClear(MT_ACQUIRE_MSG_TYPE) )
		return FALSE;

	// set defaults
	MT_ACQUIRE_MSG* pMsg = m_Data.m_pMtAcquire;
	ASSERT( pMsg );

	pMsg->min_count_msw = 0;
	pMsg->min_count_lsw = 1;

	pMsg->max_percent = 75;

	pMsg->min_life = 1;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultMtTrack()
//
// Set the message type and setup default values
//
BOOL CTrackerMessage::SetDefaultMtTrack()
{
	// setup as an user string message
	if( !SetTypeOrClear(MT_TRACK_MSG_TYPE) )
		return FALSE;

	// set defaults
	MT_TRACK_MSG* pMsg = m_Data.m_pMtTrack;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultMtData()
//
// Set the message type and setup default values
//
BOOL CTrackerMessage::SetDefaultMtData()
{
	// setup as an user string message
	if( !SetTypeOrClear(MT_DATA_MSG_TYPE) )
		return FALSE;

	// set defaults
	MT_DATA_MSG* pMsg = m_Data.m_pMtData;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultMtValidation()
//
// Set the message type and setup default values
//
BOOL CTrackerMessage::SetDefaultMtValidation()
{
	// setup as an user string message
	if( !SetTypeOrClear(MT_VALIDATION_MSG_TYPE) )
		return FALSE;

	// set defaults
	MT_VALIDATION_MSG* pMsg = m_Data.m_pMtValidation;
	ASSERT( pMsg );

	pMsg->force_position = 0;
	pMsg->pixel_count_en = 1;
	pMsg->size_en = 1;

	pMsg->position_tolerance	= 1000;	// 10% of FOV
	pMsg->pixel_count_tolerance = 3000;	// 30% of target mass
	pMsg->width_tolerance		= 2500;	// 25% of target x size
	pMsg->height_tolerance		= 2500;	// 25% of target y size

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultScan()
//
// Set the message type to scan and setup default values
//
BOOL CTrackerMessage::SetDefaultScan()
{
	// setup as an user string message
	if( !SetTypeOrClear(SCAN_MSG_TYPE) )
		return FALSE;

	// set defaults
	SCAN_MSG* pMsg = m_Data.m_pScan;
	ASSERT( pMsg );


	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultMountRateDrive()
//
// Set the message type to mount rate drive and setup default values
//
BOOL CTrackerMessage::SetDefaultMountRateDrive()
{
	// setup as an user string message
	if( !SetTypeOrClear(MOUNT_RATE_DRIVE_MSG_TYPE) )
		return FALSE;

	// set defaults
	MOUNT_RATE_DRIVE_MSG* pMsg = m_Data.m_pMountRateDrive;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultMountControl()
//
// Set the message type to mount control and setup default values
//
BOOL CTrackerMessage::SetDefaultMountControl()
{
	// setup as an user string message
	if( !SetTypeOrClear(MOUNT_CONTROL_MSG_TYPE) )
		return FALSE;

	// set defaults
	MOUNT_CONTROL_MSG* pMsg = m_Data.m_pMountControl;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultControlBox()
//
// Set the message type to control box and setup default values
//
BOOL CTrackerMessage::SetDefaultControlBox()
{
	// setup as a control box message
	if( !SetTypeOrClear(CONTROL_BOX_MSG_TYPE) )
		return FALSE;

	// set defaults
	CONTROL_BOX_MSG* pMsg = m_Data.m_pControlBox;
	ASSERT( pMsg );

	pMsg->enable_box = 0;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultQueryConfig()
//
// Set the message type to query config and setup default values
//
BOOL CTrackerMessage::SetDefaultQueryConfig()
{
	// set message type
	if( !SetTypeOrClear(QUERY_CONFIG_MSG_TYPE) )
		return FALSE;

	// set defaults
	QUERY_CONFIG_MSG* pMsg = m_Data.m_pQueryConfig;
	ASSERT( pMsg );

	pMsg->get_msg_type = STATUS_MSG_TYPE;
	pMsg->get_msg_id = 0;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultPresetConfig()
//
// Set the message type to preset config and setup default values
//
BOOL CTrackerMessage::SetDefaultPresetConfig()
{
	// set message type
	if( !SetTypeOrClear(PRESET_CONFIG_MSG_TYPE) )
		return FALSE;

	// set defaults
	PRESET_CONFIG_MSG* pMsg = m_Data.m_pPresetConfig;
	ASSERT( pMsg );

	pMsg->command = PRESET_NO_ACTION;
	pMsg->config_bank = 0;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultBuiltInTest()
//
// Set the message type to built in test and setup default values
//
BOOL CTrackerMessage::SetDefaultBuiltInTest()
{
	// set message type
	if( !SetTypeOrClear(BUILT_IN_TEST_MSG_TYPE) )
		return FALSE;

	// set defaults
	BUILT_IN_TEST_MSG* pMsg = m_Data.m_pBuiltInTest;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultMountStatus()
//
// Set the message type to mount status and setup default values
//
BOOL CTrackerMessage::SetDefaultMountStatus()
{
	// set message type
	if( !SetTypeOrClear(MOUNT_CONTROL_MSG_TYPE) )
		return FALSE;

	// set defaults
	MOUNT_STATUS_MSG* pMsg = m_Data.m_pMountStatus;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultLrfControl()
//
// Set the message type to laser range finder control and setup default values
//
BOOL CTrackerMessage::SetDefaultLrfControl()
{
	// set message type
	if( !SetTypeOrClear(LRF_CONTROL_MSG_TYPE) )
		return FALSE;

	// set defaults
	LRF_CONTROL_MSG* pMsg = m_Data.m_pLrfControl;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultTargetRange()
//
// Set the message type to target range and setup default values
//
BOOL CTrackerMessage::SetDefaultTargetRange()
{
	// set message type
	if( !SetTypeOrClear(TARGET_RANGE_MSG_TYPE) )
		return FALSE;

	// set defaults
	TARGET_RANGE_MSG* pMsg = m_Data.m_pTargetRange;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultTargetGenerator()
//
// Set the message type to target generator and setup default values
//
BOOL CTrackerMessage::SetDefaultTargetGenerator()
{
	// set message type
	if( !SetTypeOrClear(TARGET_GENERATOR_MSG_TYPE) )
		return FALSE;

	// set defaults
	TARGET_GENERATOR_MSG* pMsg = m_Data.m_pTargetGenerator;
	ASSERT( pMsg );

//	pMsg->enable = ENABLE;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultGateControl()
//
// Set the message type to gate control and setup default values
//
BOOL CTrackerMessage::SetDefaultGateControl()
{
	// set message type
	if( !SetTypeOrClear(GATE_CONTROL_MSG_TYPE) )
		return FALSE;

	// set defaults
	GATE_CONTROL_MSG* pMsg = m_Data.m_pGateControl;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultMountFeedback()
//
// Set the message type to mount feedback and setup default values
//
BOOL CTrackerMessage::SetDefaultMountFeedback()
{
	// set message type
	if( !SetTypeOrClear(MOUNT_FEEDBACK_MSG_TYPE) )
		return FALSE;

	// set defaults
	MOUNT_FEEDBACK_MSG* pMsg = m_Data.m_pMountFeedback;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultDigitalIO()
//
// Set the message type to mount digital I/O and setup default values
//
BOOL CTrackerMessage::SetDefaultDigitalIO()
{
	// set message type
	if( !SetTypeOrClear(DIGITAL_IO_MSG_TYPE) )
		return FALSE;

	// set defaults
	DIGITAL_IO_MSG* pMsg = m_Data.m_pDigitalIO;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultDownloadCode()
//
// Set the message type to download code and setup default values
//
BOOL CTrackerMessage::SetDefaultDownloadCode()
{
	// setup as a download code message
	if( !SetTypeOrClear(DL_CODE_RECEIVE_MSG_TYPE) )
		return FALSE;

	// set defaults
	DL_CODE_RECEIVE_MSG* pMsg = m_Data.m_pDownloadCode;
	ASSERT( pMsg );

	pMsg->data_flag	= 0;
	pMsg->target	= 0;

	memset(pMsg->data, 0, DL_CODE_SIZE);

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultDownloadLicense()
//
// Set the message type to download license and setup default values
//
BOOL CTrackerMessage::SetDefaultDownloadLicense()
{
	// setup as a download code message
	if( !SetTypeOrClear(DL_LICENSE_MSG_TYPE) )
		return FALSE;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigGateSize()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultConfigGateSize()
{
	// setup message
	if( !SetTypeOrClear(CONFIG_GATE_SIZE_MSG_TYPE) )
		return FALSE;

	// set defaults
	CONFIG_GATE_SIZE_MSG* pMsg = m_Data.m_pConfigGateSize;
	ASSERT( pMsg );

	pMsg->min_sizex	= 32/4;
	pMsg->min_sizey	= 8;

	pMsg->max_sizex	= 984/4;
	pMsg->max_sizey	= 224;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigGatePos()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultConfigGatePos()
{
	// setup message
	if( !SetTypeOrClear(CONFIG_GATE_POS_MSG_TYPE) )
		return FALSE;

	// set defaults
	CONFIG_GATE_POS_MSG* pMsg = m_Data.m_pConfigGatePos;
	ASSERT( pMsg );

	pMsg->min_posx	= -511;
	pMsg->min_posy	= 127;

	pMsg->max_posx	= 511;
	pMsg->max_posy	= -127;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigAnnotation()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultConfigAnnotation()
{
	// setup message
	if( !SetTypeOrClear(CONFIG_ANNOTATION_MSG_TYPE) )
		return FALSE;

	// set defaults
	CONFIG_ANNOTATION_MSG* pMsg = m_Data.m_pConfigAnnotation;
	ASSERT( pMsg );

	pMsg->string2	= 26;
	pMsg->string1	= 0;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigSymbology()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultConfigSymbology()
{
	// setup message
	if( !SetTypeOrClear(CONFIG_SYMBOLOGY_MSG_TYPE) )
		return FALSE;

	// set defaults
	CONFIG_SYMBOLOGY_MSG* pMsg = m_Data.m_pConfigSymbology;
	ASSERT( pMsg );

	pMsg->flash_en	= OFF;
	pMsg->ret_style	= 0;
	pMsg->ret_disp	= OFF;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigCorrRefPos()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultConfigCorrRefPos()
{
	// setup message
	if( !SetTypeOrClear(CONFIG_CORR_REF_POS_MSG_TYPE) )
		return FALSE;

	// set defaults
	CONFIG_CORR_REF_POS_MSG* pMsg = m_Data.m_pConfigCorrRefPos;
	ASSERT( pMsg );

	pMsg->ref_x	= 511;
	pMsg->ref_y	= 127;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigVideo()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultConfigVideo()
{
	// setup message
	if( !SetTypeOrClear(CONFIG_VIDEO_MSG_TYPE) )
		return FALSE;

	// set defaults
	CONFIG_VIDEO_MSG* pMsg = m_Data.m_pConfigVideo;
	ASSERT( pMsg );

	pMsg->vid_type	= VIDEO_NTSC;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigPresetConfig()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultConfigPresetConfig()
{
	// setup message
	if( !SetTypeOrClear(CONFIG_PRESET_CONFIG_MSG_TYPE) )
		return FALSE;

	// set defaults
	CONFIG_PRESET_CONFIG_MSG* pMsg = m_Data.m_pConfigPresetConfig;
	ASSERT( pMsg );

	pMsg->config_bank = 0;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigAutoSize()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultConfigAutoSize()
{
	// setup message
	if( !SetTypeOrClear(CONFIG_AUTOSIZE_MSG_TYPE) )
		return FALSE;

	// set defaults
	CONFIG_AUTOSIZE_MSG* pMsg = m_Data.m_pConfigAutoSize;
	ASSERT( pMsg );

	pMsg->enable_rate = DISABLE;
	pMsg->grow_rate_x = 400;
	pMsg->grow_rate_y = 400;
	pMsg->shrink_rate_x = 400;
	pMsg->shrink_rate_y = 400;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigValidation()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultConfigValidation()
{
	// setup message
	if( !SetTypeOrClear(CONFIG_VALIDATION_MSG_TYPE) )
		return FALSE;

	// set defaults
	CONFIG_VALIDATION_MSG* pMsg = m_Data.m_pConfigValidation;
	ASSERT( pMsg );

	pMsg->min_pixels = 1;
	pMsg->max_percent = 75;
	pMsg->history_depth = 20;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigJoystick()
//
// Set the message type to config joystick and setup default values
//
BOOL CTrackerMessage::SetDefaultConfigJoystick()
{
	// setup as a config control box message
	if( !SetTypeOrClear(CONFIG_JOYSTICK_MSG_TYPE) )
		return FALSE;

	// set defaults
	CONFIG_JOYSTICK_MSG* pMsg = m_Data.m_pConfigJoystick;
	ASSERT( pMsg );

	pMsg->joy_reset = OFF;
	pMsg->joy_gain_x = 100;
	pMsg->joy_gain_y = 100;
	pMsg->joy_offset_x = 0;
	pMsg->joy_offset_y = 0;
	pMsg->joy_dead_x = 0;
	pMsg->joy_dead_y = 0;
	pMsg->zoom_scaling = ENABLE;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigLensFov()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultConfigLensFov()
{
	// setup message
	if( !SetTypeOrClear(CONFIG_LENS_FOV_MSG_TYPE) )
		return FALSE;

	// set defaults
	CONFIG_LENS_FOV_MSG* pMsg = m_Data.m_pConfigLensFov;
	ASSERT( pMsg );

	pMsg->scalar = 100;
	pMsg->bias = 0;
	pMsg->fov0 = 10000;
	pMsg->fov1 = 10000;
	pMsg->fov2 = 10000;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigMount()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultConfigMount()
{
	// setup message
	if( !SetTypeOrClear(CONFIG_MOUNT_MSG_TYPE) )
		return FALSE;

	// set defaults
	CONFIG_MOUNT_MSG* pMsg = m_Data.m_pConfigMount;
	ASSERT( pMsg );

	pMsg->mount_type = MOUNT_NONE;
	pMsg->auto_drift_cal = OFF;
	pMsg->manual_drift_cal = OFF;
	pMsg->drift_az = 0;
	pMsg->drift_el = 0;
	pMsg->min_az = -180;
	pMsg->max_az = 180;
	pMsg->min_el = -180;
	pMsg->max_el = 180;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigAnalogJoystick()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultConfigAnalogJoystick()
{
	// setup message
	if( !SetTypeOrClear(CONFIG_ANALOG_JOYSTICK_MSG_TYPE) )
		return FALSE;

	// set defaults
	CONFIG_ANALOG_JOYSTICK_MSG* pMsg = m_Data.m_pConfigAnalogJoystick;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigDigitalIO()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultConfigDigitalIO()
{
	// setup message
	if( !SetTypeOrClear(CONFIG_DIGITAL_IO_MSG_TYPE) )
		return FALSE;

	// set defaults
	CONFIG_DIGITAL_IO_MSG* pMsg = m_Data.m_pConfigDigitalIO;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigZoomToRange()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultConfigZoomToRange()
{
	// setup message
	if( !SetTypeOrClear(CONFIG_ZOOM_TO_RANGE_MSG_TYPE) )
		return FALSE;

	// set defaults
	CONFIG_ZOOM_TO_RANGE_MSG* pMsg = m_Data.m_pConfigZoomToRange;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigGateStyle()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultConfigGateStyle()
{
	// setup message
	if( !SetTypeOrClear(CONFIG_GATE_STYLE_MSG_TYPE) )
		return FALSE;

	// set defaults
	CONFIG_GATE_STYLE_MSG* pMsg = m_Data.m_pConfigGateStyle;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigGateReticle()
//
// Set the message type and default values
//
// ONLY WORKS FOR THE SECOND GATE (GATE1)
//
BOOL CTrackerMessage::SetDefaultConfigGateReticle()
{
	// setup message
	if( !SetTypeOrClear(CONFIG_GATE_RETICLE_MSG_TYPE, GATE1_SYNC_WORD) )
		return FALSE;

	// set defaults
	CONFIG_GATE_RETICLE_MSG* pMsg = m_Data.m_pConfigGateReticle;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigGateReticle2()
//
// Set the message type and default values
//
// ONLY WORKS FOR THE SECOND GATE (GATE1)
//
BOOL CTrackerMessage::SetDefaultConfigGateReticle2()
{
	// setup message
	if( !SetTypeOrClear(CONFIG_GATE_RETICLE2_MSG_TYPE, GATE1_SYNC_WORD) )
		return FALSE;

	// set defaults
	CONFIG_GATE_RETICLE2_MSG* pMsg = m_Data.m_pConfigGateReticle2;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigLosReticle()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultConfigLosReticle()
{
	// setup message
	if( !SetTypeOrClear(CONFIG_LOS_RETICLE_MSG_TYPE) )
		return FALSE;

	// set defaults
	CONFIG_LOS_RETICLE_MSG* pMsg = m_Data.m_pConfigLosReticle;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigTrackFlag()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultConfigTrackFlag()
{
	// setup message
	if( !SetTypeOrClear(CONFIG_TRACK_FLAG_MSG_TYPE) )
		return FALSE;

	// set defaults
	CONFIG_TRACK_FLAG_MSG* pMsg = m_Data.m_pConfigTrackFlag;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigNorthOffset()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultConfigNorthOffset()
{
	// setup message
	if( !SetTypeOrClear(CONFIG_NORTH_OFFSET_MSG_TYPE) )
		return FALSE;

	// set defaults
	CONFIG_NORTH_OFFSET_MSG* pMsg = m_Data.m_pConfigNorthOffset;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigDigitalVideo()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultConfigDigitalVideo()
{
	// setup message
	if( !SetTypeOrClear(CONFIG_DIGITAL_VIDEO_MSG_TYPE) )
		return FALSE;

	// set defaults
	CONFIG_DIGITAL_VIDEO_MSG* pMsg = m_Data.m_pConfigDigitalVideo;
	ASSERT( pMsg );

	pMsg->pixels_per_clock_ext = 1;
	pMsg->out_pixels_per_clock = 1;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigAnnotation2()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultConfigAnnotation2()
{
	// setup message
	if( !SetTypeOrClear(CONFIG_ANNOTATION2_MSG_TYPE) )
		return FALSE;

	// set defaults
	CONFIG_ANNOTATION2_MSG* pMsg = m_Data.m_pConfigAnnotation2;
	ASSERT( pMsg );

	pMsg->string2	= 26;
	pMsg->string1	= 0;

	pMsg->anno_size_x = 1;
	pMsg->anno_size_y = 0;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigSerialPorts()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultConfigSerialPorts()
{
	// setup message
	if( !SetTypeOrClear(CONFIG_SERIAL_PORTS_MSG_TYPE) )
		return FALSE;

	// set defaults
	CONFIG_SERIAL_PORTS_MSG* pMsg = m_Data.m_pConfigSerialPorts;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigControlBox()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultConfigControlBox()
{
	// setup message
	if( !SetTypeOrClear(CONFIG_CONTROL_BOX_MSG_TYPE) )
		return FALSE;

	// set defaults
	CONFIG_CONTROL_BOX_MSG* pMsg = m_Data.m_pConfigControlBox;
	ASSERT( pMsg );

	pMsg->vid_select1 = VS_ANALOG1;
	pMsg->vid_select2 = VS_ANALOG2;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigTargetSimulator()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultConfigTargetSimulator()
{
	// setup message
	if( !SetTypeOrClear(CONFIG_TARGET_SIMULATOR_MSG_TYPE) )
		return FALSE;

	// set defaults
	CONFIG_TARGET_SIMULATOR_MSG* pMsg = m_Data.m_pConfigTargetSimulator;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigCrp()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultConfigCrp()
{
	// setup message
	if( !SetTypeOrClear(CONFIG_CRP_MSG_TYPE) )
		return FALSE;

	// set defaults
	CONFIG_CRP_MSG* pMsg = m_Data.m_pConfigCrp;
	ASSERT( pMsg );

	pMsg->gate_size_x = 600;
	pMsg->gate_size_y = 400;
	pMsg->min_life = 3;
	pMsg->max_count_lsw = LOWORD(1024*1024);
	pMsg->max_count_msw = HIWORD(1024*1024);
	pMsg->min_ave_growth_lsw = 10;
	pMsg->growth_filter_alpha = 1000;	// 0.1
	pMsg->gate_size_ratio = 200;		// 2:1

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigAutoThreshold()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultConfigAutoThreshold()
{
	// setup message
	if( !SetTypeOrClear(CONFIG_AUTOTHRESHOLD_MSG_TYPE) )
		return FALSE;

	// set defaults
	CONFIG_AUTOTHRESHOLD_MSG* pMsg = m_Data.m_pConfigAutoThreshold;
	ASSERT( pMsg );

	pMsg->enable_alpha_filter = 0;
	pMsg->acquire_alpha = 5000;		// 0.5
	pMsg->track_alpha = 5000;		// 0.5
	pMsg->min_contrast = 500;		// 5.0%

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigEthernet()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultConfigEthernet()
{
	// setup message
	if( !SetTypeOrClear(CONFIG_ETHERNET_MSG_TYPE) )
		return FALSE;

	// set defaults
	CONFIG_ETHERNET_MSG* pMsg = m_Data.m_pConfigEthernet;
	ASSERT( pMsg );

	pMsg->enable_dhcp = TRUE;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigDigitalVideoExt()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultConfigDigitalVideoExt()
{
	// setup message
	if( !SetTypeOrClear(CONFIG_DIGITAL_VIDEO_EXT_MSG_TYPE) )
		return FALSE;

	// set defaults
	CONFIG_DIGITAL_VIDEO_EXT_MSG* pMsg = m_Data.m_pConfigDigitalVideoExt;
	ASSERT( pMsg );

	pMsg->enable_nonstandard = DISABLE;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigDigitalPreprocess()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultConfigDigitalPreprocess()
{
	// setup message
	if( !SetTypeOrClear(CONFIG_DIGITAL_PREPROCESS_MSG_TYPE) )
		return FALSE;

	// set defaults
	CONFIG_DIGITAL_PREPROCESS_MSG* pMsg = m_Data.m_pConfigDigitalPreprocess;
	ASSERT( pMsg );

	pMsg->enable_crop = DISABLE;
	pMsg->enable_line_flip = DISABLE;
	pMsg->enable_frame_flip = DISABLE;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigIffTrack()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultConfigIffTrack()
{
	// setup message
	if( !SetTypeOrClear(CONFIG_IFF_TRACK_MSG_TYPE) )
		return FALSE;

	// set defaults
	CONFIG_IFF_TRACK_MSG* pMsg = m_Data.m_pConfigIffTrack;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigIntrusionDetect()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultConfigIntrusionDetect()
{
	// setup message
	if( !SetTypeOrClear(CONFIG_INTRUSION_DETECT_MSG_TYPE) )
		return FALSE;

	// set defaults
	CONFIG_INTRUSION_DETECT_MSG* pMsg = m_Data.m_pConfigIntrusionDetect;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigPosTrack()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultConfigPosTrack()
{
	// setup message
	if( !SetTypeOrClear(CONFIG_POS_TRACK_MSG_TYPE) )
		return FALSE;

	// set defaults
	CONFIG_POS_TRACK_MSG* pMsg = m_Data.m_pConfigPosTrack;
	ASSERT( pMsg );

	pMsg->enable					= OFF;
	pMsg->invert_az					= OFF;
	pMsg->invert_el					= OFF;

	pMsg->az_threshold				= 100;		// 0.1 degrees
	pMsg->az_filter_lambda			= 1000;		// 1.0 (no smoothing)
	pMsg->az_filter_limit			= 65535;	// 65.535 degrees (max / don't reject)
	pMsg->az_rejected_points_limit	= 3;		// 3 point rejection limit
	pMsg->az_near_proportion		= 100;		// 1.0
	pMsg->az_near_integral			= 0;		// disable integration
	pMsg->az_near_integral_limit	= 0;		// no limit
	pMsg->az_far_proportion			= 100;		// 1.0
	pMsg->az_far_integral			= 0;		// disable integration
	pMsg->az_far_integral_limit		= 0;		// no limit

	pMsg->el_threshold				= 100;		// 0.1 degrees
	pMsg->el_filter_lambda			= 1000;		// 1.0 (no smoothing)
	pMsg->el_filter_limit			= 65535;	// 65.535 degrees (max / don't reject)
	pMsg->el_rejected_points_limit	= 3;		// 3 point rejection limit
	pMsg->el_near_proportion		= 100;		// 1.0
	pMsg->el_near_integral			= 0;		// disable integration
	pMsg->el_near_integral_limit	= 0;		// no limit
	pMsg->el_far_proportion			= 100;		// 1.0
	pMsg->el_far_integral			= 0;		// disable integration
	pMsg->el_far_integral_limit		= 0;		// no limit

	pMsg->timeout					= 60;		// 60 fields (1 second for NTSC video)

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigControlBoxIO()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultConfigControlBoxIO()
{
	// setup message
	if( !SetTypeOrClear(CONFIG_CONTROL_BOX_IO_MSG_TYPE) )
		return FALSE;

	// set defaults
	CONFIG_CONTROL_BOX_IO_MSG* pMsg = m_Data.m_pConfigControlBoxIO;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigVideoSwitch()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultConfigVideoSwitch()
{
	// setup message
	if( !SetTypeOrClear(CONFIG_VIDEO_SWITCH_MSG_TYPE) )
		return FALSE;

	// set defaults
	CONFIG_VIDEO_SWITCH_MSG* pMsg = m_Data.m_pConfigVideoSwitch;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultConfigGps()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultConfigGps()
{
	// setup message
	if( !SetTypeOrClear(CONFIG_GPS_MSG_TYPE) )
		return FALSE;

	// set defaults
	CONFIG_GPS_MSG* pMsg = m_Data.m_pConfigGps;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultLensConfig()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultLensConfig()
{
	// setup message
	if( !SetTypeOrClear(LENS_CONFIG_MSG_TYPE) )
		return FALSE;

	// set defaults
	LENS_CONFIG_MSG* pMsg = m_Data.m_pLensConfig;
	ASSERT( pMsg );

	pMsg->analog1 = LENS_NONE;
	pMsg->analog2 = LENS_NONE;
	pMsg->analog3 = LENS_NONE;
	pMsg->analog4 = LENS_NONE;
	pMsg->digital1 = LENS_NONE;
	pMsg->digital2 = LENS_NONE;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultLensGraflex()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultLensGraflex()
{
	// setup message
	if( !SetTypeOrClear(LENS_GRAFLEX_MSG_TYPE) )
		return FALSE;

	// set defaults
	LENS_GRAFLEX_MSG* pMsg = m_Data.m_pLensGraflex;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultLensSerialTfov()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultLensSerialTfov()
{
	// setup message
	if( !SetTypeOrClear(LENS_SERIAL_TFOV_MSG_TYPE) )
		return FALSE;

	// set defaults
	LENS_SERIAL_TFOV_MSG* pMsg = m_Data.m_pLensSerialTfov;
	ASSERT( pMsg );

	pMsg->serial_port = 4;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultLensSerialDfov()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultLensSerialDfov()
{
	// setup message
	if( !SetTypeOrClear(LENS_SERIAL_DFOV_MSG_TYPE) )
		return FALSE;

	// set defaults
	LENS_SERIAL_DFOV_MSG* pMsg = m_Data.m_pLensSerialDfov;
	ASSERT( pMsg );

	pMsg->serial_port = 4;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultLensGeneric()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultLensGeneric()
{
	// setup message
	if( !SetTypeOrClear(LENS_GENERIC_MSG_TYPE) )
		return FALSE;

	// set defaults
	LENS_GENERIC_MSG* pMsg = m_Data.m_pLensGeneric;
	ASSERT( pMsg );

	pMsg->mount_gain = 2048; // this is a gain of 1.0

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultLensSerialZoom()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultLensSerialZoom()
{
	// setup message
	if( !SetTypeOrClear(LENS_SERIAL_ZOOM_MSG_TYPE) )
		return FALSE;

	// set defaults
	LENS_SERIAL_ZOOM_MSG* pMsg = m_Data.m_pLensSerialZoom;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultLensSerialIrZoom()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultLensSerialIrZoom()
{
	// setup message
	if( !SetTypeOrClear(LENS_SERIAL_IR_ZOOM_MSG_TYPE) )
		return FALSE;

	// set defaults
	LENS_SERIAL_IR_ZOOM_MSG* pMsg = m_Data.m_pLensSerialIrZoom;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultLensAnalogZoom()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultLensAnalogZoom()
{
	// setup message
	if( !SetTypeOrClear(LENS_ANALOG_ZOOM_MSG_TYPE) )
		return FALSE;

	// set defaults
	LENS_ANALOG_ZOOM_MSG* pMsg = m_Data.m_pLensAnalogZoom;
	ASSERT( pMsg );

	pMsg->gain = 100;		// 1.00
	pMsg->coeff1 = 10000;	// 1.0000
	pMsg->max_fov = 100;	// 1.00

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultCameraConfig()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultCameraConfig()
{
	// setup message
	if( !SetTypeOrClear(CAMERA_CONFIG_MSG_TYPE) )
		return FALSE;

	// set defaults
	CAMERA_CONFIG_MSG* pMsg = m_Data.m_pCameraConfig;
	ASSERT( pMsg );

	pMsg->analog1 = CAMERA_NONE;
	pMsg->analog2 = CAMERA_NONE;
	pMsg->analog3 = CAMERA_NONE;
	pMsg->analog4 = CAMERA_NONE;
	pMsg->digital1 = CAMERA_NONE;
	pMsg->digital2 = CAMERA_NONE;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultCameraGeneric()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultCameraGeneric()
{
	// setup message
	if( !SetTypeOrClear(CAMERA_GENERIC_MSG_TYPE) )
		return FALSE;

	// set defaults
	CAMERA_GENERIC_MSG* pMsg = m_Data.m_pCameraGeneric;
	ASSERT( pMsg );

	pMsg->serial_port = 5;
	pMsg->agc = MANUAL;
	pMsg->manual_gain = 0;
	pMsg->nuc_table = 0;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultLensSerialFixedFov()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultLensSerialFixedFov()
{
	// setup message
	if( !SetTypeOrClear(LENS_SERIAL_FIXED_FOV_MSG_TYPE) )
		return FALSE;

	// set defaults
	LENS_SERIAL_FIXED_FOV_MSG* pMsg = m_Data.m_pLensSerialFixedFov;
	ASSERT( pMsg );

	pMsg->serial_port = 5;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultLensSerialIrDfov()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultLensSerialIrDfov()
{
	// setup message
	if( !SetTypeOrClear(LENS_SERIAL_IR_DFOV_MSG_TYPE) )
		return FALSE;

	// set defaults
	LENS_SERIAL_IR_DFOV_MSG* pMsg = m_Data.m_pLensSerialIrDfov;
	ASSERT( pMsg );

	pMsg->serial_port = 5;

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultLensMoogZoom()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultLensMoogZoom()
{
	// setup message
	if( !SetTypeOrClear(LENS_MOOG_ZOOM_MSG_TYPE) )
		return FALSE;

	// set defaults
	LENS_MOOG_ZOOM_MSG* pMsg = m_Data.m_pLensMoogZoom;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}


///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultControlBoxControl()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultControlBoxControl()
{
	// setup message
	if( !SetTypeOrClear(CONTROL_BOX_CONTROL_MSG_TYPE) )
		return FALSE;

	// set data
	CONTROL_BOX_CONTROL_MSG* pMsg = m_Data.m_pControlBoxControl;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultControlBoxStatus()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultControlBoxStatus()
{
	// setup message
	if( !SetTypeOrClear(CONTROL_BOX_STATUS_MSG_TYPE) )
		return FALSE;

	// set data
	CONTROL_BOX_STATUS_MSG* pMsg = m_Data.m_pControlBoxStatus;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage::SetDefaultCapabilities()
//
// Set the message type and default values
//
BOOL CTrackerMessage::SetDefaultCapabilities()
{
	// setup message
	if( !SetTypeOrClear(CAPABILITIES_MSG_TYPE) )
		return FALSE;

	// set defaults
	CAPABILITIES_MSG* pMsg = m_Data.m_pCapabilities;
	ASSERT( pMsg );

	// set checksum and exit
	return SetChecksum();
}

