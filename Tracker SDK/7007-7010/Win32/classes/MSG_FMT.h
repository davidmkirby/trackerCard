///////////////////////////////////////////////////////////////////////////////
// MSG_FMT.H
//
// Message structure definitions to support the following products:
// * Series 7000 VME, PCI and PCI Express Video Trackers
// * Series 8000 Video Trackers
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

#ifndef __MSG_FMT_H__
#define __MSG_FMT_H__

#pragma pack(push, 2)	// pack all messages with two byte alignment

/****************************************************************************/
#if defined(_USE_XVME) || defined(_USE_VMIC)

	#if !defined(_USE_VME)
		#define _USE_VME
	#endif

#else

	#if !defined(_NO_VME)
		#define _NO_VME
	#endif

#endif
/****************************************************************************/

// data types
#ifndef USHORT
	typedef unsigned short	USHORT;
#endif

#ifndef UCHAR
	typedef unsigned char	UCHAR;
#endif

// include overlay message defines and structures
#include "MSG_OVL_FMT.H"

// include camera message defines and structures
#include "MSG_CAM_FMT.H"

// Bit defines
#define BIT0					0x0001	// bit 0
#define BIT1					0x0002	// bit 1
#define BIT2					0x0004	// bit 2
#define BIT3					0x0008	// bit 3
#define BIT4					0x0010	// bit 4
#define BIT5					0x0020	// bit 5
#define BIT6					0x0040	// bit 6
#define BIT7					0x0080	// bit 7
#define BIT8					0x0100	// bit 8
#define BIT9					0x0200	// bit 9
#define BIT10					0x0400	// bit 10
#define BIT11					0x0800	// bit 11
#define BIT12					0x1000	// bit 12
#define BIT13					0x2000	// bit 13
#define BIT14					0x4000	// bit 14
#define BIT15					0x8000	// bit 15

// E-O Imaging Tracker Models
#define TRKR_MODEL_6005		6005	// single target VME
#define TRKR_MODEL_6006		6006	// dual target VME
#define TRKR_MODEL_6007		6007	// single target PCI
#define TRKR_MODEL_6008		6008	// dual target PCI
#define TRKR_MODEL_6010		6010	// single target CompactPCI
#define TRKR_MODEL_6011		6011	// dual target CompactPCI
#define TRKR_MODEL_7005		7005	// single target VME
#define TRKR_MODEL_7006		7006	// dual target VME
#define TRKR_MODEL_7007		7007	// single target PCI
#define TRKR_MODEL_7008		7008	// dual target PCI
#define TRKR_MODEL_7010		7007	// single target PCI Express
#define TRKR_MODEL_7011		7008	// dual target PCI Express
#define TRKR_MODEL_8100		8100	// single target, standalone (low cost)
#define TRKR_MODEL_8101		8101	// dual target, standalone (low cost)
#define TRKR_MODEL_8200		8200	// single target, standalone (low cost)
#define TRKR_MODEL_8201		8201	// dual target, standalone (low cost)

// Tracker FPGA versions (see CAPABILITIES_MSG)
#define HW_VER_60XX_VME			1	// obsolete
#define HW_VER_60XX_PCI			2	// obsolete
#define HW_VER_60XX_CPCI		3	// obsolete
#define HW_VER_70XX_VME_CL		4	// 6U VME with Camera Link full
#define HW_VER_70XX_VME_HD		5	// 6U VME with dual HD-SDI
#define HW_VER_70XX_ITT_CUSTOM	6	// custom board
#define HW_VER_70XX_PCI			7	// full length PCI or PCIe (daughter card for digital video)
#define HW_VER_810X				8	// Standalone (2 analog video in/out)
#define HW_VER_820X				9	// Standalone (1 analog video & 1 HD-SDI video in/out)
#define HW_VER_701X_VME			10	// 6U VME, conduction cooled (analog video only)
#define HW_VER_741X_PCIE		11	// half length PCI Express with DVI-D video only (no SRIO)
#define HW_VER_741X_PCIE_V2		12	// half length PCI Express with DVI-D video only (with SRIO support and AReady EMIF)
#define HW_VER_880X				13	// Standalone (low cost, 4 input 3G-SDI or analog, 1 output each)
#define HW_VER_821X				14	// Standalone (2 input/output 3G-SDI)

// Tracker FPGA types (see CAPABILITIES_MSG)
#define HW_FPGA_XVE_1600		1	// obsolete (6000 series)
#define HW_FPGA_XVE_2000		2	// obsolete (6000 series)
#define HW_FPGA_XC4V_LX80		3	// obsolete (6000 series)
#define HW_FPGA_XC4V_LX160		4
#define HW_FPGA_XC5V_LX110		5
#define HW_FPGA_XC5V_LX115T		6
#define HW_FPGA_XC6S_LX100T		7
#define HW_FPGA_XC6S_LX150		8
#define HW_FPGA_XC6S_LX150T		9	// 7410, 8800 and 8210

// sync word
#define GATE0_SYNC_WORD		0xA5A5
#define GATE1_SYNC_WORD		0xA6A6
#define GATE2_SYNC_WORD		0xA7A7
#define TRACKER_SYNC_WORD	GATE0_SYNC_WORD

// maximum possible message size (including sync word, data and checksum)
#define MAX_MSG_SIZE_BYTES		128
#define MAX_MSG_SIZE_WORDS		(MAX_MSG_SIZE_BYTES/2)	// 64 short words

// maximum number of track gates
#define MAX_GATES				3

// maximum user string length (not counting the NULL termination)
#define MAX_USER_STRING_LEN		37

// maximum shared memory user string length (not counting the NULL termination)
#define MAX_SM_USER_STRING_LEN	39

// built in test data size (40 words / 80 bytes)
#define MAX_TEST_DATA_SIZE		40

// On / Off defines
#define OFF 0
#define ON  1

// track status bit defines
#define TSTAT_TOO_FEW_PIXELS			BIT1
#define TSTAT_TOO_MANY_PIXELS			BIT2
#define TSTAT_X_POSITION_FAIL			BIT3
#define TSTAT_Y_POSITION_FAIL			BIT4
#define TSTAT_PIXEL_COUNT_TOO_LARGE		BIT5
#define TSTAT_PIXEL_COUNT_TOO_SMALL		BIT6
#define TSTAT_X_SIZE_FAIL				BIT7
#define TSTAT_Y_SIZE_FAIL				BIT8
#define TSTAT_INTRUSION_DETECTED		BIT9
#define TSTAT_BOOT_BIT_FAIL				BIT10
#define TSTAT_RUNTIME_BIT_FAIL			BIT11
#define TSTAT_CORR_MATCH_FAIL			BIT12
#define TSTAT_NO_VIDEO_INPUT			BIT15

// track state defines
#define TRACK_STATE_INITIALIZATION		0
#define TRACK_STATE_ACQUIRE				1
#define TRACK_STATE_PENDING_TRACK		2
#define TRACK_STATE_ON_TRACK			3
#define TRACK_STATE_COAST				4
#define TRACK_STATE_OFF_TRACK			5
#define TRACK_STATE_AUTO_ACQUIRE		6

// target polarity defines
#define POLARITY_GRAY	0
#define POLARITY_WHITE	1
#define POLARITY_BLACK	2
#define POLARITY_MIX	3
#define POLARITY_AGRAY	4	// auto polarity

// enable / disable defines
#define DISABLE 0
#define ENABLE  1

// Manual / Auto defines
#define MANUAL    0
#define AUTOMATIC 1

// Acquire/track defines
#define ACQUIRE  0
#define TRACK    1

// Symbology defines
#define BLACK	0
#define WHITE	1

// Track mode defines
#define TOP_EDGE     0
#define BOTTOM_EDGE  1
#define LEFT_EDGE    2
#define RIGHT_EDGE   3
#define CENTROID     4
#define INTENSITY	 5
#define VECTOR		 6
#define CORRELATION  7

// Auto-acquire target selection ratio
#define TARSEL_RATIO_TALL	0
#define TARSEL_RATIO_SQUARE	1
#define TARSEL_RATIO_WIDE	2

// Auto-acquire target selection direction
#define TARSEL_DIR_TOPCENTER		0
#define TARSEL_DIR_TOPRIGHT			1
#define TARSEL_DIR_MIDRIGHT			2
#define TARSEL_DIR_BOTRIGHT			3
#define TARSEL_DIR_BOTCENTER		4
#define TARSEL_DIR_BOTLEFT			5
#define TARSEL_DIR_MIDLEFT			6
#define TARSEL_DIR_TOPLEFT			7

// Coast mode defines
#define COAST_ZERO_OUTPUT	0
#define COAST_HOLD_LAST		1
#define COAST_PREDICTED		2

#define COAST_LOOP_CLOSED	0
#define COAST_LOOP_OPEN		1

// Coast gate growth rate defines
#define COAST_GATE_GROW0	0
#define COAST_GATE_GROW1	1
#define COAST_GATE_GROW2	2
#define COAST_GATE_GROW4	3

// Search mode defines
#define SEARCH_NONE					0
#define SEARCH_RETURN_BORESIGHT		1
#define SEARCH_HOLD_LAST_POS		2
#define SEARCH_RASTER_SCAN			3
#define SEARCH_SPIRAL_SCAN			4

// Video source defines (see SYSTEM_CTRL_MSG)
#define VS_INPUT_1		0
#define VS_INPUT_2		1
#define VS_INPUT_3		2
#define VS_INPUT_4		3
#define VS_INPUT_5		4
#define VS_INPUT_6		5

#define VS_ANALOG1		VS_INPUT_1
#define VS_ANALOG2		VS_INPUT_2
#define VS_ANALOG3		VS_INPUT_3
#define VS_ANALOG4		VS_INPUT_4
#define VS_DIGITAL1		VS_INPUT_5
#define VS_DIGITAL2		VS_INPUT_6

#define VS_DIGITAL		VS_DIGITAL1	// legacy helper

#define VS_MAX_INPUT	VS_INPUT_6
#define VS_NUM_INPUTS	(VS_MAX_INPUT+1)

// Video type defines
#define VIDEO_NTSC		0	// Analog RS-170/NTSC video
#define VIDEO_DIGITAL	1	// Digital video (automatic format detection)
#define VIDEO_PAL		7	// Analog CCIR/PAL video

// manual position types
#define MP_GATE   1  // Manual positioning track gate
#define MP_LOS    2  // Manual positioning line of sight
#define MP_OA     3  // Manual positioning offset aim

// mouse button defines
#define RMOUSE_BUTTON_IDLE	0
#define RMOUSE_BUTTON_DOWN	1
#define RMOUSE_BUTTON_UP	2

// download code defines
#define DL_CODE_SIZE	80

#define DL_DSP1				1		// DSP1 text HEX files (C6455)
#define DL_DSP2				2		// DSP1 text HEX files (C6455)
#define DL_DSP_BIN			3		// DSP binary BIN files (C667x)
#define DL_FPGA_XSVF		4		// FPGA binary XSVF files
#define DL_FPGA_MCS			5		// FPGA text MCS files
#define DL_IFF_LUT			7		// IFF look up table
#define DL_FPGA2_XSVF		8		// daughter card FPGA binary XSVF files
#define DL_FPGA2_MCS		9		// daughter card FPGA text MCS files
#define DL_NUC_GAIN			10
#define DL_NUC_OFFSET		11
#define DL_NUC_BAD_PIXEL	12

#define DL_FIRSTBLOCK	1
#define DL_MIDDLEBLOCK	3
#define DL_LASTBLOCK	5
#define DL_FAIL			7

#define DL_NEXTBLOCK	2
#define DL_REDOBLOCK	4
#define DL_FINISHED		6
#define DL_RESTART		8
#define DL_ABORT		10

// joystick track/acquire defines
#define JOYSTICK_ACQUIRE	2
#define JOYSTICK_TRACK		3

// joystick response functions
#define JOYSTICK_RESP_LINEAR		0
#define JOYSTICK_RESP_NONLINEAR		1
#define JOYSTICK_RESP_SQUARED		2
#define JOYSTICK_RESP_CUBED			3
#define JOYSTICK_RESP_QUAD			4

// scan mode types
#define SCAN_LINE				0
#define SCAN_HORIZONTAL_RASTER	1
#define SCAN_VERTICAL_RASTER	2
#define SCAN_HORIZONTAL_ZIGZAG	3
#define SCAN_VERTICAL_ZIGZAG	4
#define SCAN_STEP_SPIRAL		5
#define SCAN_CONTINUOUS_SPIRAL	6

// mount control commands
#define MOUNT_NO_ACTION				0
#define MOUNT_SET_ZERO				1   // set AZ and EL offsets so the current mount position is zero
#define MOUNT_CLEAR_OFFSETS			2   // clear offsets (both AZ and EL)
#define MOUNT_DRIVE_ZERO			3   // go to zero position (0, 0)
#define MOUNT_DRIVE_AZ_EL			4	// rate mode (DEBUG ONLY, use MOUNT_RATE_DRIVE_MSG instead)
#define MOUNT_MOVE_TO_AZ_EL			5	// position mode
#define MOUNT_STANDBY				6	// motor power off
#define MOUNT_ACTIVE				7	// motor power on
#define MOUNT_SET_OFFSET_AZ			8	// set AZ offset (used for setting true north position)
#define MOUNT_SET_OFFSET_EL			9	// set EL offset
#define MOUNT_SET_OFFSETS			10	// set offset for both AZ and EL, also used to query the offsets (get_msg_id in QUERY_CONFIG_MSG)
#define MOUNT_SET_VELOCITY_LIMITS	11	// set AZ and EL velocity limits, also used to query the limits (get_msg_id in QUERY_CONFIG_MSG)
#define MOUNT_STOW1					12	// stow mode (go to primary stow position and power off) on supported mounts
#define MOUNT_STOW2					13	// stow mode (go to secondary stow position and power off) on supported mounts

// mount types
#define MOUNT_NONE					0
#define MOUNT_VINTEN_HS105P			1	// EO Imaging custom modified Vinten
#define MOUNT_VINTEN_HS2010ME		2	// EO Imaging custom modified Vinten
#define MOUNT_RPM_513				3	// ***OBSOLETE***
#define MOUNT_SAGEBRUSH				4	// Sagebrush Technology (custom)
#define MOUNT_INSTRO_WASP			5	// Instro Precision Limited (tracking protocol only)
#define MOUNT_RPM_PG2053			6	// Rotating Precision Mechanisms PG-2053
#define MOUNT_QUICKSET_QPT			7	// Moog/QuickSet QPT (legacy/generic)
#define MOUNT_RPM_PT0517			8	// Rotating Precision Mechanisms PT-0517 (max velocity of 100 deg/sec)
#define MOUNT_ORBIT_AL2613			9	// Orbit Technology Group (dual serial ports, max velocity 10 deg/sec)
#define MOUNT_APS_SPS1000			10	// Atlantic Positioning Systems SPS-1000 (aka-Xybion or Cobham)
#define MOUNT_INSTRO_MANTIS			11	// Instro Precision Limited (tracking protocol only)
#define MOUNT_AEROFLEX_ITT			12	// ITT custom (uses steered mirror filter)
#define MOUNT_ORBIT_AL1613			13	// Orbit Technology Group (single serial port, max velocity 10 deg/sec)
#define MOUNT_RPM_PG10523			14	// Rotating Precision Mechanisms PG-10523 (max velocity 40 deg/sec)
#define MOUNT_APS_SPS2000			15	// Atlantic Positioning Systems SPS-2000
#define MOUNT_RPM_PG1023			16	// Rotating Precision Mechanisms PG-1023 (max velocity 40 deg/sec)
#define MOUNT_GRAFLEX_PT150			17	// Graflex PT-150 version 1
#define MOUNT_MRA_P848_HD50			18	// Malibu Research P848 HD50
#define MOUNT_RPM_AUTO				19	// Rotating Precision Mechanisms, automatic detection (for newer controllers)
#define MOUNT_ORBIT_AL4015			20	// Orbit Technology Group (max velocity 40 deg/sec)
#define MOUNT_QUICKSET_GEMINEYE		21	// Moog/Quickset GeminEye (max velocity 100 deg/sec pan, 60 deg/sec tilt)
#define MOUNT_FLIR_ESERIES			22	// FLIR E-Series PTU (aka-Directed Perception)
#define MOUNT_EVPU_MS02				23	// EVPU MS02 (used by FLIR)
										//	NOTE: UART3 through UART7 are virtual serial ports used for positioner passthrough
#define MOUNT_GRAFLEX_PT150_V2		24	// Graflex PT-150 version 2
#define MOUNT_QUASONIX_DACU			25	// Quasonix DACU (aka-Telemetry Antenna Corp/Telantco)
#define MOUNT_GALIL_DMC_ETHERNET	26	// Galil DMC via Ethernet (on a PVP Night Hawk and CMG systems)
#define MOUNT_MOOG_MERCURY			27	// Moog Mercury (PTCR-1000 protocol)
										//	NOTE: UART6 and UART7 are virtual serial ports used for positioner passthrough
#define MOUNT_MOOG_QMP				28	// Moog QMP/Taurus (PTCR-96 protocol)
										//	NOTE: UART6 and UART7 are virtual serial ports used for positioner passthrough
#define MOUNT_GALIL_DMC				29	// Galil DMC via serial (on a PVP Night Hawk and CMG systems)
#define MOUNT_DSCU					30	// EO Imaging Digital Servo Control Unit (DSCU)
#define MOUNT_MOOG_EDMC				31	// Moog embedded Digital Motion Controller (eDMC)
#define MOUNT_MOOG_MPT				32	// Moog MPT positioner (PTZ protocol using SBC controller board)
										//	NOTE: UART6 and UART7 are virtual serial ports used for positioner passthrough
#define MOUNT_MOOG_MPT_NO_PASS		33	// Moog MPT positioner with no serial passthrough supported
#define MOUNT_LAST_TYPE				MOUNT_MOOG_MPT_NO_PASS


// preset configuration commands
#define PRESET_NO_ACTION		0
#define PRESET_SAVE				1
#define PRESET_LOAD				2
#define PRESET_CLEAR			3

// lens types
#define LENS_NONE							0
#define LENS_GRAFLEX						1	// OBSOLETE: use LENS_GRAFLEX_VINTEN instead
#define LENS_OOS_TFOV						2	// uses LENS_SERIAL_TFOV_MSG
#define LENS_SOPHIE_THERMAL_BINOCULARS		3	// uses LENS_SERIAL_TFOV_MSG
#define LENS_GENERIC						4	// uses LENS_GENERIC_MSG
#define LENS_ITS_6125DF						5	// uses LENS_SERIAL_ZOOM_MSG
#define LENS_DIOP_FIELDPRO5X				6	// uses LENS_SERIAL_IR_ZOOM_MSG
#define LENS_GRAFLEX_SERIAL					7	// uses LENS_SERIAL_ZOOM_MSG
#define LENS_GRAFLEX_VINTEN					8	// uses LENS_SERIAL_ZOOM_MSG
#define LENS_ANALOG_ZOOM					9	// uses LENS_ANALOG_ZOOM_MSG
#define LENS_COHU_MPC						10	// uses LENS_SERIAL_ZOOM_MSG
#define LENS_JANOS_ASIO_DFOV				11	// uses LENS_SERIAL_DFOV_MSG
#define LENS_JANOS_ALBA_TFOV				12	// uses LENS_SERIAL_TFOV_MSG
#define LENS_OOS_MULTIBAND_TELESCOPE		13	// uses LENS_SERIAL_FIXED_FOV_MSG
#define LENS_FLIR_MILCAM_DFOV				14	// uses LENS_SERIAL_IR_DFOV_MSG
#define LENS_FUJINON_D60					15	// uses LENS_SERIAL_ZOOM_MSG
#define LENS_GRAFLEX_35X					16	// uses LENS_SERIAL_ZOOM_MSG
#define LENS_FLIR_RANGER_HRC				17	// uses LENS_SERIAL_IR_ZOOM_MSG
#define LENS_FUJINON_C22X23R2DZP1			18	// uses LENS_SERIAL_ZOOM_MSG
#define LENS_GRAFLEX_FIXED_FOV				19	// uses LENS_SERIAL_FIXED_FOV_MSG
#define LENS_FLIR_RS6700_DFOV				20	// uses LENS_SERIAL_IR_DFOV_MSG
#define LENS_OPTEC_FOCUSER					21 	// uses LENS_SERIAL_FIXED_FOV_MSG
#define LENS_STINGRAY_OPTICS_SR2536			22 	// uses LENS_SERIAL_IR_ZOOM_MSG
#define LENS_PVP_NIGHTHAWK_IR_ZOOM			23	// uses LENS_SERIAL_IR_ZOOM_MSG
#define LENS_PVP_NIGHTHAWK_VIS_ZOOM			24	// uses LENS_SERIAL_ZOOM_MSG
#define LENS_MOOG_ZOOM_1					25	// uses LENS_MOOG_ZOOM_MSG
#define LENS_MOOG_ZOOM_2					26	// uses LENS_MOOG_ZOOM_MSG
#define LENS_G5_INFRARED_550CZ				27	// uses LENS_SERIAL_IR_ZOOM_MSG
#define LENS_L3_WALRSS_HD					28	// uses LENS_SERIAL_IR_ZOOM_MSG
#define LENS_HITACHI_HD2005_D60X16			29	// uses LENS_SERIAL_ZOOM_MSG
#define LENS_HITACHI_HD2005_FH32X15			30	// uses LENS_SERIAL_ZOOM_MSG
#define LENS_IRC_QUAZIR_LRSD_RPO_ODEM825	31	// uses LENS_SERIAL_IR_ZOOM_MSG
#define LENS_IRC_QUAZIR_LRSD_RPO_DIAMOND	32	// uses LENS_SERIAL_IR_ZOOM_MSG
#define LENS_OFFICINA_STELLARE_FOCUSER		33 	// uses LENS_SERIAL_FIXED_FOV_MSG
#define LENS_SONY_FCB_EX980S				34  // uses LENS_SERIAL_ZOOM_MSG
#define LENS_FUJINON_SX800					35  // uses LENS_SERIAL_ZOOM_MSG
#define LENS_FLIR_RANGER_HDC				36	// uses LENS_SERIAL_IR_ZOOM_MSG
#define LENS_G5_INFRARED_785CZ				37	// uses LENS_SERIAL_IR_ZOOM_MSG
#define LENS_FLIR_NEUTRINO_SX12ISR1200		38	// uses LENS_SERIAL_IR_ZOOM_MSG
#define LENS_INVEO_THEIA_HD900M				39	// uses LENS_SERIAL_IR_ZOOM_MSG
#define LENS_LAST_TYPE						LENS_INVEO_THEIA_HD900M

// lens commands
#define ZOOM_NONE		0
#define ZOOM_NARROW		1
#define ZOOM_WIDE		2
#define ZOOM_GO_TO		3

#define FOCUS_NONE		0
#define FOCUS_NEAR		1
#define FOCUS_FAR		2
#define FOCUS_GOTO		3
#define FOCUS_AUTO		4

#define IRIS_NONE		0
#define IRIS_CLOSE		1
#define IRIS_OPEN		2

#define FOV_NONE		0
#define FOV_WIDE		1
#define FOV_MEDIUM		2
#define FOV_NARROW		3

// camera/lens OSD commands (keypad emulation)
#define OSD_CMD_NONE	0
#define OSD_CMD_ENTER	1
#define OSD_CMD_CANCEL	2
#define OSD_CMD_LEFT	3
#define OSD_CMD_RIGHT	4
#define OSD_CMD_UP		5
#define OSD_CMD_DOWN	6
#define OSD_CMD_TAB		7

// camera types
#define CAMERA_NONE				0	// DEPRECATED (NOT USED)
#define CAMERA_INDIGO_MERLIN	1	// DEPRECATED (NOT USED)

// laser range finder commands
#define LRF_CMD_CONFIG			0	// no action (just configuration)
#define LRF_CMD_FIRE_SINGLE		1	// fire the laser one time
#define LRF_CMD_FIRE_PERIODIC	2	// fire the laser continuously
#define LRF_CMD_FIRE_STOP		3	// stop firing the laser continuously
#define LRF_CMD_QUERY_STATUS	4	// query the LRF status and return a TARGET_RANGE_MSG
#define LRF_CMD_BIT				5	// run built-in-test
#define LRF_CMD_SHOT_COUNT		6	// get the shot counter

// laser range finder types
#define LRF_TYPE_NONE						0
#define LRF_TYPE_ALST_ELRF1					1
#define LRF_TYPE_ALST_ELRF2					2
#define LRF_TYPE_ALST_ELRF3					3
#define LRF_TYPE_NEWCONOPTIK_LRB25000		4
#define LRF_TYPE_NEWCONOPTIK_MOD25HFLC		5
#define LRF_TYPE_NEWCONOPTIK_MOD25HFLC_V3	6	// revision 3 of the protocol
#define LRF_TYPE_ZEISS_LP17D				7	// Zeiss/Airbus LP17D
#define LRF_TYPE_ZEISS_LP17D_1				8	// Zeiss/Airbus LP17D-1 (no parity version)
#define LRF_TYPE_PVP_NIGHTHAWK				9	// PVP Night Hawk and CMG Systems
#define LRF_TYPE_JENOPTIK_DLEM				10	// Jenoptik DLEM 20/30/45 series
#define LRF_LAST_TYPE						LRF_TYPE_JENOPTIK_DLEM

// analog video switch types
#define AVID_SWITCH_NONE				0
#define AVID_SWITCH_EXTRON_MMX_42_AV	1	// Extron MMX 42 AV (4 inputs / 2 outputs)

// analog video switch function types
#define AVID_FUNCT_NONE					0
#define AVID_FUNCT_OUTPUT_UNSELECTED	1	// of 2 inputs, output unselected video source

// digital video switch types
#define DVID_SWITCH_NONE				0
#define DVID_SWITCH_PHRONTIER_CLEVER_SW	1	// Phrontier CLEVER-SW Camera Link (2 inputs / 2 outputs)
#define DVID_SWITCH_EXTRON_SW4_3G		2	// Extron SW4 3G HD-SDI (4 inputs / 1 output)
#define DVID_SWITCH_MATRIX_MSC_HD22L	3	// Matrix Switch MSC-HD22L 3G-SDI (2 inputs / 2 outputs)

