Moog, Inc. / Electro-Optical Imaging
Model 7007 PCI and 7010 PCI Express Video Tracker
Software Development Kit

* version 6.4 (18 August 2020)

  - Added new mount type MOUNT_MOOG_MPT_NO_PASS (type 33) to control the
    Moog MPT positioner using the PTZ protocol without any mount serial
    passthrough support (see MSG_FMT.H).

  - Added new lens type LENS_FLIR_NEUTRINO_SX12ISR1200 (type 38) to control
    the FLIR Neutrino SX12-ISR1200 thermal camera with zoom lens package.

  - Added new lens type LENS_INVEO_THEIA_HD900M (type 39) to control
    the InVeo THEIA HD900M thermal camera with zoom lens package.

  - Added new laser rangefinder type LRF_TYPE_JENOPTIK_DLEM (type 10)
    to control the Jenoptik DLEM 20/30/45 series laser range finders.

  - Message modified (see MSG_FMT.H):
    Modified LENS_SERIAL_IR_ZOOM_MSG (type 28) to add a bit to control
    the focus to range (aka-focus to distance) feature on cameras which
    support this function.

  - Renamed extended camera type (see MSG_CAM_FMT.H):
    CAMTYPE_G5_INFRARED_550CZ (type 2) have been renamed to
    CAMTYPE_G5_INFRARED_REVD (type 2) to allow for updated G5 protocol
    and new features.

  - New extended camera support added (see MSG_CAM_FMT.H):
    CAMTYPE_G5_INFRARED_REVG (type 4) added to support extended control of
    the updated G5 Infrared 550CZ and new 785CZ camera features.

  - New extended camera support added (see MSG_CAM_FMT.H):
    CAMTYPE_INVEO_AGILE_CORE (type 5) added to support extended control of
    the InVeo AgileCore based cameras and cameras with InVeo electronics.

  - Documentation added (see MSG_OVL_FMT.H):
    Added overlay pixel format documentation.

* version 6.3 (17 February 2020)

  - Added new lens type LENS_FUJINON_SX800 (type 35) to control the
    Fujinon SX800 camera with zoom lens package.

  - Added new lens type LENS_FLIR_RANGER_HDC (type 36) to control the
    FLIR Ranger HDC thermal camera with zoom lens package.

  - Added new lens type LENS_G5_INFRARED_785CZ (type 37) to control the
    G5 Infrared 785 thermal camera with zoom lens package.

  - Message modified (see MSG_FMT.H):
    Modified SYMBOLOGY_CTRL_MSG (type 5) to add a flag to show the line
    of sight (boresight) reticle on the unselected video output for
    our Series 8000 boards.

  - Message modified (see MSG_FMT.H)
    Modified LENS_SERIAL_TFOV_MSG (type 24) to add serial communication
    status flags (not_present and error_detected).

  - Message modified (see MSG_FMT.H)
    Modified LENS_SERIAL_DFOV_MSG (type 25) to add serial communication
    status flags (not_present and error_detected).

  - Message modified (see MSG_FMT.H)
    Modified LENS_SERIAL_IR_DFOV_MSG (type 33) to add serial communication
    status flags (not_present and error_detected).

  - NOTE: While not a change in messaging, newer tracker firmware has
          algorithm changes to the tracking PID (see FILTER_CTRL_MSG) to
          better support systems which incorporate multiple cameras with
          different frame rates.  When updating firmware, you may need to
          retune the tracking PID or at least the integral (I) parameter.

* version 6.2 (22 August 2019)

  - Updates to CTrackerConfiguration to properly get the configuration

  - Added new mount type MOUNT_MOOG_MPT (type 32) to control the
    Moog MPT positioner using the PTZ protocol (see MSG_FMT.H).

  - Added new GPS type GPS_TYPE_MOOG_EDMC (type 3) to get GPS data
    from the Moog embedded digital motion controller (see MSG_FMT.H).

  - Message modified (see MSG_FMT.H):
    Modified CONFIG_JOYSTICK_MSG (type 209) to change the units for the
    joystick gain parameters and also update comments.

