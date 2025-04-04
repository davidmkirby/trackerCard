///////////////////////////////////////////////////////////////////////////////
// MSG_CAM_FMT.H
//
// Message structure definitions to support various cameras/lenses and
// their additional functions and features.
//

/*******************************************************************************
 * Copyright (c) 2003-2020 Moog, Inc. All Rights Reserved
 *
 * Moog, Inc. licenses this software under specific terms and conditions.
 * Use of any of the software or derivatives thereof in any product without
 * a Moog, Inc. video tracker is strictly prohibited.
 *
 * Moog, Inc. provides this software AS IS, WITHOUT ANY WARRANTY, EXPRESS OR
 * IMPLIED, INCLUDING, WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  Moog makes no guarantee or representations
 * regarding the use of, or the results of the use of, the software and
 * documentation in terms of correctness, accuracy, reliability, currentness,
 * or otherwise; and you rely on the software, documentation and results
 * solely at your own risk.
 *
 * IN NO EVENT SHALL MOOG BE LIABLE FOR ANY LOSS OF USE, LOSS OF BUSINESS,
 * LOSS OF PROFITS, INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES
 * OF ANY KIND.  IN NO EVENT SHALL MOOG'S TOTAL LIABILITY EXCEED THE SUM
 * PAID TO MOOG FOR THE PRODUCT LICENSED HEREUNDER.
 *
 ******************************************************************************/

#ifndef __MSG_CAM_FMT_H__
#define __MSG_CAM_FMT_H__

#pragma pack(push, 2)	// pack all messages with two byte alignment

// data types
#ifndef USHORT
	typedef unsigned short	USHORT;
#endif

#ifndef UCHAR
	typedef unsigned char	UCHAR;
#endif

// maximum camera/lens data structure size in bytes
#define CAM_DATA_SIZE				36


//////////////////////////////////////////////////////////////////////////////
// Camera Types
//
#define CAMTYPE_NONE						0	// no camera control available (QUERY RESPONSE ONLY)
#define CAMTYPE_IRC_QUAZIR_LR				1	// IRCameras QuazIR-LR camera
#define CAMTYPE_G5_INFRARED_REVD			2	// G5 Infrared 550CZ camera (revision D of protocol)
#define CAMTYPE_L3_WALRSS_HD				3	// L-3 WALRSS HD camera
#define CAMTYPE_G5_INFRARED_REVG			4	// G5 Infrared camera (revision G of protocol)
#define CAMTYPE_INVEO_AGILE_CORE			5	// InVeo Agile Core based cameras


//////////////////////////////////////////////////////////////////////////////
// CAMERA_IRC_QUAZIR_LR
//
// IRCameras QuazIR-LR camera extended settings and controls.
//
// Valid lens types which could support this camera type:
//		LENS_PVP_NIGHTHAWK_IR_ZOOM
//		LENS_IRC_QUAZIR_LRSD_RPO_ODEM825
//		LENS_IRC_QUAZIR_LRSD_RPO_DIAMOND
//
// NOTES FOR LENS_PVP_NIGHTHAWK_IR_ZOOM SUPPORT LIMITATIONS:
//   - PVP uses an operational_mode which is 1 based, but the tracker uses the
//     native zero based reference.
//   - The following features/controls are available through the PVP
//	   controller: digital_zoom, infinity_track, freeze_image, test_pattern,
//                 noise_filter, cal_refresh_internal, cal_refresh_external,
//				   aglc_roi, temp_sensor_0 and temp_sensor_1.
//
typedef struct
{
	// Word 1
	USHORT operational_mode		:4;		  // operational mode (0 to 5), sets integration time and calibration table
	USHORT digital_zoom			:4;		  // digital zoom (0=none/1x, 1=2x, 2=reserved, 3=4x)
	USHORT color_palette		:4;		  // color palette (0=IR monochrome, 1-7=IR false color, 8-9 for visible)
	USHORT spare1				:4;

	// Word 2
	USHORT restore_on_boot		:1;		  // restore the camera settings from tracker flash memory (1=restore on boot)
	USHORT infinity_focus		:1;		  // one-shot focus at infinity for current FOV (1=focus infinity)
	USHORT infinity_track		:1;		  // focus at infinity during/after zooming FOV (0=off, 1=on)
	USHORT continuous_autofocus	:1;		  // enable continuous auto focus (0=off, 1=on)
	USHORT display_overlay		:1;		  // display overlay graphics (0=off, 1=on)
	USHORT freeze_image			:1;		  // freeze the camera image / snapshot (0=off, 1=on)
	USHORT test_pattern			:1;		  // display the color test pattern (0=off, 1=on)
	USHORT noise_filter			:1;		  // noise reduction filter (0=off, 1=on)
	USHORT cal_refresh_internal	:1;		  // run one point NUC refresh using internal reference (1=run NUC)
	USHORT cal_refresh_external	:1;		  // run one point NUC refresh using external reference (1=run NUC)
	USHORT spare2				:6;

	// Word 3
	USHORT aglc_mode			:4;		  // automatic gain and level processing / AGLC (0=off, 1=manual, 2=linear, 3=histogram, 4=gamma remap)
	USHORT aglc_roi				:4;		  // AGLC region of interest (0 to 3)
	USHORT aglc_restore			:1;		  // restore AGLC default values (1=load defaults)
	USHORT spare3				:7;

	// Word 4 & 5
	short  aglc_brightness		:16;	  // AGLC brightness control (-32768 to 32767)
	USHORT aglc_contrast		:16;	  // AGLC contrast control (0 to 65535)

	// Word 6
	USHORT lap_dnce				:1;		  // LAP-DnCE local area processing (0=off, 1=on)
	USHORT lap_dnce_restore		:1;		  // restore LAP-DnCE settings (1=load defaults)
	USHORT spare6				:14;

	// Word 7 & 8
	USHORT lap_background_level	:16;	  // LAP-DnCE background enhancement level (0 to 65535)
	USHORT lap_foreground_boost	:16;	  // LAP-DnCE foreground enhancement boost (0 to 65535)

	// Word 9, 10 &	11
	USHORT temp_sensor_0		:16;	  // temperature sensor #0 (ADC value)
	USHORT temp_sensor_1		:16;	  // temperature sensor #1 (ADC value)
	USHORT fpa_temperature		:16;	  // FPA temperature (ADC value)
										  //   degrees C = (150 / 19200) * (value - 32768)
} CAMERA_IRC_QUAZIR_LR;