// digital video switch function types
#define DVID_FUNCT_NONE					0
#define DVID_FUNCT_OUTPUT_SELECTED		1	// of 2 inputs, output selected video source

// digital I/O function types
#define DIG_FUNCT_DISABLED				0
#define DIG_FUNCT_FOCUS_FAR				1
#define DIG_FUNCT_FOCUS_NEAR			2
#define DIG_FUNCT_ZOOM_NARROW			3
#define DIG_FUNCT_ZOOM_WIDE				4
#define DIG_FUNCT_VIDEO_SELECT			5	// toggles between video source 1 and 2
#define DIG_FUNCT_GATE_SELECT			6
#define DIG_FUNCT_LRF_ENABLE			7
#define DIG_FUNCT_DATA_LOGGING			8
#define DIG_FUNCT_OFFSET_AIM			9
#define DIG_FUNCT_RETURN_BORESIGHT		10
#define DIG_FUNCT_GAIN_OVERRIDE			11
#define DIG_FUNCT_TRACK_ACQUIRE			12
#define DIG_FUNCT_SECOND_GATE_SLAVE		13
#define DIG_FUNCT_RESET_TRACKER			14
#define DIG_FUNCT_VELOCITY_LIMIT_ENABLE	15
#define DIG_FUNCT_LRF_ON_TRACK_ENABLE	16
#define DIG_FUNCT_ZOOM_TO_RANGE_ENABLE	17
#define DIG_FUNCT_VIDEO_CYCLE_LENSES	18	// cycles through video sources with configured lenses
#define DIG_FUNCT_SLAVE_FOVS			19	// slave all configured lens FOVs to the currently selected camera/lens
#define DIG_FUNCT_DISABLE_ALL_FUNCTIONS	20	// global digital I/O function disable (for cable disconnect detection)
#define DIG_FUNCT_AUTO_IRIS				21
#define DIG_FUNCT_IRIS_OPEN				22
#define DIG_FUNCT_IRIS_CLOSE			23
#define DIG_FUNCT_ZOOM_2X				24	// zoom lens 2X extender

// digital I/O logic types
#define DIG_LOGIC_DISABLED			0
#define DIG_LOGIC_ACTIVE_HIGH		1
#define DIG_LOGIC_ACTIVE_LOW		2
#define DIG_LOGIC_RIGING_EDGE		3
#define DIG_LOGIC_FALLING_EDGE		4

// digital I/O port mappings
#define DIG_PORT_16IN				0
#define DIG_PORT_8IN_8OUT			1	// low 8-bits are inputs, high 8-bits are outputs
#define DIG_PORT_16OUT				2

// digital I/O message types
#define DIG_TYPE_READ				0	// read of DIO sent from tracker
#define DIG_TYPE_WRITE				1	// write DIO command sent to tracker

// target generator selections
#define TARGEN_SELECT_BACKGROUND	0
#define TARGEN_SELECT_TARGET1		1
#define TARGEN_SELECT_TARGET2		2

// target generator types
#define TARGEN_TYPE_DISABLED		0
#define TARGEN_TYPE_RECTANGLE		1
#define TARGEN_TYPE_BACKGROUND		1  // only for background enable
#define TARGEN_TYPE_DIAMOND			2
#define TARGEN_TYPE_COLOR_BARS		3  // only for target 1
#define TARGEN_TYPE_SINGLE_PIXEL	3  // only for target 2

// target simulator commands
#define TARSIM_CMD_NONE				0	// free run at the specified time
#define TARSIM_CMD_RUN				1	// run the simulation starting at the specified time
#define TARSIM_CMD_STOP				2	// stop the simulation

// multi-target selection criteria
#define MT_SELECT_BORESIGHT			0	// target closest to boresight
#define MT_SELECT_GATE				1	// target closest to gate center
#define MT_SELECT_LARGEST			2	// largest target
#define MT_SELECT_FASTEST			3	// fastest target
#define MT_SELECT_SLOWEST			4	// slowest target
#define MT_SELECT_BRIGHTEST			5	// target with highest average pixel intensity
#define MT_SELECT_DARKEST			6	// target with lowest average pixel intensity

// GPS types
#define GPS_TYPE_NONE				0
#define GPS_TYPE_XMONKEY			1	// Ryan Mechatronics X-Monkey GPS (binary messages)
#define GPS_TYPE_GARMIN_19X_HVS		2	// Garmin 19x HVS (NMEA 0183, 10 samples/sec at 38400 bps)
#define GPS_TYPE_MOOG_EDMC			3	// get GPS data from Moog embedded Digital Motion Controller (eDMC)
#define GPS_LAST_TYPE				GPS_TYPE_MOOG_EDMC


// Message Types ------------------------------------------

#define PING_MSG_TYPE						0	// Poll/Ping Message
#define RUN_TIME_CTRL_MSG_TYPE				1	// Run-Time Control Msg
#define SYSTEM_CTRL_MSG_TYPE				2	// System Control Msg
#define LOS_OFFSET_CTRL_MSG_TYPE			3	// use LOS_OFFSET_CTRL2_MSG_TYPE instead
#define OFFSET_AIM_CTRL_MSG_TYPE			4	// use OFFSET_AIM_CTRL2_MSG_TYPE instead
#define SYMBOLOGY_CTRL_MSG_TYPE				5
#define CORRELATION_CTRL_MSG_TYPE			6
#define RESERVED_MSG_TYPE					7	// RESERVED (NOT USED)
#define FILTER_CTRL_MSG_TYPE				8
#define COAST_CTRL_MSG_TYPE					9
#define TGT_VALIDATION_CTRL_MSG_TYPE		10
#define AAQ_ACQUIRE_CTRL_MSG_TYPE			11	// DEPRECATED (use multi-target instead)
#define AAQ_TRACK_CTRL_MSG_TYPE				12	// DEPRECATED (use multi-target instead)
#define AAQ_TGT_SELECT_CTRL_MSG_TYPE		13	// DEPRECATED (use multi-target instead)
#define ANNOTATION_MSG_TYPE					14
#define USER_STRING_MSG_TYPE				15
#define	SCAN_MSG_TYPE						16
#define MOUNT_RATE_DRIVE_MSG_TYPE			17	// Real-time (field rate) mount velocity drive
#define MOUNT_CONTROL_MSG_TYPE				18	// Mount control and diagnostics
#define CONTROL_BOX_MSG_TYPE				19
#define QUERY_CONFIG_MSG_TYPE				20
#define PRESET_CONFIG_MSG_TYPE				21
#define LENS_CONFIG_MSG_TYPE				22
#define LENS_GRAFLEX_MSG_TYPE				23
#define LENS_SERIAL_TFOV_MSG_TYPE			24
#define LENS_SERIAL_DFOV_MSG_TYPE			25
#define LENS_GENERIC_MSG_TYPE				26
#define LENS_SERIAL_ZOOM_MSG_TYPE			27
#define LENS_SERIAL_IR_ZOOM_MSG_TYPE		28
#define LENS_ANALOG_ZOOM_MSG_TYPE			29
#define CAMERA_CONFIG_MSG_TYPE				30	// DEPRECATED (NOT USED)
#define CAMERA_GENERIC_MSG_TYPE				31	// DEPRECATED (NOT USED)
#define LENS_SERIAL_FIXED_FOV_MSG_TYPE		32
#define LENS_SERIAL_IR_DFOV_MSG_TYPE		33
#define LENS_MOOG_ZOOM_MSG_TYPE				34

#define ANALOG_INPUT_MSG_TYPE				40
#define CAPABILITIES_MSG_TYPE				41
#define BUILT_IN_TEST_MSG_TYPE				42
#define MOUNT_STATUS_MSG_TYPE				43
#define LRF_CONTROL_MSG_TYPE				44	// Laser range finder control
#define TARGET_RANGE_MSG_TYPE				45
#define TARGET_GENERATOR_MSG_TYPE			46
#define GATE_CONTROL_MSG_TYPE				47
#define MOUNT_FEEDBACK_MSG_TYPE				48
#define DIGITAL_IO_MSG_TYPE					49
#define DL_CODE_RECEIVE_MSG_TYPE			50
#define DL_CODE_STATUS_MSG_TYPE				51
#define DL_LICENSE_MSG_TYPE					52
#define DL_CODE_STATUS2_MSG_TYPE			53
#define GATE_STATISTICS_MSG_TYPE			54
#define DIGITAL_VIDEO_STATUS_MSG_TYPE		55
#define USER_STRING2_MSG_TYPE				56
#define TARGET_SIMULATOR_MSG_TYPE			57
#define CRP_CONTROL_MSG_TYPE				58	// OBSOLETE (use multi-target instead)
#define STEERED_MIRROR_FILTER_MSG_TYPE		59  // steered mirror filter
#define IFF_TRACK_STATUS_MSG_TYPE			60	// custom IFF tracking
#define STEERED_MIRROR_CALIBRATION_MSG_TYPE	61	// steered mirror filter calibration
#define OVERLAY_CONTROL_MSG_TYPE			62	// video overlay control
#define OVERLAY_STATUS_MSG_TYPE				63	// video overlay status (query only)
#define LOS_OFFSET_CTRL2_MSG_TYPE			64	// updated version of LOS_OFFSET_CTRL_MSG
#define OFFSET_AIM_CTRL2_MSG_TYPE			65	// updated version of OFFSET_AIM_CTRL_MSG
#define POS_TRACK_STATUS_MSG_TYPE			66	// position tracking status
#define CONTROL_BOX_CONTROL_MSG_TYPE		67	// message from control box to tracker
#define CONTROL_BOX_STATUS_MSG_TYPE			68	// message from tracker to control box
#define THRESHOLD_STATISTICS_MSG_TYPE		69
#define OVERLAY_STATUS_EXT_MSG_TYPE			70	// video overlay extended status (query only)
#define CAMERA_CONTROL_MSG_TYPE				71	// extended camera/lens control (see MSG_CAM_FMT.h)
#define GPS_DATA_MSG_TYPE					72	// external GPS data
#define SYSTEM_STATUS_MSG_TYPE				73	// consolidated system status (for 8000 series boards)
#define FPGA_VIDEO_STATUS_MSG_TYPE			74
#define ETHERNET_STATUS_MSG_TYPE			75

#define MT_GENERAL_MSG_TYPE					80	// multi-target (MT) hardware engine configuration
#define MT_ACQUIRE_MSG_TYPE					81	// MT acquisition configuration
#define MT_TRACK_MSG_TYPE					82	// MT track configuration
#define MT_DATA_MSG_TYPE					83	// MT target data output
#define MT_VALIDATION_MSG_TYPE				84	// MT target validation configuration

// NOTE: Message numbers 100 - 120 are reserved
//       for internal tracker messaging

#define CONFIG_GATE_SIZE_MSG_TYPE			200
#define CONFIG_GATE_POS_MSG_TYPE			201
#define	CONFIG_ANNOTATION_MSG_TYPE			202
#define CONFIG_SYMBOLOGY_MSG_TYPE			203
#define CONFIG_CORR_REF_POS_MSG_TYPE		204
#define CONFIG_VIDEO_MSG_TYPE				205
#define CONFIG_PRESET_CONFIG_MSG_TYPE		206
#define CONFIG_AUTOSIZE_MSG_TYPE			207
#define CONFIG_VALIDATION_MSG_TYPE			208
#define CONFIG_JOYSTICK_MSG_TYPE			209
#define CONFIG_LENS_FOV_MSG_TYPE			210 // DEPRECATED (NOT USED)
#define CONFIG_MOUNT_MSG_TYPE				211
#define CONFIG_ANALOG_JOYSTICK_MSG_TYPE		212
#define CONFIG_DIGITAL_IO_MSG_TYPE			213
#define CONFIG_ZOOM_TO_RANGE_MSG_TYPE		214
#define CONFIG_GATE_STYLE_MSG_TYPE			215
#define CONFIG_GATE_RETICLE_MSG_TYPE		216	// also see newer CONFIG_GATE_RETICLE2_MSG
#define CONFIG_LOS_RETICLE_MSG_TYPE			217
#define CONFIG_TRACK_FLAG_MSG_TYPE			218
#define CONFIG_NORTH_OFFSET_MSG_TYPE		219
#define CONFIG_DIGITAL_VIDEO_MSG_TYPE		220
#define	CONFIG_ANNOTATION2_MSG_TYPE			221
#define CONFIG_SERIAL_PORTS_MSG_TYPE		222
#define CONFIG_CONTROL_BOX_MSG_TYPE			223
#define CONFIG_TARGET_SIMULATOR_MSG_TYPE	224
#define CONFIG_CRP_MSG_TYPE					225	// OBSOLETE (use multi-target instead)
#define CONFIG_AUTOTHRESHOLD_MSG_TYPE		226
#define CONFIG_ETHERNET_MSG_TYPE			227
#define CONFIG_DIGITAL_VIDEO_EXT_MSG_TYPE	228 // non-standard digital video input config (Model 6007 ONLY)
#define CONFIG_DIGITAL_PREPROCESS_MSG_TYPE	229	// digital video input preprocessing
#define CONFIG_IFF_TRACK_MSG_TYPE			230	// custom IFF tracking
#define CONFIG_INTRUSION_DETECT_MSG_TYPE	231 // gate intrusion detection and break-lock
#define CONFIG_POS_TRACK_MSG_TYPE			232 // position tracking config
#define CONFIG_CONTROL_BOX_IO_MSG_TYPE		233
#define CONFIG_VIDEO_SWITCH_MSG_TYPE		234
#define CONFIG_GATE_RETICLE2_MSG_TYPE		235
#define CONFIG_GPS_MSG_TYPE					236	// external GPS config

#define MESSAGE_ACK_MSG_TYPE				254	// Message acknowledge/received response 
#define STATUS_MSG_TYPE						255	// Status Message


// Outgoing Message Table Structure ------------------------

#define MSG_TBL_LEN     115  // number of msgs in table

typedef struct
{
   int	type;
   int	byte_count;

} MSG_TBL;


// Shared Memory Fast Text Annotation Structure -------------

typedef struct
{
	// Word 1
	USHORT enable;			  // non-zero=enable this annotation string

	// Word 2
	USHORT col			:8;   // start column range = 0-63
	USHORT row			:8;   // start row    range = 0-31

	// Words 3 through 22
	// ** This character string is a standard C string, so
	//    it must be NULL terminated
	char   string[MAX_SM_USER_STRING_LEN+1];

} SM_USER_STRING_MSG;


// Mount Performance Data Structure -------------------------

typedef struct
{
	unsigned long	sequence;
	unsigned long	time_tag;

	float			az_delta_mount;
	float			az_mount;
	float			az_current_velocity;
	float			az_avg_mount_velocity;
	float			az_avg_mount_accel;
	float			az_error_signal;
	float			az_last_mount_drive;
	float			az_p_term;
	float			az_i_term;
	float			az_d_term;
	float			az_pid_out;
	float			az_vff_term;

	float			el_delta_mount;
	float			el_mount;
	float			el_current_velocity;
	float			el_avg_mount_velocity;
	float			el_avg_mount_accel;
	float			el_error_signal;
	float			el_last_mount_drive;
	float			el_p_term;
	float			el_i_term;
	float			el_d_term;
	float			el_pid_out;
	float			el_vff_term;

} SM_MOUNT_PERFORMANCE_DATA;


// -------------- Poll/Ping Message Structure ---------------
typedef struct
{
	// Word 1
	USHORT sync     :16;  // sync word

	// Word 2
	USHORT spare2	:8;   // spare bits
	USHORT msg_type :8;   // message type = 0

	// Word 3
	short  checksum :16;  // message checksum

} PING_MSG;

// ---------- Run Time Control Message Structure -----------
typedef struct
{
	// Word 1
	USHORT sync				:16;  // sync word

	// Word 2
	USHORT spare2			:6;   // spare bits
	USHORT act_qui			:1;   // Active/Quiet Command (0-quiet, 1-active) *** ALWAYS = 1 ***
	USHORT reset			:1;   // RESET command 1=reset (need 3 consecutive)
	USHORT msg_type			:8;   // message type = 1

	// Word 3
	USHORT spare3			:2;   // spare bits
	USHORT force_trk_acq	:1;   // force an update to the track/acquire cmd (0-idle 1-force)
	USHORT rmouse_button	:2;	  // right mouse button (0-idle, 1-down/pressed, 2-up/released)
	USHORT ath				:1;	  // threshold mode (0-manual, 1-auto)
	USHORT awp				:1;	  // window position mode (0-manual, 1-auto)
	USHORT aws				:1;	  // window size mode (0-manual, 1-auto)
	USHORT auto_trk			:1;	  // auto-track enable (0-disable, 1-enable)
	USHORT polarity			:3;	  // target polarity
	USHORT mode				:3;	  // Track Mode  (edge/centroid/correlation)
	USHORT trk_acq			:1;	  // track/acquire command (0-acquire, 1-track)

	// Word 4
	short  gtposx			:16;   // gate position X (pixel / 2)

	// Word 5
	short  gtposy			:16;   // gate position Y (line / 2)

	// Word 6
	USHORT gtsizx			:16;   // gate size X (pixels / 4)

	// Word 7
	USHORT gtsizy			:16;   // gate size Y (lines)

	// Word 8
	USHORT bkthrs			:10;  // manual black threshold level
	USHORT spare8			:6;   // SPACE KEEPER -- DO NOT REMOVE!

	// Word 9
	USHORT whthrs			:10;  // manual white threshold level
	USHORT spare9			:6;   // SPACE KEEPER -- DO NOT REMOVE

	// Word 10
	USHORT spare10			:16;  // spare word

	// Word 11
	short  checksum			:16;  // message checksum

} RUN_TIME_CTRL_MSG;

// ---------- System Control Message Structure -----------
typedef struct
{
	// Word 1
	USHORT sync				:16;	// sync word

	// Word 2
	USHORT vid_src			:4;		// video source selection code
									//   0=Analog1, 1=Analog2,  2=Analog3/Differential,
									//   3=Analog4, 4=Digital1, 5=Digital2
	USHORT out_60hz			:1;		// video rate (60 Hz) status output enable (0=disabled, 1=enabled)
	USHORT dualgates		:1;		// enable second gate (0=disabled, 1=enabled)
	USHORT rt_status_dest	:2;		// destination for video rate status output (0=both, 1=bus only, 2=serial only)
	USHORT msg_type			:8;		// message type = 2

	// Word 3
	USHORT auto_size_ratio	:16;	// auto size ratio (divide by 100 to get value)
									//    range: 1.00 to 655.35 (ex: 200 is a 2:1 gate to target ratio)
	// Word 4
	USHORT acquire_val_time	:8;		// acquire validation time in fields required to enter track
	USHORT vec_trans_time	:8;		// (vector track mode only) aim point transition time
									//   in fields when changing edges
	// Word 5
	USHORT awp_in_acquire	:1;		// allow auto gate position when in acquire mode (1=enable)
	USHORT aws_in_acquire	:1;		// allow auto gate size when in acquire mode (1=enable)
	USHORT aws_in_edge		:1;		// allow auto gate size when in edge mode (1=enable)
	USHORT centroid_in_edge :1;		// use the centroid projected in edge mode (1=enable)
	USHORT message_ack		:1;		// enable sending of message acknowledgments (1=enable)
	USHORT errors_in_acquire:1;		// allow target error output when in acquire mode (1=enable)
	USHORT slave_lens_fovs	:1;		// slave all configured lens FOVs to the currently selected camera/lens (1=enable)
	USHORT third_gate		:1;		// enable third gate (0=disabled, 1=enabled)
	USHORT extended_status	:1;		// enable the extended status bits in the STATUS_MSG (0=disabled, 1=enabled)
	USHORT spare5			:7;		// spare bits

	// Word 6
	short  checksum			:16;	// message checksum

} SYSTEM_CTRL_MSG;

// -------- Line Of Sight Control Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync     :16;  // sync word

	// Word 2
	USHORT spare2   :8;	  // spare bits
	USHORT msg_type :8;   // message type = 3

	// Word 3
	short  posx		:9;   // line-of-sight (boresight reticle) position X
	USHORT spare3   :7;   // spare bits

	// Word 4
	short  posy		:9;   // line-of-sight (boresight reticle) position Y
	USHORT spare4   :7;   // spare bits

	// Word 5
	short  checksum :16;  // message checksum

} LOS_OFFSET_CTRL_MSG;

// --------- Offset Aim Control Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync				:16;  // sync word

	// Word 2
	USHORT spare2			:7;   // spare bits
	USHORT ofaim_ena		:1;   // offset aim enable 0-disable, 1-enable
	USHORT msg_type			:8;   // message type = 4

	// Word 3
	short  posx				:9;   // offset-aim position(X)
	USHORT spare3			:7;   // spare bits

	// Word 4
	short  posy				:9;   // offset-aim position(Y)
	USHORT spare4			:7;   // spare bits

	// Word 5
	USHORT los_trans_time	:16;  // return to line of sight transition time in fields

	// Word 6
	short  checksum			:16;  // message checksum

} OFFSET_AIM_CTRL_MSG;

// -------- Symbology Control Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync			:16;  // sync word

	// Word 2
	USHORT spare2		:1;	  // spare bits
	USHORT los2_ena		:1;	  // show line of sight (boresight) reticle on unselected video output (8000 only)
	USHORT enh_data		:1;   // enhancement enable 0-off, 1-on
	USHORT symb_pol		:1;   // symbology color 0-black, 1-white
	USHORT trk_flag		:1;   // track flag symbol enable 0-off, 1-on
	USHORT trk_wind		:1;   // gate symbol enable 0-off, 1-on
	USHORT los_ena		:1;	  // line of sight (boresight) reticle enable 0-off, 1-on
	USHORT ofaim_ena	:1;	  // offset aim symbol enable 0-off, 1-on
	USHORT msg_type		:8;   // message type = 5

	// Word 3
	USHORT symb_color	:16;  // symbology color (0=use symb_pol, 1 to 1023)

	// Word 4
	short  checksum		:16;  // message checksum

} SYMBOLOGY_CTRL_MSG;

// --------- Correlation Control Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync				:16; // sync word

	// Word 2
	USHORT spare2			:8;  // spare bits
	USHORT msg_type			:8;  // message type = 6

	// Word 3
	USHORT ref_window		:1;  // reference window symbology 0-off, 1-on
	USHORT ref_image		:1;  // reference image display 0-off, 1-on
	USHORT ref_left			:1;  // move reference image left (re-center target)
	USHORT ref_right		:1;  // move reference image right (re-center target)
	USHORT ref_up			:1;  // move reference image up (re-center target)
	USHORT ref_down			:1;  // move reference image down (re-center target)
	USHORT spare3			:2;  // spare bits
	USHORT ref_speed		:8;  // speed when moving (re-centering) reference (1 to 16)

	// Word 4
	USHORT ref_sizex		:8;  // reference image size X (in pixels)
	USHORT ref_sizey		:8;  // reference image size Y (in lines)
								 //   The reference image size X and Y has a
								 //   minimum of 4, must be divisible by 4, maximum is 32
								 //   valid values are 4, 8, 12, 16, 20, 24, 28, 32

	// Word 5
	USHORT match_percent	:8;  // correlation match percent (0 to 100, 0=auto)
	USHORT update_rate		:8;  // reference image update rate in frames (0=no updates)

	// Word 6
	short  checksum			:16; // message checksum

} CORRELATION_CTRL_MSG;

// --------- Reserved Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync     :16;  // sync word

	// Word 2
	USHORT spare2   :8;   // spare bits
	USHORT msg_type :8;   // message type = 7

	// Word 3
	USHORT spare3	:16;  // spare word

	// Word 4
	short  checksum :16;  // message checksum

} RESERVED_MSG;

// --------- Filter Control Message Structure ---------
typedef struct
{
	// Word 1
	USHORT sync				:16; // sync word

	// Word 2
	USHORT pid_enable		:1;	 // PID compensation filter enable
	USHORT dig_fltr			:1;	 // digital video filter enable
	USHORT invert_el		:1;	 // invert elevation error
	USHORT invert_az		:1;	 // invert azimuth error
	USHORT fir_enable		:1;	 // FIR filter enable
	USHORT mount_pid_enable	:1;  // mount analog PID filter enable
	USHORT advanced_enable	:1;  // enable advanced PID filter features (only with mount feedback)
	USHORT spare2			:1;	 // spare bits
	USHORT msg_type			:8;	 // Message Type = 8

    // Words 3 to 9 -- X-Axis PID Filter Parameters
	// NOTE: All PID parameters are scaled by 1000 unless otherwise noted
	// Word 3
	short  gain_x;			 // gain

	// Word 4
	short  propor_x;		 // proportion

	// Word 5
	short  integ_x;			 // integral

	// Word 6
	short  deriv_x;			 // derivative

	// Word 7
	USHORT integ_clip_x;	 // integral clipping
							 //   with a scaling factor of 10 (ie: 0 to 6553.5)

	// Word 8
	short  vff_x;			 // velocity feed forward

	// Word 9
	short  aff_x;			 // acceleration feed forward

    // Words 10 to 16 -- Y-Axis PID Filter Parameters
	// NOTE: All PID parameters are scaled by 1000 unless otherwise noted
	// Word 10
	short  gain_y;			 // gain

	// Word 11
	short  propor_y;		 // proportion

	// Word 12
	short  integ_y;			 // integral

	// Word 13
	short  deriv_y;			 // derivative

	// Word 14
	USHORT integ_clip_y;	 // integral clipping
							 //   with a scaling factor of 10 (ie: 0 to 6553.5)

	// Word 15
	short  vff_y;			 // velocity feed forward

	// Word 16
	short  aff_y;			 // acceleration feed forward

	// Word 17
	USHORT fir_x			:8;	 // FIR filter x depth in fields
	USHORT fir_y			:8;	 // FIR filter y depth in fields

	// Word 18
	USHORT step_rsp_enable	:1;	 // step response filter enable
	USHORT spare18			:7;	 // spare bits
	USHORT step_percent		:8;  // percent of error for initial step (range: 0 to 100)

	// Word 19
	USHORT ramp_time;			 // step response filter time to ramp to full error (in fields)

	// Word 20
	short  checksum			:16; // message checksum

} FILTER_CTRL_MSG;

