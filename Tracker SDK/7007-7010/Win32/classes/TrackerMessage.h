///////////////////////////////////////////////////////////////////////////////
// TrackerMessage.h: interface for the CTrackerMessage class.
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

#if !defined(AFX_TRACKERMESSAGE_H__92DFD911_7112_11D3_8132_009027728EF1__INCLUDED_)
#define AFX_TRACKERMESSAGE_H__92DFD911_7112_11D3_8132_009027728EF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GenArray.h"
#include "MSG_FMT.h"
#include "TimeStamp.h"

///////////////////////////////////////////////////////////////////////////////
// CTrackerMessage
//
class CTrackerMessage  
{
protected:
	static	MSG_TBL	MessageTable[MSG_TBL_LEN];

public:
	static	USHORT	CurrentSyncWord;

protected:
	CTimeStamp	m_TimeStamp;

	int			m_Type;
	int			m_nRawSize;
	
	union
	{
		unsigned char*				m_pRaw;
		PING_MSG*					m_pPing;
		RUN_TIME_CTRL_MSG*			m_pControl;
		SYSTEM_CTRL_MSG*			m_pSystem;
		LOS_OFFSET_CTRL_MSG*		m_pLOSOffset;
		OFFSET_AIM_CTRL_MSG*		m_pOffsetAim;
		SYMBOLOGY_CTRL_MSG*			m_pSymbology;
		CORRELATION_CTRL_MSG*		m_pCorrelation;
		FILTER_CTRL_MSG*			m_pFilter;
		COAST_CTRL_MSG*				m_pCoast;
		TGT_VALIDATION_CTRL_MSG*	m_pTargetValidation;
		AAQ_ACQUIRE_CTRL_MSG*		m_pAutoAcquire;
		AAQ_TRACK_CTRL_MSG*			m_pAutoAcquireTrack;
		AAQ_TGT_SELECT_CTRL_MSG*	m_pTargetSelect;
		ANNOTATION_MSG*				m_pAnnotation;
		USER_STRING_MSG*			m_pUserString;
		SCAN_MSG*					m_pScan;
		MOUNT_RATE_DRIVE_MSG*		m_pMountRateDrive;
		MOUNT_CONTROL_MSG*			m_pMountControl;
		CONTROL_BOX_MSG*			m_pControlBox;
		QUERY_CONFIG_MSG*			m_pQueryConfig;
		PRESET_CONFIG_MSG*			m_pPresetConfig;
		LENS_CONFIG_MSG*			m_pLensConfig;
		LENS_GRAFLEX_MSG*			m_pLensGraflex;
		LENS_SERIAL_TFOV_MSG*		m_pLensSerialTfov;
		LENS_SERIAL_DFOV_MSG*		m_pLensSerialDfov;
		LENS_GENERIC_MSG*			m_pLensGeneric;
		LENS_SERIAL_ZOOM_MSG*		m_pLensSerialZoom;
		LENS_SERIAL_IR_ZOOM_MSG*	m_pLensSerialIrZoom;
		LENS_ANALOG_ZOOM_MSG*		m_pLensAnalogZoom;
		CAMERA_CONFIG_MSG*			m_pCameraConfig;
		CAMERA_GENERIC_MSG*			m_pCameraGeneric;
		LENS_SERIAL_FIXED_FOV_MSG*	m_pLensSerialFixedFov;
		LENS_SERIAL_IR_DFOV_MSG*	m_pLensSerialIrDfov;
		LENS_MOOG_ZOOM_MSG*			m_pLensMoogZoom;
		ANALOG_INPUT_MSG*			m_pAnalogInput;
		CAPABILITIES_MSG*			m_pCapabilities;
		BUILT_IN_TEST_MSG*			m_pBuiltInTest;
		MOUNT_STATUS_MSG*			m_pMountStatus;
		LRF_CONTROL_MSG*			m_pLrfControl;
		TARGET_RANGE_MSG*			m_pTargetRange;
		TARGET_GENERATOR_MSG*		m_pTargetGenerator;
		GATE_CONTROL_MSG*			m_pGateControl;
		MOUNT_FEEDBACK_MSG*			m_pMountFeedback;
		DIGITAL_IO_MSG*				m_pDigitalIO;
		DL_CODE_RECEIVE_MSG*		m_pDownloadCode;
		DL_CODE_STATUS_MSG*			m_pDownloadCodeStatus;
		DL_LICENSE_MSG*				m_pDownloadLicense;
		DL_CODE_STATUS2_MSG*		m_pDownloadCodeStatus2;
		GATE_STATISTICS_MSG*		m_pGateStatistics;
		DIGITAL_VIDEO_STATUS_MSG*	m_pDigitalVideoStatus;
		USER_STRING2_MSG*			m_pUserString2;
		TARGET_SIMULATOR_MSG*		m_pTargetSimulator;
		CRP_CONTROL_MSG*			m_pCrpControl;
		STEERED_MIRROR_FILTER_MSG*	m_pSteeredMirrorFilter;
		IFF_TRACK_STATUS_MSG*		m_pIffTrackStatus;
		STEERED_MIRROR_CALIBRATION_MSG* m_pSteeredMirrorCalibration;
		OVERLAY_CONTROL_MSG*		m_pOverlayControl;
		OVERLAY_STATUS_MSG*			m_pOverlayStatus;
		OVERLAY_STATUS_EXT_MSG*		m_pOverlayStatusExt;
		LOS_OFFSET_CTRL2_MSG*		m_pLOSOffset2;
		OFFSET_AIM_CTRL2_MSG*		m_pOffsetAim2;
		POS_TRACK_STATUS_MSG*		m_pPosTrackStatus;
		CAMERA_CONTROL_MSG*			m_pCameraControl;
		GPS_DATA_MSG*				m_pGpsData;
		SYSTEM_STATUS_MSG*			m_pSystemStatus;
		FPGA_VIDEO_STATUS_MSG*		m_pFpgaVideoStatus;
		ETHERNET_STATUS_MSG*		m_pEthernetStatus;
		MT_GENERAL_MSG*				m_pMtGeneral;
		MT_ACQUIRE_MSG*				m_pMtAcquire;
		MT_TRACK_MSG*				m_pMtTrack;
		MT_DATA_MSG*				m_pMtData;
		MT_VALIDATION_MSG*			m_pMtValidation;
		CONTROL_BOX_CONTROL_MSG*	m_pControlBoxControl;
		CONTROL_BOX_STATUS_MSG*		m_pControlBoxStatus;
		THRESHOLD_STATISTICS_MSG*	m_pThresholdStatistics;
		CONFIG_GATE_SIZE_MSG*		m_pConfigGateSize;
		CONFIG_GATE_POS_MSG*		m_pConfigGatePos;
		CONFIG_ANNOTATION_MSG*		m_pConfigAnnotation;
		CONFIG_SYMBOLOGY_MSG*		m_pConfigSymbology;
		CONFIG_CORR_REF_POS_MSG*	m_pConfigCorrRefPos;
		CONFIG_VIDEO_MSG*			m_pConfigVideo;
		CONFIG_PRESET_CONFIG_MSG*	m_pConfigPresetConfig;
		CONFIG_AUTOSIZE_MSG*		m_pConfigAutoSize;
		CONFIG_VALIDATION_MSG*		m_pConfigValidation;
		CONFIG_JOYSTICK_MSG*		m_pConfigJoystick;
		CONFIG_LENS_FOV_MSG*		m_pConfigLensFov;
		CONFIG_MOUNT_MSG*			m_pConfigMount;
		CONFIG_ANALOG_JOYSTICK_MSG*	m_pConfigAnalogJoystick;
		CONFIG_DIGITAL_IO_MSG*		m_pConfigDigitalIO;
		CONFIG_ZOOM_TO_RANGE_MSG*	m_pConfigZoomToRange;
		CONFIG_GATE_STYLE_MSG*		m_pConfigGateStyle;
		CONFIG_GATE_RETICLE_MSG*	m_pConfigGateReticle;
		CONFIG_LOS_RETICLE_MSG*		m_pConfigLosReticle;
		CONFIG_TRACK_FLAG_MSG*		m_pConfigTrackFlag;
		CONFIG_NORTH_OFFSET_MSG*	m_pConfigNorthOffset;
		CONFIG_DIGITAL_VIDEO_MSG*	m_pConfigDigitalVideo;
		CONFIG_ANNOTATION2_MSG*		m_pConfigAnnotation2;
		CONFIG_SERIAL_PORTS_MSG*	m_pConfigSerialPorts;
		CONFIG_CONTROL_BOX_MSG*		m_pConfigControlBox;
		CONFIG_TARGET_SIMULATOR_MSG* m_pConfigTargetSimulator;
		CONFIG_CRP_MSG*				m_pConfigCrp;
		CONFIG_AUTOTHRESHOLD_MSG*	m_pConfigAutoThreshold;
		CONFIG_ETHERNET_MSG*		m_pConfigEthernet;
		CONFIG_DIGITAL_VIDEO_EXT_MSG* m_pConfigDigitalVideoExt;
		CONFIG_DIGITAL_PREPROCESS_MSG* m_pConfigDigitalPreprocess;
		CONFIG_IFF_TRACK_MSG*		m_pConfigIffTrack;
		CONFIG_INTRUSION_DETECT_MSG* m_pConfigIntrusionDetect;
		CONFIG_POS_TRACK_MSG*		m_pConfigPosTrack;
		CONFIG_CONTROL_BOX_IO_MSG*	m_pConfigControlBoxIO;
		CONFIG_VIDEO_SWITCH_MSG*	m_pConfigVideoSwitch;
		CONFIG_GATE_RETICLE2_MSG*	m_pConfigGateReticle2;
		CONFIG_GPS_MSG*				m_pConfigGps;
		MESSAGE_ACK_MSG*			m_pMessageAck;
		STATUS_MSG*					m_pStatus;

	} m_Data;

public:
	CTrackerMessage();
	CTrackerMessage(const CTrackerMessage& src) { m_Data.m_pRaw = NULL; Copy(src); }
	virtual ~CTrackerMessage();