//////////////////////////////////////////////////////////////////////////////
// CAMTYPE_G5_INFRARED_REVD (revision D of protocol)
//
// G5 Infrared 550CZ camera extended settings and controls.
//
// Valid lens types which could support this camera type:
//		LENS_G5_INFRARED_550CZ
//
typedef struct
{
	// Word 1
	char   sensitivity			:8;		  // sets dynamic range / sensitivity (-1=wide DR/low sens, 0=normal, 1=low DR/high sens)
	char   filter				:8;		  // image noise reduction / edge enhancement filter (0=off, -5 to +5)

	// Word 2
	USHORT restore_on_boot		:1;		  // restore the camera settings from tracker flash memory (1=restore on boot)
	USHORT aglc					:1;		  // automatic gain and level control enable (0=off, 1=on)
	USHORT auto_calibration		:1;		  // automatic calibration (NUC) enable (0=off, 1=on)
	USHORT spare2				:13;

	// Word 3 & 4
	USHORT manual_gain			:16;	  // manual gain control (0 to 1000)
	USHORT manual_level			:16;	  // manual level control (0 to 1000)

	// Word 5
	USHORT auto_cal_time		:16;	  // automatic calibration (NUC) time (0 to 32767 seconds)

	// Word 6 & 7
	USHORT software_ver_major	:8;		  // software version (in the form major.mid.minor)
	USHORT software_ver_mid		:8;
	USHORT software_ver_minor	:8;
	USHORT spare6				:8;

	// Word 8 & 9
	USHORT runtime				:16;	  // total camera runtime in hours
	USHORT runtime_fraction		:8;		  // fractional part of runtime in 1/100 of an hour
	USHORT spare9				:8;

} CAMERA_G5_INFRARED_REVD;

