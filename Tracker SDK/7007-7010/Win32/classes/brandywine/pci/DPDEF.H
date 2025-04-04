/* DPDEF.H 10JAN03 JCK add DP_Control0:IgnorePPS&Ignore_Code definitions */
/* DPDEF.H 6MAY99 JCK change irig-g code select from 0f to 09 */
/* DPDEF.H 3FEB98 JCK add DP_Match_ht & DP_Match_SS */
/* DPDEF.H 6AUG97 JCK fix DP_CodeSelect_NASA36, add DP_CodeSelect_IRIGA, Binary */
/* DPDEF.H 13JAN97 Set_Ctrx & GPS lock/unlock commands added */
/* DPDEF.H 8JAN97 DP_ctl_rw added */
/* DPDEF.H 24DEC96 DP_Ctr2_ctl..DP_Ctr0_msb added */
/* DPDEF.H 31MAY96 */
#define DP_Command 0xff
#define No_op                   0 /* no operation */
#define Command_Set_Major       2 /* Set clock seconds..days to Major seconds..days */
#define Command_Set_Years       4 /* Set clock years to dual port years  */
#define Command_Set_RAM_FIFO    6 /* Set RAM FIFO external time tag mode */
#define Command_Reset_RAM_FIFO  8 /* Reset RAM FIFO external time tag mode */
#define Command_Empty_RAM_FIFO 10 /* Empty RAM FIFO */
#define Command_Set_Ctr0       12 /* Set 82C54 ctr 2 ("lowrate") params */
#define Command_Set_Ctr1       14 /* Set 82C54 ctr 2 ("heartbeat") params */
#define Command_Set_Ctr2       16 /* Set 82C54 ctr 2 ("rate2") params */
#define Command_Rejam          18 /* Re-jam at start of next second */
#define Command_Spfun1         20 /* Reserved for special function #1 */
#define Command_Spfun2         22 /* Reserved for special function #2 */
#define GPS_Readlock           24 /* lock GPS position buffer for read */
#define GPS_Readunlock         26 /* unlock GPS position buffer to allow update*/
/*   DUAL PORT RAM LOCATIONS 0x00..0x7F ARE READ-ONLY */
#define DP_Extd_Sts 0x00 /* Extended status READ ONLY */
#define DP_Extd_Sts_Nosync 0x01 /* Set if NOT in sync */
#define DP_Extd_Sts_Nocode 0x02 /* Set if selected input code NOT decodeable */
#define DP_Extd_Sts_NoPPS  0x04 /* Set if PPS input invalid */
#define DP_Extd_Sts_NoMajT 0x08 /* Set if major time NOT set since jam */
#define DP_Extd_Sts_NoYear 0x10 /* Set if year NOT set */
#define DP_Code_CtlA 0x0f       /* Control field "A" read data */
#define DP_Code_CtlB 0x10       /* Control field "B" read data */
#define DP_Code_CtlC 0x11       /* Control field "C" read data */
#define DP_Code_CtlD 0x12       /* Control field "D" read data */
#define DP_Code_CtlE 0x13       /* Control field "E" read data */
#define DP_Code_CtlF 0x14       /* Control field "F" read data */
#define DP_Code_CtlG 0x15       /* Control field "G" read data */


#define DP_Control0 0x80 /* Dual Port Ram Address for Control Register */
#define DP_Control0_Leapyear     0x01 /* Current year is leap year*/
#define DP_Control0_CodePriority 0x02 /* Time code input has priority over PPS*/
#define DP_Control0_NegCodePropD 0x04 /* code input prop delay setting is - */
#define DP_Control0_NegPPSPropD  0x08 /* PPS input prop delay setting is - */
#define DP_Control0_IgnorePPS    0x40 /* Ignore 1 PPS input reference */
#define DP_Control0_IgnoreCode   0x80 /* Ignore time code input reference */


#define DP_CodeSelect 0x81              /* Time code input select */
#define DP_CodeSelect_IRIGB 0x0b        /* IRIG-B */
#define DP_CodeSelect_IRIGA 0x0a        /* IRIG-A */
#define DP_CodeSelect_NASA36 0x06       /* NASA36 */
#define DP_CodeSelect_2137 0x07         /* 2137   */
#define DP_CodeSelect_XR3 0x03          /* XR3    */
#define DP_CodeSelect_IRIGG 0x09        /* IRIG-G */
#define DP_CodeSelect_IRIGE 0x0e        /* IRIG-E */

#define DP_LeapSec_Day10Day1 0x82       /* Day (10s & 1s) ending in leap sec*/

#define DP_LeapSec_Day1000Day100 0x83   /* Day (0,100s) ending in leap sec*/

