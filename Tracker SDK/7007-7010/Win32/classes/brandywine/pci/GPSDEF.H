/* gpsdef.h 24mar03 add GPS commands for open,short bits in RcvrStatusM12 */
/* gpsdef.h 4mar03  correct antenna ok, open,short bits in RcvrStatusM12 */
/* gpsdef.h 16jan03 add DP_GPS_DOP_Type,DP_GPS_RcvrStatus defs for M12 */
/* gpsdef.h 24nov00 add DP_GPS_PosFracSec */
/* gpsdef.h 24aug00 add GPS_Disable_Pos_Hold_Command */
/* gpsdef.h 12aug00 add DP_GPS_Sawtooth,GPS_Command,GPS cable comp  */
/* gpsdef.h 5jan99 add DP_GPS_CH0..DP_GPS_RcvrStatus */
/* GPSDEF.H 28apr98 DP_GPS_Altbin3124..DP_GPS_Altbin0700 added  */
/* GPSDEF.H 31jul97 DP_GPS_UpdateFlag..DP_GPS_RTCM_Ack  */
/* GPSDEF.H 8jan97 JCK add DP_HQ_TFOM */
/* GPSDEF.H 7jun96 JCK */
#define DP_GPS_Semaphore          0xA3     /* 0=unlocked,1=read lock,-1=wr lock */

#define DP_GPS_Status             0xA4
#define DP_GPS_Status_Sats        0x0F     /* lo order nibble: BIN # sats tracked */
#define DP_GPS_Status_South       0x80     /* Bit 7: 1=South,0=North latitude */
#define DP_GPS_Status_West        0x40     /* Bit 6: 1=West,0=East longitude */
#define DP_GPS_Status_Nav         0x10     /* Bit 4: 1=Navigate, 0=Acquiring */

#define DP_GPS_Lat_MinEM34        0xA5     /* BCD 10-3,10-4 min latitude */
#define DP_GPS_Lat_MinEM12        0xA6     /* BCD 10-1,10-2 min latitude */
#define DP_GPS_Lat_MinE10         0xA7     /* BCD 10+1,10+0 min latitude */
#define DP_GPS_Lat_DegE10         0xA8     /* BCD 10+1,10+0 deg latitude */
#define DP_GPS_Lon_MinEM34        0xA9     /* BCD 10-3,10-4 min longitude */
#define DP_GPS_Lon_MinEM12        0xAA     /* BCD 10-1,10-2 min longitude */
#define DP_GPS_Lon_MinE10         0xAB     /* BCD 10+1,10+0 min longitude */
#define DP_GPS_Lon_DegE10         0xAC     /* BCD 10+1,10+0 deg longitude */
#define DP_GPS_Lon_DegE32         0xAD     /* BCD 10+3,10+2 deg longitude */
#define DP_GPS_SOG0M1             0xAE     /* BCD speed over ground, 1,10-1 m/sec */
#define DP_GPS_SOG21              0xAF     /* BCD speed over ground, 100,10 m/sec */
#define DP_GPS_HOG0M1             0xB0     /* BCD heading over ground, 1,10-1 deg */
#define DP_GPS_HOG21              0xB1     /* BCD heading over ground, 100,10 deg */
#define DP_HQ_TFOM                0xB2     /* HaveQuick Time Figure of Merit */
#define DP_GPS_UpdateFlag         0xB3     /* set non-0 by board when GPS data updated */ 
#define DP_GPS_Latbin3124         0xB4     /* Oncore: ms byte lat arc milliseconds */
#define DP_GPS_Latbin2316         0xB5     /* Oncore: <23:16> lat arc milliseconds */
#define DP_GPS_Latbin1508         0xB6     /* Oncore: <15:08> lat arc milliseconds */
#define DP_GPS_Latbin0700         0xB7     /* Oncore: ls byte lat arc milliseconds */
#define DP_GPS_Lonbin3124         0xB8     /* Oncore: ms byte lon arc milliseconds */
#define DP_GPS_Lonbin2316         0xB9     /* Oncore: <23:16> lon arc milliseconds */
#define DP_GPS_Lonbin1508         0xBA     /* Oncore: <15:08> lon arc milliseconds */
#define DP_GPS_Lonbin0700         0xBB     /* Oncore: ls byte lon arc milliseconds */
#define DP_GPS_RTCM_Ack           0xBC     /* Oncore: Ack count of RTCM104 messages received */
#define DP_GPS_Altbin3124         0xC0     /* Oncore: ms byte alt above geoid in cm.*/
#define DP_GPS_Altbin2316         0xC1     /* Oncore: <23:16> alt above geoid in cm.*/
#define DP_GPS_Altbin1508         0xC2     /* Oncore: <15:08> alt above geoid in cm.*/
#define DP_GPS_Altbin0700         0xC3     /* Oncore: ls byte alt above geoid in cm.*/