* version 6.1 (07 May 2019)

  - Added new mount type MOUNT_MOOG_EDMC (type 31) to control our
    Moog embedded digital motion controller unit (see MSG_FMT.H).

  - New message added (see MSG_FMT.H):
    SYSTEM_STATUS_MSG_TYPE (type 73) added to provide consolidated system
    status for tracking systems built using our Series 8000 boards.

  - New message added (see MSG_FMT.H):
    FPGA_VIDEO_STATUS_MSG_TYPE (type 74) added to provide video status
    on the two digital video inputs to the FPGA.  The actual video input
    is dependant on the tracker board type and video signal routing.

  - New message added (see MSG_FMT.H):
    ETHERNET_STATUS_MSG_TYPE (type 75) added to provide status on the
    Ethernet connetions to and from the tracker board.

* version 6.0 (06 November 2018)

  - Added new mount type MOUNT_DSCU (type 30) to control our
    EO Imaging digital servo control unit (see MSG_FMT.H).

  - Added new lens type LENS_SONY_FCB_EX980S (type 34) to control the
    Sony FCB-EX980S camera with zoom lens package.

  - Added new GPS type GPS_TYPE_GARMIN_19X_HVS (type 2) to support the
    Garmin 19x HVS (10 samples per second at 38,400 bps serial rate).

  - Message modified (see MSG_FMT.H):
    Modified CAPABILITIES_MSG (type 41) to add bits which provide flags
    to identify when the tracker needs firmware (running boot loader) and
    if the multi-target output feature is enabled.

* version 5.9 (04 April 2018)

  - Added new laser rangefinder type LRF_TYPE_ZEISS_LP17D (type 7)
    to control the Zeiss/Airbus LP17D laser range finder (see MSG_FMT.H).

  - Added new laser rangefinder type LRF_TYPE_ZEISS_LP17D_1 (type 8)
    to control the Zeiss/Airbus LP17D-1 laser range finder (see MSG_FMT.H).

  - Added new laser rangefinder type LRF_TYPE_PVP_NIGHTHAWK (type 9)
    to control the PVP NightHawk and CMG system's laser range finder
    over Ethernet (see MSG_FMT.H).

* version 5.8 (30 January 2018)

  - Added new digital I/O functions for lens iris and 2X extender
    including DIG_FUNCT_AUTO_IRIS, DIG_FUNCT_IRIS_OPEN, DIG_FUNCT_IRIS_CLOSE
    and DIG_FUNCT_ZOOM_2X

* version 5.7 (12 January 2018)

  - Added new lens type LENS_OFFICINA_STELLARE_FOCUSER (type 33) to control the
    Officina Stellare telescope focuser.

  - Message modified (see MSG_FMT.H):
    Modified LENS_SERIAL_FIXED_FOV_MSG (type 32) to add speed control for the
    Officina Stellare telescope focuser and to add lens communication status
    feedback (serial link up/down and error).

  - Added new laser rangefinder type LRF_TYPE_NEWCONOPTIK_MOD25HFLC_V3 (type 6)
    to control the Newcon Optik MOD 25HFLC v3 laser range finder.

  - Message modified (see MSG_FMT.H):
    Modified LRF_CONTROL_MSG (type 44) to add laser rangefinder communication
    status feedback (serial link up/down and error).

  - Message modified (see MSG_FMT.H):
    Modified TARGET_RANGE_MSG (type 45) to add hw_error flag to report failure
    status of the laser rangefinder.

  - Message modified (see MSG_FMT.H):
    Modified ANNOTATION_MSG (type 14) to add support for dual annotation on the
    series 8000 tracker boards.  The show_unselected_video variable was added to
    show some standard annotations on the unselected video output.

  - Message modified (see MSG_FMT.H):
    Modified USER_STRING2_MSG (type 56) to add support for dual annotation on the
    series 8000 tracker boards.  The dest variable is used to specify the video
    output(s) to be annotated.