// --------- Coast Control Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync				:16;  // sync word

	// Word 2
	USHORT grow_rate		:2;   // gate growth rate selection
	USHORT mode				:2;   // coast mode selection
	USHORT cst_ena			:1;   // coast enable (0=disable, 1=enable)
	USHORT loop_mode		:1;	  // loop mode (0=closed, 1=open)
	USHORT gate_control		:1;   // enable manual gate size/position control during coast (0=disable, 1=enable)
	USHORT spare2			:1;   // spare bits
	USHORT msg_type			:8;   // message type = 9

	// Word 3
	USHORT duration			:16;  // coast duration (fields)

	// Word 4
	USHORT search			:4;	  // search mode
	USHORT spare4			:12;  // spare word

	// Word 5
	USHORT search_dur		:16;  // search duration (fields)
								  // 0=No Timeout/Search until target is found
	// Word 6
	short  checksum			:16;  // message checksum

} COAST_CTRL_MSG;

// --------- Target Validation Control Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync		:16;  // sync word

	// Word 2
	USHORT tql      :1;   // target validation (aka-track quality) enable
	USHORT sze      :1;   // size test enable
	USHORT pse      :1;   // position test enable
	USHORT nce      :1;   // n-count test enable
	USHORT gte		:1;   // target fully enclosed in gate test enable
	USHORT spare2   :3;   // spare bits
	USHORT msg_type	:8;   // message type = 10

	// Words 3 and 4
	USHORT size_x	:16;  // size tolerance in percent for x and y
	USHORT size_y	:16;  //   range: 0 to 6553.5% (divide by 10 to get value)

	// Words 5 and 6
	USHORT pos_x	:16;  // position tolerance in pixels for x and y
	USHORT pos_y	:16;  //   range: 0 to 6553.5 pixels (divide by 10 to get value)

	// Word 7
	USHORT ncount	:16;  // pixel count tolerance in percent
						  //   range: 0 to 6553.5% (divide by 10 to get value)
	// Word 8
	short  checksum :16;  // message checksum

} TGT_VALIDATION_CTRL_MSG;

// ------ Auto Acquire Control Message Structure ------
// THIS MESSAGE IS DEPRECATED, DO NOT USE
// PLEASE USE MULTI-TARGET INSTEAD.
typedef struct
{
	// Word 1
	USHORT sync			:16;  // sync word

	// Word 2
	USHORT spare2		:8;   // spare bits
	USHORT msg_type		:8;   // message type = 11

	// Word 3
	USHORT gtsizx		:11;  // acquire gate size x
	USHORT spare3		:5;   // spare bits

	// Word 4
	USHORT gtsizy		:11;  // acquire gate size y
	USHORT spare4		:5;   // spare bits

	// Word 5
	short  gtposx		:11;  // acquire gate position x
	USHORT auto_acquire :1;   // auto acquire enable
	USHORT spare5		:4;   // spare bits

	// Word 6
	short  gtposy		:11;  // acquire gate position y
	USHORT spare6		:5;   // spare bits

	// Word 7
	USHORT bkthrs		:10;  // black threshold
	USHORT ath		    :1;   // threshold mode (0-manual, 1-auto)
	USHORT spare7		:2;   // spare bits
	USHORT polarity		:3;	  // acquire target polarity code

	// Word 8
	USHORT whthrs		:10;  // white threshold
	USHORT spare8       :6;   // spare bits

	// Word 9
	USHORT spare9		:16;  // spare word

	// Word 10
	short  checksum		:16;  // message checksum

} AAQ_ACQUIRE_CTRL_MSG;

// ------ Auto Acquire Track Control Message Structure ------
// THIS MESSAGE IS DEPRECATED, DO NOT USE
// PLEASE USE MULTI-TARGET INSTEAD.
typedef struct
{
	// Word 1
	USHORT sync			:16;  // sync word

	// Word 2
	USHORT spare2		:8;   // spare bits
	USHORT msg_type		:8;   // message type = 12

	// Word 3
	USHORT gtsizx		:11;  // track gate size x
	USHORT aws			:1;   // gate auto size enable
	USHORT spare3		:4;   // spare bits

	// Word 4
	USHORT gtsizy		:11;  // track gate size y
	USHORT unique_track	:1;   // unique track parameters enable
	USHORT spare4		:4;   // spare bits

	// Word 5
	short  gtposx		:11;  // track gate position x
	USHORT awp			:1;   // gate auto position enable
	USHORT spare5		:4;   // spare bits

	// Word 6
	short  gtposy		:11;  // track gate position y
	USHORT spare6		:5;   // spare bits

	// Word 7
	USHORT bkthrs		:10;  // manual black threshold
	USHORT ath		    :1;   // threshold mode (0-manual, 1-auto)
	USHORT spare7		:2;   // spare bits
	USHORT polarity		:3;   // track target polarity code

	// Word 8
	USHORT whthrs		:10;  // manual white threshold
	USHORT spare8       :6;   // spare bits

	// Word 9
	USHORT spare9		:16;  // spare word

	// Word 10
	short  checksum		:16;  // message checksum

} AAQ_TRACK_CTRL_MSG;

// ------ Auto Acquire Target Select Control Message Structure ------
// THIS MESSAGE IS DEPRECATED, DO NOT USE
// PLEASE USE MULTI-TARGET INSTEAD.
typedef struct
{
	// Word 1
	USHORT sync			:16;  // sync word

	// Word 2
	USHORT spare2		:8;   // spare bits
	USHORT msg_type		:8;   // message type = 13

	// Word 3
	USHORT tsel_sizex   :10;  // tgt select size (X)
	USHORT tsel_ena		:1;	  // tgt select enable (0-disable, 1-enable)
	USHORT size_ena		:1;	  // select size enable
	USHORT aspect_ena	:1;	  // select aspect enable
	USHORT direct_ena	:1;	  // select direction enable
	USHORT speed_ena	:1;	  // select speed enable
	USHORT boresight_ena:1;	  // select boresight enable

	// Word 4
	USHORT tsel_sizey   :10;  // tgt select size (Y)
	USHORT spare4   	:6;   // spare bits

	// Word 5
	USHORT tsel_ratio   :2;   // tgt select aspect ratio code
	USHORT start_dir	:3;   // tgt select direction start angle
	USHORT end_dir  	:3;   // tgt select direction end angle
	USHORT size_tol     :7;   // tgt select size tolerance code (0 - 100%)
	USHORT spare5		:1;   // spare bit

	// Word 6
	USHORT tsel_speed	:9;	  // tgt select speed in pixels/field
	USHORT spare6		:7;   // spare bits

	// Word 7
	USHORT spare7		:16;  // spare word

	// Word 8
	short  checksum		:16;  // message checksum

} AAQ_TGT_SELECT_CTRL_MSG;

// ---------- Annotation Message Structure ----------
typedef struct
{
   	// Word 1
	USHORT sync						:16;  // sync word

	// Word 2
	USHORT anno_en					:1;   // global text annotation enable
	USHORT anno_color				:1;   // annotation color (0=black on gray, 1=white on gray)
	USHORT spare2					:6;   // spare bits
	USHORT msg_type					:8;   // message type = 14

	// Word 3
	USHORT show_mode				:1;   // track mode display enable
	USHORT show_pol					:1;   // track polarity display enable
	USHORT show_state				:1;   // track state display enable
	USHORT show_status				:1;   // target status display enable
	USHORT show_auto				:1;   // auto controls display enable
	USHORT show_az					:1;   // azimuth error signal display enable
	USHORT show_el					:1;   // elevation error signal display enable
	USHORT show_tval				:1;   // target validation selection display enable
	USHORT show_mount_az			:1;   // mount azimuth feedback display enable
	USHORT show_mount_el			:1;   // mount elevation feedback display enable
	USHORT show_mount_velocity_az	:1;   // mount velocity azimuth display enable
	USHORT show_mount_velocity_el	:1;   // mount velocity elevation display enable
	USHORT show_range				:1;	  // target range display enable
	USHORT show_lens_fov			:1;   // current lens field-of-view display enable
	USHORT show_unselected_video	:1;	  // show annotations on unselected video output (8000 only)
	USHORT spare3					:1;   // spare bits

	// Word 4
	USHORT foreground_color			:8;	  // annotation foreground color (0=transparent, 1=black to 255=white)
	USHORT background_color			:8;	  // annotation background color (0=transparent, 1=black to 255=white)
										  //   if both colors are set to 0, then the anno_color variable is
										  //   used to determine the colors (the legacy behavior)
	// Word 5
	short  checksum					:16;  // message checksum

} ANNOTATION_MSG;

// ---------- User String Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync			:16;  // sync word

	// Word 2
	USHORT spare2		:8;   // spare bits
	USHORT msg_type		:8;   // message type = 15

	// Word 3
	USHORT col			:6;   // start column range = 0-63
	USHORT row			:5;   // start row    range = 0-31
	USHORT spare3		:5;   // spare bits

	// ** This character string is a standard C string, so
	//    it must be NULL terminated
	char   string[MAX_USER_STRING_LEN+1];

	// Word (4 + (MAX_USER_STRING_LEN+1)/2)
	short  checksum		:16;  // message checksum

} USER_STRING_MSG;

// -------------- Scan Message Structure --------------
typedef struct
{
	// Word 1
	USHORT sync				:16;  // sync word

	// Word 2
	USHORT spare2			:8;   // spare bits
	USHORT msg_type			:8;   // msg type = 16

	// Word 3
	USHORT enable			:1;   // enable scan mode (0=disabled/stop, 1=enabled/start)
	USHORT reset			:1;   // move to start location and reset scan (1=reset)
	USHORT acq_targets		:1;   // acquire targets while in scan (0=disabled, 1=enabled)
	USHORT enable_joystick	:1;   // enable joystick during scan (0=disable, 1=enabled)
	USHORT spare3			:4;   // spare bits
	USHORT type				:8;	  // type of scan (0=line, 1=horizontal raster, ...)

	// Word 4
	USHORT step_az			:16;  // scan steps in azimuth (X)
								  //   or step per 360 degrees in spiral mode

	// Word 5
	USHORT step_el			:16;  // scan steps in elevation (Y)
								  //   or growth factor in spiral mode (divide by 1000 to get value)

	// Word 6
	USHORT dwell_time		:16;  // scan dwell time in fields

	// Word 7 & 8
	short   start_az_lsw	:16;  // start azimuth of mount in degrees, least significant word (lsw)
	short   start_az_msw	:16;  // and most significant word (msw) (divide by 10000 to get value)

	// Word 9 & 10
	short   start_el_lsw	:16;  // start elevation of mount in degrees, least significant word (lsw)
	short   start_el_msw	:16;  // and most significant word (msw) (divide by 10000 to get value)

	// Word 11 & 12
	short   stop_az_lsw		:16;  // stop azimuth of mount in degrees, least significant word (lsw)
	short   stop_az_msw		:16;  // and most significant word (msw) (divide by 10000 to get value)

	// Word 13 & 14
	short   stop_el_lsw		:16;  // stop elevation of mount in degrees, least significant word (lsw)
	short   stop_el_msw		:16;  // and most significant word (msw) (divide by 10000 to get value)

	// Word 15
	USHORT	spare15			:16;  // spare word

	// Word 16
	short checksum			:16;  // checksum

} SCAN_MSG;

// -------------- Mount Rate Drive Message Structure --------------
typedef struct
{
	// Word 1
	USHORT	sync			:16;  // sync word

	// Word 2
	USHORT  velocity_dac	:1;	 // 0=velocity in degrees/sec, 1=velocity in DAC counts
	USHORT	spare2			:7;   // spare bits
	USHORT	msg_type		:8;   // msg type = 17

	// Word 3 & 4
	short   velocity_az_lsw	:16;  // the azimuth velocity to drive the mount
	short   velocity_az_msw	:16;  // least significant word (lsw) and most significant word (msw)
								  // (degrees/sec: multiply float by 1000 to set value)
								  // (DAC counts: signed 32-bit integer)

	// Word 5 & 6
	short   velocity_el_lsw	:16;  // the elevation velocity to drive the mount
	short   velocity_el_msw	:16;  // least significant word (lsw) and most significant word (msw)
								  // (degrees/sec: multiply float by 1000 to set value)
								  // (DAC counts: signed 32-bit integer)

	// Word 7
	short	checksum		:16;  // checksum

} MOUNT_RATE_DRIVE_MSG;

// -------------- Mount Control Message Structure --------------
typedef struct
{
	// Word 1
	USHORT	sync			:16;  // sync word

	// Word 2
	USHORT	spare2			:8;   // spare bits
	USHORT	msg_type		:8;   // msg type = 18

	// Word 3
	USHORT	command			:8;  // see mount command defines (0=no action)
	USHORT  velocity_dac	:1;	 // 0=velocity in degrees/sec, 1=velocity in DAC counts
	USHORT  loop_move		:1;	 // 1=loop the movement command, moving back and forth
	USHORT  position_track	:1;  // enable the position mode tracking filter in the mount (1=enabled)
	USHORT  limit_velocity	:1;  // enable velocity limiting (use MOUNT_SET_VELOCITY_LIMITS command to set)
	USHORT	spare3			:4;  // spare bits

	// Word 4 & 5
	short   azimuth_lsw		:16;  // the target azimuth position of the mount in degrees
	short   azimuth_msw		:16;  // least significant word (lsw) and most significant word (msw)
								  // (multiply float by 10,000 to set value)

	// Word 6 & 7
	short   elevation_lsw	:16;  // the target elevation position of the mount in degrees
	short   elevation_msw	:16;  // least significant word (lsw) and most significant word (msw)
								  // (multiply float by 10,000 to set value)

	// Word 8 & 9
	short   velocity_az_lsw	:16;  // the target azimuth velocity of the mount during the move
	short   velocity_az_msw	:16;  // least significant word (lsw) and most significant word (msw)
								  // (degrees/sec: multiply float by 1000 to set value)
								  // (DAC counts: signed 32-bit integer)
								  // 0=Maximum velocity of mount

	// Word 10 & 11
	short   velocity_el_lsw	:16;  // the target elevation velocity of the mount during the move
	short   velocity_el_msw	:16;  // least significant word (lsw) and most significant word (msw)
								  // (degrees/sec: multiply float by 1000 to set value)
								  // (DAC counts: signed 32-bit integer)
								  // 0=Maximum velocity of mount

	// Word 12
	USHORT	duration		:16;  // MOUNT_DRIVE_AZ_EL: the number of video fields to drive the mount

	// Word 13
	USHORT  ramp_accelerate	:8;	  // the number of video fields to ramp up to the target velocity
	USHORT  ramp_decelerate	:8;	  // the number of video fields to ramp down the velocity before
								  //   reaching the target position
								  // 0=no ramp / step function

	// Word 14
	short	checksum		:16;  // checksum

} MOUNT_CONTROL_MSG;

// ---------- Control Box Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync			:16;  // sync word

	// Word 2
	USHORT spare2		:8;   // spare bits
	USHORT msg_type		:8;   // message type = 19

	// Word 3
	USHORT enable_box	:1;   // enable the control box (1=enabled)
							  // if enabled, tracker will ignore all
							  // RUN_TIME_CTRL_MSG messages
	USHORT spare3		:15;

	// Word 4
	short  checksum		:16;  // message checksum

} CONTROL_BOX_MSG;

// ---------- Query Config Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync			:16;  // sync word

	// Word 2
	USHORT spare2		:8;   // spare bits
	USHORT msg_type		:8;   // message type = 20

	// Word 3
	USHORT get_msg_type	:8;   // requested message number for the tracker to
							  //   respond with its current configuration
	USHORT get_msg_id	:8;   // message specific data to identify a unique message
							  //   (only necessary for some messages)

	// Word 4
	short  checksum		:16;  // message checksum

} QUERY_CONFIG_MSG;

// ---------- Preset Config Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync			:16;  // sync word

	// Word 2
	USHORT spare2		:8;   // spare bits
	USHORT msg_type		:8;   // message type = 21

	// Word 3
	USHORT command		:16;  // preset configuration command (save/load/clear)

	// Word 4
	USHORT config_bank	:16;  // preset configuration bank (0-9)

	// Word 5
	USHORT spare5		:16;  // spare word

	// Word 6
	short  checksum		:16;  // message checksum

} PRESET_CONFIG_MSG;

// ---------- Lens Config Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync			:16;  // sync word

	// Word 2
	USHORT spare2		:8;   // spare bits
	USHORT msg_type		:8;   // message type = 22

	// Word 3
	USHORT analog1		:16;  // lens connected to analog video source 1

	// Word 4
	USHORT analog2		:16;  // lens connected to analog video source 2

	// Word 5
	USHORT analog3		:16;  // lens connected to analog video source 3
							  // (differential input on Model 6005 R2)

	// Word 6
	USHORT analog4		:16;  // lens connected to analog video source 4
							  // (not available on Model 6005 R2)

	// Word 7
	USHORT digital1		:16;  // lens connected to digital video source 1

	// Word 8
	USHORT digital2		:16;  // lens connected to digital video source 2
							  // (not available on Model 6005 and only
							  //  supported on 6007 with daughter card)

	// Word 9
	USHORT spare9		:16;  // spare word

	// Word 10
	short  checksum		:16;  // message checksum

} LENS_CONFIG_MSG;

// ---------- Lens Graflex Config Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync				:16;  // sync word

	// Word 2
	USHORT spare2			:8;   // spare bits
	USHORT msg_type			:8;   // message type = 23

	// Word 3
	USHORT zoom_cmd			:3;  // zoom command (0=none, 1=narrow, 2=wide, 3=go to pos)
	USHORT focus_cmd		:3;	 // focus command (0=none, 1=near, 2=far)
	USHORT iris_cmd			:3;  // iris command (0=none, 1=close, 2=open)
	USHORT iris_auto		:1;	 // automatic iris (0=disabled, 1=enabled)
	USHORT zoom_cal			:1;  // perform zoom scale calibration (1=run now)
	USHORT spare3			:5;  // spare bits

	// Word 4
	USHORT zoom_pos			:16;  // zoom position

	// Word 5
	USHORT min_zoom_gain	:16;  // limit on minimum zoom gain (0 to .99999)
								  //   no decimal and 16 bits of precision

	// Word 6
	USHORT max_zoom_gain	:16;  // limit on maximum zoom gain (0 to .99999)
								  //   no decimal and 16 bits of precision

	// Word 7
	USHORT spare7			:16;  // spare word

	// Word 8
	short  checksum			:16;  // message checksum

} LENS_GRAFLEX_MSG;

// ---------- Lens Serial Triple FOV Config Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync				:16;  // sync word

	// Word 2
	USHORT spare2			:8;   // spare bits
	USHORT msg_type			:8;   // message type = 24

	// Word 3
	USHORT video_source		:4;   // video source lens is connected to
	USHORT serial_port		:3;   // tracker serial port lens is connected to (3-7, 0-2 are reserved)
	USHORT fov_cmd			:2;   // field of view command/status (0=none, 1=wide, 2=medium, 3=narrow)
	USHORT focus_cmd		:2;	  // focus command (0=none, 1=near, 2=far)
	USHORT iris_cmd			:2;   // iris command (0=none, 1=close, 2=open)
	USHORT iris_auto		:1;	  // automatic iris (0=disabled, 1=enabled)
	USHORT not_present		:1;   // lens is not present and not communicating with the tracker (query only)
	USHORT error_detected	:1;   // lens communication error(s) detected (query only)

	// Word 4
	USHORT fov_wide			:16;  // wide field-of-view of the lens in degrees
								  //   range: 0 to 360.00 (divide by 100 to get value)

	// Word 5
	USHORT fov_medium		:16;  // medium field-of-view of the lens in degrees
								  //   range: 0 to 360.00 (divide by 100 to get value)

	// Word 6
	USHORT fov_narrow		:16;  // narrow field-of-view of the lens in degrees
								  //   range: 0 to 360.00 (divide by 100 to get value)

	// Words 7 & 8
	short  los_wide_x		:16;  // line of sight (boresight) offset for wide FOV
	short  los_wide_y		:16;

	// Words 9 & 10
	short  los_medium_x		:16;  // line of sight (boresight) offset for medium FOV
	short  los_medium_y		:16;

	// Words 11 & 12
	short  los_narrow_x		:16;  // line of sight (boresight) offset for narrow FOV
	short  los_narrow_y		:16;

	// Word 13
	USHORT focus_wide		:16;  // focus setting for the wide field of view

	// Word 14
	USHORT focus_medium		:16;  // focus setting for the medium field of view

	// Word 15
	USHORT focus_narrow		:16;  // focus setting for the narrow field of view

	// Word 16
	short  checksum			:16;  // message checksum

} LENS_SERIAL_TFOV_MSG;

// ---------- Lens Serial Dual FOV Config Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync				:16;  // sync word

	// Word 2
	USHORT spare2			:8;   // spare bits
	USHORT msg_type			:8;   // message type = 25

	// Word 3
	USHORT video_source		:4;   // video source lens is connected to
	USHORT serial_port		:3;   // tracker serial port lens is connected to (3-7, 0-2 are reserved)
	USHORT fov_cmd			:2;   // field of view command/status (0=none, 1=wide, 2=narrow)
	USHORT focus_cmd		:2;   // focus command (0=none, 1=near, 2=far)
	USHORT iris_cmd			:2;   // iris command (0=none, 1=close, 2=open)
	USHORT iris_auto		:1;   // automatic iris (0=disabled, 1=enabled)
	USHORT not_present		:1;   // lens is not present and not communicating with the tracker (query only)
	USHORT error_detected	:1;   // lens communication error(s) detected (query only)

	// Word 4
	USHORT fov_wide			:16;  // wide field-of-view of the lens in degrees
								  //   range: 0 to 360.00 (divide by 100 to get value)
	// Word 5
	USHORT fov_narrow		:16;  // narrow field-of-view of the lens in degrees
								  //   range: 0 to 360.00 (divide by 100 to get value)
	// Words 6 & 7
	short  los_wide_x		:16;  // line of sight (boresight) offset for wide FOV
	short  los_wide_y		:16;

	// Words 8 & 9
	short  los_narrow_x		:16;  // line of sight (boresight) offset for narrow FOV
	short  los_narrow_y		:16;

	// Word 10
	USHORT focus_wide		:16;  // focus setting for the wide field of view

	// Word 11
	USHORT focus_narrow		:16;  // focus setting for the narrow field of view

	// Word 12
	short  checksum			:16;  // message checksum

} LENS_SERIAL_DFOV_MSG;

// ---------- Lens Generic Config Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync			:16;  // sync word

	// Word 2
	USHORT spare2		:8;   // spare bits
	USHORT msg_type		:8;   // message type = 26

	// Word 3
	USHORT video_source	:4;   // video source lens is connected to
	USHORT use_fov		:1;	  // use the lens field-of-view parameter instead of raw mount gain
	USHORT spare3		:11;  // spare bits

	// Word 4
	USHORT mount_gain	:16;  // mount gain (only set if use_fov = 0)
							  //   scaled by 2048 (ie: 0 to 31.999)

	// Word 5
	USHORT lens_fov		:16;  // lens field-of-view in degrees (only set if use_fov = 1)
							  //   range: 0 to 360.00 (divide by 100 to get value)
	// Word 6
	short  checksum		:16;  // message checksum

} LENS_GENERIC_MSG;

// ---------- Lens Serial Zoom Config Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync				:16;  // sync word

	// Word 2
	USHORT lens_id			:8;   // some lenses have an ID number in their serial protocol (LENS_COHU_MPC)
	USHORT msg_type			:8;   // message type = 27

	// Word 3
	USHORT lens_type		:16;  // lens type

	// Word 4
	USHORT video_source		:4;   // video source lens is connected to
	USHORT serial_port		:3;   // tracker serial port lens is connected to (3-7, 0-2 are reserved)
	USHORT zoom_cmd			:3;   // zoom command (0=none, 1=narrow, 2=wide, 3=go to pos)
	USHORT focus_cmd		:3;	  // focus command (0=none, 1=near, 2=far, 3=go to pos, 4=auto)
	USHORT iris_cmd			:2;   // iris command (0=none, 1=close, 2=open)
	USHORT iris_auto		:1;	  // automatic iris (0=disabled, 1=enabled/automatic)

	// Word 5
	USHORT zoom_cal			:1;   // perform zoom scale calibration (1=run now)
	USHORT use_old_protocol	:1;	  // use older lens communication protocol (LENS_COHU_MPC)
	USHORT enable_2x		:1;   // enable 2X extender (LENS_FUJINON_D60 and others)
	USHORT spare5_1			:1;
	USHORT osd_command		:4;	  // button-press command (keypad emulation) for camera on-screen display (OSD)
	USHORT filter_select	:4;	  // filter select, support is lens dependent (0=none, 1=??? ...)
	USHORT spare5_2			:2;
	USHORT not_present		:1;	  // lens is not present and not communicating with the tracker (query only)
	USHORT error_detected	:1;	  // lens communication error(s) detected (query only)

	// Word 6
	USHORT zoom_fov			:16;  // zoom field-of-view in degrees
								  //   range: 0 to 360.00 (divide by 100 to get value)

	// Word 7
	USHORT min_fov			:16;  // minimum zoom field-of-view of the lens in degrees
								  //   range: 0 to 360.00 (divide by 100 to get value)

	// Word 8
	USHORT max_fov			:16;  // maximum zoom field-of-view of the lens in degrees
								  //   range: 0 to 360.00 (divide by 100 to get value)

	// Word 9
	USHORT zoom_speed		:8;   // zoom speed control  (0=automatic, 1 through 100% for fixed speed)
	USHORT focus_speed		:8;   // focus speed control (0=automatic, 1 through 100% for fixed speed)

	// Word 10
	USHORT spare10			:16;

	// Word 11
	USHORT focus_pos		:16;  // focus position

	// Word 12
	short  checksum			:16;  // message checksum

} LENS_SERIAL_ZOOM_MSG;