#define DP_GPS_Command            0xD2     /* GPS receiver commands: */
#define GPS_Autosurvey_Command    0x01     /* init auto-survey */ 
#define GPS_Cable_Length_Command  0x02     /* set cable compensation */ 
#define GPS_Disable_Pos_Hold_Command 0x03  /* disable position hold mode */ 
#define GPS_Set_Hold_Position_Command 0x04 /* specify hold position */ 
#define GPS_Set_1_1_2001_Command  0x05     /* init rcvr clock to 1-1-2001 */ 
#define GPS_Disable_TRAIM         0x06     /* disable TRAIM            */ 
#define GPS_Enable_TRAIM          0x07     /* enable TRAIM             */ 
#define GPS_Set_1_1_2019_Command  0x08     /* init rcvr clock to 1-1-2019 */ 
#define GPS_Set_1_1_2038_Command  0x09     /* init rcvr clock to 1-1-2038 */ 
#define GPS_Set_Default_Commmand  0x0A     /* init rcvr settings to default */
#define GPS_Enable_Pos_Hold_Command 0x0B   /* enable position hold mode */ 



#define DP_GPS_cablcomp3          0xD3     /* cable length compensation 2**31..2**24 ns */
#define DP_GPS_cablcomp2          0xD4     /* cable length compensation 2**23..2**16 ns */
#define DP_GPS_cablcomp1          0xD5     /* cable length compensation 2**15..2**8 ns */
#define DP_GPS_cablcomp0          0xD6     /* cable length compensation 2**7..2**0 ns */
#define DP_GPS_SawtoothErr        0xd7     /* 1PPS pulse sawtooth error */
#define DP_GPS_UTC_Offset         0x18     /* GPS/UTC time offset */
#define DP_GPS_RcvrType           0x19     /* 0=not def., 1=Mot Oncore UT+ */
                                           /* type 2= Mot M12 (Dynamic) */
                                           /* type 5= Mot M12 (Timing) */
#define DP_GPS_ChanDat            0x20     /* old name for DP_GPS_CH0 */
/* DP_GPS_CH0..CH7 valid for units shipped 6 Mar 1999 and later */
#define DP_GPS_CH0              0x20    /* 4 byte channel 0 info */
#define DP_GPS_CH1              0x24    /* 4 byte channel 1 info */
#define DP_GPS_CH2              0x28    /* 4 byte channel 2 info */
#define DP_GPS_CH3              0x2c    /* 4 byte channel 3 info */
#define DP_GPS_CH4              0x30    /* 4 byte channel 4 info */
#define DP_GPS_CH5              0x34    /* 4 byte channel 5 info */
#define DP_GPS_CH6              0x38    /* 4 byte channel 6 info */
#define DP_GPS_CH7              0x3c    /* 4 byte channel 7 info */
/* DP_GPS_CH8..11 will be 0 for 8 channel receivers */
#define DP_GPS_CH8              0x40    /* 4 byte channel 8 info */
#define DP_GPS_CH9              0x44    /* 4 byte channel 9 info */
#define DP_GPS_CH10             0x48    /* 4 byte channel 10 info */
#define DP_GPS_CH11             0x4c    /* 4 byte channel 11 info */