* version 5.6 (14 November 2017)

  - Added new lens type LENS_HITACHI_HD2005_FH32X15 (type 30) to control the
    Hitachi HD2005 camera with Fujinon FH32x15.6 zoom lens.

  - Added new lens type LENS_IRC_QUAZIR_LRSD_RPO_ODEM825 (type 31) to control
    the IRCameras QuazIR-LR SD camera with RP Optical ODEM925 zoom lens.

  - Added new lens type LENS_IRC_QUAZIR_LRSD_RPO_DIAMOND (type 32) to control
    the IRCameras QuazIR-LR SD camera with RP Optical Diamond zoom lens.

  - New message added (see MSG_FMT.H):
    GPS_DATA_MSG_TYPE (type 72) added to support GPS time and position feedback
    from a serial GPS unit attached to the tracker.

  - New message added (see MSG_FMT.H):
    CONFIG_GPS_MSG_TYPE (type 236) added to support configuration of the serial
    GPS unit attached to the tracker.  Only one type of GPS unit (X-Monkey) is
    currently supported.

  - Messages modified (see MSG_FMT.H):
    Modified LENS_SERIAL_ZOOM_MSG (type 27) and LENS_SERIAL_IR_ZOOM_MSG (type 28)
    to add lens communication status feedback (serial link up/down and error).

  - Modified extended camera support (see MSG_CAM_FMT.H):
    CAMTYPE_IRC_QUAZIR_LR (type 1) expanded to support extended control of
    the IRCameras QuazIR-LR SD camera features for the PVP and IRC lens types.

  - New extended camera support added (see MSG_CAM_FMT.H):
    CAMTYPE_G5_INFRARED_550CZ (type 2) added to support extended control of
    the G5 Infrared 550CZ camera features.

  - New extended camera support added (see MSG_CAM_FMT.H):
    CAMTYPE_L3_WALRSS_HD (type 3) added to support extended control of
    the L-3 WALRSS HD camera features.

* version 5.5 (26 May 2017)

  - Added support for Model 8210 tracker

  - Changed name of mount type 26 to MOUNT_GALIL_DMC_ETHERNET (see MSG_FMT.H).

  - Added new mount type MOUNT_GALIL_DMC (type 29) to control the
    PVP NightHawk and CMG systems using direct serial communications to
    the embedded Galil digital motion controller (see MSG_FMT.H).

  - New message added (see MSG_FMT.H):
    CAMERA_CONTROL_MSG (type 17) added to support extended control of
    various cameras and their features (see MSG_FMT.H and MSG_CAM_FMT.h).
    
  - New header file MSG_CAM_FMT.h added to support the camera control message.

  - Messages modified (see MSG_FMT.H):
    Modified LENS_SERIAL_ZOOM_MSG (type 27) and LENS_SERIAL_IR_ZOOM_MSG (type 28)
    to add zoom and focus speed control for lenses which support this.