//////////////////////////////////////////////////////////////////////////////
// CAMERA_L3_WALRSS_HD
//
// L-3 WMIR WALRSS HD camera extended settings and controls.
//
// Valid lens types which could support this camera type:
//		LENS_L3_WALRSS_HD
//
typedef struct
{
	// Word 1
	USHORT range						:4;		  // sets dynamic range / sensitivity (1 to 3)
	USHORT auto_range					:1;		  // automatically determine the range (0=no action, 1=determine range)
	USHORT spare1						:3;
	USHORT adaptive_noise_reduction		:4;		  // adaptive image noise reduction (0=off, 1=8DU, 2=16DU, 3=32DU)
	USHORT agc_mode						:4;		  // automatic gain control mode (0=off, 1=AGLC, 2=ALC)

	// Word 2
	USHORT restore_on_boot				:1;		  // restore the camera settings from tracker flash memory (1=restore on boot)
	USHORT nuc_full						:1;		  // run full NUC (0=no action, 1=run full correction)
	USHORT nuc_offset					:1;		  // run offset NUC (0=no action, 1=run offset correction)
	USHORT nuc_save						:1;		  // save results of NUC to flash (0=no action, 1=save results when complete)
	USHORT tmsr_overlay					:1;		  // turbulence mitigation overlay (0=off, 1=on)
	USHORT reset						:1;		  // reset all boards in the camera (0=no action, 1=reset)
	USHORT video_restore				:1;		  // restore video parameters to factory defaults (0=no action, 1=restore factory settings)
	USHORT display_phm					:1;		  // PHM display (0=off, 1=on)
	USHORT overlay_hud					:1;		  // overlay HUD (0=off, 1=on)
	USHORT local_area_contrast			:1;		  // local area contrast (0=off, 1=on)
	USHORT overlay_tactical_reticle		:1;		  // overlay tactical reticle (0=off, 1=on)
	USHORT edge_enhancement_adaptive	:1;		  // adaptive edge enhancement (0=off, 1=on)
	USHORT video_freeze					:1;		  // freeze/snapshot video image (0=off, 1=on)
	USHORT stabilization				:1;		  // electronic video stabilization (0=off, 1=on)
	USHORT video_image_border			:1;		  // video image boarder (0=off, 1=on)
	USHORT spare2						:1;

	// Word 3
	USHORT video_orientation			:2;		  // video orientation (0=normal, 1=left2Right, 2=top2bottom, 3=both)
	USHORT video_orientation_save		:1;		  // save video orientation to flash (0=no action, 1=save)
	USHORT video_only_test_pattern		:2;		  // show video test pattern (0=off, 1=vertical, 2=horizontal)
	USHORT correction_test_pattern		:1;		  // show correction test pattern (0=no action, 1=show test pattern)
	USHORT spare3						:10;

	// Word 4 & 5
	USHORT video_contrast				:16;	  // contrast control for agc_mode=0 or 2 (16 to 1024)
	short  video_brightness				:16;	  // brightness control for agc_mode=0 (-16384 to 16383)

	// Word 6 & 7
	short  video_agc_control			:16;	  // AGC value for agc_mode=1 (1 to 15)
	short  video_alc_control			:16;	  // ALC value for agc_mode=2 (-512 to 511)

	// Word 8
	USHORT tmsr_control					:4;		  // turbulence mitigation (0=off, 1=on 1X, 2=on 2X)
	USHORT stabilization_horiz			:4;		  // video stabilization X (0=off, 1=light, 2=normal, 3=strong, 4=stronger, 5=strongest)
	USHORT stabilization_vert			:4;		  // video stabilization Y (0=off, 1=light, 2=normal, 3=strong, 4=stronger, 5=strongest)
	USHORT spare8						:4;

	// Word 9
	USHORT tmsr_blur_level				:8;		  // turbulence mitigation blur level (0 to 31)
	USHORT tmsr_warp_level				:8;		  // turbulence mitigation warp level (0 to 64)

	// Word 10
	USHORT local_area_contrast_spread	:8;		  // local area contrast spread (0 to 16, 0=max contrast & 16=min contrast)
	USHORT edge_enhancement				:8;		  // edge enhancement control (0=off, 1 to 145)

	// Word 11
	USHORT hud_number					:8;		  // overlay HUD number (1 to 12)
	USHORT tactical_reticle_number		:8;		  // overlay tactical reticle number (1 to 6)

	// Word 12
	USHORT fpa_temperature				:16;	  // FPA temperature (in 1/100 Kelvin)

	// Word 13, 14 & 15
	USHORT cooler_cooldown_count		:16;	  // number of cooler cooldown cycles
	USHORT cooler_runtime_minutes_lsw	:16;	  // total cooler runtime in minutes (low word,  24-bits)
	USHORT cooler_runtime_minutes_msb	:8;		  // total cooler runtime in minutes (high byte, 24-bits)
	USHORT fpa_temperature_cold			:1;		  // FPA at operational temperature (0=cooling, 1=cold)
	USHORT spare15						:7;

} CAMERA_L3_WALRSS_HD;


// defines for G5 Infrared camera aglc_roi variable (region of interest used for AGLC algorithm)
#define G5_INFRARED_ROI_CENTER_QUARTER			0
#define G5_INFRARED_ROI_CENTER_HALF				1
#define G5_INFRARED_ROI_CENTER_THREE_QUARTERS	2
#define G5_INFRARED_ROI_WHOLE					3
#define G5_INFRARED_ROI_TOP_THIRD				4
#define G5_INFRARED_ROI_MIDDLE_THIRD			5
#define G5_INFRARED_ROI_BOTTOM_THIRD			6