// ---------- Lens Serial IR Zoom Config Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync				:16;  // sync word

	// Word 2
	USHORT spare2			:8;   // spare bits
	USHORT msg_type			:8;   // message type = 28

	// Word 3
	USHORT lens_type		:16;  // lens type

	// Word 4
	USHORT video_source		:4;   // video source lens is connected to
	USHORT serial_port		:3;   // tracker serial port lens is connected to (3-7, 0-2 are reserved)
	USHORT zoom_cmd			:3;   // zoom command (0=none, 1=narrow, 2=wide, 3=go to pos)
	USHORT zoom_cal			:1;   // perform zoom scale calibration (1=run now)
	USHORT focus_cmd		:3;	  // focus command (0=none, 1=near, 2=far, 3=go to pos, 4=auto)
	USHORT polarity			:1;	  // image polarity (0=normal/white hot, 1=inverted/black hot)
	USHORT agc				:1;	  // automatic gain control (0=disabled, 1=enabled/automatic)

	// Word 5
	USHORT day_mode			:1;   // day mode enable (0=disabled/night, 1=enabled/day)
	USHORT high_sensitivity	:1;	  // high sensitivity enable (0=disabled/normal, 1=enabled/high)
	USHORT auto_calibration	:1;	  // auto calibration enable (0=disabled, 1=enabled)
	USHORT lens_cover_off	:1;	  // remove lens cover control
	USHORT osd_command		:4;	  // button-press command (keypad emulation) for camera on-screen display (OSD)
	USHORT atherm_enable	:1;   // athermalization / focus temperature correction (0=disabled, 1=enabled)
	USHORT full_nuc			:1;	  // perform a full/complete NUC (1=run now)
	USHORT focus_to_range	:1;   // focus to range enable (0=disabled, 1=enabled)
	USHORT spare5			:3;
	USHORT not_present		:1;	  // lens is not present and not communicating with the tracker (query only)
	USHORT error_detected	:1;	  // lens communication error(s) detected (query only)

	// Word 6
	USHORT manual_gain		:16;  // sensor gain (when AGC is disabled)

	// Word 7
	USHORT manual_offset	:16;  // sensor offset (when AGC is disabled)

	// Word 8
	USHORT nuc_table		:16;  // non-uniformity correction table to apply (OBSOLETE)

	// Word 9
	USHORT zoom_fov			:16;  // zoom field-of-view in degrees
								  //   range: 0 to 360.00 (divide by 100 to get value)

	// Word 10
	USHORT min_fov			:16;  // minimum zoom field-of-view of the lens in degrees
								  //   range: 0 to 360.00 (divide by 100 to get value)

	// Word 11
	USHORT max_fov			:16;  // maximum zoom field-of-view of the lens in degrees
								  //   range: 0 to 360.00 (divide by 100 to get value)

	// Word 12
	USHORT zoom_speed		:8;   // zoom speed control  (0=automatic, 1 through 100% for fixed speed)
	USHORT focus_speed		:8;   // focus speed control (0=automatic, 1 through 100% for fixed speed)

	// Word 13
	USHORT spare13			:16;

	// Word 14
	USHORT focus_pos		:16;  // focus position

	// Word 15
	USHORT spare15			:16;

	// Word 16
	short  checksum			:16;  // message checksum

} LENS_SERIAL_IR_ZOOM_MSG;

// ---------- Lens Analog Zoom Config Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync				:16;  // sync word

	// Word 2
	USHORT spare2			:8;   // spare bits
	USHORT msg_type			:8;   // message type = 29

	// Word 3
	USHORT video_source		:4;   // video source lens is connected to
	USHORT spare3			:4;   // spare bits
	USHORT zoom_feedback	:8;   // analog input channel to use for zoom position feedback
								  //   (0 = disabled, 1-8 = tracker analog input,
								  //    9 = 702 controller lens input 1,
								  //    10= 702 controller lens input 2)
	// Word 4
	short  gain				:16;  // input voltage gain (divide by 100 to get value)
								  //   x = gain * (input voltage + bias)
	// Word 5
	short  bias				:16;  // input voltage bias (divide by 100 to get value)
								  //   x = gain * (input voltage + bias)
	// Word 6
	short  coeff0			:16;  // polynomial coefficient 0 (divide by 10000 to get value)
								  //   field of view = (coeff2 * x * x) + (coeff1 * x) + coeff0
	// Word 7
	short  coeff1			:16;  // polynomial coefficient 1 (divide by 10000 to get value)
								  //   field of view = (coeff2 * x * x) + (coeff1 * x) + coeff0
	// Word 8
	short  coeff2			:16;  // polynomial coefficient 2 (divide by 10000 to get value)
								  //   field of view = (coeff2 * x * x) + (coeff1 * x) + coeff0
	// Word 9
	USHORT spare9			:16;

	// Word 10
	short  zoom_voltage		:16;  // current zoom feedback voltage before adjustment (as seen by tracker)
								  //   tracker range: -10.000 to 10.000 (divide by 1000 to get value)
								  //   controller range:    0 to 10.000 (divide by 1000 to get value)
	// Word 11
	USHORT zoom_fov			:16;  // current zoom field-of-view in degrees (as calculated by tracker)
								  //   range: 0 to 360.00 (divide by 100 to get value)
	// Word 12
	USHORT min_fov			:16;  // minimum zoom field-of-view of the lens in degrees (narrow)
								  //   range: 0 to 360.00 (divide by 100 to get value)
	// Word 13
	USHORT max_fov			:16;  // maximum zoom field-of-view of the lens in degrees (wide)
								  //   range: 0 to 360.00 (divide by 100 to get value)
	// Word 14
	short  checksum			:16;  // message checksum

} LENS_ANALOG_ZOOM_MSG;

// ---------- Camera Config Message Structure ----------
// THIS MESSAGE IS DEPRECATED, DO NOT USE
typedef struct
{
	// Word 1
	USHORT sync			:16;  // sync word

	// Word 2
	USHORT spare2		:8;   // spare bits
	USHORT msg_type		:8;   // message type = 30

	// Word 3
	USHORT analog1		:16;  // camera connected to analog video source 1

	// Word 4
	USHORT analog2		:16;  // camera connected to analog video source 2

	// Word 5
	USHORT analog3		:16;  // camera connected to analog video source 3
							  // (differential input on Model 6005 R2)

	// Word 6
	USHORT analog4		:16;  // camera connected to analog video source 4
							  // (not available on Model 6005 R2)

	// Word 7
	USHORT digital1		:16;  // camera connected to digital video source 1

	// Word 8
	USHORT digital2		:16;  // camera connected to digital video source 2
							  // (not available on Model 6005 and only
							  //  supported on 6007 with daughter card)

	// Word 9
	USHORT spare9		:16;  // spare word

	// Word 10
	short  checksum		:16;  // message checksum

} CAMERA_CONFIG_MSG;

// ---------- Camera Generic Config Message Structure ----------
// THIS MESSAGE IS DEPRECATED, DO NOT USE
typedef struct
{
	// Word 1
	USHORT sync			:16;  // sync word

	// Word 2
	USHORT spare2		:8;   // spare bits
	USHORT msg_type		:8;   // message type = 31

	// Word 3
	USHORT video_source	:4;   // video source lens is connected to
	USHORT serial_port	:3;   // tracker serial port camera is connected to (3-7, 0-2 are reserved)
	USHORT agc			:1;	  // automatic gain control (1=enabled)
	USHORT spare3		:8;   // spare bits

	// Word 4
	USHORT manual_gain	:16;  // sensor gain (when AGC is disabled)

	// Word 5
	USHORT nuc_table	:16;  // non-uniformity correction table to apply

	// Word 6
	USHORT spare6		:16;  // spare word

	// Word 7
	USHORT spare7		:16;  // spare word

	// Word 8
	USHORT spare8		:16;  // spare word

	// Word 9
	USHORT spare9		:16;  // spare word

	// Word 10
	short  checksum		:16;  // message checksum

} CAMERA_GENERIC_MSG;

// ---------- Lens Serial Fixed FOV Config Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync				:16;  // sync word

	// Word 2
	USHORT lens_id			:8;   // some lenses have an ID character in their serial protocol (send as type char)
	USHORT msg_type			:8;   // message type = 32

	// Word 3
	USHORT lens_type		:16;  // lens type

	// Word 4
	USHORT video_source		:4;   // video source lens is connected to
	USHORT serial_port		:3;   // tracker serial port lens is connected to (3-7, 0-2 are reserved)
	USHORT focus_cmd		:2;	  // focus command (0=none, 1=near, 2=far, 3=go to pos)
	USHORT iris_cmd			:2;   // iris command (0=none, 1=close, 2=open)
	USHORT iris_auto		:1;	  // automatic iris (0=disabled, 1=enabled)
	USHORT atherm_enable	:1;   // athermalization / focus temperature correction (0=disabled, 1=enabled)
	USHORT focus_to_range	:1;   // focus to range tracking (0=disabled, 1=enabled)
	USHORT not_present		:1;	  // lens is not present and not communicating with the tracker (query only)
	USHORT error_detected	:1;	  // lens communication error(s) detected (query only)

	// Word 5
	USHORT lens_fov			:16;  // lens field-of-view in degrees
								  //   range: 0 to 360.00 (divide by 100 to get value)
	// Word 6
	USHORT focus			:16;  // current focus setting
								  //   for type LENS_OFFICINA_STELLARE_FOCUSER, this is a signed value (short)
	// Word 7
	USHORT focus_speed		:8;   // focus speed control (0=automatic, 1 through 100% for fixed speed)
	USHORT spare7			:8;

	// Word 8
	short  checksum			:16;  // message checksum

} LENS_SERIAL_FIXED_FOV_MSG;

// ---------- Lens Serial IR Dual FOV Config Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync				:16;  // sync word

	// Word 2
	USHORT spare2			:8;   // spare bits
	USHORT msg_type			:8;   // message type = 33

	// Word 3
	USHORT lens_type		:16;  // lens type

	// Word 4
	USHORT video_source		:4;   // video source lens is connected to
	USHORT serial_port		:3;   // tracker serial port lens is connected to (3-7, 0-2 are reserved)
	USHORT fov_cmd			:2;   // field of view command/status (0=none, 1=wide, 2=narrow)
	USHORT focus_cmd		:3;	  // focus command (0=none, 1=near, 2=far, 3=go to pos, 4=auto)
	USHORT polarity			:1;	  // image polarity (0=normal/white hot, 1=inverted/black hot)
	USHORT auto_offset		:1;   // automatic offset/level/bias control (0=disabled, 1=enabled/automatic)
	USHORT auto_gain		:1;	  // automatic gain control (0=disabled, 1=enabled/automatic)
	USHORT spare4			:1;

	// Word 5
	USHORT run_partial_nuc	:1;	  // run partial/quick non-uniformity correction command (1=run now)
	USHORT run_full_nuc		:1;	  // run full non-uniformity correction command (1=run now)
	USHORT not_present		:1;   // lens is not present and not communicating with the tracker (query only)
	USHORT error_detected	:1;   // lens communication error(s) detected (query only)
	USHORT spare5			:4;
	USHORT nuc_table		:8;   // non-uniformity correction (equalization) table to apply

	// Word 6
	USHORT manual_offset	:16;  // sensor offset/level/bias setting

	// Word 7
	USHORT manual_gain		:16;  // sensor gain setting

	// Word 8
	USHORT fov_wide			:16;  // wide field-of-view of the lens in degrees
								  //   range: 0 to 360.00 (divide by 100 to get value)
	// Word 9
	USHORT fov_narrow		:16;  // narrow field-of-view of the lens in degrees
								  //   range: 0 to 360.00 (divide by 100 to get value)
	// Words 10 & 11
	short  los_wide_x		:16;  // line of sight (boresight) offset for wide FOV
	short  los_wide_y		:16;

	// Words 12 & 13
	short  los_narrow_x		:16;  // line of sight (boresight) offset for narrow FOV
	short  los_narrow_y		:16;

	// Word 14
	USHORT focus_wide		:16;  // focus setting for the wide field of view

	// Word 15
	USHORT focus_narrow		:16;  // focus setting for the narrow field of view

	// Word 16
	short  checksum			:16;  // message checksum

} LENS_SERIAL_IR_DFOV_MSG;

// ---------- Lens Moog Zoom Config Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync				:16;  // sync word

	// Word 2
	USHORT spare2			:8;
	USHORT msg_type			:8;   // message type = 34

	// Word 3
	USHORT lens_type		:16;  // lens type

	// Word 4
	USHORT video_source		:4;   // video source lens is connected to
	USHORT zoom_cmd			:3;   // zoom command (0=none, 1=narrow, 2=wide, 3=go to pos)
	USHORT focus_cmd		:3;	  // focus command (0=none, 1=near, 2=far, 3=go to pos, 4=auto)
	USHORT monochrome		:1;   // set camera to monochrome mode (0=color, 1=monochrome)
	USHORT filter_enable	:1;   // apply lens filter (0=none, 1=monochrome with filter)
	USHORT spare4			:4;

	// Word 5
	USHORT spare5			:16;

	// Word 6
	USHORT focus_pos		:16;  // lens focus position feedback (0 to 255)

	// Word 7
	USHORT zoom_pos			:16;  // lens zoom position feedback (0 to 255)

	// Word 8
	USHORT zoom_fov			:16;  // zoom field-of-view in degrees
								  //   range: 0 to 360.00 (divide by 100 to get value)
	// Word 9
	USHORT min_fov			:16;  // minimum zoom field-of-view of the lens in degrees
								  //   range: 0 to 360.00 (divide by 100 to get value)
	// Word 10
	USHORT max_fov			:16;  // maximum zoom field-of-view of the lens in degrees
								  //   range: 0 to 360.00 (divide by 100 to get value)
	// Word 11
	short  zoom_gain		:16;  // input zoom position gain (divide by 100 to get value)
								  //   x = zoom_gain * (zoom_pos + zoom_bias)
	// Word 12
	short  zoom_bias		:16;  // input zoom position bias (divide by 100 to get value)
								  //   x = zoom_gain * (zoom_pos + zoom_bias)
	// Word 13 & 14
	float  zoom_coeff0;			  // polynomial coefficient 0 (32-bit IEEE 754 value)
								  //   field of view = (coeff3 * x^3) + (coeff2 * x^2) + (coeff1 * x) + coeff0
	// Word 15 & 16
	float  zoom_coeff1;			  // polynomial coefficient 1 (32-bit IEEE 754 value)
								  //   field of view = (coeff3 * x^3) + (coeff2 * x^2) + (coeff1 * x) + coeff0
	// Word 17 & 18
	float  zoom_coeff2;			  // polynomial coefficient 2 (32-bit IEEE 754 value)
								  //   field of view = (coeff3 * x^3) + (coeff2 * x^2) + (coeff1 * x) + coeff0
	// Word 19 & 20
	float  zoom_coeff3;			  // polynomial coefficient 3 (32-bit IEEE 754 value)
								  //   field of view = (coeff3 * x^3) + (coeff2 * x^2) + (coeff1 * x) + coeff0
	// Word 21
	USHORT zoom_speed		:8;   // zoom speed control  (0=automatic, 1 through 127 for fixed speed)
	USHORT focus_speed		:8;   // focus speed control (0=automatic, 1 through 127 for fixed speed)

	// Word 22
	short  checksum			:16;  // message checksum

} LENS_MOOG_ZOOM_MSG;


// ---------- Analog Input Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync			:16;  // sync word

	// Word 2
	USHORT spare2		:8;   // spare bits
	USHORT msg_type		:8;   // message type = 40

	// analog 0-7 scale to +/-10 volts using the following equation
	//   volts = analog * 10/32767

	// Word 3
	short  analog0		:16;  // ADC value for analog input 0

	// Word 4
	short  analog1		:16;  // ADC value for analog input 1

	// Word 5
	short  analog2		:16;  // ADC value for analog input 2

	// Word 6
	short  analog3		:16;  // ADC value for analog input 3

	// Word 7
	short  analog4		:16;  // ADC value for analog input 4

	// Word 8
	short  analog5		:16;  // ADC value for analog input 5

	// Word 9
	short  analog6		:16;  // ADC value for analog input 6

	// Word 10
	short  analog7		:16;  // ADC value for analog input 7

	// Word 11
	USHORT spare11		:16;  // spare

	// Word 12
	short  checksum		:16;  // message checksum

} ANALOG_INPUT_MSG;

// ---------- Tracker Capabilities Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync				:16;  // sync word

	// Word 2
	USHORT spare2			:8;   // spare bits
	USHORT msg_type			:8;   // message type = 41

	// Word 3
	USHORT type				:16;  // The type/model of tracker

	// Word 4
	USHORT correlation		:1;   // 1=correlation available
	USHORT second_gate		:1;	  // 1=second gate available
	USHORT hdsdi			:1;   // 1=SDI digital video input(s) present
	USHORT camera_link		:1;   // 1=Camera Link digital video input present
	USHORT dvi				:1;   // 1=DVI digital video input present
	USHORT third_gate		:1;	  // 1=third gate available
	USHORT needs_firmware	:1;   // 1=message is from boot loader, user needs to load DSP firmware
	USHORT mt_output		:1;   // 1=multi-target output available
	USHORT spare4			:8;

	// Word 5 & 6
	USHORT dsp1_major		:16;  // The DSP1 major software version
	USHORT dsp1_minor		:16;  // The DSP1 minor software version

	// Word 7 & 8
	USHORT dsp2_major		:16;  // The DSP1 major software version
	USHORT dsp2_minor		:16;  // The DSP1 minor software version

	// Word 9
	USHORT hw_version		:4;   // The FPGA hardware version (VME, PCI, cPCI)
	USHORT hw_type			:4;	  // The FPGA type on the board
	USHORT hw_revision		:8;   // The FPGA hardware revision

	// Words 10-16
	char   build_date[14];    // The DSP software build date

	// Words 17-21
	char   build_time[10];    // The DSP software build time

	// Words 22-25
	char   serial[8];		  // Tracker board serial number

	// Word 26
	USHORT dsp1_boot_major	:8;  // The DSP1 major boot loader software version
	USHORT dsp1_boot_minor	:8;  // The DSP1 minor boot loader software version

	// Word 27
	USHORT dsp2_boot_major	:8;  // The DSP2 major boot loader software version
	USHORT dsp2_boot_minor	:8;  // The DSP2 minor boot loader software version

	// Word 28
	short  checksum			:16;  // message checksum

} CAPABILITIES_MSG;

// ---------- Built In Test Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync			:16;  // sync word

	// Word 2
	USHORT spare2		:8;   // spare bits
	USHORT msg_type		:8;   // message type = 42

	// Word 3
	USHORT type			:16;  // the test number

	// Word 4
	USHORT subtype		:16;  // the subtest number

	// Word 5
	USHORT datasize		:16;  // the size (in words) of valid data in testdata

	// Words 6-45 (80 bytes)
	short  testdata[MAX_TEST_DATA_SIZE];	// test data

	// Word 46
	short  checksum		:16;  // message checksum

} BUILT_IN_TEST_MSG;

// ---------- Mount Status Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync			:16;  // sync word

	// Word 2
	USHORT spare2		:8;   // spare bits
	USHORT msg_type		:8;   // message type = 43

	// Word 3
	USHORT enabled		:1;   // tracker mount support enabled
							  //   0 = mount not enabled/connected/detected (no communication)
							  //   1 = mount communication established and functioning
	USHORT active		:1;   // active mode (1=mount motor power is on)
	USHORT limit_alarm	:1;   // limit alarm (1=mount has reached a limit)
	USHORT fault_alarm	:1;   // fault alarm (1=mount fault detected)
	USHORT spare3		:12;

	// Word 4
	USHORT status_byte1	:8;   // raw status bytes as returned by mount (if supported)
	USHORT status_byte2	:8;

	// Word 5
	USHORT status_byte3	:8;
	USHORT status_byte4	:8;

	// Word 6
	short  checksum		:16;  // message checksum

} MOUNT_STATUS_MSG;

// ---------- Laser Range Finder Control Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync				:16;  // sync word

	// Word 2
	USHORT spare2			:8;   // spare bits
	USHORT msg_type			:8;   // message type = 44

	// Word 3
	USHORT command			:8;   // see LRF_CMD_XXX defines
	USHORT serial_port		:3;   // tracker serial port the LRF is connected to (3-7, 0-2 are reserved)
	USHORT hv_enable		:1;   // 1=enable high voltage to laser
	USHORT first_target		:1;   // 1=first target inside the range gate, 0=last target
	USHORT spare3			:1;
	USHORT not_present		:1;	  // LRF is not present and not communicating with the tracker (query only)
	USHORT error_detected	:1;	  // LRF communication error(s) detected (query only)

	// Word 4
	USHORT type				:16;  // laser range finder type (see LRF_TYPE_XXX defines)

	// Word 5
	USHORT fire_interval	:16;  // periodic fire time in milliseconds

	// Word 6 & 7
	USHORT min_range_lsw	:16;  // minimum range in meters, least significant word (lsw)
	USHORT min_range_msw	:16;  // and most significant word (msw)

	// Word 8 & 9
	USHORT max_range_lsw	:16;  // maximum range in meters, least significant word (lsw)
	USHORT max_range_msw	:16;  // and most significant word (msw)

	// Word 10
	short  checksum			:16;  // message checksum

} LRF_CONTROL_MSG;

// ---------- Target Range Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync				:16;  // sync word

	// Word 2
	USHORT spare2			:8;   // spare bits
	USHORT msg_type			:8;   // message type = 45

	// Word 3
	USHORT source			:1;   // source of range data (0=tracker, 1=user)
	USHORT units			:1;   // units of range data (0=meters, 1=centimeters)
	USHORT spare31			:6;
	USHORT ready_to_fire	:1;   // 1=laser ready to fire (for LRF only)
	USHORT multi_target		:1;   // 1=multiple targets in range gate (for LRF data)
	USHORT valid			:1;   // 1=valid range data
	USHORT laser_fired		:1;   // 1=laser successfully fired (for LRF only)
	USHORT heater_on		:1;   // 1=heater turned on (some LRFs only)
	USHORT range_gate_err	:1;   // 1=range gate error (max <= min) (for LRF only)
	USHORT hw_error			:1;   // 1=hardware/laser failure error (for LRF only)
	USHORT spare32			:1;

	// Word 4 & 5
	USHORT range_lsw		:16;  // range in meters/centimeters, least significant word (lsw)
	USHORT range_msw		:16;  // and most significant word (msw)

	// Word 6
	short  checksum			:16;  // message checksum

} TARGET_RANGE_MSG;

// ---------- Target Generator Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync				:16;  // sync word

	// Word 2
	USHORT enable			:1;   // global target generator enable/disable
	USHORT motion_en		:1;   // target motion enable/disable (DEBUG ONLY, set to 0)
	USHORT spare2			:6;   // spare bits
	USHORT msg_type			:8;   // message type = 46

	// Word 3
	USHORT select			:8;   // target select (0=background, 1=target1, 2=target2, etc...)
	USHORT type				:8;   // target type (0=disabled/off, 1=rectangle, 2=diamond, etc...)

	// Word 4
	USHORT color			:16;  // target color (grayscale value of target, 0 to 1023)

	// Word 5
	short  position_x		:16;  // target location (X/pixels)

	// Word 6
	short  position_y		:16;  // target location (Y/lines)

	// Word 7
	USHORT size_x			:16;  // target size (X/pixels)

	// Word 8
	USHORT size_y			:16;  // target size (Y/lines)

	// Word 9
	short  checksum			:16;  // message checksum

} TARGET_GENERATOR_MSG;

// ---------- Gate Control Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync					:16;  // sync word

	// Word 2
	USHORT prime_gate			:8;   // the gate number currently generating the drive/filtered track errors
	USHORT msg_type				:8;   // message type = 47

	// Word 3
	USHORT transition_event		:8;   // the event to trigger a transition between gates
									  //   0=none, 1=second gate entering track
	USHORT second_slave_en		:1;   // second gate slaved to the first gate enable/disable
									  //   NOTE: this will be automatically disabled after a transition
	USHORT spare3				:7;

	// Word 4
	USHORT transition_step		:16;  // percent of gate error for initial transition step (range: 0 to 100)

	// Word 5
	USHORT transition_time		:16;  // time to transition from one gate's error output to the other (in fields)

	// Word 6
	short  slave_offset_x		:16;  // second gate slaved offset from position of the primary gate (X/pixels)

	// Word 7
	short  slave_offset_y		:16;  // second gate slaved offset from position of the primary gate (Y/lines)

	// Word 8
	short  checksum				:16;  // message checksum

} GATE_CONTROL_MSG;

// -------------- Mount Feedback Message Structure --------------
typedef struct
{
	// Word 1
	USHORT	sync			:16;  // sync word

	// Word 2
	USHORT	spare2			:8;   // spare bits
	USHORT	msg_type		:8;   // msg type = 48

	// Word 3 & 4
	short   azimuth_lsw		:16;  // the current azimuth angle of the mount
	short   azimuth_msw		:16;  // least significant word (lsw) and most significant word (msw)
								  // (degrees: multiply float by 10,000 to set value)
	// Word 5 & 6
	short   elevation_lsw	:16;  // the current elevation angle of the mount
	short   elevation_msw	:16;  // least significant word (lsw) and most significant word (msw)
								  // (degrees: multiply float by 10,000 to set value)
	// Word 7 & 8
	short   velocity_az_lsw	:16;  // the current azimuth velocity of the mount
	short   velocity_az_msw	:16;  // least significant word (lsw) and most significant word (msw)
								  // (degrees/sec: multiply float by 1,000 to set value)
	// Word 9 & 10
	short   velocity_el_lsw	:16;  // the current elevation velocity to the mount
	short   velocity_el_msw	:16;  // least significant word (lsw) and most significant word (msw)
								  // (degrees/sec: multiply float by 1,000 to set value)
	// Word 11
	USHORT	spare11			:16;

	// Word 12
	short	checksum		:16;  // checksum

} MOUNT_FEEDBACK_MSG;