	CTrackerMessage& Copy(const CTrackerMessage& src);
	CTrackerMessage& operator=(const CTrackerMessage& src) { return Copy(src); }

	BOOL IsEqual(const CTrackerMessage& msg2) const;

public:
	unsigned char*	GetRawBuffer() { return m_Data.m_pRaw; }
	int				GetRawSize() { return m_nRawSize; }

	BOOL			GetAsHexString(char* pString, int nBufferLen);

	PING_MSG*					GetPing() { return m_Data.m_pPing; }
	RUN_TIME_CTRL_MSG*			GetControl() { return m_Data.m_pControl; }
	SYSTEM_CTRL_MSG*			GetSystem() { return m_Data.m_pSystem; }
	LOS_OFFSET_CTRL_MSG*		GetLOSOffset() { return m_Data.m_pLOSOffset; }
	OFFSET_AIM_CTRL_MSG*		GetOffsetAim() { return m_Data.m_pOffsetAim; }
	SYMBOLOGY_CTRL_MSG*			GetSymbology() { return m_Data.m_pSymbology; }
	CORRELATION_CTRL_MSG*		GetCorrelation() { return m_Data.m_pCorrelation; }
	FILTER_CTRL_MSG*			GetFilter() { return m_Data.m_pFilter; }
	COAST_CTRL_MSG*				GetCoast() { return m_Data.m_pCoast; }
	TGT_VALIDATION_CTRL_MSG*	GetTargetValidation() { return m_Data.m_pTargetValidation; }
	AAQ_ACQUIRE_CTRL_MSG*		GetAutoAcquire() { return m_Data.m_pAutoAcquire; }
	AAQ_TRACK_CTRL_MSG*			GetAutoAcquireTrack() { return m_Data.m_pAutoAcquireTrack; }
	AAQ_TGT_SELECT_CTRL_MSG*	GetTargetSelect() { return m_Data.m_pTargetSelect; }
	ANNOTATION_MSG*				GetAnnotation() { return m_Data.m_pAnnotation; }
	USER_STRING_MSG*			GetUserString() { return m_Data.m_pUserString; }
	SCAN_MSG*					GetScan() { return m_Data.m_pScan; }
	MOUNT_RATE_DRIVE_MSG*		GetMountRateDrive() { return m_Data.m_pMountRateDrive; }
	MOUNT_CONTROL_MSG*			GetMountControl() { return m_Data.m_pMountControl; }
	CONTROL_BOX_MSG*			GetControlBox() { return m_Data.m_pControlBox; }
	QUERY_CONFIG_MSG*			GetQueryConfig() { return m_Data.m_pQueryConfig; }
	PRESET_CONFIG_MSG*			GetPresetConfig() { return m_Data.m_pPresetConfig; }
	LENS_CONFIG_MSG*			GetLensConfig() { return m_Data.m_pLensConfig; }
	LENS_GRAFLEX_MSG*			GetLensGraflex() { return m_Data.m_pLensGraflex; }
	LENS_SERIAL_TFOV_MSG*		GetLensSerialTfov() { return m_Data.m_pLensSerialTfov; }
	LENS_SERIAL_DFOV_MSG*		GetLensSerialDfov() { return m_Data.m_pLensSerialDfov; }
	LENS_GENERIC_MSG*			GetLensGeneric() { return m_Data.m_pLensGeneric; }
	LENS_SERIAL_ZOOM_MSG*		GetLensSerialZoom() { return m_Data.m_pLensSerialZoom; }
	LENS_SERIAL_IR_ZOOM_MSG*	GetLensSerialIrZoom() { return m_Data.m_pLensSerialIrZoom; }
	LENS_ANALOG_ZOOM_MSG*		GetLensAnalogZoom() { return m_Data.m_pLensAnalogZoom; }
	CAMERA_CONFIG_MSG*			GetCameraConfig() { return m_Data.m_pCameraConfig; }
	CAMERA_GENERIC_MSG*			GetCameraGeneric() { return m_Data.m_pCameraGeneric; }
	LENS_SERIAL_FIXED_FOV_MSG*	GetLensSerialFixedFov() { return m_Data.m_pLensSerialFixedFov; }
	LENS_SERIAL_IR_DFOV_MSG*	GetLensSerialIrDfov() { return m_Data.m_pLensSerialIrDfov; }
	LENS_MOOG_ZOOM_MSG*			GetLensMoogZoom() { return m_Data.m_pLensMoogZoom; }
	ANALOG_INPUT_MSG*			GetAnalogInput() { return m_Data.m_pAnalogInput; }
	CAPABILITIES_MSG*			GetCapabilities() { return m_Data.m_pCapabilities; }
	BUILT_IN_TEST_MSG*			GetBuiltInTest() { return m_Data.m_pBuiltInTest; }
	MOUNT_STATUS_MSG*			GetMountStatus() { return m_Data.m_pMountStatus; }
	LRF_CONTROL_MSG*			GetLrfControl() { return m_Data.m_pLrfControl; }
	TARGET_RANGE_MSG*			GetTargetRange() { return m_Data.m_pTargetRange; }
	TARGET_GENERATOR_MSG*		GetTargetGenerator() { return m_Data.m_pTargetGenerator; }
	GATE_CONTROL_MSG*			GetGateControl() { return m_Data.m_pGateControl; }
	MOUNT_FEEDBACK_MSG*			GetMountFeedback() { return m_Data.m_pMountFeedback; }
	DIGITAL_IO_MSG*				GetDigitalIO() { return m_Data.m_pDigitalIO; }
	DL_CODE_RECEIVE_MSG*		GetDownloadCode() { return m_Data.m_pDownloadCode; }
	DL_CODE_STATUS_MSG*			GetDownloadCodeStatus() { return m_Data.m_pDownloadCodeStatus; }
	DL_LICENSE_MSG*				GetDownloadLicense() { return m_Data.m_pDownloadLicense; }
	DL_CODE_STATUS2_MSG*		GetDownloadCodeStatus2() { return m_Data.m_pDownloadCodeStatus2; }
	GATE_STATISTICS_MSG*		GetGateStatistics() { return m_Data.m_pGateStatistics; }
	DIGITAL_VIDEO_STATUS_MSG*	GetDigitalVideoStatus() { return m_Data.m_pDigitalVideoStatus; }
	USER_STRING2_MSG*			GetUserString2() { return m_Data.m_pUserString2; }
	TARGET_SIMULATOR_MSG*		GetTargetSimulator() { return m_Data.m_pTargetSimulator; }
	CRP_CONTROL_MSG*			GetCrpControl() { return m_Data.m_pCrpControl; }
	STEERED_MIRROR_FILTER_MSG*	GetSteeredMirrorFilter() { return m_Data.m_pSteeredMirrorFilter; }
	IFF_TRACK_STATUS_MSG*		GetIffTrackStatus() { return m_Data.m_pIffTrackStatus; }
	STEERED_MIRROR_CALIBRATION_MSG* GetSteeredMirrorCalibration() { return m_Data.m_pSteeredMirrorCalibration; }
	OVERLAY_CONTROL_MSG*		GetOverlayControl() { return m_Data.m_pOverlayControl; }
	OVERLAY_STATUS_MSG*			GetOverlayStatus() { return m_Data.m_pOverlayStatus; }
	OVERLAY_STATUS_EXT_MSG*		GetOverlayStatusExt() { return m_Data.m_pOverlayStatusExt; }
	LOS_OFFSET_CTRL2_MSG*		GetLOSOffset2() { return m_Data.m_pLOSOffset2; }
	OFFSET_AIM_CTRL2_MSG*		GetOffsetAim2() { return m_Data.m_pOffsetAim2; }
	POS_TRACK_STATUS_MSG*		GetPosTrackStatus() { return m_Data.m_pPosTrackStatus; }
	CAMERA_CONTROL_MSG*			GetCameraControl() { return m_Data.m_pCameraControl; }
	GPS_DATA_MSG*				GetGpsData() { return m_Data.m_pGpsData; }
	SYSTEM_STATUS_MSG*			GetSystemStatus() { return m_Data.m_pSystemStatus; }
	FPGA_VIDEO_STATUS_MSG*		GetFpgaVideoStatus() { return m_Data.m_pFpgaVideoStatus;  }
	ETHERNET_STATUS_MSG*		GetEthernetStatus() { return m_Data.m_pEthernetStatus; }
	MT_GENERAL_MSG*				GetMtGeneral() { return m_Data.m_pMtGeneral; }
	MT_ACQUIRE_MSG*				GetMtAcquire() { return m_Data.m_pMtAcquire; }
	MT_TRACK_MSG*				GetMtTrack() { return m_Data.m_pMtTrack; }
	MT_DATA_MSG*				GetMtData() { return m_Data.m_pMtData; }
	MT_VALIDATION_MSG*			GetMtValidation() { return m_Data.m_pMtValidation; }
	CONTROL_BOX_CONTROL_MSG*	GetControlBoxControl() { return m_Data.m_pControlBoxControl; }
	CONTROL_BOX_STATUS_MSG*		GetControlBoxStatus() { return m_Data.m_pControlBoxStatus; }
	THRESHOLD_STATISTICS_MSG*	GetThresholdStatistics() { return m_Data.m_pThresholdStatistics; }
	CONFIG_GATE_SIZE_MSG*		GetConfigGateSize() { return m_Data.m_pConfigGateSize; }
	CONFIG_GATE_POS_MSG*		GetConfigGatePos() { return m_Data.m_pConfigGatePos; }
	CONFIG_ANNOTATION_MSG*		GetConfigAnnotation() { return m_Data.m_pConfigAnnotation; }
	CONFIG_SYMBOLOGY_MSG*		GetConfigSymbology() { return m_Data.m_pConfigSymbology; }
	CONFIG_CORR_REF_POS_MSG*	GetConfigCorrRefPos() { return m_Data.m_pConfigCorrRefPos; }
	CONFIG_VIDEO_MSG*			GetConfigVideo() { return m_Data.m_pConfigVideo; }
	CONFIG_PRESET_CONFIG_MSG*	GetConfigPresetConfig() { return m_Data.m_pConfigPresetConfig; }
	CONFIG_AUTOSIZE_MSG*		GetConfigAutoSize() { return m_Data.m_pConfigAutoSize; }
	CONFIG_VALIDATION_MSG*		GetConfigValidation() { return m_Data.m_pConfigValidation; }
	CONFIG_JOYSTICK_MSG*		GetConfigJoystick() { return m_Data.m_pConfigJoystick; }
	CONFIG_LENS_FOV_MSG*		GetConfigLensFov() { return m_Data.m_pConfigLensFov; }
	CONFIG_MOUNT_MSG*			GetConfigMount() { return m_Data.m_pConfigMount; }
	CONFIG_ANALOG_JOYSTICK_MSG*	GetConfigAnalogJoystick() { return m_Data.m_pConfigAnalogJoystick; }
	CONFIG_DIGITAL_IO_MSG*		GetConfigDigitalIO() { return m_Data.m_pConfigDigitalIO; }
	CONFIG_ZOOM_TO_RANGE_MSG*	GetConfigZoomToRange() { return m_Data.m_pConfigZoomToRange; }
	CONFIG_GATE_STYLE_MSG*		GetConfigGateStyle() { return m_Data.m_pConfigGateStyle; }
	CONFIG_GATE_RETICLE_MSG*	GetConfigGateReticle() { return m_Data.m_pConfigGateReticle; }
	CONFIG_LOS_RETICLE_MSG*		GetConfigLosReticle() { return m_Data.m_pConfigLosReticle; }
	CONFIG_TRACK_FLAG_MSG*		GetConfigTrackFlag() { return m_Data.m_pConfigTrackFlag; }
	CONFIG_NORTH_OFFSET_MSG*	GetConfigNorthOffset() { return m_Data.m_pConfigNorthOffset; }
	CONFIG_DIGITAL_VIDEO_MSG*	GetConfigDigitalVideo() { return m_Data.m_pConfigDigitalVideo; }
	CONFIG_ANNOTATION2_MSG*		GetConfigAnnotation2() { return m_Data.m_pConfigAnnotation2; }
	CONFIG_SERIAL_PORTS_MSG*	GetConfigSerialPorts() { return m_Data.m_pConfigSerialPorts; }
	CONFIG_CONTROL_BOX_MSG*		GetConfigControlBox() { return m_Data.m_pConfigControlBox; }
	CONFIG_TARGET_SIMULATOR_MSG* GetConfigTargetSimulator() { return m_Data.m_pConfigTargetSimulator; }
	CONFIG_CRP_MSG*				GetConfigCrp() { return m_Data.m_pConfigCrp; }
	CONFIG_AUTOTHRESHOLD_MSG*	GetConfigAutoThreshold() { return m_Data.m_pConfigAutoThreshold; }
	CONFIG_ETHERNET_MSG*		GetConfigEthernet() { return m_Data.m_pConfigEthernet; }
	CONFIG_DIGITAL_VIDEO_EXT_MSG* GetConfigDigitalVideoExt() { return m_Data.m_pConfigDigitalVideoExt; }
	CONFIG_DIGITAL_PREPROCESS_MSG* GetConfigDigitalPreprocess() { return m_Data.m_pConfigDigitalPreprocess; }
	CONFIG_IFF_TRACK_MSG*		GetConfigIffTrack() { return m_Data.m_pConfigIffTrack; }
	CONFIG_INTRUSION_DETECT_MSG* GetConfigIntrusionDetect() { return m_Data.m_pConfigIntrusionDetect; }
	CONFIG_POS_TRACK_MSG*		GetConfigPosTrack() { return m_Data.m_pConfigPosTrack; }
	CONFIG_CONTROL_BOX_IO_MSG*	GetConfigControlBoxIO() { return m_Data.m_pConfigControlBoxIO; }
	CONFIG_VIDEO_SWITCH_MSG*	GetConfigVideoSwitch() { return m_Data.m_pConfigVideoSwitch; }
	CONFIG_GATE_RETICLE2_MSG*	GetConfigGateReticle2() { return m_Data.m_pConfigGateReticle2; }
	CONFIG_GPS_MSG*				GetConfigGps() { return m_Data.m_pConfigGps; }
	MESSAGE_ACK_MSG*			GetMessageAck() { return m_Data.m_pMessageAck; }
	STATUS_MSG*					GetStatus() { return m_Data.m_pStatus; }