#define DP_CodePropDel_ns100ns10  0x84  /* time code prop. delay 100,10 ns */
#define DP_CodePropDel_us10us1    0x85  /* time code prop. delay 10,1 us */
#define DP_CodePropDel_ms1us100   0x86  /* time code prop. delay 1000,100 us */
#define DP_CodePropDel_ms100ms10  0x87  /* time code prop. delay 100,10 ms */


#define DP_PPS_PropDel_ns100ns10  0x88       /* PPS prop. delay 100,10 ns  */
#define DP_PPS_PropDel_us10us1    0x89       /* PPS prop. delay 10,1 us    */
#define DP_PPS_PropDel_ms1us100   0x8a       /* PPS prop. delay 1000,100 us*/
#define DP_PPS_PropDel_ms100ms10  0x8b       /* PPS prop. delay 100,10 ms  */

#define DP_PPS_Time_ns100ns10     0x8c          /* PPS time 100,10ns */
#define DP_PPS_Time_us10us1       0x8d          /* PPS time 10,1us */
#define DP_PPS_Time_ms1us100      0x8e          /* PPS time 1000,100us */
#define DP_PPS_Time_ms100ms10     0x8f          /* PPS time 100,10ms */
#define DP_Major_Time_s10s1       0x90          /* Major time 10,1second */
#define DP_Major_Time_m10m1       0x91          /* Major time 10,1minute */
#define DP_Major_Time_h10h1       0x92          /* Major time 10,1hour */
#define DP_Major_Time_d10d1       0x93          /* Major time 10,1 day */
#define DP_Major_Time_d1000d10    0x94           /* Major time 0, 100 day */
#define DP_Year10Year1       0x95               /* 10,1 years */
#define DP_Year1000Year100   0x96               /* 1000,100 years */
#define DP_Codebypass        0X97               /* #frames to validate code */

#define DP_Ctr2_ctl          0x98     /* ctr 2 control word */
#define DP_Ctr1_ctl          0x99     /* ctr 1 control word */
#define DP_Ctr0_ctl          0x9A     /* ctr 0 control word */
#define DP_Ctr2_ctl_sel                 0x80  /* ALWAYS used for ctr 2 */
#define DP_Ctr1_ctl_sel                 0x40  /* ALWAYS used for ctr 1 */
#define DP_Ctr0_ctl_sel                 0x00  /* ALWAYS used for ctr 0 */
#define DP_ctl_rw                       0x30  /* ALWAYS used */
#define DP_ctl_mode0                    0x00  /* Ctrx mode 0 select */
#define DP_ctl_mode1                    0x02  /* Ctrx mode 1 select */
#define DP_ctl_mode2                    0x04  /* Ctrx mode 2 select */
#define DP_ctl_mode3                    0x06  /* Ctrx mode 3 select */
#define DP_ctl_mode4                    0x08  /* Ctrx mode 4 select */
#define DP_ctl_mode5                    0x0A  /* Ctrx mode 5 select */
#define DP_ctl_bin                      0x00  /* Ctrx binary mode select */
#define DP_ctl_bcd                      0x01  /* Ctrx bcd mode select */
#define DP_Ctr2_lsb          0x9B     /* ctr 2 count LSB    */
#define DP_Ctr2_msb          0x9C     /* ctr 2 count MSB    */
#define DP_Ctr1_lsb          0x9D     /* ctr 1 count LSB    */
#define DP_Ctr1_msb          0x9E     /* ctr 1 count MSB    */
#define DP_Ctr0_lsb          0x9F     /* ctr 0 count LSB    */
#define DP_Ctr0_msb          0xA0     /* ctr 0 count MSB    */
#define DP_Battery_Holdoff   0xBD     /* hold off time before sync to 1 PPS */
#define DP_Match_ht          0xBE     /* match time .ht (BCD)(VME -EXTMATCH opt)*/
#define DP_Match_SS          0xBF     /* match time ss (BCD)(VME -EXTMATCH opt)*/
#define DP_Match_MM          0xCB     /* -EXTMATCH option: match time mm (BCD)  */
#define DP_Match_HH          0xCC     /* -EXTMATCH option: match time hh (BCD)  */
#define DP_Match_D1D0        0xCD     /* -EXTMATCH option: match time day (10,1 digits) (BCD) */
#define DP_Match_XD2         0xCE     /* -EXTMATCH option: match time don't care, 100 days digit */
#define DP_GPS_TFOM_GEN      0xC9     /* 3..0 generated TFOM decade */
#define DP_GPS_4430_Scale_Leap_Ind 0xCA /* see manual STANAG4430 programming */