// -------------- Digital I/O Message Structure --------------
typedef struct
{
	// Word 1
	USHORT	sync			:16;  // sync word

	// Word 2
	USHORT	type			:1;   // type of message (0=dio read, 1=dio write)
	USHORT	spare2			:7;
	USHORT	msg_type		:8;   // msg type = 49

	// Word 3
	USHORT  dio_bits		:16;

	// Word 4
	short	checksum		:16;  // checksum

} DIGITAL_IO_MSG;

// -------- Software Download Message Structure ---------
typedef struct
{
	// Word 1
	USHORT sync			:16;	// sync word

	// Word 2
	USHORT data_flag	:4;		// 1 = Initial data block
								// 3 = Continuation data block
								// 5 = Last data block / End of file
								// 7 = Fail (this is for a GUI related failure or abort)
	USHORT target		:4;		// 1 = DSP1, 2 = DSP2, 3=DSP BIN, 4&5 = FPGA, 7 = IFF LUT, 10 = NUC Gain, 11 = NUC Offset, 12 = NUC Bad Pixel
	USHORT msg_type     :8;		// message type = 50

	// Word 3
	USHORT sequence		:16;	// message sequence number

	// Words 4 thru 43 (total of 80 bytes / 40 words)
	UCHAR  data[DL_CODE_SIZE];	// data bytes

	// Word 44
	short  checksum		:16;	// message checksum

} DL_CODE_RECEIVE_MSG;

// -------- Software Download Status Message Structure ---------
typedef struct
{
	// Word 1
	USHORT sync			:16;	// sync word

	// Word 2
	USHORT data_flag	:4;		// 2 = Send next data block
								// 4 = Error, re-transmit data block
								// 6 = Finished
								// 8 = Restart file download
								// 10 = Abort download
	USHORT spare2		:4;		// spare bits
	USHORT msg_type		:8;		// message type = 51

	// Word 3
	short  checksum		:16;	// message checksum

} DL_CODE_STATUS_MSG;

// -------- Download License Message Structure ---------
typedef struct
{
	// Word 1
	USHORT sync			:16;	// sync word

	// Word 2
	USHORT spare2		:8;		// spare bits
	USHORT msg_type		:8;		// message type = 52

	// Words 3-9
	USHORT key[7];				// license key

	// Word 10
	short  checksum		:16;	// message checksum

} DL_LICENSE_MSG;

// -------- Software Download Status 2 Message Structure ---------
typedef struct
{
	// Word 1
	USHORT sync			:16;	// sync word

	// Word 2
	USHORT data_flag	:4;		// 2 = Send next data block
								// 4 = Error, re-transmit data block
								// 6 = Finished
								// 8 = Restart file download
								// 10 = Abort download
	USHORT spare2		:4;		// spare bits
	USHORT msg_type		:8;		// message type = 53

	// Word 3
	USHORT sequence		:16;	// message sequence number

	// Word 4
	short  checksum		:16;	// message checksum

} DL_CODE_STATUS2_MSG;

// -------- Gate Statistics Message Structure ---------
typedef struct
{
	// Word 1
	USHORT sync				:16;	// sync word

	// Word 2
	USHORT spare2			:8;
	USHORT msg_type			:8;		// message type = 54

	// Word 3 & 4
	USHORT abs_max			:16;	// absolute maximum intensity value (peak white)
	USHORT abs_min			:16;	// absolute minimum intensity value (peak black)

	// Word 5 & 6
	USHORT maximum			:16;	// (statistically significant) maximum intensity value
	USHORT minimum			:16;	// (statistically significant) minimum intensity value

	// Word 7
	USHORT mean				:16;	// average intensity value (arithmetic mean)

	// Word 8
	USHORT median			:16;	// middle intensity value

	// Word 9
	USHORT mode				:16;	// peak intensity value (largest histogram value)

	// Word 10
	short  checksum			:16;	// message checksum

} GATE_STATISTICS_MSG;

// -------- Digital Video Status Message Structure ---------
//
// FPGA type HW_FPGA_XC4V_LX80 or greater ONLY
//
typedef struct
{
	// Word 1
	USHORT sync				:16;	// sync word

	// Word 2
	USHORT spare2			:8;
	USHORT msg_type			:8;		// message type = 55

	// Word 3
	USHORT video_present	:1;		// 1=digital video input source detected
	USHORT interlaced		:1;		// 0=progressive, 1=interlaced
	USHORT spare3			:14;

	// Word 4
	USHORT pixel_count		:16;	// number of pixels per line

	// Word 5
	USHORT line_count		:16;	// number of lines per field/frame

	// Word 6
	USHORT video_rate		:16;	// video field/frame rate in microseconds

	// Word 7
	USHORT pixel_clock		:16;	// pixel clock frequency in MHz (divide by 100 to get value)

	// Word 8
	short  checksum			:16;	// message checksum

} DIGITAL_VIDEO_STATUS_MSG;

// ---------- User String2 Message Structure ----------
//
// FPGA type HW_FPGA_XC4V_LX80 or greater ONLY
//
typedef struct
{
	// Word 1
	USHORT sync			:16;  // sync word

	// Word 2
	USHORT dest			:4;   // destination (0=selected video, 1=unselected video, 2=both)
	USHORT spare2		:4;
	USHORT msg_type		:8;   // message type = 56

	// Word 3
	USHORT col			:8;   // start column
	USHORT row			:8;   // start row

	// ** This character string is a standard C string, so
	//    it must be NULL terminated
	char   string[MAX_USER_STRING_LEN+1];

	// Word (4 + (MAX_USER_STRING_LEN+1)/2)
	short  checksum		:16;  // message checksum

} USER_STRING2_MSG;

// -------- Target Simulator Message Structure ---------
typedef struct
{
	// Word 1
	USHORT sync;					  // sync word

	// Word 2
	USHORT spare2				:8;
	USHORT msg_type				:8;	  // message type = 57

	// Word 3
	USHORT enable				:1;	  // enable the simulator
	USHORT video_rate_feedback	:1;   // if enabled, the tracker will send unsolicited feedback at video rate
	USHORT sim_running			:1;   // set (by tracker) if simulation is currently running
	USHORT spare3				:5;
	USHORT command				:8;	  // simulator command (0=none, 1=run, 2=stop)

	// Word 4 & 5
	USHORT time_lsw;				  // current simulation time in milliseconds, least significant word (lsw)
	USHORT time_msw;				  // and most significant word (msw)

	// Word 6 & 7
	short  azimuth_lsw;				  // azimuth of mount in degrees, least significant word (lsw)
	short  azimuth_msw;				  // and most significant word (msw) (divide by 10000 to get value)
									  //    range: +/- 360.0000  (divide by 10,000 to get value)
	// Word 8 & 9
	short  elevation_lsw;			  // elevation of mount in degrees, least significant word (lsw)
	short  elevation_msw;			  // and most significant word (msw) (divide by 10000 to get value)
									  //    range: +/- 360.0000  (divide by 10,000 to get value)
	// Word 10 & 11
	USHORT range_lsw;				  // range in millimeters, least significant word (lsw)
	USHORT range_msw;				  // and most significant word (msw)

	// Word 12
	short  checksum;				  // message checksum

} TARGET_SIMULATOR_MSG;

// -------- Clutter Rejection Processor Control Message Structure ---------
// THIS MESSAGE AND FUNCTIONALLITY IS OBSOLETE.
// PLEASE USE MULT-TARGET INSTEAD.
typedef struct
{
	// Word 1
	USHORT sync;					  // sync word

	// Word 2
	USHORT spare2				:8;
	USHORT msg_type				:8;	  // message type = 58

	// Word 3
	USHORT enable				:1;	  // enable the CRP
	USHORT run					:1;   // processor run mode (0=idle, 1=run)
	USHORT state				:4;   // processor state (0=acquire, 1=confirm, 2=track, 3=coast)
	USHORT clear_overflow		:1;   // clear the overflow counter (1=clear)
	USHORT spare3				:9;

	// Word 4
	USHORT object_count;			  // total number of objects found (last field/frame)

	// Word 5
	USHORT overflow_count;			  // processing overflow count

	// Word 6
	USHORT spare6;

	// Word 7
	USHORT spare7;

	// Word 8
	short  checksum;				  // message checksum

} CRP_CONTROL_MSG;

// -------- Steered Mirror Filter Control Message Structure ---------
typedef struct
{
	// Word 1
	USHORT sync;					  // sync word

	// Word 2
	USHORT spare2				:8;
	USHORT msg_type				:8;	  // message type = 59

	// Word 3
	USHORT enable				:1;	  // enable/disable the filter
	USHORT spare3				:15;

	// Word 4
	USHORT camera_fov_x;			  // horizontal camera field-of-view
									  //   range: 0 to 360.00 (divide by 100 to get value)
	// Word 5
	USHORT camera_fov_y;			  // vertical camera field-of-view
									  //   range: 0 to 360.00 (divide by 100 to get value)
	// Word 6
	short  az_translation_amp_x;	  // (OBSOLETE) azimuth translation amplitude X
									  //   range: -327.67 to 327.67 (divide by 100 to get value)
	// Word 7
	short  az_translation_amp_y;	  // (OBSOLETE) azimuth translation amplitude Y
									  //   range: -327.67 to 327.67 (divide by 100 to get value)
	// Word 8
	short  az_translation_phase_x;	  // (OBSOLETE) azimuth translation phase X
									  //   range: -3.2767 to 3.2767 (divide by 10,000 to get value)
	// Word 9
	short  az_translation_phase_y;	  // (OBSOLETE) azimuth translation phase Y
									  //   range: -3.2767 to 3.2767 (divide by 10,000 to get value)
	// Word 10
	short  az_offset;				  // azimuth parallax adjustment
									  //   range: -3276.7 to 3276.7 (divide by 10 to get value)
	// Word 11
	short  el_translation_amp_x;	  // (OBSOLETE) elevation translation amplitude X
									  //   range: -32.767 to 327.67 (divide by 100 to get value)
	// Word 12
	short  el_translation_amp_y;	  // (OBSOLETE) elevation translation amplitude Y
									  //   range: -32.767 to 32.767 (divide by 100 to get value)
	// Word 13
	short  el_translation_phase_x;	  // (OBSOLETE) elevation translation phase X
									  //   range: -3.2767 to 3.2767 (divide by 10,000 to get value)
	// Word 14
	short  el_translation_phase_y;	  // (OBSOLETE) elevation translation phase Y
									  //   range: -3.2767 to 3.2767 (divide by 10,000 to get value)
	// Word 15
	short  el_offset;				  // (OBSOLETE) elevation final offset adjustment
									  //   range: -3276.7 to 3276.7 (divide by 10 to get value)
	// Word 16
	short  checksum;				  // message checksum

} STEERED_MIRROR_FILTER_MSG;

// -------- IFF Track Status Message Structure ---------
typedef struct
{
	// Word 1
	USHORT sync;					  // sync word

	// Word 2
	USHORT spare2				:8;
	USHORT msg_type				:8;	  // message type = 60

	// Word 3
	USHORT az_tracking			:1;	  // azimuth axis track indicator (1=azimuth is currently tracking)
	USHORT el_tracking			:1;	  // elevation axis track indicator (1=elevation is currently tracking)
	USHORT rss1_fault			:1;	  // Azimuth Received Signal Strength 1 (RSS1) fault indicator (0=ok, 1=fault)
	USHORT rss2_fault			:1;	  // Azimuth Received Signal Strength 2 (RSS2) fault indicator (0=ok, 1=fault)
	USHORT spare3				:12;

	// NOTE: To convert analog readings to +/-10 volts using the following equation
	//       volts = analog * 10/32767

	// Word 4
	short  az_rss1_raw;				  // raw analog input reading for Azimuth Received Signal Strength 1 (RSS1)

	// Word 5
	short  az_rss2_raw;				  // raw analog input reading for Azimuth Received Signal Strength 2 (RSS2)

	// Word 6
	short  az_error_raw;			  // raw analog input reading for Azimuth Pointing Error (AzPE)

	// Word 7 & 8
	short  az_error_lsw;			  // Azimuth Point Error (AzPE) in degrees after lookup table is applied
	short  az_error_msw;			  // least significant word (lsw) and most significant word (msw)
									  //   range: +/- 360.0000 (divide by 10,000 to get value)
	// Word 9 & 10
	short  az_drive_lsw;			  // current azimuth velocity drive in degrees per second (if tracking)
	short  az_drive_msw;			  // least significant word (lsw) and most significant word (msw)
									  //   (divide by 1000 to get value)
	// Word 11 & 12
	short  el_drive_lsw;			  // current elevation velocity drive in degrees per second (if tracking)
	short  el_drive_msw;			  // least significant word (lsw) and most significant word (msw)
									  //   (divide by 1000 to get value)
	// Word 13
	short  checksum;				  // message checksum

} IFF_TRACK_STATUS_MSG;

// -------- Steered Mirror Filter Calibration Message Structure ---------
typedef struct
{
	// Word 1
	USHORT sync;					  // sync word

	// Word 2
	USHORT spare2				:8;
	USHORT msg_type				:8;	  // message type = 61

	// Word 3
	USHORT command				:8;   // calibration command (0=no action, 1=start cal, 2=abort cal)
	USHORT spare3				:8;

	// Word 4
	USHORT status				:8;   // calibration status (0=not running, 1=running, 2=failed, 3=complete)
	USHORT error_code			:4;   // error code if status is failed (0=none, 1=aborted, 2=save error)
	USHORT invalid_target_count	:1;   // invalid target count flag (0=ok, both targets found)
	USHORT spare4				:3;

	// Word 5
	USHORT point_count;				  // number of points collected so far

	// Word 6
	short  checksum;				  // message checksum

} STEERED_MIRROR_CALIBRATION_MSG;

// -------- Overlay Control Message Structure ---------
//  See the MSG_OVL_FMT.H file for additional details
typedef struct
{
	// Word 1
	USHORT sync;					  // sync word

	// Word 2
	USHORT spare2				:8;
	USHORT msg_type				:8;	  // message type = 62

	// Word 3
	USHORT target				:8;   // target (0=none, 1=overlay, 2=sprite1, ...)
	USHORT command				:8;   // command (0=no action, 1=enable, ...)

	// Word 4 through 21
	OVERLAY_DATA data;				  // command parameters (see MSG_OVL_FMT.H)

	// Word 22
	short  checksum;				  // message checksum

} OVERLAY_CONTROL_MSG;

// -------- Overlay Status Message Structure ---------
typedef struct
{
	// Word 1
	USHORT sync;					  // sync word

	// Word 2
	USHORT spare2				:8;
	USHORT msg_type				:8;	  // message type = 63

	// Word 3
	USHORT overlay_en			:1;   // overlay enabled
	USHORT overlay_displayed	:1;   // overlay currently displayed (0=overlay #1, 1=overlay #2)
	USHORT overlay_busy			:1;   // busy flag (0=ready, 1=busy)
	USHORT sprite1_en			:1;   // sprite #1 enabled
	USHORT sprite2_en			:1;   // sprite #2 enabled
	USHORT sprite3_en			:1;   // sprite #3 enabled
	USHORT sprite4_en			:1;   // sprite #4 enabled
	USHORT overlay_invert		:1;   // overlay output inverted
	USHORT sprite1_invert		:1;   // sprite #1 output inverted
	USHORT sprite2_invert		:1;   // sprite #2 output inverted
	USHORT sprite3_invert		:1;   // sprite #3 output inverted
	USHORT sprite4_invert		:1;   // sprite #4 output inverted
	USHORT spare3				:4;

	// Word 4 & 5
	short  sprite1_pos_x;
	short  sprite1_pos_y;

	// Word 6 & 7
	short  sprite2_pos_x;
	short  sprite2_pos_y;

	// Word 8 & 9
	short  sprite3_pos_x;
	short  sprite3_pos_y;

	// Word 10 & 11
	short  sprite4_pos_x;
	short  sprite4_pos_y;

	// Word 12 & 13
	short  overlay_pos_x;
	short  overlay_pos_y;

	// Word 14
	short  checksum;				  // message checksum

} OVERLAY_STATUS_MSG;

// -------- Line Of Sight Control 2 Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync;				  // sync word

	// Word 2
	USHORT spare2   :8;			  // spare bits
	USHORT msg_type :8;			  // message type = 64

	// Word 3
	short  posx;				  // line-of-sight (boresight reticle) position X

	// Word 4
	short  posy;				  // line-of-sight (boresight reticle) position Y

	// Word 5
	short  checksum;			  // message checksum

} LOS_OFFSET_CTRL2_MSG;

// --------- Offset Aim Control 2 Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync;				  // sync word

	// Word 2
	USHORT spare2			:7;   // spare bits
	USHORT ofaim_ena		:1;   // offset aim enable (0=disable, 1=enable)
	USHORT msg_type			:8;   // message type = 65

	// Word 3
	short  posx;				  // offset-aim position(X)

	// Word 4
	short  posy;				  // offset-aim position(Y)

	// Word 5
	USHORT los_trans_time;		  // return to line of sight transition time in fields

	// Word 6
	short  checksum;			  // message checksum

} OFFSET_AIM_CTRL2_MSG;

// -------- Position Tracking Status Message Structure ---------
typedef struct
{
	// Word 1
	USHORT sync				:16;	  // sync word

	// Word 2
	USHORT spare2			:8;
	USHORT msg_type			:8;		  // message type = 66

	// Word 3
	USHORT az_tracking		:1;		  // azimuth track indicator
	USHORT el_tracking		:1;		  // elevation track indicator
	USHORT az_estimating	:1;	 	  // azimuth estimation indicator   (1=coasting using Kalman filter estimation)
	USHORT el_estimating	:1;	  	  // elevation estimation indicator (1=coasting using Kalman filter estimation)
	USHORT spare3			:12;

	// Word 4 & 5
	short  az_drive_lsw;			  // current azimuth velocity drive in degrees per second (if tracking)
	short  az_drive_msw;			  // least significant word (lsw) and most significant word (msw)
									  //   (divide by 1000 to get value)
	// Word 6 & 7
	short  el_drive_lsw;			  // current elevation velocity drive in degrees per second (if tracking)
	short  el_drive_msw;			  // least significant word (lsw) and most significant word (msw)
									  //   (divide by 1000 to get value)
	// Word 8
	short  checksum;				  // message checksum

} POS_TRACK_STATUS_MSG;

// ---------- Control Box Control Message Structure ----------
//
// Control box pass-through/proxy message.  This tracker message
// encapsulates the Controller's output message bound for the
// tracker (which is typically directly connected to the
// tracker's UART1 serial port).
//
typedef struct  
{
	// Word 1
	USHORT sync					:16;	// sync word

	// Word 2 
	USHORT spare2				:8;				
	USHORT msg_type				:8;		// message type = 67

	////// START -- Embedded Controller Message //////

	// Word 3
	USHORT 	control_box_sync;			// sync = 0xC3C3

	// Word 4
	USHORT spare4				:8;
	USHORT control_box_msg_type	:8;		// type = 102

	// Word 5
	USHORT video_source	 		:1; 	// video input select (0=video #1, 1=video #2)
	USHORT mount_gain_override	:1; 	// gain override (0=normal, 1=override)
	USHORT aim_point_offset		:1;		// offset aim (0=inactive, 1=switch pressed)
	USHORT reset_to_boresight 	:1;		// reset aim point to boresight (0=inactive, 1=switch pressed)
	USHORT track_button_state	:1;		// joystick track button (0=not pressed, 1=pressed)
	USHORT box_reset			:1; 	// reset indicator (0=running, 1=just booted)
	USHORT gate_pos_mode		:1;		// gate position mode (0=manual, 1=automatic)
	USHORT gate_size_mode		:1; 	// gate size mode (0=manual, 1=automatic)

	USHORT target_polarity		:2;		// target polarity (0=auto, 1=white, 2=black)
	USHORT threshold_mode		:1;		// threshold mode (0=manual, 1=automatic)
	USHORT auto_track			:1;		// auto track (0=manual, 1=automatic)
	USHORT track_mode			:3; 	// track mode (0=top edge, 1=bottom edge, 2=left edge, 3=right edge
										//			   4=centroid, 5=intensity, 6=leading edge, 7=correlation)
	USHORT track_acquire		:1;		// obsolete -- this bit is not used by the tracker

	// Word 6
	USHORT lens2_iris			:2;		// lens #2 iris mode (0=inactive, 1=open, 2=close, 3=auto)
	USHORT lens2_zoom_wide		:1; 	// lens #2 zoom wide (0=inactive, 1=zoom wide)
	USHORT lens2_zoom_narrow	:1; 	// lens #2 zoom narrow (0=inactive, 1=zoom narrow)
	USHORT lens2_focus_near		:1; 	// lens #2 focus near (0=inactive, 1=focus near)
	USHORT lens2_focus_far		:1; 	// lens #2 focus far (0=inactive, 1=focus far)
	USHORT lens2_TFOV			:2; 	// lens #2 tri-FOV (0=medium, 1=narrow, 2=wide)

	USHORT lens1_iris			:2;		// lens #1 iris mode (0=inactive, 1=open, 2=close, 3=auto)
	USHORT lens1_zoom_wide		:1; 	// lens #1 zoom wide (0=inactive, 1=zoom wide)
	USHORT lens1_zoom_narrow	:1; 	// lens #1 zoom narrow (0=inactive, 1=zoom narrow)
	USHORT lens_focus_near		:1; 	// lens #1 focus near (0=inactive, 1=focus near)
	USHORT lens1_focus_far		:1; 	// lens #1 focus far (0=inactive, 1=focus far)
	USHORT lens1_TFOV			:2; 	// lens #1 tri-FOV (0=medium, 1=narrow, 2=wide)

	// Word 7
	USHORT user_inputs			:16;	// user digital inputs to Controller (16 bits)

	// Word 8
	USHORT user_outputs			:8;		// state of user digital outputs (8 bits)
	USHORT control_box_version	:1;		// 0=Rev -, 1=Rev A (default)
	USHORT spare8			 	:4;
	USHORT symbology			:2; 	// symbology (0=Obey GUI symbology, 1=black, 2=white, 3=off)
	USHORT reticle_control		:1; 	// reticle control (0=off, 1=on)

	// Word 9
	USHORT joystick_pan			:16;	// joystick pan/azimuth reading (10-bit ADC, 0-1023)
										//   center position is nominally 511
	// Word 10
	USHORT joystick_tilt		:16;	// joystick tilt/elevation reading (10-bit ADC, 0-1023)
										//   center position is nominally 511
	// Word 11
	USHORT gate_size_x			:16;	// gate size X reading (10-bit ADC, 0-1023)

	// Word 12
	USHORT gate_size_y			:16;	// gate size Y reading (10-bit ADC, 0-1023)

	// Word 13
	USHORT black_threshold		:16;	// black threshold reading (10-bit ADC, 0-1023)

	// Word 14
	USHORT white_threshold		:16;	// white threshold reading (10-bit ADC, 0-1023)

	// Word 15
	USHORT analog_input_1		:16;	// external analog input #1 reading (10-bit ADC, 0-1023)

	// Word 16
	USHORT analog_input_2		:16;	// external analog input #2 reading (10-bit ADC, 0-1023)

	// Word 17
	USHORT control_box_checksum	:16;

	////// END -- Embedded Controller Message //////

	// Word 18
	short  checksum				:16;  	// message checksum

} CONTROL_BOX_CONTROL_MSG;

// ---------- Control Box Status Message Structure ----------
//
// Control box pass-through/proxy message.  This tracker message
// encapsulates the Controller's input message sent by the
// tracker and bound for the Controller (which is typically
// directly connected to the tracker's UART1 serial port).
//
typedef struct  
{
	// Word 1
	USHORT sync					:16;  	// sync word

	// Word 2 
	USHORT spare2				:8;				
	USHORT msg_type				:8;		// message type = 68

	////// START -- Embedded Controller Message //////

	// Word 3
	USHORT control_box_sync;		  	// sync = 0xC3C3

	// Word 4
	USHORT track_acquire		:1;		// track/acquire LED (1=light, 0=dark)
	USHORT on_target			:1;		// on target LED
	USHORT video1_tfov			:1;		// video source #1 multi-FOV lens LED
	USHORT video2_tfov			:1;		// video source #2 multi-FOV lens LED
	USHORT video1_zoom			:1;		// video source #1 zoom lens LED
	USHORT video2_zoom			:1;		// video source #1 zoom lens LED
	USHORT spare4				:2;
	USHORT control_box_msg_type	:8;		// type = 103

	// Word 5
	USHORT spare5				:16;

	// Word 6
	USHORT user_outputs			:8;		// user digital outputs (8 bits)
	USHORT spare6				:8;

	// Word 7
	USHORT control_box_checksum	:16;

	////// END -- Embedded Controller Message //////

	// Word 8
	short  checksum				:16;  	// message checksum

} CONTROL_BOX_STATUS_MSG;

// -------- Threshold Statistics Message Structure ---------
typedef struct
{
	// Word 1
	USHORT sync					:16;	// sync word

	// Word 2
	USHORT spare2				:8;
	USHORT msg_type				:8;		// message type = 69

	// Word 3
	USHORT target_contrast		:16;	// contrast of the thresholded target in the gate (as a percentage)
										//   range: 0.00 to 100.00 (divide by 100 to get value)
	// Word 4
	USHORT target_average		:16;	// average intensity of the thresholded target pixels in the gate

	// Word 5
	USHORT target_background	:16;	// average intensity of the non-thresholded pixels in the gate

	// Word 6
	USHORT gate_peak_white		:16;	// maximum pixel intensity in the gate

	// Word 7
	USHORT gate_peak_black		:16;	// minimum pixel intensity in the gate

	// Word 8
	USHORT gate_average			:16;	// average pixel intensity in the gate

	// Word 9
	USHORT background_average	:16;	// average intensity of the background (intrusion area around gate)

	// Word 10
	USHORT white_contrast		:16;	// contrast of potential target data in the white region (above background average)
										//   range: 0.00 to 100.00 (divide by 100 to get value)
	// Word 11
	USHORT black_contrast		:16;	// contrast of potential target data in the black region (below background average)
										//   range: 0.00 to 100.00 (divide by 100 to get value)
	// Word 12
	USHORT spare12				:16;

	// Word 13
	USHORT spare13				:16;

	// Word 14
	short  checksum				:16;	// message checksum

} THRESHOLD_STATISTICS_MSG;