	const PING_MSG*					GetPing() const { return m_Data.m_pPing; }
	const RUN_TIME_CTRL_MSG*		GetControl() const { return m_Data.m_pControl; }
	const SYSTEM_CTRL_MSG*			GetSystem() const { return m_Data.m_pSystem; }
	const LOS_OFFSET_CTRL_MSG*		GetLOSOffset() const { return m_Data.m_pLOSOffset; }
	const OFFSET_AIM_CTRL_MSG*		GetOffsetAim() const { return m_Data.m_pOffsetAim; }
	const SYMBOLOGY_CTRL_MSG*		GetSymbology() const { return m_Data.m_pSymbology; }
	const CORRELATION_CTRL_MSG*		GetCorrelation() const { return m_Data.m_pCorrelation; }
	const FILTER_CTRL_MSG*			GetFilter() const { return m_Data.m_pFilter; }
	const COAST_CTRL_MSG*			GetCoast() const { return m_Data.m_pCoast; }
	const TGT_VALIDATION_CTRL_MSG*	GetTargetValidation() const { return m_Data.m_pTargetValidation; }
	const AAQ_ACQUIRE_CTRL_MSG*		GetAutoAcquire() const { return m_Data.m_pAutoAcquire; }
	const AAQ_TRACK_CTRL_MSG*		GetAutoAcquireTrack() const { return m_Data.m_pAutoAcquireTrack; }
	const AAQ_TGT_SELECT_CTRL_MSG*	GetTargetSelect() const { return m_Data.m_pTargetSelect; }
	const ANNOTATION_MSG*			GetAnnotation() const { return m_Data.m_pAnnotation; }
	const USER_STRING_MSG*			GetUserString() const { return m_Data.m_pUserString; }
	const SCAN_MSG*					GetScan() const { return m_Data.m_pScan; }
	const MOUNT_RATE_DRIVE_MSG*		GetMountRateDrive() const { return m_Data.m_pMountRateDrive; }
	const MOUNT_CONTROL_MSG*		GetMountControl() const { return m_Data.m_pMountControl; }
	const CONTROL_BOX_MSG*			GetControlBox() const { return m_Data.m_pControlBox; }
	const QUERY_CONFIG_MSG*			GetQueryConfig() const { return m_Data.m_pQueryConfig; }
	const PRESET_CONFIG_MSG*		GetPresetConfig() const { return m_Data.m_pPresetConfig; }
	const LENS_CONFIG_MSG*			GetLensConfig() const { return m_Data.m_pLensConfig; }
	const LENS_GRAFLEX_MSG*			GetLensGraflex() const { return m_Data.m_pLensGraflex; }
	const LENS_SERIAL_TFOV_MSG*		GetLensSerialTfov() const { return m_Data.m_pLensSerialTfov; }
	const LENS_SERIAL_DFOV_MSG*		GetLensSerialDfov() const { return m_Data.m_pLensSerialDfov; }
	const LENS_GENERIC_MSG*			GetLensGeneric() const { return m_Data.m_pLensGeneric; }
	const LENS_SERIAL_ZOOM_MSG*		GetLensSerialZoom() const { return m_Data.m_pLensSerialZoom; }
	const LENS_SERIAL_IR_ZOOM_MSG*	GetLensSerialIrZoom() const { return m_Data.m_pLensSerialIrZoom; }
	const LENS_ANALOG_ZOOM_MSG*		GetLensAnalogZoom() const { return m_Data.m_pLensAnalogZoom; }
	const CAMERA_CONFIG_MSG*		GetCameraConfig() const { return m_Data.m_pCameraConfig; }
	const CAMERA_GENERIC_MSG*		GetCameraGeneric() const { return m_Data.m_pCameraGeneric; }
	const LENS_SERIAL_FIXED_FOV_MSG* GetLensSerialFixedFov() const { return m_Data.m_pLensSerialFixedFov; }
	const LENS_SERIAL_IR_DFOV_MSG*	GetLensSerialIrDfov() const { return m_Data.m_pLensSerialIrDfov; }
	const LENS_MOOG_ZOOM_MSG*		GetLensMoogZoom() const { return m_Data.m_pLensMoogZoom; }
	const ANALOG_INPUT_MSG*			GetAnalogInput() const { return m_Data.m_pAnalogInput; }
	const CAPABILITIES_MSG*			GetCapabilities() const { return m_Data.m_pCapabilities; }
	const BUILT_IN_TEST_MSG*		GetBuiltInTest() const { return m_Data.m_pBuiltInTest; }
	const MOUNT_STATUS_MSG*			GetMountStatus() const { return m_Data.m_pMountStatus; }
	const LRF_CONTROL_MSG*			GetLrfControl() const { return m_Data.m_pLrfControl; }
	const TARGET_RANGE_MSG*			GetTargetRange() const { return m_Data.m_pTargetRange; }
	const TARGET_GENERATOR_MSG*		GetTargetGenerator() const { return m_Data.m_pTargetGenerator; }
	const GATE_CONTROL_MSG*			GetGateControl() const { return m_Data.m_pGateControl; }
	const MOUNT_FEEDBACK_MSG*		GetMountFeedback() const { return m_Data.m_pMountFeedback; }
	const DIGITAL_IO_MSG*			GetDigitalIO() const { return m_Data.m_pDigitalIO; }
	const DL_CODE_RECEIVE_MSG*		GetDownloadCode() const { return m_Data.m_pDownloadCode; }
	const DL_CODE_STATUS_MSG*		GetDownloadCodeStatus() const { return m_Data.m_pDownloadCodeStatus; }
	const DL_LICENSE_MSG*			GetDownloadLicense() const { return m_Data.m_pDownloadLicense; }
	const DL_CODE_STATUS2_MSG*		GetDownloadCodeStatus2() const { return m_Data.m_pDownloadCodeStatus2; }
	const GATE_STATISTICS_MSG*		GetGateStatistics() const { return m_Data.m_pGateStatistics; }
	const DIGITAL_VIDEO_STATUS_MSG*	GetDigitalVideoStatus() const { return m_Data.m_pDigitalVideoStatus; }
	const USER_STRING2_MSG*			GetUserString2() const { return m_Data.m_pUserString2; }
	const TARGET_SIMULATOR_MSG*		GetTargetSimulator() const { return m_Data.m_pTargetSimulator; }
	const CRP_CONTROL_MSG*			GetCrpControl() const { return m_Data.m_pCrpControl; }
	const STEERED_MIRROR_FILTER_MSG* GetSteeredMirrorFilter() const { return m_Data.m_pSteeredMirrorFilter; }
	const IFF_TRACK_STATUS_MSG*		GetIffTrackStatus() const { return m_Data.m_pIffTrackStatus; }
	const STEERED_MIRROR_CALIBRATION_MSG* GetSteeredMirrorCalibration() const { return m_Data.m_pSteeredMirrorCalibration; }
	const OVERLAY_CONTROL_MSG*		GetOverlayControl() const { return m_Data.m_pOverlayControl; }
	const OVERLAY_STATUS_MSG*		GetOverlayStatus() const { return m_Data.m_pOverlayStatus; }
	const OVERLAY_STATUS_EXT_MSG*	GetOverlayStatusExt() const { return m_Data.m_pOverlayStatusExt; }
	const LOS_OFFSET_CTRL2_MSG*		GetLOSOffset2() const { return m_Data.m_pLOSOffset2; }
	const OFFSET_AIM_CTRL2_MSG*		GetOffsetAim2() const { return m_Data.m_pOffsetAim2; }
	const POS_TRACK_STATUS_MSG*		GetPosTrackStatus() const { return m_Data.m_pPosTrackStatus; }
	const CAMERA_CONTROL_MSG*		GetCameraControl() const { return m_Data.m_pCameraControl; }
	const GPS_DATA_MSG*				GetGpsData() const { return m_Data.m_pGpsData; }
	const SYSTEM_STATUS_MSG*		GetSystemStatus() const { return m_Data.m_pSystemStatus; }
	const FPGA_VIDEO_STATUS_MSG*	GetFpgaVideoStatus() const { return m_Data.m_pFpgaVideoStatus; }
	const ETHERNET_STATUS_MSG*		GetEthernetStatus() const { return m_Data.m_pEthernetStatus; }
	const MT_GENERAL_MSG*			GetMtGeneral() const { return m_Data.m_pMtGeneral; }
	const MT_ACQUIRE_MSG*			GetMtAcquire() const { return m_Data.m_pMtAcquire; }
	const MT_TRACK_MSG*				GetMtTrack() const { return m_Data.m_pMtTrack; }
	const MT_DATA_MSG*				GetMtData() const { return m_Data.m_pMtData; }
	const MT_VALIDATION_MSG*		GetMtValidation() const { return m_Data.m_pMtValidation; }
	const CONTROL_BOX_CONTROL_MSG*	GetControlBoxControl()const { return m_Data.m_pControlBoxControl; }
	const CONTROL_BOX_STATUS_MSG*	GetControlBoxStatus()const { return m_Data.m_pControlBoxStatus; }
	const THRESHOLD_STATISTICS_MSG*	GetThresholdStatistics()const { return m_Data.m_pThresholdStatistics; }
	const CONFIG_GATE_SIZE_MSG*		GetConfigGateSize() const { return m_Data.m_pConfigGateSize; }
	const CONFIG_GATE_POS_MSG*		GetConfigGatePos() const { return m_Data.m_pConfigGatePos; }
	const CONFIG_ANNOTATION_MSG*	GetConfigAnnotation() const { return m_Data.m_pConfigAnnotation; }
	const CONFIG_SYMBOLOGY_MSG*		GetConfigSymbology() const { return m_Data.m_pConfigSymbology; }
	const CONFIG_CORR_REF_POS_MSG*	GetConfigCorrRefPos() const { return m_Data.m_pConfigCorrRefPos; }
	const CONFIG_VIDEO_MSG*			GetConfigVideo() const { return m_Data.m_pConfigVideo; }
	const CONFIG_PRESET_CONFIG_MSG*	GetConfigPresetConfig() const { return m_Data.m_pConfigPresetConfig; }
	const CONFIG_AUTOSIZE_MSG*		GetConfigAutoSize() const { return m_Data.m_pConfigAutoSize; }
	const CONFIG_VALIDATION_MSG*	GetConfigValidation() const { return m_Data.m_pConfigValidation; }
	const CONFIG_JOYSTICK_MSG*		GetConfigJoystick() const { return m_Data.m_pConfigJoystick; }
	const CONFIG_LENS_FOV_MSG*		GetConfigLensFov() const { return m_Data.m_pConfigLensFov; }
	const CONFIG_MOUNT_MSG*			GetConfigMount() const { return m_Data.m_pConfigMount; }
	const CONFIG_ANALOG_JOYSTICK_MSG*	GetConfigAnalogJoystick() const { return m_Data.m_pConfigAnalogJoystick; }
	const CONFIG_DIGITAL_IO_MSG*	GetConfigDigitalIO() const { return m_Data.m_pConfigDigitalIO; }
	const CONFIG_ZOOM_TO_RANGE_MSG*	GetConfigZoomToRange() const { return m_Data.m_pConfigZoomToRange; }
	const CONFIG_GATE_STYLE_MSG*	GetConfigGateStyle() const { return m_Data.m_pConfigGateStyle; }
	const CONFIG_GATE_RETICLE_MSG*	GetConfigGateReticle() const { return m_Data.m_pConfigGateReticle; }
	const CONFIG_LOS_RETICLE_MSG*	GetConfigLosReticle() const { return m_Data.m_pConfigLosReticle; }
	const CONFIG_TRACK_FLAG_MSG*	GetConfigTrackFlag() const { return m_Data.m_pConfigTrackFlag; }
	const CONFIG_NORTH_OFFSET_MSG*	GetConfigNorthOffset() const { return m_Data.m_pConfigNorthOffset; }
	const CONFIG_DIGITAL_VIDEO_MSG*	GetConfigDigitalVideo() const { return m_Data.m_pConfigDigitalVideo; }
	const CONFIG_ANNOTATION2_MSG*	GetConfigAnnotation2() const { return m_Data.m_pConfigAnnotation2; }
	const CONFIG_SERIAL_PORTS_MSG*	GetConfigSerialPorts() const { return m_Data.m_pConfigSerialPorts; }
	const CONFIG_CONTROL_BOX_MSG*	GetConfigControlBox() const { return m_Data.m_pConfigControlBox; }
	const CONFIG_TARGET_SIMULATOR_MSG* GetConfigTargetSimulator() const { return m_Data.m_pConfigTargetSimulator; }
	const CONFIG_CRP_MSG*			GetConfigCrp() const { return m_Data.m_pConfigCrp; }
	const CONFIG_AUTOTHRESHOLD_MSG*	GetConfigAutoThreshold() const { return m_Data.m_pConfigAutoThreshold; }
	const CONFIG_ETHERNET_MSG*		GetConfigEthernet() const { return m_Data.m_pConfigEthernet; }
	const CONFIG_DIGITAL_VIDEO_EXT_MSG*	GetConfigDigitalVideoExt() const { return m_Data.m_pConfigDigitalVideoExt; }
	const CONFIG_DIGITAL_PREPROCESS_MSG* GetConfigDigitalPreprocess() const { return m_Data.m_pConfigDigitalPreprocess; }
	const CONFIG_IFF_TRACK_MSG*		GetConfigIffTrack() const { return m_Data.m_pConfigIffTrack; }
	const CONFIG_INTRUSION_DETECT_MSG* GetConfigIntrusionDetect() const { return m_Data.m_pConfigIntrusionDetect; }
	const CONFIG_POS_TRACK_MSG*		GetConfigPosTrack() const { return m_Data.m_pConfigPosTrack; }
	const CONFIG_CONTROL_BOX_IO_MSG*	GetConfigControlBoxIO() const { return m_Data.m_pConfigControlBoxIO; }
	const CONFIG_VIDEO_SWITCH_MSG*	GetConfigVideoSwitch() const { return m_Data.m_pConfigVideoSwitch; }
	const CONFIG_GATE_RETICLE2_MSG*	GetConfigGateReticle2() const { return m_Data.m_pConfigGateReticle2; }
	const CONFIG_GPS_MSG*			GetConfigGps() const { return m_Data.m_pConfigGps; }
	const MESSAGE_ACK_MSG*			GetMessageAck() const { return m_Data.m_pMessageAck; }
	const STATUS_MSG*				GetStatus() const { return m_Data.m_pStatus; }