// defines for G5 Infrared camera display_warn variable (warning level for image overlay of icons)
#define G5_INFRARED_WARN_OFF					0
#define G5_INFRARED_WARN_CRITICAL_ONLY			1
#define G5_INFRARED_WARN_MAINTENANCE			2	// critical + maintenance required
#define G5_INFRARED_WARN_INFORMATIVE			3	// critical + maintenance required + informative

//////////////////////////////////////////////////////////////////////////////
// CAMTYPE_G5_INFRARED_REVG (revision G of protocol)
//
// G5 Infrared camera extended settings and controls.
//
// Valid lens types which could support this camera type:
//		LENS_G5_INFRARED_550CZ
//		LENS_G5_INFRARED_785CZ
//
typedef struct
{
	// Word 1
	char   sensitivity				:8;		// sets dynamic range / sensitivity (-1=wide DR/low sens/hot, 0=normal, 1=low DR/high sens/cold)
	UCHAR  filter					:8;		// image noise reduction / edge enhancement filter (0=off, 1 to 5=dynamic filter, 6 to 10=fixed filter)

	// Word 2
	USHORT restore_on_boot			:1;		// restore the camera settings from tracker flash memory (1=restore on boot)
	USHORT auto_calibration			:1;		// automatic calibration (NUC) (0=off, 1=on)
	USHORT auto_sensitivity			:1;		// camera automatically determines the best sensitivity (0=off, 1=on)
	USHORT digital_zoom_link		:1;		// combine optical and digital zoom (0=off, 1=on)
	USHORT camera_link_output		:1;		// Camera Link digital video output control (0=off, 1=on)
	USHORT video_freeze				:1;		// freeze/snapshot video image (0=off, 1=on)
	USHORT display_reticle			:1;		// display reticle overlay (0=off, 1=on)
	USHORT display_logo				:1;		// display corner logo image (0=off, 1=on)
	USHORT display_overlay			:1;		// global display overlay enable (0=off, 1=on)
	USHORT overlay_roi				:1;		// display overlay for AGLC and auto focus ROI boxes (0=off, 1=on)
	USHORT overlay_lens				:1;		// display overlay for lens zoom and focus activity (0=off, 1=on)
	USHORT overlay_glc				:1;		// display overlay for gain and level control activity (0=off, 1=on)
	USHORT save_lap					:1;		// save LAP parameters for current AGC mode (0=no action, 1=save)
	USHORT reset					:1;		// reset entire camera system (0=no action, 1=reset)
	USHORT reset_camera				:1;		// reset thermal camera only (0=no action, 1=reset)
	USHORT reset_lens				:1;		// reset zoom lens only (0=no action, 1=reset)

	// Word 3
	USHORT aglc						:8;		// automatic gain and level control - AGLC (0=off, 1=linear, 2=normal, 3=LAP)
	USHORT aglc_roi					:8;		// region of interest used for AGLC (1 to 7)

	// Word 4 & 5
	USHORT manual_gain				:16;	// manual gain control (0 to 1000)
	USHORT manual_level				:16;	// manual level control (0 to 1000)

	// Word 6
	USHORT auto_cal_time			:16;	// automatic calibration (NUC) time (0 to 32767 seconds)

	// Word 7
	USHORT digital_zoom				:16;	// digital zoom level (1.00 to 8.00, divide by 100 to get value)

	// Word 8
	USHORT palette					:8;		// color palette (0 to 6)
	USHORT display_warn				:8;		// display warning level for image overlay (0 to 3)

	// Word 9
	USHORT lap_equal				:16;	// histogram equalization level (0 to 100.00, divide by 100 to get value)

	// Word 10
	USHORT lap_hcnt					:8;		// histogram counts to ignore at top/bottom of histogram (0 to 10)
	USHORT lap_tau					:8;		// low pass filter setting (0 to 5)

	// Word 11
	USHORT lap_lace					:16;	// local area contrast enhancement level (0 to 100.00, divide by 100 to get value)

	// Word 12
	USHORT lap_sigma				:16;	// edge enhancement level (0 to 100.00, divide by 100 to get value)

	// Word 13 & 14
	USHORT software_ver_major		:8;		// software version (in the form major.mid.minor)
	USHORT software_ver_mid			:8;
	USHORT software_ver_minor		:8;
	USHORT spare14					:8;

	// Word 15
	USHORT fpa_temperature			:16;	// FPA temperature (in 1/100 Kelvin)

	// Word 16 & 17
	USHORT runtime					:16;	// total camera runtime in hours
	USHORT runtime_fraction			:8;		// fractional part of runtime in 1/100 of an hour
	USHORT spare17					:8;

} CAMERA_G5_INFRARED_REVG;