* version 5.4 (15 November 2016)

  - Changed name of obsolete mount type MOUNT_QUICKSET (type 7) to
    MOUNT_QUICKSET_QPT(see MSG_FMT.H).  This type should no longer be used.
    
  - Changed name of mount type MOUNT_TELANTCO (type 25) to
    MOUNT_QUASONIX_DACU due to company name change (see MSG_FMT.H).
    
  - Added new mount type MOUNT_MOOG_MERCURY (type 27) to control the
    Moog Mercury positioner using their PTCR-1000 protocol (see MSG_FMT.H).
    Serial pass-through for camera control is implemented using tracker
    virtual UARTs 6 and 7.

  - Added new mount type MOUNT_MOOG_QMP (type 28) to control the
    Moog QMP/Taurus positioner using their PTCR-96 protocol (see MSG_FMT.H).
    Serial pass-through for camera control is implemented using tracker
    virtual UARTs 6 and 7.

  - Added new lens types LENS_MOOG_ZOOM_1 (type 25) and
    LENS_MOOG_ZOOM_2 (type 26) to control cameras attached to the
    Moog Mercury and QMP/Taurus positioners using Moog's integrated
    camera control (see MSG_FMT.H).

  - Added new lens type LENS_G5_INFRARED_550CZ (type 27) to control the
    G5 Infrared 550CZ thermal camera (see MSG_FMT.H).

  - Added new lens type LENS_L3_WALRSS_HD (type 28) to control the
    L-3 WALRSS HD thermal camera (see MSG_FMT.H).

  - Added new lens type LENS_HITACHI_HD2005_D60X16 (type 29) to control
    the Hitachi KP-HD visible integrated camera system with Hitachi HD2005
    camera and Fujinon D60x16.7 zoom lens (see MSG_FMT.H).

  - Added new digital switch type DVID_SWITCH_MATRIX_MSC_HD22L (type 3) to
    use the Matrix Switch MSC-HD22L 3G-SDI video switch as a virtual second
    digital video input to the tracker (see MSG_FMT.H).

  - Message CAMERA_CONFIG_MSG_TYPE (type 30) is deprecated.

  - Message CAMERA_GENERIC_MSG_TYPE (type 31) is deprecated.

  - New message added (see MSG_FMT.H):
    LENS_MOOG_ZOOM_MSG_TYPE (type 34) added to support control of cameras
    attached to the Moog Mercury and QMP/Taurus positioners using Moog's
    integrated camera control (see MSG_FMT.H).

  - Message MOUNT_FEEDBACK_MSG_TYPE (type 48) is officially supported to
    accept external mount azimuth and elevation angle input to the tracker.

  - Message modified (see MSG_FMT.H):
    Modified LENS_SERIAL_ZOOM_MSG (type 27) to add the osd_command variable
    for camera OSD control and a filter_select variable to support lenses with
    filter wheels.  Both the min_fov_gain and max_fov_gain variables which
    were previously deprecated have been removed and set as spare words
    for future use.

  - Message modified (see MSG_FMT.H):
    Modified LENS_SERIAL_IR_ZOOM_MSG (type 28) to change the name of the
    variable flir_menu_command to osd_command for more general use.
    A new full_nuc bit has been defined in order to run a camera NUC
    and the nuc_table variable has been marked as deprecated/obsolete
    to be replaced in the future.

  - Message modified (see MSG_FMT.H):
    Modified DIGITAL_VIDEO_STATUS_MSG (type 55) to add an interlaced bit
    to report the input video format as progressive or interlaced.

* version 5.3 (28 June 2016)

  - Added new mount type MOUNT_GALIL_DMC_NIGHTHAWK (type 26) to control the
    PVP NightHawk system using direct Ethernet communications to the
    embedded Galil digital motion controller (see MSG_FMT.H).

  - Added new lens type LENS_PVP_NIGHTHAWK_IR_ZOOM (type 23) to control the
    PVP NightHawks IR camera payload over Ethernet (see MSG_FMT.H).

  - Added new lens type LENS_PVP_NIGHTHAWK_VIS_ZOOM (type 24) to control the
    PVP NightHawks visible camera payload over Ethernet (see MSG_FMT.H).

  - Added new digital switch type DVID_SWITCH_EXTRON_SW4_3G (type 2) to
    use the Extron SW4 3G HD-SDI video switch as a virtual second
    digital video input to the tracker (see MSG_FMT.H).

  - New message added (see MSG_FMT.H):
    OVERLAY_STATUS_EXT_MSG (type 70) added to support additional status
    feedback including the user font flash load status and info.

  - Message modified (see MSG_FMT.H):
    Modified CORRELATION_CTRL_MSG (type 6) to add support for correlation
    reference adjustment/nudge speed control.

  - Structure added (see MSG_OVL_FMT.H):
    Added OVERLAY_FONT_SETUP structure to support configuring the custom
    user font character size before uploading a character bitmap.

  - Structure added (see MSG_OVL_FMT.H):
    Added OVERLAY_FONT_DOWNLOAD structure to support uploading a character
    bitmap in the custom user font.

  - Structure added (see MSG_OVL_FMT.H):
    Added OVERLAY_FONT_SAVE structure to support saving the currenly loaded
    custom user font to the tracker's flash memory.

  - Structure added (see MSG_OVL_FMT.H):
    Added OVERLAY_FONT_STRING structure to support overlay/sprite annotation
    using the custom user font.

  - Fix for CTimeStamp::GetAsTimet function to ensure time is UTC.