#define DP_GPS_SatID    0 /* offset 0 in 4 byte field for satellite ID */

#define DP_GPS_ChMode   1 /* offset 1 in 4 byte field for channel mode */
/* definition of DP_GPS_ChMode values for ONCORE receivers  */
#define DP_GPS_ChMode_Code_Search  0 /* Code search mode if ChMode=0 */
#define DP_GPS_ChMode_Code_Acquire 1 /* Code acquire mode if ChMode=1 */
#define DP_GPS_ChMode_AGCset 2 /* AGC Set mode if ChMode=2 */
#define DP_GPS_ChMode_PreqAcq 3 /* Pre-acquire mode if ChMode=3 */
#define DP_GPS_ChMode_BitSyncDet 4 /* Bit Sync Detect mode if ChMode=4 */
#define DP_GPS_ChMode_MsgSyncDet 5 /* Msg Sync Detect mode if ChMode=5 */
#define DP_GPS_ChMode_SatTimeAvail 6 /* Sat time avail mode if ChMode=6 */
#define DP_GPS_ChMode_EphemAcq 7 /* Ephemeris acq mode if ChMode=7 */
#define DP_GPS_ChMode_AvailPos 8 /* Available for position mode if ChMode=8 */

#define DP_GPS_ChCNo    2 /* offset 2 in 4 byte field for channel C/no ratio */

#define DP_GPS_ChStatus 3 /* offset 3 n 4 byte field for channel status flags */
/* bit assignments for DP_GPS_ChStatus: for ONCORE GPS receivers*/
#define DP_GPS_ChStatus_PosFix   0x80 /* Using for position fix flag */
#define DP_GPS_ChStatus_SatMom   0x40 /* Satellite momentum alert flag */
#define DP_GPS_ChStatus_SatAntiSpoof 0x20 /* Satellite Anti-Spoof flag */
#define DP_GPS_ChStatus_SatUnhealthy 0x10 /* Satellite unhealthy flag */
#define DP_GPS_ChStatus_SatInaccurate 0x08 /* Satellite inaccurate flag */
#define DP_GPS_ChStatus_Spare         0x04 /* spare flag */
#define DP_GPS_ChStatus_TimeSoln      0x02 /* Using sat for time solution flag */
#define DP_GPS_ChStatus_ParityErr     0x01 /* Parity error flag */
/* bit assignments for DP_GPS_ChStatus: for M12 GPS receivers*/
#define DP_GPS_ChStatusM12_PosFix       0x80 /* Using for position fix flag */
#define DP_GPS_ChStatusM12_SatMom       0x40 /* Satellite momentum alert flag */
#define DP_GPS_ChStatusM12_SatAntiSpoof 0x20 /* Satellite Anti-Spoof flag */
#define DP_GPS_ChStatusM12_SatUnhealthy 0x10 /* Satellite unhealthy flag */
#define DP_GPS_ChStatusM12_SatAccu      0x0f /* <3:0> encode satellite URA*/

/* DP_GPS_DOP_Type..DP_GPS_RcvrStatus defined in units shipped 5jan2000 & later */