// -------- Overlay Extended Status Message Structure ---------
typedef struct
{
	// Word 1
	USHORT sync;					  // sync word

	// Word 2
	USHORT spare2				:8;
	USHORT msg_type				:8;	  // message type = 70

	// Word 3
	USHORT font_loaded			:1;   // overlay font loaded from flash (0=flash empty)
	USHORT spare3				:15;

	// Word 4
	USHORT font_info;				  // overlay font info (loaded from flash)

	// Words 5 through 13
	USHORT spare5;
	USHORT spare6;
	USHORT spare7;
	USHORT spare8;
	USHORT spare9;
	USHORT spare10;
	USHORT spare11;
	USHORT spare12;
	USHORT spare13;

	// Word 14
	short  checksum;				  // message checksum

} OVERLAY_STATUS_EXT_MSG;

// ---------- Camera Control Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync				:16;	  // sync word

	// Word 2
	USHORT spare2			:8;		  // spare bits
	USHORT msg_type			:8;		  // message type = 71

	// Word 3
	USHORT camera_type		:8;		  // camera type (see MSG_CAM_FMT.H)
	USHORT video_source		:8;		  // video source camera/lens is connected to
									  //   (NOTE: A valid lens must be configured for this source)
	// Word 4 through 21
	CAMERA_DATA data;				  // camera control structure (see MSG_CAM_FMT.H)

	// Word 22
	short  checksum;				  // message checksum

} CAMERA_CONTROL_MSG;

// ---------- GPS Data Message Structure ----------
//  Example latitude (or longitude) decoding:
//
//		int latitude = pos_latitude_msw;
//		latitude = (latitude << 16) | (pos_latitude_lsw & 0xFFFF);
//
//		float latitude_deg = (float)latitude / (float)(60*60*1000);
//
//		char NS;
//		if( latitude < 0 )
//		{
//			NS = 'S';
//			latitude = -latitude;
//		}
//		else
//			NS = 'N';
//
//		int latdeg  = latitude / (60*60*1000);
//		int latmin  = latitude % (60*60*1000) / (60*1000);
//		int latsec  = (latitude/1000) % 60;
//		int latmsec = latitude % 1000;
//
typedef struct
{
	// Word 1
	USHORT sync					:16;	  // sync word

	// Word 2
	USHORT spare2				:8;		  // spare bits
	USHORT msg_type				:8;		  // message type = 72

	// Word 3
	USHORT detected				:1;		  // GPS data detected (communications link up)
	USHORT locked				:1;		  // GPS locked / data valid
	USHORT spare3				:14;

	// Word 4
	USHORT quality				:8;		  // quality of fix (dependent on hardware)
	USHORT num_satellites		:8;		  // number of satellites being tracked

	// Word 5
	USHORT date_year			:16;	  // year  (four digit year, UTC date)

	// Word 6
	USHORT date_month			:8;		  // month (two digit month, UTC date)
	USHORT date_day				:8;		  // day   (two digit day,   UTC date)

	// Word 7
	USHORT time_hours			:8;		  // hours        (0-23, UTC time)
	USHORT time_minutes			:8;		  // minutes      (0-59, UTC time)

	// Word 8
	USHORT time_seconds			:8;		  // seconds      (0-60, UTC time)
	USHORT spare8				:8;

	// Word 9
	USHORT time_milliseconds	:16;	  // milliseconds (0-999, UTC time)

	// Word 10 and 11
	short  pos_latitude_lsw;			  // latitude in milliseconds, least significant word (lsw)
	short  pos_latitude_msw;			  // and most significant word (msw)
										  // positive is North and negative is South
	// Word 12 and 13
	short  pos_longitude_lsw;			  // longitude in milliseconds, least significant word (lsw)
	short  pos_longitude_msw;			  // and most significant word (msw)
										  // positive is East and negative is West
	// Word 14 and 15
	short  pos_altitude_lsw;			  // altitude in centimeters above the ellipsoid, least significant word (lsw)
	short  pos_altitude_msw;			  // and most significant word (msw)

	// Word 16
	USHORT spare16				:16;

	// Word 17
	USHORT spare17				:16;

	// Word 18
	short  checksum;					  // message checksum

} GPS_DATA_MSG;

// ---------- System Status Message Structure ----------
//  Consolidated system status primarily for 8000 series tracker boards
typedef struct
{
	// Word 1
	USHORT sync					:16;	// sync word

	// Word 2
	USHORT spare2				: 8;	// spare bits
	USHORT msg_type				: 8;	// message type = 73

	// Word 3
	USHORT vid1_source			: 4;	// video source routed to FPGA video input 1 (see VS_XXX defines)
	USHORT vid2_source			: 4;	// video source routed to FPGA video input 2 (see VS_XXX defines)
	USHORT vid1_present			: 1;	// signal on FPGA video input 1 is detected (video input depends on board type)
	USHORT vid2_present			: 1;	// signal on FPGA video input 2 is detected (video input depends on board type)
	USHORT lens1_not_present	: 1;	// lens 1 is not present or not communicating with the tracker
	USHORT lens1_error_detected	: 1;	// lens 1 communication/status error(s) detected
	USHORT lens2_not_present	: 1;	// lens 2 is not present or not communicating with the tracker
	USHORT lens2_error_detected	: 1;	// lens 2 communication/status error(s) detected
	USHORT spare3				: 2;

	// Word 4 & 5
	USHORT vid1_syncloss_count	:16;	// video sync loss count on FPGA video input 1 (will roll over to zero)
	USHORT vid1_reschange_count	:16;	// video resolution change detected count on FPGA video input 1 (will roll over to zero)

	// Word 6 & 7
	USHORT vid2_syncloss_count	:16;	// video sync loss count on FPGA video input 2 (will roll over to zero)
	USHORT vid2_reschange_count	:16;	// video resolution change detected count on FPGA video input 2 (will roll over to zero)

	// Word 8
	USHORT lens1_type			: 8;	// lens type configured for video input 1 (video input depends on board type)
	USHORT lens2_type			: 8;	// lens type configured for video input 2 (video input depends on board type)

	// Word 9
	USHORT eth_server_conns		: 4;	// number of current Ethernet connections to the tracker (server)
	USHORT eth_client_conns		: 4;	// number of current Ethernet connections to devices (client)
	short  tracker_board_temp	: 8;	// tracker board temperature (in degrees Celsius)

	// Word 10
	USHORT mount_type			: 8;	// configured mount type (see MOUNT_XXX defines)
	USHORT mount_not_present	: 1;	// mount is not present or not communicating with the tracker
	USHORT mount_active			: 1;	// mount is active (1=mount motor power is on)
	USHORT mount_limit_alarm	: 1;	// mount limit alarm (1=mount has reached a limit)
	USHORT mount_fault_alarm	: 1;	// mount fault alarm (1=mount fault detected)
	USHORT spare10				: 4;

	// Word 11
	USHORT mount_status_byte1	: 8;	// raw status bytes as returned by mount (if supported)
	USHORT mount_status_byte2	: 8;

	// Word 12
	USHORT mount_status_byte3	: 8;	// raw status bytes as returned by mount (if supported)
	USHORT mount_status_byte4	: 8;

	// Word 13
	USHORT lrf_type				: 8;	// laser range finder type (see LRF_TYPE_XXX defines)
	USHORT lrf_not_present		: 1;	// LRF is not present or not communicating with the tracker
	USHORT lrf_error_detected	: 1;	// LRF communication error(s) detected
	USHORT spare13				: 6;

	// Word 14
	USHORT gps_type				: 8;	// GPS equipment type (see GPS_TYPE_XXX defines)
	USHORT gps_not_present		: 1;	// GPS is not present or not communicating with the tracker
	USHORT gps_locked			: 1;	// GPS locked / data valid
	USHORT spare14				: 6;

	// Word 15
	USHORT gps_num_satellites	: 8;	// number of satellites being tracked
	USHORT spare15				: 8;

	// Word 16
	USHORT ircamera_fpa_temp	:16;	// IR camera FPA temperature if available (in 1/100 Kelvin)

	// Word 17
	USHORT spare17				:16;

	// Word 18
	short  checksum;					  // message checksum

} SYSTEM_STATUS_MSG;

// -------- FPGA Video Status Message Structure ---------
// Status for the two video inputs on the FPGA
//   actual video input depends on board and signal routing
//   only supported on FPGA revisions >= 24
typedef struct
{
	// Word 1
	USHORT sync					:16;	// sync word

	// Word 2
	USHORT spare2				: 8;
	USHORT msg_type				: 8;	// message type = 74

	// Word 3
	USHORT vid1_present			: 1;	// signal on FPGA video input 1 is detected (video input depends on board type)
	USHORT vid1_interlaced		: 1;	//   if present, input 1 is 0=progressive or 1=interlaced
	USHORT vid2_present			: 1;	// signal on FPGA video input 2 is detected (video input depends on board type)
	USHORT vid2_interlaced		: 1;	//   if present, input 2 is 0=progressive or 1=interlaced
	USHORT spare3				:12;

	// Word 4
	USHORT vid1_pixel_count		:16;	// number of pixels per line (FPGA video input 1)

	// Word 5
	USHORT vid1_line_count		:16;	// number of lines per field/frame

	// Word 6
	USHORT vid1_video_rate		:16;	// video field/frame rate in microseconds

	// Word 7
	USHORT vid1_pixel_clock		:16;	// pixel clock frequency in MHz (divide by 100 to get value)

	// Word 8
	USHORT vid1_syncloss_count	:16;	// video sync loss count (will roll over to zero)

	// Word 9
	USHORT vid1_reschange_count	:16;	// video resolution change detected count (will roll over to zero)
										
	// Word 10
	USHORT vid2_pixel_count		:16;	// number of pixels per line (FPGA video input 2)

	// Word 11
	USHORT vid2_line_count		:16;	// number of lines per field/frame

	// Word 12
	USHORT vid2_video_rate		:16;	// video field/frame rate in microseconds

	// Word 13
	USHORT vid2_pixel_clock		:16;	// pixel clock frequency in MHz (divide by 100 to get value)

	// Word 14
	USHORT vid2_syncloss_count	:16;	// video sync loss count (will roll over to zero)

	// Word 15
	USHORT vid2_reschange_count	:16;	// video resolution change detected count (will roll over to zero)

	// Word 16
	short  checksum				:16;	// message checksum

} FPGA_VIDEO_STATUS_MSG;

// ---------- Ethernet Status Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync					:16;	// sync word

	// Word 2
	USHORT spare2				: 8;	// spare bits
	USHORT msg_type				: 8;	// message type = 75

	// Word 3
	USHORT server_max			: 4;	// maximum possible number of connections to the tracker (server)
	USHORT server_connections	: 4;	// number of current Ethernet connections to the tracker (server)
	USHORT spare3				: 8;

	// Word 4
	USHORT client_max			: 4;	// maximum possible number of connections to devices (client)
	USHORT client_connections	: 4;	// number of current Ethernet connections to devices (client)
	USHORT client_try_connect	: 4;	// number of Ethernet devices the tracker is trying to connection to (client)
	USHORT spare4				: 4;

	// Word 5
	USHORT spare5;

	// Word 6 & 7
	UCHAR  server_ipaddr1_b1;			// server connection #1 IP address (b1.b2.b3.b4)
	UCHAR  server_ipaddr1_b2;
	UCHAR  server_ipaddr1_b3;
	UCHAR  server_ipaddr1_b4;

	// Word 8 & 9
	UCHAR  server_ipaddr2_b1;			// server connection #2 IP address (b1.b2.b3.b4)
	UCHAR  server_ipaddr2_b2;
	UCHAR  server_ipaddr2_b3;
	UCHAR  server_ipaddr2_b4;

	// Word 10 & 11
	UCHAR  server_ipaddr3_b1;			// server connection #3 IP address (b1.b2.b3.b4)
	UCHAR  server_ipaddr3_b2;
	UCHAR  server_ipaddr3_b3;
	UCHAR  server_ipaddr3_b4;

	// Word 12 & 13
	UCHAR  server_ipaddr4_b1;			// server connection #4 IP address (b1.b2.b3.b4)
	UCHAR  server_ipaddr4_b2;
	UCHAR  server_ipaddr4_b3;
	UCHAR  server_ipaddr4_b4;

	// Word 14
	short  checksum				:16;	// message checksum

} ETHERNET_STATUS_MSG;


// -------- Multi-Target General Setup Message Structure ---------
typedef struct
{
	// Word 1
	USHORT sync;					  // sync word

	// Word 2
	USHORT spare2				:8;
	USHORT msg_type				:8;	  // message type = 80

	// Word 3 & 4
	USHORT min_count_lsw;			  // minimum pixel count to be considered a target (0=disabled)
	USHORT min_count_msw;

	// Word 5
	USHORT max_percent;				  // maximum pixel count to be considered a target, expressed as
									  //   a percentage of the total gate pixel count (1 to 100, 0=disabled)
	// Word 6
	USHORT enable_output		:1;	  // enable video rate output of multi-target data (MT_DATA_MSG)
	USHORT spare6				:15;

	// Word 7
	USHORT spare7;

	// Word 8
	USHORT spare8;

	// Word 9
	USHORT spare9;

	// Word 10
	short  checksum;				  // message checksum

} MT_GENERAL_MSG;

// -------- Multi-Target Acquire Setup Message Structure ---------
typedef struct
{
	// Word 1
	USHORT sync;					  // sync word

	// Word 2
	USHORT spare2				:8;
	USHORT msg_type				:8;	  // message type = 81

	// Word 3
	USHORT enable				:1;   // enable multi-target acquire
	USHORT select_user			:1;   // if set, allows the user to select which target to track (otherwise the best match is selected)
	USHORT select_next			:1;   // selects the next valid target (only when select_user = 1)
	USHORT spare3				:5;
	USHORT select_method		:8;   // selection method (0=closest to boresight, 1=closest to gate center, 2=largest, 3=fastest...)

	// Word 4
	USHORT max_targets			:8;   // maximum number of targets to identify (range: 1 to 10)
	USHORT aspect				:2;	  // aspect ratio selection filter (0=disabled, 1=square, 2=tall and 3=long)
	USHORT motion_x				:2;   // X/azimuth motion selection filter (0=disabled, 1=left, 2=right)
	USHORT motion_y				:2;   // Y/elevation motion selection filter (0=disabled, 1=up, 2=down)
	USHORT inside_gate			:1;   // gate filter (0=disabled, 1=targets must be fully enclosed inside the gate)
	USHORT spare4				:1;

	// Word 5 & 6
	USHORT min_count_lsw;			  // minimum pixel count to be considered a target (0=disabled)
	USHORT min_count_msw;

	// Word 7
	USHORT max_percent;				  // maximum pixel count to be considered a target, expressed as
									  //   a percentage of the total gate pixel count (range: 1 to 100, 0=disabled)
	// Word 8
	USHORT min_life;				  // minimum life to be considered a target (in frames/fields)

	// Word 9
	USHORT min_speed;				  // minimum speed to be considered a target as a percentage of the field-of-view
									  // traversed by the target in one second (0=disabled)
									  //    range: 0.001 to 65.535  (divide by 1000 to get value)
	// Word 10
	USHORT max_speed;				  // maximum speed to be considered a target as a percentage of the field-of-view
									  // traversed by the target in one second (0=disabled)
									  //    range: 0.001 to 65.535  (divide by 1000 to get value)
	// Word 11
	USHORT spare11;

	// Word 12
	short  checksum;				  // message checksum

} MT_ACQUIRE_MSG;

// -------- Multi-Target Track Setup Message Structure ---------
typedef struct
{
	// Word 1
	USHORT sync;					  // sync word

	// Word 2
	USHORT spare2				:8;
	USHORT msg_type				:8;	  // message type = 82

	// Word 3
	USHORT enable				:1;   // enable multi-target tracking
	USHORT spare3				:15;

	// Word 4
	USHORT spare4;

	// Word 5
	USHORT spare5;

	// Word 6
	short  checksum;				  // message checksum

} MT_TRACK_MSG;

// -------- Multi-Target Data Structure ---------
// Used for multi-target data output in MT_DATA_MSG
// This structure is 11 words (22 bytes) in size
typedef struct
{
	USHORT		id;					// target identifier (0=invalid/unused)

	USHORT		pixel_count_lsw;	// target pixel count, least significant word (lsw)
	USHORT		pixel_count_msw;	//   and most significant word (msw)

	USHORT		size_x;				// target width (X size) in pixels
	USHORT		size_y;				// target height (Y size) in lines

	USHORT		left_x;				// the left (X/pixel) and top (Y/line) corner position
	USHORT		top_y;				//   of the bounding rectangle of the target
									//   range: 0 to 2047 (top/left of image is 0,0)

	USHORT		avg_intensity;		// average target pixel intensity

	short		centroid_x;			// target centroid X (pixels) and Y (lines)	from boresight		
	short		centroid_y;			//    range: +/- 1023.969  (divide by 32 to get value)

	USHORT		confidence;			// target match confidence (as a percentage)
									//   range: 0.00 to 100.00 (divide by 100 to get value)
} MT_TARGET;

// -------- Multi-Target Data Output Message Structure ---------
typedef struct
{
	// Word 1
	USHORT sync;						// sync word

	// Word 2
	USHORT spare2				:8;
	USHORT msg_type				:8;		// message type = 83

	// Word 3
	USHORT target_count			:16;	// total number of targets detected
										//   0=no targets detected, 0xFFFF = overflow
	// Word 4
	USHORT selected_id			:16;	// ID of the currently selected target
										//   0=no target selected
	// Word 5
	USHORT spare5				:16;

	// Word 6
	USHORT spare6				:16;

	// Words 7 - 61
	MT_TARGET targets[5];				// sorted array of best targets

	// Word 62
	short  checksum;					// message checksum

} MT_DATA_MSG;

// -------- Multi-Target Validation Setup Message Structure ---------
typedef struct
{
	// Word 1
	USHORT sync;					  // sync word

	// Word 2
	USHORT spare2				:8;
	USHORT msg_type				:8;	  // message type = 84

	// Word 3
	USHORT force_position		:1;   // force position validation (1=always validate target position)
	USHORT pixel_count_en		:1;   // pixel count validation enable
	USHORT size_en				:1;   // size validation enable
	USHORT spare3				:13;

	// Word 4
	USHORT position_tolerance;		  // percent of total FOV to use for target position/movement tolerance
									  //    range: 0.00 to 100.00  (divide by 100 to get value)
	// Word 5
	USHORT pixel_count_tolerance;	  // percent of target pixel count to use for mass change tolerance
									  //    range: 0.00 to 100.00  (divide by 100 to get value)
	// Word 6
	USHORT width_tolerance;			  // percent of target width to use for x size change tolerance
									  //    range: 0.00 to 100.00  (divide by 100 to get value)
	// Word 7
	USHORT height_tolerance;		  // percent of target height to use for y size change tolerance
									  //    range: 0.00 to 100.00  (divide by 100 to get value)
	// Word 8
	USHORT spare8;

	// Word 9
	USHORT spare9;

	// Word 10
	USHORT spare10;

	// Word 11
	USHORT spare11;

	// Word 12
	short  checksum;				  // message checksum

} MT_VALIDATION_MSG;


// ---------- Gate Size Configuration Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync			:16;  // sync word

	// Word 2
	USHORT spare2		:8;   // spare bits
	USHORT msg_type		:8;   // message type = 200

	// Word 3
	USHORT min_sizex	:10;  // minimum gate x size (pixels / 4)
	USHORT spare3		:6;   // spare bits

	// Word 4
	USHORT min_sizey	:10;  // minimum gate y size
							  //  lines for analog video sources or
							  //  lines / 2 for digital video sources
	USHORT spare4		:6;   // spare bits

	// Word 5
	USHORT max_sizex	:10;  // maximum gate x size (pixels / 4)
	USHORT spare5		:6;   // spare bits

	// Word 6
	USHORT max_sizey	:10;  // maximum gate y size
							  //  lines for analog video sources or
							  //  lines / 2 for digital video sources
	USHORT spare6		:6;   // spare bits

	// Word 7
	USHORT spare7		:16;  // spare word

	// Word 8
	short  checksum		:16;  // message checksum

} CONFIG_GATE_SIZE_MSG;

// ---------- Gate Position Configuration Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync			:16;  // sync word

	// Word 2
	USHORT spare2		:8;   // spare bits
	USHORT msg_type		:8;   // message type = 201

	// Word 3
	short min_posx		:10;  // minimum gate x/left position
							  //  pixels for analog video sources or
							  //  pixels / 2 for digital video sources
	USHORT spare3		:6;   // spare bits

	// Word 4
	short min_posy		:10;  // minimum gate y/top position
							  //  lines for analog video sources or
							  //  lines / 2 for digital video sources
	USHORT spare4		:6;   // spare bits

	// Word 5
	short max_posx		:10;  // maximum gate x/right position
							  //  pixels for analog video sources or
							  //  pixels / 2 for digital video sources
	USHORT spare5		:6;   // spare bits

	// Word 6
	short max_posy		:10;  // maximum gate y/bottom position
							  //  lines for analog video sources or
							  //  lines / 2 for digital video sources
	USHORT spare6		:6;   // spare bits

	// Word 7
	USHORT spare7		:16;  // spare word

	// Word 8
	short  checksum		:16;  // message checksum

} CONFIG_GATE_POS_MSG;

// ---------- Annotation Configuration Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync			:16;  // sync word

	// Word 2
	USHORT spare2		:8;   // spare bits
	USHORT msg_type		:8;   // message type = 202

	// Word 3
	USHORT string2		:5;   // string 2 y position (bottom line)
	USHORT string1	    :5;   // string 1 y position (top line)
	USHORT spare3		:6;   // spare bits

	// Word 4
	USHORT spare4		:16;  // spare word

	// Word 5
	short  checksum		:16;  // message checksum

} CONFIG_ANNOTATION_MSG;

// ---------- Symbology Configuration Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync			:16;  // sync word

	// Word 2
	USHORT spare2		:8;   // spare bits
	USHORT msg_type		:8;   // message type = 203

	// Word 3
	USHORT flash_en		:1;   // enable gate flashing on coast timeout
	USHORT ret_style    :3;   // LOS reticle style (0=solid/closed, 1=open, 2=wide open, 3=custom)
							  //   NOTE: when set to 3=custom, control using CONFIG_LOS_RETICLE_MSG
	USHORT ret_disp		:1;   // LOS reticle display enable
	USHORT ret_thickness:1;   // LOS reticle line thickness (0=double, 1=single)
	USHORT spare3		:10;  // spare bits

	// Word 4
	USHORT spare4		:16;  // spare word

	// Word 5
	short  checksum		:16;  // message checksum

} CONFIG_SYMBOLOGY_MSG;

// ---------- Correlation Configuration Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync			:16;  // sync word

	// Word 2
	USHORT spare2		:8;   // spare bits
	USHORT msg_type		:8;   // message type = 204

	// Word 3
	short ref_x			:10;  // correlation reference image x position
	USHORT spare3		:6;   // spare bits

	// Word 4
	short ref_y			:10;  // correlation reference image y position
	USHORT spare4		:6;   // spare bits

	// Word 5
	USHORT spare5		:16;  // spare word

	// Word 6
	short  checksum		:16;  // message checksum

} CONFIG_CORR_REF_POS_MSG;

// ---------- Video Configuration Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync			:16;  // sync word

	// Word 2
	USHORT spare2		:8;   // spare bits
	USHORT msg_type		:8;   // message type = 205

	// Word 3
	USHORT vid_type		:3;   // video type, PAL = 7, NTSC = 0, DIGITAL = 1
	USHORT spare3		:13;  // spare bits

	// Word 4
	short  checksum		:16;  // message checksum

} CONFIG_VIDEO_MSG;

// ---------- Preset Configuration Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync			:16;  // sync word

	// Word 2
	USHORT spare2		:8;   // spare bits
	USHORT msg_type		:8;   // message type = 206

	// Word 3
	USHORT config_bank	:16;  // default preset configuration bank (0-9) the
							  // tracker will load on power up

	// Word 4
	short  checksum		:16;  // message checksum

} CONFIG_PRESET_CONFIG_MSG;

// ---------- Configure AutoSize Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync				:16;  // sync word

	// Word 2
	USHORT spare2			:8;   // spare bits
	USHORT msg_type			:8;   // message type = 207

	// Word 3
	USHORT enable_rate		:1;   // enable autosize rate control
	USHORT spare3			:15;

	// Word 4 & 5
	USHORT grow_rate_x		:16;  // the rate in pixels per field to grow the gate
	USHORT grow_rate_y		:16;  // the rate in lines per field to grow the gate
								  //   range: 0 to 655.35 (divide by 100 to get value)

	// Word 6 & 7
	USHORT shrink_rate_x	:16;  // the rate in pixels per field to shrink the gate
	USHORT shrink_rate_y	:16;  // the rate in lines per field to shrink the gate
								  //   range: 0 to 655.35 (divide by 100 to get value)

	// Word 8
	short  checksum			:16;  // message checksum

} CONFIG_AUTOSIZE_MSG;

// ---------- Configure Validation Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync				:16;  // sync word

	// Word 2
	USHORT spare2			:8;   // spare bits
	USHORT msg_type			:8;   // message type = 208

	// Word 3
	USHORT min_pixels		:16;  // minimum amount of target pixels
								  //   if the number of thresholded pixels is less
								  //   than this value, you will get a TOO FEW status
								  //   range: 1 to 10k
	// Word 4
	USHORT max_percent		:8;   // maximum amount of target pixels as a percentage of
								  // the max gate pixel count (gate size x * gate size y)
								  //   if this test fails, you will get a TOO MANY status
								  //   range: 1 to 100
	USHORT spare4			:8;

	// Word 5
	USHORT history_depth	:8;   // depth of target history queue (smooths target validation statistics)
								  //   range: 1 to 255
	USHORT spare5			:8;

	// Word 6
	short  checksum			:16;  // message checksum

} CONFIG_VALIDATION_MSG;