* version 5.2 (25 January 2016)

  - Added new lens type LENS_STINGRAY_OPTICS_SR2536 (type 22) to control the
    StingRay Optics SR2536 LWIR zoom lens (see MSG_FMT.H).

  - Added digital I/O function mapping for global I/O function disable.
    This can be used for joystick cable disconnect detection.
    
  - Message CONFIG_DIGITAL_VIDEO_EXT_MSG (type 228) is deprecated.
    This message was only supported on the obsolete Model 6007.
    
  - New message added (see MSG_FMT.H):
    CONFIG_GATE_RETICLE2_MSG (type 235) added to support additional gate
    reticle features including size based on the current field of view.
    This message obsoletes message CONFIG_GATE_RETICLE_MSG (type 216).

  - Message modified (see MSG_FMT.H):
    Modified LENS_SERIAL_IR_ZOOM_MSG (type 28) to add atherm_enable
    for focus temperature correction on StingRay SR2536 lens.

* version 5.1 (18 May 2015)

  - New message added (see MSG_FMT.H):
    MT_VALIDATION_MSG_TYPE (type 84) added to configure control
    of multi-target validation parameters.
    
  - Message modified (see MSG_FMT.H):
    Modified DIGITAL_VIDEO_STATUS_MSG (type 55) to add pixel_clock
    for reporting the digital video pixel clock rate in MHz.

  - Message modified (see MSG_FMT.H):
    Modified MT_ACQUIRE_MSG (type 81) to add inside_gate bit
    to filter out targets which touch the edge(s) of the gate.

* version 5.0 (3 February 2015)

  - Added multi-target selection defines for brightest and darkest target
  
  - New message added (see MSG_FMT.H):
    MT_DATA_MSG (type 83) added to support multi-target output
    
  - Message modified (see MSG_FMT.H):
    Modified MT_GENERAL_MSG (type 80) to add enable_output bit
    to control the video rate output of multi-target data

  - Structure added (see MSG_OVL_FMT.H):
    Added OVERLAY_DIAMOND structure to draw diamond shapes and partial
    diamond shapes to the graphic overlay/sprites.

  - Structure added (see MSG_OVL_FMT.H):
    Added OVERLAY_STRING structure to draw ASCII text characters and
    strings to the graphic overlay/sprites.

* version 4.9 (9 December 2014)

  - Added new lens type LENS_FLIR_RS6700_DFOV (type 20) to control the
    FLIR RS6700 MWIR camera system (see MSG_FMT.H).

  - New message added (see MSG_FMT.H):
    LENS_SERIAL_IR_DFOV_MSG (type 33) added to control the FLIR RS6700
    MWIR camera system.

  - Added new lens type LENS_OPTEC_FOCUSER (type 21) to control the
    Optec telescope focuser (see MSG_FMT.H).  This lens is supported by
    the LENS_SERIAL_FIXED_FOV_MSG (type 32) message.

  - Message modified (see MSG_FMT.H):
    Modified OVERLAY_STATUS_MSG (type 63) to add inversion status bits
    for the overlay and four sprites.  Also, added overlay position
    feeback.
    
  - Added commands to set the inversion state of the video graphic
    overlay and the sprites.  Also added comments to the position command
    (OVL_CMD_POSITION) to reflect a new feature which allows the overlay
    to be positioned on the display like sprites (see MSG_OVL_FMT.H).
    
  - Structure modified (see MSG_OVL_FMT.H):
    Modified OVERLAY_POSITION structure to use signed value.  This is
    necessary to support positions off the top/left of the display.