#define DP_GPS_DOP_Type   0x50  /* DOP type & antenna connection info */
/* bit assignments for DP_GPS_DOP_Type: (for Oncore receivers)*/
#define DP_GPS_DOP_Type_AntOpen  0x80  /* antenna undercurrent flag */
#define DP_GPS_DOP_Type_AntShort 0x40  /* antenna overcurrent flag */
#define DP_GPS_DOP_Type_AutoSurv 0x20  /* Auto-survey mode flag     */
#define DP_GPS_DOP_Type_Spare4   0x10  /* spare flag     */
#define DP_GPS_DOP_Type_Spare3   0x08  /* spare flag     */
#define DP_GPS_DOP_Type_Spare2   0x04  /* spare flag     */
#define DP_GPS_DOP_Type_Spare1   0x02  /* spare flag     */
#define DP_GPS_DOP_Type_DOP2D    0x01  /* DOP is 2D if set,3D if not set flag */
/* bit assignments for DP_GPS_DOP_Type: (for M12 receivers)*/
#define DP_GPS_DOP_TypeM12_3DFix    0xe0 /* <7:5>=111 =3D FIX */ 
#define DP_GPS_DOP_TypeM12_2DFix    0xc0 /* <7:5>=110 =2D FIX */ 
#define DP_GPS_DOP_TypeM12_PropMode 0xa0 /* <7:5>=101 =Propagate Mode*/  
#define DP_GPS_DOP_TypeM12_PosnHold 0x80 /* <7:5>=100 =Position Hold */  
#define DP_GPS_DOP_TypeM12_AcqSats  0x60 /* <7:5>=011 =Acq. Satellites*/  
#define DP_GPS_DOP_TypeM12_BadGeom  0x40 /* <7:5>=010 =Bad Geometry  */  
#define DP_GPS_DOP_TypeM12_Reservea 0x20 /* <7:5>=001 =Reserved      */  
#define DP_GPS_DOP_TypeM12_Reserveb 0x00 /* <7:5>=000 =Reserved      */  
#define DP_GPS_DOP_TypeM12_Reserve4 0x10 /* <4:2>      Reserved      */  
#define DP_GPS_DOP_TypeM12_Reserve3 0x08 /* <4:2>      Reserved      */  
#define DP_GPS_DOP_TypeM12_Reserve2 0x04 /* <4:2>      Reserved      */  
#define DP_GPS_DOP_TypeM12_FasAcqPo 0x02 /* Fast Acquisition Position*/  
#define DP_GPS_DOP_TypeM12_FResRAW  0x01 /* Filt Reset RAW GPS Soln  */

#define DP_GPS_RcvrStatus 0x51  /* Receiver status flags */
/* bit assignments for DP_GPS_RcvrStatus: for ONCORE GPS receivers */
#define DP_GPS_RcvrStatus_PosProp  0x80  /* Position propagate mode flag */
#define DP_GPS_RcvrStatus_PoorGeom 0x40 /* Poor geometry (DOP>12) flag */
#define DP_GPS_RcvrStatus_3DFix    0x20 /* 3D position fix        flag */
#define DP_GPS_RcvrStatus_2DFix    0x10 /* 2D position fix        flag */
#define DP_GPS_RcvrStatus_ACQHold  0x08 /* Acquiring sats/PosHold flag */
#define DP_GPS_RcvrStatus_DiffFix  0x04 /* Differential fix       flag */
#define DP_GPS_RcvrStatus_InsVisib 0x02 /* Insuffient vis sats    flag */
#define DP_GPS_RcvrStatus_BadAlman 0x01 /* Bad Almanac Flag       flag */
/* bit assignments for DP_GPS_RcvrStatus: for M12 GPS receivers */
#define DP_GPS_RcvrStatusM12_Cold      0x80 /* Cold start                  */
#define DP_GPS_RcvrStatusM12_Diff      0x40 /* Differential fix            */
#define DP_GPS_RcvrStatusM12_PosLock   0x20 /* Position Lock               */
#define DP_GPS_RcvrStatusM12_Autosurv  0x10 /* Autosurvey mode             */
#define DP_GPS_RcvrStatusM12_InsVisSat 0x08 /* Insufficient visible sats   */
#define DP_GPS_RcvrStatusM12_AntennaOK 0x00 /* <2:1>=00 Ant DC Current OK  */
#define DP_GPS_RcvrStatusM12_AntShort  0x02 /* <2:1>=01 Ant DC Overcurrent */
#define DP_GPS_RcvrStatusM12_AntOpen   0x04 /* <2:1>=10 Ant DC Undercurrent*/ 
#define DP_GPS_RcvrStatusM12_CodLocInt 0x01 /* 1=Int,0=Ext Code Location   */ 

#define DP_GPS_PosFracSec 0x5D   /* most sig byte of pos fix time frac sec */          