// ---------- Config Joystick Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync				:16;  // sync word

	// Word 2
	USHORT spare2			:8;   // spare bits
	USHORT msg_type			:8;   // message type = 209

	// Word 3
	USHORT zoom_scaling		:1;   // enable/disable the zoom scaling (1=enabled)
	USHORT joy_reset		:1;	  // 1=reset joystick parameters to system defaults
	USHORT response_func	:3;	  // joystick response function (0=linear, 1=non-linear, 2=squared)
	USHORT spare3			:11;

	// Word 4 & 5
	short  joy_gain_x		:16;  // joystick x-axis gain (percentage of maximum velocity/output)
	short  joy_gain_y		:16;  // joystick y-axis gain (percentage of maximum velocity/output)
								  //   range: -327.67% to 327.67% (multiply by 100 to set value)

	// Word 6 & 7
	short  joy_offset_x		:16;  // joystick x-axis offset (in 10-bit joystick counts to center)
	short  joy_offset_y		:16;  // joystick y-axis offset (in 10-bit joystick counts to center)

	// Word 8 & 9
	USHORT joy_dead_x		:16;  // joystick x-axis dead band (in 10-bit joystick counts)
	USHORT joy_dead_y		:16;  // joystick y-axis dead band (in 10-bit joystick counts)

	// Word 10
	short  checksum			:16;  // message checksum

} CONFIG_JOYSTICK_MSG;

// ---------- Lens Field of View Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync			:16;  // sync word

	// Word 2
	USHORT spare2		:8;   // spare bits
	USHORT msg_type		:8;   // message type = 210

	// Word 3
	USHORT scalar		:16;  // scalar (divide by 100 to get value)

	// Word 4
	short bias			:16;  // bias (divide by 100 to get value)

	// Word 5
	USHORT fov0			:16;  // FOV0 (divide by 10000 to get value)

	// Word 6
	USHORT fov1			:16;  // FOV1 (divide by 10000 to get value)

	// Word 7
	USHORT fov2			:16;  // FOV2 (divide by 10000 to get value)

	// Word 8
	short  checksum		:16;  // message checksum

} CONFIG_LENS_FOV_MSG;

// -------------- Config Mount Message Structure --------------
typedef struct
{
	// Word 1
	USHORT	sync				:16;  // sync word

	// Word 2
	USHORT	spare2				:8;   // spare bits
	USHORT	msg_type			:8;   // msg type = 211

	// Word 3
	USHORT	mount_type			:16;  // type of mount connected to tracker (0=none)

	// Word 4
	USHORT	auto_drift_cal		:1;   // automatic drift calibration (1=run calibration)
	USHORT	manual_drift_cal	:1;   // manual drift calibration (1=enable calibration mode)
	USHORT	analog_with_serial	:1;   // use the analog error outputs for rate drive during track
									  //   for a mount which is controlled via serial (1=enable)
	USHORT	angle_format		:1;	  // mount position angle display/output format
									  //    0=signed angle (-180 to 180), 1=bearing (0 to 360)
	USHORT	spare4				:12;  // spare bits

	// Word 5 & 6
	short   drift_az			:16;  // azimuth drift calibration value (+/- 10000)
	short   drift_el			:16;  // elevation drift calibration value (+/- 10000)

	// Word 7 & 8
	short	min_az				:16;  // minimum azimuth limit of the mount (-360 to 360)
	short	max_az				:16;  // maximum azimuth limit of the mount (-360 to 360)

	// Word 9 & 10
	short	min_el				:16;  // minimum elevation limit of the mount (-360 to 360)
	short	max_el				:16;  // maximum elevation limit of the mount (-360 to 360)

	// Word 11
	USHORT	spare11				:16;  // spare word

	// Word 12
	short	checksum			:16;  // checksum

} CONFIG_MOUNT_MSG;

// -------------- Config Analog Joystick Message Structure --------------
typedef struct
{
	// Word 1
	USHORT	sync				:16;  // sync word

	// Word 2
	USHORT	spare2				:8;   // spare bits
	USHORT	msg_type			:8;   // msg type = 212

	// Word 3
	USHORT	enable_joystick		:1;   // enable analog joystick (1=enabled)
	USHORT	trk_acq_rising		:1;   // track/acquire rising edge trigger (0=falling edge, 1=rising edge)
	USHORT	offset_aim_act_high	:1;   // offset aim active high (0=low level activation, 1=high level activation)
	USHORT	gain_over_act_high	:1;   // gain override active high (0=low level activation, 1=high level activation)
	USHORT	spare3				:12;  // spare bits

	// Word 4
	USHORT	joy_axis_x			:8;   // joystick x axis analog channel (0=disabled, otherwise 1 through 8)
	USHORT	joy_axis_y			:8;   // joystick y axis analog channel (0=disabled)

	// Word 5
	USHORT	track_acquire		:8;   // track/acquire button analog channel (0=disabled)
	USHORT	offset_aim			:8;   // offset aim button analog channel (0=disabled)

	// Word 6
	USHORT	gain_override		:8;   // gain override button analog channel (0=disabled)
	USHORT	spare6				:8;   // spare bits

	// Word 7 & 8
	short	joy_left_adc		:16;  // joystick left most ADC (analog channel) value
	short	joy_right_adc		:16;  // joystick right most ADC (analog channel) value
									  //   volts = analog * 10/32767

	// Word 9 & 10
	short	joy_up_adc			:16;  // joystick upper most ADC (analog channel) value
	short	joy_down_adc		:16;  // joystick lower most ADC (analog channel) value
									  //   volts = analog * 10/32767

	// Word 11
	USHORT	spare11				:16;  // spare word

	// Word 12
	short	checksum			:16;  // checksum

} CONFIG_ANALOG_JOYSTICK_MSG;

// -------------- Config Digital I/O Message Structure --------------
typedef struct
{
	// Word 1
	USHORT	sync				:16;  // sync word

	// Word 2
	USHORT	spare2				:8;   // spare bits
	USHORT	msg_type			:8;   // msg type = 213

	// Word 3
	USHORT	enable_dio			:1;   // enable user digital I/O (0=digital track error output, 1=user DIO)
	USHORT	port_setup			:3;   // user DIO port setup (0=16in, 1=8in/8out, 2=16out)
	USHORT	enable_unsolicited	:1;   // enable unsolicited field rate DIO reads
	USHORT	spare3				:11;  // spare bits

	// Word 4
	USHORT	bit0_funct			:8;   // function mapping for bit 0 (see DIG_FUNCT_XXX defines)
	USHORT	bit0_logic			:8;   // logic for bit 0 (see DIG_LOGIC_XXX defines)

	// Word 5
	USHORT	bit1_funct			:8;
	USHORT	bit1_logic			:8;

	// Word 6
	USHORT	bit2_funct			:8;
	USHORT	bit2_logic			:8;

	// Word 7
	USHORT	bit3_funct			:8;
	USHORT	bit3_logic			:8;

	// Word 8
	USHORT	bit4_funct			:8;
	USHORT	bit4_logic			:8;

	// Word 9
	USHORT	bit5_funct			:8;
	USHORT	bit5_logic			:8;

	// Word 10
	USHORT	bit6_funct			:8;
	USHORT	bit6_logic			:8;

	// Word 11
	USHORT	bit7_funct			:8;
	USHORT	bit7_logic			:8;

	// Word 12
	USHORT	bit8_funct			:8;
	USHORT	bit8_logic			:8;

	// Word 13
	USHORT	bit9_funct			:8;
	USHORT	bit9_logic			:8;

	// Word 14
	USHORT	bit10_funct			:8;
	USHORT	bit10_logic			:8;

	// Word 15
	USHORT	bit11_funct			:8;
	USHORT	bit11_logic			:8;

	// Word 16
	USHORT	bit12_funct			:8;
	USHORT	bit12_logic			:8;

	// Word 17
	USHORT	bit13_funct			:8;
	USHORT	bit13_logic			:8;

	// Word 18
	USHORT	bit14_funct			:8;
	USHORT	bit14_logic			:8;

	// Word 19
	USHORT	bit15_funct			:8;   // function mapping for bit 15 (see DIG_FUNCT_XXX defines)
	USHORT	bit15_logic			:8;   // logic for bit 15 (see DIG_LOGIC_XXX defines)

	// Word 20
	short	checksum			:16;  // checksum

} CONFIG_DIGITAL_IO_MSG;

// ---------- Config Zoom to Range Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync				:16;  // sync word

	// Word 2
	USHORT spare2			:8;   // spare bits
	USHORT msg_type			:8;   // message type = 214

	// Word 3
	USHORT video_source		:4;   // video source to configure (which lens is connected to)
	USHORT enable			:1;   // enable zoom-to-range for this video source/lens (1=enable)
	USHORT use_one_point	:1;   // use a single point algorithm (min range and max fov only) instead of two points
	USHORT spare3			:10;

	// Word 4
	USHORT min_lens_fov		:16;  // maximum lens (zoom) field-of-view in degrees
								  //   range: 0 to 360.00 (divide by 100 to get value)
	// Word 5
	USHORT max_lens_fov		:16;  // minimum lens (zoom) field-of-view in degrees
								  //   range: 0 to 360.00 (divide by 100 to get value)
	// Word 6 & 7
	USHORT min_range_lsw	:16;  // minimum range in centimeters, least significant word (lsw)
	USHORT min_range_msw	:16;  // and most significant word (msw)
								  // which corresponds to the maximum FOV of the lens
								  // (divide by 100 to get meters)
	// Word 8 & 9
	USHORT max_range_lsw	:16;  // maximum range in centimeters, least significant word (lsw)
	USHORT max_range_msw	:16;  // and most significant word (msw)
								  // which corresponds to the minimum FOV of the lens
								  // (divide by 100 to get meters)
	// Word 10
	short  checksum			:16;  // message checksum

} CONFIG_ZOOM_TO_RANGE_MSG;

// ---------- Config Gate Style Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync				:16;  // sync word

	// Word 2
	USHORT spare2			:8;   // spare bits
	USHORT msg_type			:8;   // message type = 215

	// Word 3
	USHORT acq_style		:1;   // gate style when in acquire/off (0=solid, 1=corners)
	USHORT trk_style		:1;   // gate style when in track/coast (0=solid, 1=corners)
	USHORT corner_type		:1;   // type of corners (0=manual/fixed size, 1=automatic)
	USHORT lock_symmetry	:1;	  // make the gate corners symmetric (0=independent, 1=symmetric)
	USHORT spare3			:12;  // spare bits

	// Word 4
	USHORT fixed_size_x		:16;  // fixed X size of gate corners
								  //   range: 0 to 1023 pixels
	// Word 5
	USHORT fixed_size_y		:16;  // fixed Y size of gate corners
								  //   range: 0 to 1023 lines
	// Word 6
	USHORT percent_size_x	:8;   // percentage X gate size to use for corners
	USHORT percent_size_y	:8;   // percentage Y gate size to use for corners
								  //   range: 0 to 100 percent
	// Word 7
	USHORT min_size_x		:16;  // minimum X size of gate corners when in auto
								  //   range: 0 to 1023 pixels
	// Word 8
	USHORT min_size_y		:16;  // minimum Y size of gate corners when in auto
								  //   range: 0 to 1023 lines
	// Word 9
	USHORT max_size_x		:16;  // maximum X size of gate corners when in auto
								  //   range: 0 to 1023 pixels
	// Word 10
	USHORT max_size_y		:16;  // maximum Y size of gate corners when in auto
								  //   range: 0 to 1023 lines
	// Word 11
	USHORT spare11			:16;

	// Word 12
	short  checksum			:16;  // message checksum

} CONFIG_GATE_STYLE_MSG;

// ---------- Config Gate Reticle Message Structure ----------
//
// NOTE: The second gate is used as the reticle, so dual
//       gates mode must be disabled to use this feature.
//
// See new message CONFIG_GATE_RETICLE2_MSG (type 235)
//
typedef struct
{
	// Word 1
	USHORT sync				:16;  // sync word

	// Word 2
	USHORT spare2			:8;   // spare bits
	USHORT msg_type			:8;   // message type = 216

	// Word 3
	USHORT enable			:1;   // enable gate as reticle (0=normal gate, 1=use as reticle)
	USHORT spare3			:15;  // spare bits

	// Word 4
	short  reticle_pos_x	:16;  // reticle position (X)

	// Word 5
	short  reticle_pos_y	:16;  // reticle position (Y)

	// Word 6
	USHORT reticle_size_x	:16;  // reticle size (X)

	// Word 7
	USHORT reticle_size_y	:16;  // reticle size (Y)

	// Word 8
	USHORT corner_size_x	:16;  // reticle corner size (X)

	// Word 9
	USHORT corner_size_y	:16;  // reticle corner size (Y)

	// Word 10
	short  checksum			:16;  // message checksum

} CONFIG_GATE_RETICLE_MSG;

// ---------- Config LOS Reticle Message Structure ----------
//
// NOTE: Only used if ret_style set to 3 (custom) in the CONFIG_SYMBOLOGY_MSG
//
typedef struct
{
	// Word 1
	USHORT sync				:16;  // sync word

	// Word 2
	USHORT spare2			:8;   // spare bits
	USHORT msg_type			:8;   // message type = 217

	// Word 3
	USHORT spare3			:16;

	// Word 4 & 5
	short  left_start		:16;  // left leg of reticle start point
	short  left_stop		:16;  // left leg of reticle stop point (start < stop)
								  //   range: 0 to -511 pixels
	// Word 6 & 7
	short  right_start		:16;  // right leg of reticle start point
	short  right_stop		:16;  // right leg of reticle stop point (start < stop)
								  //   range: 0 to 511 pixels
	// Word 8 & 9
	short  top_start		:16;  // top leg of reticle start point
	short  top_stop			:16;  // top leg of reticle stop point (start > stop)
								  //   range: 0 to 511 lines
	// Word 10 & 11
	short  bottom_start		:16;  // bottom leg of reticle start point
	short  bottom_stop		:16;  // bottom leg of reticle stop point (start > stop)
								  //   range: 0 to -511 lines
	// Word 12
	short  checksum			:16;  // message checksum

} CONFIG_LOS_RETICLE_MSG;

// ---------- Config Track Flag Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync				:16;  // sync word

	// Word 2
	USHORT spare2			:8;   // spare bits
	USHORT msg_type			:8;   // message type = 218

	// Word 3
	USHORT type				:4;	  // track flag type (0=line, 1=crosshair)
	USHORT thickness		:1;   // thickness of line drawing (0=single, 1=double)
	USHORT spare3			:11;

	// Word 4 & 5
	short  left_start		:16;  // left leg of crosshair start point
	short  left_stop		:16;  // left leg of crosshair stop point (start < stop)
								  //   range: 0 to -511 pixels
	// Word 6 & 7
	short  right_start		:16;  // right leg of crosshair start point
	short  right_stop		:16;  // right leg of crosshair stop point (start < stop)
								  //   range: 0 to 511 pixels
	// Word 8 & 9
	short  top_start		:16;  // top leg of crosshair start point
	short  top_stop			:16;  // top leg of crosshair stop point (start > stop)
								  //   range: 0 to 511 lines
	// Word 10 & 11
	short  bottom_start		:16;  // bottom leg of crosshair start point
	short  bottom_stop		:16;  // bottom leg of crosshair stop point (start > stop)
								  //   range: 0 to -511 lines
	// Word 12
	short  checksum			:16;  // message checksum

} CONFIG_TRACK_FLAG_MSG;

// ---------- Config North Offset Message Structure ----------
//
// NOTE: This message informs the tracker about an azimuth mount offset
//       which is applied in the mount controller.  Currently, this
//       message is only supported when using the MOUNT_RPM_XXXX type.
//
typedef struct
{
	// Word 1
	USHORT sync					:16;  // sync word

	// Word 2
	USHORT spare2				:8;   // spare bits
	USHORT msg_type				:8;   // message type = 219

	// Word 3
	USHORT enable				:1;   // enable the north offset
	USHORT spare3				:15;

	// Word 4 & 5
	USHORT mount_bearing_lsw	:16;  // the mount azimuth bearing as reported by the controller in degrees (0 to 360)
	USHORT mount_bearing_msw	:16;  // least significant word (lsw) and most significant word (msw)
									  // (multiply float by 10,000 to set value)
	// Word 6 & 7
	USHORT measured_angle_lsw	:16;  // the measured "true" azimuth bearing of the mount in degrees (0 to 360)
	USHORT measured_angle_msw	:16;  // least significant word (lsw) and most significant word (msw)
									  // (multiply float by 10,000 to set value)
	// Word 8
	short  checksum				:16;  // message checksum

} CONFIG_NORTH_OFFSET_MSG;

// ---------- Config Digital Video Message Structure ----------
//
// FPGA type HW_FPGA_XC4V_LX80 or greater ONLY
//
typedef struct
{
	// Word 1
	USHORT sync						:16;  // sync word

	// Word 2
	USHORT spare2					:8;   // spare bits
	USHORT msg_type					:8;   // message type = 220

	// Word 3
	USHORT scan_mode				:1;	  // video scan mode (0=progressive, 1=interlaced)
	USHORT bits_per_pixel			:3;   // bits per pixel (0=8bpp, 1=10bpp, 2=12bpp, 3=14bpp, 4=16bpp)
	USHORT pixels_per_clock			:1;	  // pixels per clock cycle (0=one pixel per clock, 1=two pixels per clock)
	USHORT pixel_clock_edge			:1;	  // pixel clock edge (0=falling edge, 1=rising edge)
										  //   ALWAYS rising edge for 6000 series, 7005-CL and 7005-HD
	USHORT line_polarity			:1;	  // line valid polarity (0=active low, 1=active high)
	USHORT frame_polarity			:1;	  // frame valid polarity (0=active low, 1=active high)
	USHORT data_polarity			:1;	  // pixel data polarity (0=normal, 1=inverse)
	USHORT pixels_per_clock_ext		:4;   // extended pixels per clock cycle (0=use older pixels_per_clock variable)
	USHORT enable_data_valid		:1;   // use data valid signal to qualify video (1=enabled, will delay video by one line)
	USHORT spare3					:2;

	// Word 4
	USHORT enable_nuc				:1;   // enable camera normalization (NUC) and bad pixel correction (Model 7005-CL ONLY)
	USHORT spare4					:15;

	// Word 5
	USHORT custom_output			:1;	  // 1=custom output settings (different than the input)
	USHORT out_bits_per_pixel		:3;   // bits per pixel (0=8bpp, 1=10bpp, 2=12bpp, 3=14bpp, 4=16bpp)
	USHORT out_pixels_per_clock		:4;	  // pixels per clock cycle (see pixels_per_clock_ext)
	USHORT out_pixel_clock_edge		:1;	  // pixel clock edge (0=falling edge, 1=rising edge)
	USHORT out_line_polarity		:1;	  // line valid polarity (0=active low, 1=active high)
	USHORT out_frame_polarity		:1;	  // frame valid polarity (0=active low, 1=active high)
	USHORT out_data_polarity		:1;	  // pixel data polarity (0=normal, 1=inverse)
	USHORT spare5					:4;

	// Word 6
	short  checksum					:16;  // message checksum

} CONFIG_DIGITAL_VIDEO_MSG;

// ---------- Config Annotation 2 Message Structure ----------
//
// FPGA type HW_FPGA_XC4V_LX80 or greater ONLY
//
// To be used only on Trackers with a Virtex 4 FPGA type instead of
// the CONFIG_ANNOTATION_MSG.
//
typedef struct
{
	// Word 1
	USHORT sync			:16;  // sync word

	// Word 2
	USHORT spare2		:8;   // spare bits
	USHORT msg_type		:8;   // message type = 221

	// Word 3
	USHORT string2		:8;   // string 2 y position (bottom line)
	USHORT string1	    :8;   // string 1 y position (top line)

	// Word 4
	USHORT anno_size_x	:2;	  // text annotation size x (0=small, 1=medium, 2=large, 3=extra large)
	USHORT anno_size_y	:2;	  // text annotation size y (0=small, 1=medium, 2=large, 3=extra large)
	USHORT spare4		:12;  // spare word

	// Word 5
	USHORT spare5		:16;

	// Word 6
	short  checksum		:16;  // message checksum

} CONFIG_ANNOTATION2_MSG;

// ---------- Config Serial Ports Message Structure ----------
//
// Some 7000 and 8000 series of video trackers
// do not have a physical switches to set RS232/RS422
// for serial ports 1-7 (UART0 is always setup via jumper/switch).
//
typedef struct
{
	// Word 1
	USHORT sync			:16;  // sync word

	// Word 2
	USHORT spare2		:8;   // spare bits
	USHORT msg_type		:8;   // message type = 222

	// Word 3
	USHORT uart0		:1;   // UART0 GUI, 0=RS-232 1=RS-422 (QUERY/READ ONLY)
	USHORT uart1		:1;   // UART1 controller, 0=RS-232 1=RS-422
	USHORT uart2		:1;   // UART2 mount, 0=RS-232 1=RS-422
	USHORT uart3		:1;   // UART3, 0=RS-232 1=RS-422
	USHORT uart4		:1;   // UART4, 0=RS-232 1=RS-422
	USHORT uart5		:1;   // UART5, 0=RS-232 1=RS-422
	USHORT uart6		:1;   // UART6, 0=RS-232 1=RS-422
	USHORT uart7		:1;   // UART7, 0=RS-232 1=RS-422
	USHORT spare3	    :8;

	// Word 4
	short  checksum		:16;  // message checksum

} CONFIG_SERIAL_PORTS_MSG;

// ---------- Config Control Box Message Structure ----------
//
// Configuration for the 702 Controller
//
typedef struct
{
	// Word 1
	USHORT sync			:16;  // sync word

	// Word 2
	USHORT spare2		:8;   // spare bits
	USHORT msg_type		:8;   // message type = 223

	// Word 3
	USHORT vid_select1	:8;	  // video source selected when switch is in the 1 position (default=VS_ANALOG1)
	USHORT vid_select2	:8;	  // video source selected when switch is in the 2 position (default=VS_ANALOG2)

	// Word 4
	USHORT spare4;

	// Word 5
	USHORT spare5;

	// Word 6
	short  checksum		:16;  // message checksum

} CONFIG_CONTROL_BOX_MSG;

// ---------- Config Target Simulator Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync;				  // sync word

	// Word 2
	USHORT use_custom_fov	:1;   // use the field-of-view parameters specified in this message instead of
								  //   the parameters from the tracker's current lens source
	USHORT spare2			:7;   // spare bits
	USHORT msg_type			:8;   // message type = 224

	// Word 3 & 4
	short  position_x_lsw;		  // initial target X position in millimeters, least significant word (lsw)
	short  position_x_msw;		  // and most significant word (msw)

	// Word 5 & 6	(NOTE: AT THIS TIME, NEGATIVE Y POSITIONS ARE NOT SUPPORTED)
	short  position_y_lsw;		  // initial target Y position in millimeters, least significant word (lsw)
	short  position_y_msw;		  // and most significant word (msw)

	// Word 7 & 8
	short  position_z_lsw;		  // initial target Z position in millimeters, least significant word (lsw)
	short  position_z_msw;		  // and most significant word (msw)

	// Word 9 & 10
	short  velocity_x_lsw;		  // target X velocity in millimeters/second, least significant word (lsw)
	short  velocity_x_msw;		  // and most significant word (msw)

	// Word 11 & 12
	short  velocity_y_lsw;		  // target Y velocity in millimeters/second, least significant word (lsw)
	short  velocity_y_msw;		  // and most significant word (msw)

	// Word 13 & 14
	short  velocity_z_lsw;		  // target Z velocity in millimeters/second, least significant word (lsw)
	short  velocity_z_msw;		  // and most significant word (msw)

	// Word 15 & 16
	short  accel_x_lsw;			  // target X acceleration in millimeters/second^2, least significant word (lsw)
	short  accel_x_msw;			  // and most significant word (msw)

	// Word 17 & 18
	short  accel_y_lsw;			  // target Y acceleration in millimeters/second^2, least significant word (lsw)
	short  accel_y_msw;			  // and most significant word (msw)

	// Word 19 & 20
	short  accel_z_lsw;			  // target Z acceleration in millimeters/second^2, least significant word (lsw)
	short  accel_z_msw;			  // and most significant word (msw)

	// Word 21 & 22
	USHORT accel_cutoff_lsw;	  // acceleration cutoff time in milliseconds, least significant word (lsw)
	USHORT accel_cutoff_msw;	  // and most significant word (msw)

	// Word 23 & 24
	USHORT size_x_lsw;			  // target X size in millimeters, least significant word (lsw)
	USHORT size_x_msw;			  // and most significant word (msw)

	// Word 25 & 26
	USHORT size_y_lsw;			  // target Y size in millimeters, least significant word (lsw)
	USHORT size_y_msw;			  // and most significant word (msw)

	// Word 27
	USHORT intensity;			  // target intensity/color

	// Word 28
	USHORT fov_horizontal;		  // horizontal (X) field-of-view of the camera/lens in degrees
								  //   range: 0 to 360.00 (divide by 100 to get value)
	// Word 29
	USHORT fov_vertical;		  // vertical (Y) field-of-view of the camera/lens in degrees
								  //   range: 0 to 360.00 (divide by 100 to get value)
	// Word 30 & 31
	USHORT duration_lsw;		  // total simulation time in milliseconds, least significant word (lsw)
	USHORT duration_msw;		  // and most significant word (msw)

	// Word 32
	short  checksum;			  // message checksum

} CONFIG_TARGET_SIMULATOR_MSG;