* version 4.8 (9 September 2014)

  - Message modified (see MSG_FMT.H):
    Modified SYSTEM_CTRL_MSG (type 2) to add an extended_status control
    bit to enable the extended status bits in the STATUS_MSG output.

  - Message modified (see MSG_FMT.H):
    Modified COAST_CTRL_MSG (type 9) to add a gate_control bit to
    enable manual gate size/position control during coast.
    
  - Message modified (see MSG_FMT.H):
    Modified STATUS_MSG (type 255) to add extended status bits which are
    optional/backward compatible and enabled in the SYSTEM_CTRL_MSG.
    The video interlace field indicator bit is the first extended status
    bit available.

* version 4.7 (10 July 2014)

  - Added new lens type LENS_GRAFLEX_FIXED_FOV (type 19) to control the
    Model 903 Camera System which includes a telescope with only focus
    control (see MSG_FMT.H).

  - Message modified (see MSG_FMT.H):
    Modified TGT_VALIDATION_CTRL_MSG (type 10) to add a bit for enabling
    the new "invalidate target if touching gate" test for target validation.

  - Message documentation change (see MSG_FMT.H):
    See the CONFIG_GATE_SIZE_MSG (type 200) definition in the MSG_FMT.H file.
    Updated comments document the variable scaling (digital video sources).

  - Message documentation change (see MSG_FMT.H):
    See the CONFIG_GATE_POS_MSG (type 201) definition in the MSG_FMT.H file.
    Updated comments document the variable scaling (digital video sources).

  - Message modified (see MSG_FMT.H):
    Modified CONFIG_VALIDATION_MSG (type 208) to add control of the target
    history queue depth used to filter the target statistics used for validation.

  - Message modified (see MSG_FMT.H):
    Modified CONFIG_VIDEO_SWITCH_MSG (type 234) to add control of various
    digital video input switches.  Also added feedback of the connection
    status for both analog and digital switches (query only).

* version 4.6 (29 April 2014)

  - Updates to support the Model 7410 PCIe Tracker

  - Added support for up to three track gates (on boards with this capability)
  
  - Added tracker status bit defines for boot and run time BIT failures
  
  - Mount stow 1 & 2 commands added for mounts which support this function
  
  - Added support for control of external analog video switch to route
    video input to the tracker.  Currently only the Extron MMX 42AV is
    supported.

  - New message added (see MSG_FMT.H):
    CONFIG_VIDEO_SWITCH_MSG_TYPE (type 234) added to configure control
    of external video switches.

  - Message modified (see MSG_FMT.H):
    Modified SYSTEM_CTRL_MSG (type 2) to add bits for enabling the third
    track gate and for enabling lens FOV slaving.

  - Added digital I/O function mapping for lens FOV slaving

  - Message modified (see MSG_FMT.H):
    Modified CAPABILITIES_MSG (type 41) to report the availability of
    the third track gate.

* version 4.5 (9 September 2013)

  - Added virtual SMUserStrings functionality to CTrackerTcpInterface class
    in order to support IRIG/GPS annotation at frame rate.
    
  - Added a thread abort mechanism to the CTrackerConfiguration class
  
  - Minor updates to support the Model 7015 VMEbus Tracker
  
  - Mount stow command added for mounts which support this function
  
  - New message added (see MSG_FMT.H):
    THRESHOLD_STATISTICS_MSG_TYPE (type 69) added to allow monitoring of
    target threshold statistics (query only).

  - Message modified (see MSG_FMT.H):
    Modified CORRELATION_CTRL_MSG (type 6) to add bits to allow recentering
    of the correlation reference image during track.

  - Message modified (see MSG_FMT.H):
    Modified CONFIG_AUTOTHRESHOLD_MSG (type 226) to add a minimum contrast
    setting for the updated auto-threshold and auto-polarity algorithms.
    This setting provides a minimum contrast floor to avoid thresholding
    noise when there is no real target present in the gate.