//////////////////////////////////////////////////////////////////////////////
// CAMERA_INVEO_AGILE_CORE
//
// InVeo Agile Core based camera extended settings and controls.
//
// Valid lens types which could support this camera type:
//		LENS_FLIR_NEUTRINO_SX12ISR1200
//		LENS_INVEO_THEIA_HD900M
//
typedef struct
{
	// Word 1
	USHORT operational_mode		:8;		  // operational mode (0 to 15), sets integration time and calibration table
	USHORT digital_zoom			:8;		  // digital zoom (0=none/1x, 1=2x, 2=reserved, 3=4x, 16-18=hybrid zoom)

	// Word 2
	USHORT color_palette		:8;		  // color palette (0=IR monochrome, 1-27=IR false color, 30-36 for visible)
	USHORT spare1				:8;

	// Word 3
	USHORT restore_on_boot		:1;		  // restore the camera settings from tracker flash memory (1=restore on boot)
	USHORT infinity_focus		:1;		  // one-shot focus at infinity for current FOV (1=focus infinity)
	USHORT infinity_track		:1;		  // focus at infinity during/after zooming FOV (0=off, 1=on)
	USHORT continuous_autofocus	:1;		  // enable continuous auto focus (0=off, 1=on)
	USHORT display_overlay		:1;		  // display overlay graphics (0=off, 1=on)
	USHORT freeze_image			:1;		  // freeze the camera image / snapshot (0=off, 1=on)
	USHORT test_pattern			:1;		  // display the color test pattern (0=off, 1=on)
	USHORT noise_filter			:1;		  // noise reduction filter (0=off, 1=on)
	USHORT cal_refresh_internal	:1;		  // run one point NUC refresh using internal reference (1=run NUC)
	USHORT cal_refresh_external	:1;		  // run one point NUC refresh using external reference (1=run NUC)
	USHORT spare2				:6;

	// Word 4
	USHORT aglc_mode			:4;		  // automatic gain and level processing / AGLC (0=off, 1=manual, 2=linear, 3=histogram, 4=gamma remap)
	USHORT aglc_roi				:4;		  // AGLC region of interest (0 to 3)
	USHORT aglc_restore			:1;		  // restore AGLC default values (1=load defaults)
	USHORT spare3				:7;

	// Word 5 & 6
	short  aglc_brightness		:16;	  // AGLC brightness control (-32768 to 32767)
	USHORT aglc_contrast		:16;	  // AGLC contrast control (0 to 65535)

	// Word 7
	USHORT lap_dnce				:1;		  // LAP-DnCE local area processing (0=off, 1=on)
	USHORT lap_dnce_restore		:1;		  // restore LAP-DnCE settings (1=load defaults)
	USHORT spare6				:14;

	// Word 8 & 9
	USHORT lap_background_level	:16;	  // LAP-DnCE background enhancement level (0 to 65535)
	USHORT lap_foreground_boost	:16;	  // LAP-DnCE foreground enhancement boost (0 to 65535)

	// Word 10 & 11
	USHORT temp_sensor_0		:16;	  // temperature sensor #0 (ADC value)
	USHORT temp_sensor_1		:16;	  // temperature sensor #1 (ADC value)
										  //   degrees C = (150 / 19200) * (ADC value - 32768)
	// Word 12
	USHORT fpa_temperature		:16;	  // FPA temperature (in 1/128 Kelvin)

} CAMERA_INVEO_AGILE_CORE;


//////////////////////////////////////////////////////////////////////////////
// CAMERA_DATA
//
// Main overlay data structure is a union of all possible structures
// This structure is 36 bytes long (CAM_DATA_SIZE)
//
typedef struct
{
	union
	{
		CAMERA_IRC_QUAZIR_LR		ircQuazirLr;
		CAMERA_G5_INFRARED_REVD		g5InfraredRevD;
		CAMERA_L3_WALRSS_HD			l3WalrssHd;
		CAMERA_G5_INFRARED_REVG		g5InfraredRevG;
		CAMERA_INVEO_AGILE_CORE		inveoAgileCore;

		USHORT						rawWords[CAM_DATA_SIZE/2];	// access to raw words
		UCHAR						rawBytes[CAM_DATA_SIZE];	// access to raw bytes

	} msg;

} CAMERA_DATA;


/****************************************************************************/
#pragma pack(pop)	// reset to default packing

#endif //__MSG_CAM_FMT_H__