// ---------- Config Clutter Rejection Processor Message Structure ----------
// THIS MESSAGE AND FUNCTIONALLITY IS OBSOLETE.
// PLEASE USE MULT-TARGET INSTEAD.
typedef struct
{
	// Word 1
	USHORT sync;				  // sync word

	// Word 2
	USHORT spare2			:8;   // spare bits
	USHORT msg_type			:8;   // message type = 225

	// Word 3
	short  gate_pos_x;			  // CRP gate position X

	// Word 4
	short  gate_pos_y;			  // CRP gate position Y

	// Word 5
	USHORT gate_size_x;			  // CRP gate size X

	// Word 6
	USHORT gate_size_y;			  // CRP gate size Y

	// Word 7
	USHORT min_life;			  // target minimum life (in fields/frames)

	// Word 8 & 9
	USHORT min_count_lsw;		  // target minimum pixel count, least significant word (lsw)
	USHORT min_count_msw;		  // and most significant word (msw)

	// Word 10 & 11
	USHORT max_count_lsw;		  // target maximum pixel count, least significant word (lsw)
	USHORT max_count_msw;		  // and most significant word (msw)

	// Word 12 & 13
	USHORT min_ave_growth_lsw;	  // target minimum average growth (in pixels), least significant word (lsw)
	USHORT min_ave_growth_msw;	  // and most significant word (msw)

	// Word 14
	USHORT max_coast;			  // target maximum coast time (in frames/fields)

	// Word 15
	USHORT growth_filter_alpha;	  // growth filter alpha parameter
								  //   range: 0.0 to 1.0 (divide by 10,000 to get value)
	// Word 16
	USHORT gate_size_ratio;		  // gate size ratio (divide by 100 to get value)
								  //    range: 1.00 to 655.35 (ex: 200 is a 2:1 gate to target ratio)
	// Word 17
	USHORT enhancement		:1;	  // object image enhancement enable (0=off, 1=on)
	USHORT spare17			:15;

	// Word 18
	short  checksum;			  // message checksum

} CONFIG_CRP_MSG;

// ---------- Config AutoThreshold Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync					:16;  // sync word

	// Word 2
	USHORT spare2				:8;   // spare bits
	USHORT msg_type				:8;   // message type = 226

	// Word 3
	USHORT enable_alpha_filter	:1;   // enable alpha filter
	USHORT spare3				:15;

	// Word 4
	USHORT acquire_alpha		:16;  // the filter alpha when in acquire mode
									  //   range: 0 to 1.0000 (divide by 10,000 to get value)
	// Word 5
	USHORT track_alpha			:16;  // the filter alpha when in track mode
									  //   range: 0 to 1.0000 (divide by 10,000 to get value)
	// Word 6
	USHORT min_contrast			:16;  // minimum acceptable target contrast level (as a percentage)
									  //   range: 0.00 to 100.00 (divide by 100 to get value)
	// Word 7
	USHORT spare7				:16;

	// Word 8
	short  checksum				:16;  // message checksum

} CONFIG_AUTOTHRESHOLD_MSG;

// ---------- Config Ethernet Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync					:16;  // sync word

	// Word 2
	USHORT spare2				:8;   // spare bits
	USHORT msg_type				:8;   // message type = 227

	// Word 3
	USHORT enable_dhcp			:1;   // enable DHCP
	USHORT spare3				:15;

	// Word 4 & 5
	UCHAR  ip_addr_b1;				  // IP address (b1.b2.b3.b4)
	UCHAR  ip_addr_b2;
	UCHAR  ip_addr_b3;
	UCHAR  ip_addr_b4;

	// Word 6 & 7
	UCHAR  subnet_mask_b1;			  // subnet mask (b1.b2.b3.b4)
	UCHAR  subnet_mask_b2;
	UCHAR  subnet_mask_b3;
	UCHAR  subnet_mask_b4;

	// Word 8 & 9
	UCHAR  gateway_b1;				  // gateway (b1.b2.b3.b4)
	UCHAR  gateway_b2;
	UCHAR  gateway_b3;
	UCHAR  gateway_b4;

	// Word 10
	short  checksum				:16;  // message checksum

} CONFIG_ETHERNET_MSG;

// ---------- Config Digital Video Ext Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync					:16;  // sync word

	// Word 2
	USHORT spare2				:8;   // spare bits
	USHORT msg_type				:8;   // message type = 228

	// Word 3
	USHORT enable_nonstandard	:1;   // enable non-standard digital video input support
	USHORT enable_frame_valid	:1;   // enable the use of the frame valid signal
	USHORT enable_line_valid	:1;   // enable the use of the line valid signal
	USHORT enable_data_valid	:1;   // enable the use of the data valid signal
	USHORT spare3				:12;

	// Word 4
	USHORT active_pixels		:16;  // pixels per line

	// Word 5
	USHORT active_lines			:16;  // lines per frame

	// Word 6
	USHORT line_sync_pixels		:16;  // number of idle pixels between lines (aka-horizontal sync time)
									  // NOTE: This is used to construct a standard output from the input signal
	// Word 7
	USHORT spare7;

	// Word 8
	USHORT spare8;

	// Word 9
	USHORT spare9;

	// Word 10
	short  checksum				:16;  // message checksum

} CONFIG_DIGITAL_VIDEO_EXT_MSG;

// ---------- Config Digital Preprocess Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync					:16;  // sync word

	// Word 2
	USHORT spare2				:8;   // spare bits
	USHORT msg_type				:8;   // message type = 229

	// Word 3
	USHORT enable_crop			:1;   // enable cropping of the input digital video
	USHORT enable_line_flip		:1;   // enable flipping each digital video line (horizontal flip)
	USHORT enable_frame_flip	:1;   // enable flipping the digital video frame (vertical flip)
	USHORT spare3				:13;

	// Word 4
	USHORT crop_top				:16;  // starting line where all lines above this are removed (0=first line)
									  //    NOTE: all cropping values are inclusive
	// Word 5
	USHORT crop_bottom			:16;  // stop line where all lines below this are removed

	// Word 6
	USHORT crop_left			:16;  // starting pixel where all pixels before this are removed (0=first pixel)

	// Word 7
	USHORT crop_right			:16;  // stop pixel where all pixels after this are removed

	// Word 8
	short  checksum				:16;  // message checksum

} CONFIG_DIGITAL_PREPROCESS_MSG;

// ---------- Config IFF Track Message Structure ----------
// NOTE: Azimuth tracks using an analog error voltage processed through
//       a lookup table and PID filter.  Elevation uses position tracking
//       via user supplied position updates (see MOUNT_CONTROL_MSG)
//       with the PID values specified in this message.  The pedestal
//       is set to velocity mode when IFF tracking is enabled.
typedef struct
{
	// Word 1
	USHORT sync					:16;  // sync word

	// Word 2
	USHORT spare2				:8;   // spare bits
	USHORT msg_type				:8;   // message type = 230

	// Word 3
	USHORT enable_iff_track		:1;	  // enable IFF tracking
	USHORT invert_az			:1;	  // invert the sign for the azimuth drive (0=normal, 1=invert)
	USHORT invert_el			:1;	  // invert the sign for the elevation drive (0=normal, 1=invert)
	USHORT spare3				:13;

	// Word 4
	// NOTE: Analog input channels range from 0 to 7
	USHORT az_rss1_channel		:4;	  // analog input channel to use for Azimuth Received Signal Strength 1 (RSS1)
	USHORT az_rss2_channel		:4;	  // analog input channel to use for Azimuth Received Signal Strength 2 (RSS2)
	USHORT az_error_channel		:4;   // analog input channel to use for Azimuth Pointing Error (AzPE)
	USHORT spare4				:4;

	// NOTE: To convert +/-10 volts to a desired analog threshold use the following equation
	//       analog = volts * 32767 / 10

	// Word 5
	short  az_rss1_threshold;		  // Received Signal Strength 1 (RSS1) analog threshold value
									  //   voltages below this value will indicate an invalid AzPE
	// Word 6
	short  az_rss2_threshold;		  // Received Signal Strength 2 (RSS2) analog threshold value
									  //   voltages below this value will indicate an invalid AzPE
	// Word 7
	USHORT az_proportion;			  // proportion term for azimuth PID filter (P)
									  //   this value is scaled by 100
	// Word 8
	USHORT az_integral;				  // integral term for azimuth PID filter (I)
									  //   this value is scaled by 1000
	// Word 9
	USHORT az_derivative;			  // derivative term for azimuth PID filter (D)
									  //   this value is scaled by 1000
	// Word 10
	USHORT az_integral_limit;		  // limit on the integrator for azimuth PID filter
									  //   this value is scaled by 10 (0=disable/no limit)
	// Word 11
	USHORT az_coast_timeout;		  // timeout in video fields/frames to stop tracking
									  //   after RSS1 and RSS2 are no longer valid (0=stop immediately)
	// Word 12
	USHORT el_filter_lambda;		  // elevation tracking filter lambda parameter
									  //   this value is scaled by 1000
	// Word 13
	USHORT el_filter_limit;			  // elevation tracker filter error limit in degrees
									  //   this value is scaled by 1000
	// Word 14
	USHORT el_proportion;			  // proportion term for elevation PID filter (P)
									  //   this value is scaled by 100
	// Word 15
	USHORT el_integral;				  // integral term for elevation PID filter (I)
									  //   this value is scaled by 1000
	// Word 16
	USHORT el_derivative;			  // derivative term for elevation PID filter (D)
									  //   this value is scaled by 1000
	// Word 17
	USHORT el_integral_limit;		  // limit on the integrator for elevation PID filter
									  //   this value is scaled by 10 (0=disable/no limit)
	// Word 18
	USHORT el_timeout;				  // timeout in video fields/frames to stop tracking
									  //   if the tracker does not see a new position message
	// Word 19
	USHORT spare19;					  // spare word

	// Word 20
	short  checksum				:16;  // message checksum

} CONFIG_IFF_TRACK_MSG;

// ---------- Config Intrusion Detect Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync					:16;  // sync word

	// Word 2
	USHORT spare2				:8;   // spare bits
	USHORT msg_type				:8;   // message type = 231

	// Word 3
	USHORT enable				:1;   // enable intrusion detection
	USHORT spare3				:7;
	USHORT algorithm			:8;   // algorithm to use (0=intr gate pixel count, 1=percent intr gate pixel count,
									  //                   2=percent target pixel count)
	// Word 4
	USHORT threshold_count		:16;  // absolute count threshold (use depends on algorithm)

	// Word 5
	USHORT threshold_percent	:16;  // percentage threshold (use depends on algorithm)
									  //   this value is scaled by 100 (250=2.50%)
	// Word 6
	USHORT size_x				:8;   // intrusion gate size (around the current gate) in
	USHORT size_y				:8;   //   both x (pixels) and y (lines)

	// Word 7
	USHORT spare7				:16;

	// Word 8
	short  checksum				:16;  // message checksum

} CONFIG_INTRUSION_DETECT_MSG;

// ---------- Config Position Track Message Structure ----------
//	The pedestal is set to velocity mode when position tracking is enabled.
typedef struct
{
	// Word 1
	USHORT sync						:16;  // sync word

	// Word 2
	USHORT spare2					:8;   // spare bits
	USHORT msg_type					:8;   // message type = 232

	// Word 3
	USHORT enable					:1;	  // enable position tracking
	USHORT invert_az				:1;	  // invert the sign for the azimuth drive (0=normal, 1=invert)
	USHORT invert_el				:1;	  // invert the sign for the elevation drive (0=normal, 1=invert)
	USHORT spare3					:13;

	// Word 4
	USHORT az_threshold; 				  // azimuth threshold in degrees to switch between far and near parameters
										  //   this value is scaled by 1000 (0.001 to 65.535)
	// Word 5
	USHORT az_filter_lambda;			  // azimuth tracking filter lambda parameter
										  //   this value is scaled by 1000 (0.001 to 1.000)
	// Word 6
	USHORT az_filter_limit;				  // azimuth tracking filter error limit in degrees
										  //   this value is scaled by 1000 (0.001 to 65.535)
	// Word 7
	USHORT az_rejected_points_limit;	  // azimuth tracking filter rejected points limit
										  //   (number of points which exceed az_filter_limit before reset)
	// Word 8
	USHORT az_near_proportion;			  // proportion term for azimuth PI filter (P)
										  //   this value is scaled by 100 (0.01 to 655.35)
	// Word 9
	USHORT az_near_integral;			  // integral term for azimuth PI filter (I)
										  //   this value is scaled by 1000 (0.001 to 65.535)
	// Word 10
	USHORT az_near_integral_limit;		  // limit on the integrator for azimuth PI filter
										  //   this value is scaled by 10 (0=disable/no limit)
	// Word 11
	USHORT az_far_proportion;			  // proportion term for azimuth PI filter (P)
										  //   this value is scaled by 100 (0.01 to 655.35)
	// Word 12
	USHORT az_far_integral;				  // integral term for azimuth PI filter (I)
										  //   this value is scaled by 1000 (0.001 to 65.535)
	// Word 13
	USHORT az_far_integral_limit;		  // limit on the integrator for azimuth PI filter
										  //   this value is scaled by 10 (0=disable/no limit)
	// Word 14
	USHORT el_threshold;				  // elevation threshold in degrees to switch between far and near parameters
										  //   this value is scaled by 1000 (0.001 to 65.535)
	// Word 15
	USHORT el_filter_lambda;			  // elevation tracking filter lambda parameter
										  //   this value is scaled by 1000 (0.001 to 1.000)
	// Word 16
	USHORT el_filter_limit;				  // elevation tracking filter error limit in degrees
										  //   this value is scaled by 1000 (0.001 to 65.535)
	// Word 17
	USHORT el_rejected_points_limit;	  // elevation tracking filter rejected points limit
										  //   (number of points which exceed el_filter_limit before reset)
	// Word 18
	USHORT el_near_proportion;			  // proportion term for elevation PI filter (P)
										  //   this value is scaled by 100 (0.01 to 655.35)
	// Word 19
	USHORT el_near_integral;			  // integral term for elevation PI filter (I)
										  //   this value is scaled by 1000 (0.001 to 65.535)
	// Word 20
	USHORT el_near_integral_limit;		  // limit on the integrator for elevation PI filter
										  //   this value is scaled by 10 (0=disable/no limit)
	// Word 21
	USHORT el_far_proportion;			  // proportion term for elevation PI filter (P)
										  //   this value is scaled by 100 (0.01 to 655.35)
	// Word 22
	USHORT el_far_integral;				  // integral term for elevation PI filter (I)
										  //   this value is scaled by 1000 (0.001 to 65.535)
	// Word 23
	USHORT el_far_integral_limit;		  // limit on the integrator for elevation PI filter
										  //   this value is scaled by 10 (0=disable/no limit)
	// Word 24
	USHORT timeout;						  // timeout in video fields/frames to stop position tracking
										  //   if the tracker does not see a new position message
	// Word 25
	short  checksum;					  // message checksum

} CONFIG_POS_TRACK_MSG;

// -------------- Config Control Box I/O Message Structure --------------
typedef struct
{
	// Word 1
	USHORT	sync				:16;  // sync word

	// Word 2
	USHORT	spare2				:8;   // spare bits
	USHORT	msg_type			:8;   // msg type = 233

	// Word 3
	USHORT	enable_dio			:1;   // enable digital I/O function mapping
	USHORT	spare3				:15;  // spare bits

	// Word 4
	USHORT	bit0_funct			:8;   // function mapping for bit 0 (see DIG_FUNCT_XXX defines)
	USHORT	bit0_logic			:8;   // logic for bit 0 (see DIG_LOGIC_XXX defines)

	// Word 5
	USHORT	bit1_funct			:8;
	USHORT	bit1_logic			:8;

	// Word 6
	USHORT	bit2_funct			:8;
	USHORT	bit2_logic			:8;

	// Word 7
	USHORT	bit3_funct			:8;
	USHORT	bit3_logic			:8;

	// Word 8
	USHORT	bit4_funct			:8;
	USHORT	bit4_logic			:8;

	// Word 9
	USHORT	bit5_funct			:8;
	USHORT	bit5_logic			:8;

	// Word 10
	USHORT	bit6_funct			:8;
	USHORT	bit6_logic			:8;

	// Word 11
	USHORT	bit7_funct			:8;
	USHORT	bit7_logic			:8;

	// Word 12
	USHORT	bit8_funct			:8;
	USHORT	bit8_logic			:8;

	// Word 13
	USHORT	bit9_funct			:8;
	USHORT	bit9_logic			:8;

	// Word 14
	USHORT	bit10_funct			:8;
	USHORT	bit10_logic			:8;

	// Word 15
	USHORT	bit11_funct			:8;
	USHORT	bit11_logic			:8;

	// Word 16
	USHORT	bit12_funct			:8;
	USHORT	bit12_logic			:8;

	// Word 17
	USHORT	bit13_funct			:8;
	USHORT	bit13_logic			:8;

	// Word 18
	USHORT	bit14_funct			:8;
	USHORT	bit14_logic			:8;

	// Word 19
	USHORT	bit15_funct			:8;   // function mapping for bit 15 (see DIG_FUNCT_XXX defines)
	USHORT	bit15_logic			:8;   // logic for bit 15 (see DIG_LOGIC_XXX defines)

	// Word 20
	short	checksum			:16;  // checksum

} CONFIG_CONTROL_BOX_IO_MSG;

// -------------- Config Video Switch Message Structure -----------------
typedef struct  
{
	// Word 1
	USHORT	sync					:16;  // sync word

	// Word 2
	USHORT	spare2					:8;   // spare bits
	USHORT	msg_type				:8;   // msg type = 234

	// Word 3
	USHORT	analog_switch_type		:8;   // analog video switch type (0=none, 1=Extron MMX 42 AV, ...)
	USHORT	analog_switch_function	:8;   // analog video switch function (0=none, 1=unselected out, ...)

	// Word 4
	USHORT  analog_switch_port		:8;   // serial port analog video switch is connected to (3-7, 0-2 are reserved)

	USHORT	analog_switch_present	:1;	  // Switch is present and communicating with the tracker (query only)
	USHORT	analog_switch_error		:1;	  // Switch error; comm-error, NAKs, etc. (query only)
	USHORT  spare4					:6;

	// Word 5
	USHORT	digital_switch_type		:8;	  // digital video switch type (0=none, 1=Phrontier Clever, ...)
	USHORT  digital_switch_function	:8;	  // digital function value related to the digital_switch_type

	// Word 6
	USHORT	digital_switch_port		:8;   // serial port digital video switch is connected to (3-7, 0-2 are reserved)

	USHORT	digital_switch_present	:1;	  // Switch is present and communicating with the tracker (query only)
	USHORT	digital_switch_error	:1;	  // Switch error; comm-error, NAKs, etc. (query only)
	USHORT  spare6					:6;

	// Word 7
	USHORT	spare7					:16;

	// Word 8
	short	checksum				:16;  // checksum

} CONFIG_VIDEO_SWITCH_MSG;

// ---------- Config Gate Reticle 2 Message Structure ----------
//
// NOTE: The second gate is used as the reticle, so dual
//       gates mode must be disabled to use this feature.
//
typedef struct
{
	// Word 1
	USHORT sync				:16;  // sync word

	// Word 2
	USHORT spare2			:8;   // spare bits
	USHORT msg_type			:8;   // message type = 235

	// Word 3
	USHORT enable			:1;   // enable gate as reticle (0=normal gate/disable, 1=use as reticle/enable)
	USHORT size_units		:1;   // reticle size units (0=pixel/lines, 1=degrees)
	USHORT size_symmetry	:1;	  // make the reticle symmetric (0=independent, 1=symmetric use X only)
	USHORT style			:1;   // reticle style (0=solid, 1=corners)
	USHORT corner_type		:1;   // type of corners (0=manual/fixed size, 1=automatic)
	USHORT corner_symmetry	:1;	  // make the corners symmetric (0=independent, 1=symmetric use X only)
	USHORT spare3			:10;  // spare bits

	// Word 4
	short  reticle_pos_x	:16;  // reticle position (X)

	// Word 5
	short  reticle_pos_y	:16;  // reticle position (Y)

	// Word 6
	USHORT reticle_size_x	:16;  // reticle size (X)
								  //   range: if size_units=0: 0 to 1023 pixels
								  //          if size_units=1: 0.00 to 360.00 degrees (scaled by 100)
	// Word 7
	USHORT reticle_size_y	:16;  // reticle size (Y), not used if size_symmetry=1
								  //   range: if size_units=0: 0 to 1023 lines
								  //          if size_units=1: 0.00 to 360.00 degrees (scaled by 100)
	// Word 8
	USHORT corner_fixed_x	:16;  // reticle fixed corner size (X)
								  //   range: 0 to 1023 pixels
	// Word 9
	USHORT corner_fixed_y	:16;  // reticle fixed corner size (Y), not used if corner_symmetry=1
								  //   range: 0 to 1023 lines
	// Word 10
	USHORT corner_percent_x	:8;   // percentage X gate size to use for corners when corner_type=1 (auto)
	USHORT corner_percent_y	:8;   // percentage Y gate size to use for corners when corner_type=1 (auto)
								  //   range: 0 to 100 percent
	// Word 11
	USHORT corner_min_x		:16;  // minimum X size of gate corners when corner_type=1 (auto)
								  //   range: 0 to 1023 pixels
	// Word 12
	USHORT corner_min_y		:16;  // minimum Y size of gate corners when corner_type=1 (auto)
								  //   range: 0 to 1023 lines
	// Word 13
	USHORT corner_max_x		:16;  // maximum X size of gate corners when corner_type=1 (auto)
								  //   range: 0 to 1023 pixels
	// Word 14
	USHORT corner_max_y		:16;  // maximum Y size of gate corners when corner_type=1 (auto)
								  //   range: 0 to 1023 lines
	// Word 15
	USHORT spare15			:16;

	// Word 16
	short  checksum			:16;  // message checksum

} CONFIG_GATE_RETICLE2_MSG;

// -------------- Config GPS Message Structure -----------------
typedef struct
{
	// Word 1
	USHORT	sync					:16;  // sync word

	// Word 2
	USHORT	spare2					:8;   // spare bits
	USHORT	msg_type				:8;   // msg type = 236

	// Word 3
	USHORT	gps_type				:8;   // GPS equipment type (0=none, 1=X-Monkey, ...)
	USHORT	serial_port				:8;   // tracker serial port GPS is connected to (3-7, 0-2 are reserved)

	// Word 4
	USHORT  spare4					:16;

	// Word 5
	USHORT	spare5					:16;

	// Word 6
	USHORT	spare6					:16;

	// Word 7
	USHORT	spare7					:16;

	// Word 8
	short	checksum				:16;  // checksum

} CONFIG_GPS_MSG;


// ---------- Message Acknowledge Message Structure ----------
typedef struct
{
	// Word 1
	USHORT sync					:16;  // sync word

	// Word 2
	USHORT ack_type				:8;   // message type received
	USHORT msg_type				:8;   // message type = 254

	// Word 3
	USHORT error_code			:16;  // error code (0=OK/No Error, 1=Unknown Message, ...)

	// Word 4
	short  checksum				:16;  // message checksum

} MESSAGE_ACK_MSG;

// -------------- Status Message Structure --------------
typedef struct
{
	// Word 1
	USHORT sync				:16;  // sync word

	// Word 2
	USHORT gate				:4;   // gate number
	USHORT ex_field			:1;   // extended status bit - interlace field indicator (0=even, 1=odd/progressive)
	USHORT ex_spare			:3;   // spare extended status bits
	USHORT msg_type			:8;   // message type = 255

	// Word 3
	short  txerr			:16;  // raw X/pixel track error (no filters or scaling applied)
								  //    range: +/- 1023.969  (divide by 32 to get value)
	// Word 4
	short  tyerr			:16;  // raw Y/line track error (no filters or scaling applied)
								  //    range: +/- 1023.969  (divide by 32 to get value)
	// Word 5
	USHORT tgt_pol			:3;   // target polarity
	USHORT trk_state		:3;   // track state
	USHORT trk_acq			:1;   // track-acquire state (0=Acquire, 1=Track)
	USHORT trk_mode			:3;   // track mode
	USHORT auto_acquire		:1;   // auto-acquire enable
	USHORT log_scan			:1;	  // log to scan file flag (1=log this message)
	USHORT control_box		:1;	  // control box status (0=disabled, 1=enabled)
	USHORT scan_active		:1;	  // is scan mode active (0=disabled, 1=active)
	USHORT log				:1;	  // log to file flag (1=log this message)
	USHORT cmd_ack			:1;   // command acknowledge bit (0=unsolicited, 1=response to a ping)

	// Word 6
	USHORT status			:16;  // track status

	// Word 7
	USHORT txsize			:16;  // target size (X) in pixels

	// Word 8
	USHORT tysize			:16;  // target size (Y) in lines

	// Word 9
	USHORT tleft			:16;  // the left (X/pixel) position of the bounding rectangle of the target
								  //   range: 0 to 2047 (top/left of image is 0,0)
	// Word 10
	USHORT ttop				:16;  // the top (Y/line) position of the bounding rectangle of the target
								  //   range: 0 to 2047 (top/left of image is 0,0)
	// Word 11
	USHORT tcount			:16;  // the pixel count (mass size) of the target (when in contrast modes)
								  // or the correlation quality/match percentage (when in correlation mode)
	// Word 12 & 13
	short  azimuth_lsw		:16;  // azimuth of mount in degrees, least significant word (lsw)
	short  azimuth_msw		:16;  // and most significant word (msw) (divide by 10000 to get value)
								  //    range: +/- 360.0000  (divide by 10,000 to get value)
	// Word 14 & 15
	short  elevation_lsw	:16;  // elevation of mount in degrees, least significant word (lsw)
	short  elevation_msw	:16;  // and most significant word (msw) (divide by 10000 to get value)
								  //    range: +/- 360.0000  (divide by 10,000 to get value)
	// Word 16
	short  filtered_txerr	:16;  // filtered X/azimuth track error (with all filters and scaling applied)
								  //    range: +/- 1023.969  (divide by 32 to get value)
	// Word 17
	short  filtered_tyerr	:16;  // filtered Y/elevation track error (with all filters and scaling applied)
								  //    range: +/- 1023.969  (divide by 32 to get value)

	// Word 18
	short  checksum			:16;  // checksum

} STATUS_MSG;


/****************************************************************************/
#pragma pack(pop)	// reset to default packing

#endif //__MSG_FMT_H__