* version 4.4 (6 June 2013)

  - AutoAcquire functionality is deprecated.  Multi-target should be used
    instead.  The following message types are no longer recommended and
    should be avoided.
    AAQ_ACQUIRE_CTRL_MSG_TYPE (type 11)
    AAQ_TRACK_CTRL_MSG_TYPE (type 12)
    AAQ_TGT_SELECT_CTRL_MSG_TYPE (type 13)
    
  - The clutter rejection processor (CRP) is obsolete and support has
    been removed from the tracker and SDK.  The following messages types
    are no longer supported.
    CRP_CONTROL_MSG_TYPE (type 58)
    CONFIG_CRP_MSG_TYPE (type 225)
    
  - New messages added (see MSG_FMT.H):
    CONTROL_BOX_CONTROL_MSG_TYPE (type 67) and
    CONTROL_BOX_STATUS_MSG_TYPE (type 68) added to support proxy of
    the 700 Series Controllers over the main tracker interface (instead
    of connected directly via serial to the tracker's UART1).
    
  - New message added (see MSG_FMT.H):
    CONFIG_CONTROL_BOX_IO_MSG_TYPE (type 233) added to support mapping
    of the 700 Series Controller's external joystick I/O to specific
    tracker functions.

* version 4.3 (27 February 2013)

  - Minor changes to GenArray.h and GenPtrArray.h
  
  - Added option to sync PC time with GPS/IRIG board along with
    support for the Brandywine PCI Express board.
  
  - Added support for tracker VME interrupt handling
    (see vme_api.h and TrackerVMEInterface.h/c)
    
  - Updates to video overlay and sprites (see MSG_OVL_FMT.H)
  
  - Added new mount type MOUNT_GRAFLEX_PT150_V2 (see MSG_FMT.H).
  
  - Added new mount type MOUNT_TELANTCO (see MSG_FMT.H).
  
  - Added new lens type LENS_FLIR_RANGER_HRC (type 17) to control the
    FLIR Ranger HRC thermal zoom camera (see MSG_FMT.H).
    
  - Added new lens type LENS_FUJINON_C22X23R2DZP1 (type 18) to control
    the Fujinon C22X zoom lens (see MSG_FMT.H).
    
  - Added new laser range finder commands of LRF_CMD_BIT (runs built-in test)
    and LRF_CMD_SHOT_COUNT (retrieves the shot counter) to support ALST
    laser range finders.
    
  - New message added (see MSG_FMT.H):
    POS_TRACK_STATUS_MSG_TYPE (type 66) added to support position tracking
    functionality (aka-radar slaving) for any supported mount.

  - New message added (see MSG_FMT.H):
    CONFIG_POS_TRACK_MSG_TYPE (type 232) added to support position tracking
    functionality (aka-radar slaving) for any supported mount.

  - Message modified (see MSG_FMT.H):
    Modified SYSTEM_CTRL_MSG (type 2) to add an enable bit for output of
    track errors when in acquire mode.

  - Message modified (see MSG_FMT.H)
    Modified LENS_SERIAL_IR_ZOOM_MSG (type 28) to add support to control the
    FLIR Ranger HRC thermal zoom camera.
    
  - Memory optimization for CTrackerMessage class (see TrackerMessage.h/c)

* version 4.2 (28 August 2012)

  - Added new mount type MOUNT_EVPU_MS02 (see MSG_FMT.H).

  - Message modified (see MSG_FMT.H):
    Modified MT_ACQUIRE_MSG (type 81) to add additional selection criteria
    and filters including movement direction and speed.

* version 4.1 (30 July 2012)

  - Added support for Model 8200 tracker

  - Added new mount type MOUNT_FLIR_ESERIES (see MSG_FMT.H).

  - New message added (see MSG_FMT.H):
    OVERLAY_CONTROL_MSG_TYPE (type 62) added to support video overlay
    and sprites control including basic drawing.

  - New message added (see MSG_FMT.H):
    OVERLAY_STATUS_MSG_TYPE (type 63) added to support video overlay
    and sprites status feedback (query only).

  - New message added (see MSG_FMT.H):
    LOS_OFFSET_CTRL2_MSG_TYPE (type 64) added to support higher resolution
    video sources.  This message obsoletes message type LOS_OFFSET_CTRL_MSG_TYPE.

  - New message added (see MSG_FMT.H):
    OFFSET_AIM_CTRL2_MSG_TYPE (type 65) added to support higher resolution
    video sources.  This message obsoletes message type OFFSET_AIM_CTRL_MSG_TYPE.

* version 4.0 (9 December 2011)

  - TrkrPciApi DLL/LIB updated to version 3.3 to add support for reading
    the hardware frame timer (time since last vertical sync).

  - Added new mount type MOUNT_QUICKSET_GEMINEYE (see MSG_FMT.H).

  - Added new lens type LENS_GRAFLEX_35X (type 16) to serially control the
    Graflex 35X zoom lens (see MSG_FMT.H).

  - New message added (see MSG_FMT.H):
    MESSAGE_ACK_MSG_TYPE (type 254) added to send optional acknowledge
    messages when a command is recieved.

  - Message modified (see MSG_FMT.H):
    Modified SYSTEM_CTRL_MSG (type 2) to add an enable bit for sending
    message acknowledgements.

* version 3.9 (15 April 2011)

  - Message modified (see MSG_FMT.H):
    Modified CONFIG_DIGITAL_VIDEO_MSG (type 220) to add an enable_data_valid
    variable which when enabled instructs the tracker to use the data valid
    Camera Link signal to qualify the incoming video data.  Enabling this flag
    will cause the video to be delayed by a line.

* version 3.8 (7 April 2011)

  - Message modified (see MSG_FMT.H):
    Modified CAPABILITIES_MSG (type 41) to add indicator for DVI digital
    video capability.

* version 3.7 (27 October 2010)

  - Added new mount type MOUNT_ORBIT_AL4015 (see MSG_FMT.H).

  - Message modified (see MSG_FMT.H):
    Modified CONFIG_INTRUSION_DETECT_MSG (type 231) to add control of intrusion
    gate size.

  - New message added (see MSG_FMT.H):
    CONFIG_INTRUSION_DETECT_MSG (type 231) added to support target intrusion
    detection.

  - Message modified (see MSG_FMT.H):
    Modified STATUS_MSG_TYPE (type 255) to add intrusion detection flag to the
    status variable.  Bit 9 (TSTAT_INTRUSION_DETECTED) of the status variable
    is set when an intrusion is detected.

  - Message modified (see MSG_FMT.H):
    Modified SYSTEM_CTRL_MSG (type 2) to add a centroid_in_edge flag to track
    the centroid projected to the edge of the target instead of the edge most
    pixel of the target.

* version 3.6 (27 July 2010)

  - No changes

* version 3.5 (18 June 2010)

  - Updated Windows driver, library and DLL

* version 3.4 (12 March 2010)

  - New messages added (see MSG_FMT.H):
    MT_GENERAL_MSG_TYPE (type 80) added to support multi-target functionality.
    MT_ACQUIRE_MSG_TYPE (type 81) added to support multi-target functionality.
    MT_TRACK_MSG_TYPE   (type 82) added to support multi-target functionality.

  - Message modified (see MSG_FMT.H)
    Modified CAPABILITIES_MSG (type 41) to add indicators for Camera Link and
    HD-SDI digital video capability.

* version 3.3 (24 February 2010)

  - First release (see 7005 and 6007 files for extended history)
