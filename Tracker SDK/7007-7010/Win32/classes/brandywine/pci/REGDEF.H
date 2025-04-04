/* REGDEF.H 5SEP03 JCK FIX COMMENT ON Ext_Polarity: 0=^, 1=V */
/* REGDEF.H 26JUN98 JCK RAMFIFO port moved from x16 to x18 */
/* PORT ADDRESS DEFINITIONS FOR PCI-SYNCCLOCK32 */
/* ALL ADDRESSES ARE RELATIVE TO CONFIGURED BASE ADDRESS */
/* RO means Read only. RW means read write. WO means Write only. */
#define Sec10_Usec1_Port        0x00 /* LONG RO latch new time & read ms8..us1 bits*/
#define Year1_Min1_Port         0x04 /* LONG RO read latched hr8..min1 bits*/
/* READING ANY OF THE FOLLOWING PORTS WILL CLEAR EXT READY FLAG */
#define Ext_Sec10_Usec1_Port    0x08 /* LONG RO ext. time tag msec..usec    */
#define Ext_Year1_Min1_Port     0x0c /* LONG RO ext. time tag 10sec ..10msec*/
#define Ext_100ns_Port          0x13 /* BYTE RO ext. time tag 100ns .. 0000 */

#define Status_Port             0x10    /* status & interrupt enables */
#define Ext_Ready               1       /* RO Ext. Time Tag Data Ready if 1*/
#define Trigger_Sim_Ext_Time_Tag 1      /* WO bit0 = 1: Fake ext. time tag */
#define Response_Ready          2       /* RO Command Response Ready if 1*/
#define RAM_FIFO_Ready          4       /* RO RAM FIFO data ready */
#define Match                   8       /* RO Match register toggles on Match */
#define Reset_Match             8       /* WO bit3= 1: Reset Match reg */
#define Heartbeat               0x10    /* RO Heartbeat pulse detected if 1 */
#define Reset_Heartbeat         0x10    /* WO bit4 = 1: Reset Heartbeat flag*/
#define Ext_Polarity            0x20    /* RW External event input polarity 0=^ 1=V*/
#define Sync_OK                 0x40    /* RO In-sync to time reference if 1 */

#define Control_Port            0x11
#define Ext_Intr_Enb            0x01    /* RW Ext. Time Tag Intr Enable   */
#define Command_Rdy_Intr_Enb    0x02    /* RW Command Response Ready Intr Enable */
/* the RAM_FIFO_Rdy_Intr_Enb bit is implemented for -RAMFIFO option ONLY  */
#define RAM_FIFO_Rdy_Intr_Enb   0x04    /* RW RAM FIFO Ready Intr Enable */
#define Time_Match_Intr_Enb     0x08    /* RW Time Match Intr Enable   */
#define Heartbeat_Intr_Enb      0x10    /* RW Heartbeat  Intr Enable   */
#define Matchext_Enb            0x20    /* RW Enables Match Extension past 10**3 usec*/

#define Mult_Frac_Port          0x12    /* implemented for -MULFRAC option only */
#define MulFrac2                0x01    /* WO select X2 or /2  */
#define MulFrac4                0x02    /* WO select X4 or /4  */
#define Frac                    0x80    /* WO select fraction speed */
#define Mult                    0x00    /* WO select multiple speed */

#define Match_Usec10_Usec1_Port  0x14    /* WO 10**1,10**0 match usec */

#define Match_Msec1_Usec100_Port 0x15    /* WO 10**3,10**2 match usec */

#define RAM_FIFO_Port            0x18     /* RO RAM FIFO */

#define Dual_Port_Address_Port  0x1A    /* WO Dual Port RAM Address */

#define Dual_Port_Data_Port     0x1E    /* RW Dual Port RAM Data */