	BOOL			SetDefaultControl();
	BOOL			SetDefaultSystem();
	BOOL			SetDefaultLOSOffset();
	BOOL			SetDefaultOffsetAim();
	BOOL			SetDefaultSymbology();
	BOOL			SetDefaultCorrelation();
	BOOL			SetDefaultFilter();
	BOOL			SetDefaultCoast();
	BOOL			SetDefaultTargetValidation();
	BOOL			SetDefaultAutoAcquire();
	BOOL			SetDefaultAutoAcquireTrack();
	BOOL			SetDefaultTargetSelect();
	BOOL			SetDefaultAnnotation();
	BOOL			SetDefaultUserString();
	BOOL			SetDefaultScan();
	BOOL			SetDefaultMountRateDrive();
	BOOL			SetDefaultMountControl();
	BOOL			SetDefaultControlBox();
	BOOL			SetDefaultQueryConfig();
	BOOL			SetDefaultPresetConfig();
	BOOL			SetDefaultLensConfig();
	BOOL			SetDefaultLensGraflex();
	BOOL			SetDefaultLensSerialTfov();
	BOOL			SetDefaultLensSerialDfov();
	BOOL			SetDefaultLensGeneric();
	BOOL			SetDefaultLensSerialZoom();
	BOOL			SetDefaultLensSerialIrZoom();
	BOOL			SetDefaultLensAnalogZoom();
	BOOL			SetDefaultCameraConfig();
	BOOL			SetDefaultCameraGeneric();
	BOOL			SetDefaultLensSerialFixedFov();
	BOOL			SetDefaultLensSerialIrDfov();
	BOOL			SetDefaultLensMoogZoom();
	BOOL			SetDefaultCapabilities();
	BOOL			SetDefaultBuiltInTest();
	BOOL			SetDefaultMountStatus();
	BOOL			SetDefaultLrfControl();
	BOOL			SetDefaultTargetRange();
	BOOL			SetDefaultTargetGenerator();
	BOOL			SetDefaultGateControl();
	BOOL			SetDefaultMountFeedback();
	BOOL			SetDefaultDigitalIO();
	BOOL			SetDefaultDownloadCode();
	BOOL			SetDefaultDownloadLicense();
	BOOL			SetDefaultUserString2();
	BOOL			SetDefaultTargetSimulator();
	BOOL			SetDefaultCrpControl();
	BOOL			SetDefaultSteeredMirrorFilter();
	BOOL			SetDefaultIffTrackStatus();
	BOOL			SetDefaultSteeredMirrorCalibration();
	BOOL			SetDefaultOverlayControl();
	BOOL			SetDefaultOverlayStatus();
	BOOL			SetDefaultOverlayStatusExt();
	BOOL			SetDefaultLOSOffset2();
	BOOL			SetDefaultOffsetAim2();
	BOOL			SetDefaultPosTrackStatus();
	BOOL			SetDefaultCameraControl();
	BOOL			SetDefaultGpsData();
	BOOL			SetDefaultSystemStatus();
	BOOL			SetDefaultFpgaVideoStatus();
	BOOL			SetDefaultEthernetStatus();
	BOOL			SetDefaultMtGeneral();
	BOOL			SetDefaultMtAcquire();
	BOOL			SetDefaultMtTrack();
	BOOL			SetDefaultMtData();
	BOOL			SetDefaultMtValidation();
	BOOL			SetDefaultControlBoxControl();
	BOOL			SetDefaultControlBoxStatus();
	BOOL			SetDefaultConfigGateSize();
	BOOL			SetDefaultConfigGatePos();
	BOOL			SetDefaultConfigAnnotation();
	BOOL			SetDefaultConfigSymbology();
	BOOL			SetDefaultConfigCorrRefPos();
	BOOL			SetDefaultConfigVideo();
	BOOL			SetDefaultConfigPresetConfig();
	BOOL			SetDefaultConfigAutoSize();
	BOOL			SetDefaultConfigValidation();
	BOOL			SetDefaultConfigJoystick();
	BOOL			SetDefaultConfigLensFov();
	BOOL			SetDefaultConfigMount();
	BOOL			SetDefaultConfigAnalogJoystick();
	BOOL			SetDefaultConfigDigitalIO();
	BOOL			SetDefaultConfigZoomToRange();
	BOOL			SetDefaultConfigGateStyle();
	BOOL			SetDefaultConfigGateReticle();
	BOOL			SetDefaultConfigLosReticle();
	BOOL			SetDefaultConfigTrackFlag();
	BOOL			SetDefaultConfigNorthOffset();
	BOOL			SetDefaultConfigDigitalVideo();
	BOOL			SetDefaultConfigAnnotation2();
	BOOL			SetDefaultConfigSerialPorts();
	BOOL			SetDefaultConfigControlBox();
	BOOL			SetDefaultConfigTargetSimulator();
	BOOL			SetDefaultConfigCrp();
	BOOL			SetDefaultConfigAutoThreshold();
	BOOL			SetDefaultConfigEthernet();
	BOOL			SetDefaultConfigDigitalVideoExt();
	BOOL			SetDefaultConfigDigitalPreprocess();
	BOOL			SetDefaultConfigIntrusionDetect();
	BOOL			SetDefaultConfigPosTrack();
	BOOL			SetDefaultConfigIffTrack();
	BOOL			SetDefaultConfigControlBoxIO();
	BOOL			SetDefaultConfigVideoSwitch();
	BOOL			SetDefaultConfigGateReticle2();
	BOOL			SetDefaultConfigGps();

	int				GetType() const { return m_Type; }
	BOOL			SetType(int type, USHORT syncword = CTrackerMessage::CurrentSyncWord);
	BOOL			SetTypeOrClear(int type, USHORT syncword = CTrackerMessage::CurrentSyncWord);

	int				GetGateNumber() const;

	BOOL			ByteSwap();

	BOOL			VerifyChecksum() const;
	BOOL			SetChecksum();

	const CTimeStamp&	GetTimeStamp() const { return m_TimeStamp; }
	void				SetTimeStamp() { m_TimeStamp.SetTimeStamp(); }

	CTrackerMessage& SwapContents(CTrackerMessage& src);
};

BOOL operator ==(const CTrackerMessage& msg1, const CTrackerMessage& msg2);
BOOL operator !=(const CTrackerMessage& msg1, const CTrackerMessage& msg2);

typedef CGenPtrArray<CTrackerMessage>						CTrackerMessagePtrArray;
typedef CGenArray<CTrackerMessage, CTrackerMessagePtrArray>	CTrackerMessageArray;

#endif // !defined(AFX_TRACKERMESSAGE_H__92DFD911_7112_11D3_8132_009027728EF1__INCLUDED_)
