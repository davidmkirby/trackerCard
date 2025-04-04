// CallbackDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Callback.h"
#include "CallbackDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// defines
#define DATA_UPDATE_TIMER_ID			10
#define DATA_UPDATE_TIMER_INTERVAL		250		// 1/4 second

#define WM_TRACKER_MESSAGE	(WM_USER + 100 + 87)

// static data
const CString TrackStateArray[] = 
{
	"Initialization",
	"Acquire",
	"Pending Track",
	"On Track",
	"Coast",
	"Off Track",
	"Auto Acquire"
};

const CString TrackStatusArray[] =
{
	"OK",
	"Too Few Pixels",
	"Too Many Pixels",
	"X Position Fail",
	"Y Position Fail",
	"NCount Too Large",
	"NCount Too Small",
	"X Size Fail",
	"Y Size Fail",
	"?",
	"?",
	"?",
	"Corr Match Fail",
	"?",
	"?",
	"?"
};


///////////////////////////////////////////////////////////////////////////////
// Utility functions
//

///////////////////////////////////////////////////////////////////////////////
// Set the checksum on a message
//
void SetChecksum(void* pMsg, size_t MsgSize)
{
	const unsigned char* pBuffer;
	short sum;
	int nBytes, i;

	// get length to add up
	nBytes = MsgSize - 2;

	// sum up all the data bytes
	pBuffer = (unsigned char*)pMsg;
	sum = 0;

	for( i=0; i < nBytes; i++ )
	{
		sum += *pBuffer;
		pBuffer++;
	}

	// set the message checksum
	*((short*)pBuffer) = -sum;
}

///////////////////////////////////////////////////////////////////////////////
// Verify the checksum on a message
//
BOOL VerifyChecksum(void* pMsg, size_t MsgSize)
{
	const unsigned char* pBuffer;
	short sum;
	int nBytes, i;

	// sanity
	if( pMsg == NULL )
		return FALSE;

	// get length to add up
	nBytes = MsgSize - 2;

	// sum up all the data bytes
	pBuffer = (unsigned char*)pMsg;
	sum = 0;

	for( i=0; i < nBytes; i++ )
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
// Initialize tracker messages
//
void CCallbackDlg::InitMessages()
{
	memset(&m_TrkrStatusMsg, 0, sizeof(STATUS_MSG));

	memset(&m_TrkrPingMsg, 0, sizeof(PING_MSG));
	m_TrkrPingMsg.sync		= GATE0_SYNC_WORD;
	m_TrkrPingMsg.msg_type	= PING_MSG_TYPE;

	memset(&m_TrkrSystemMsg, 0, sizeof(SYSTEM_CTRL_MSG));
	m_TrkrSystemMsg.sync				= GATE0_SYNC_WORD;
	m_TrkrSystemMsg.msg_type			= SYSTEM_CTRL_MSG_TYPE;
	m_TrkrSystemMsg.vid_src				= VS_ANALOG1;
	m_TrkrSystemMsg.out_60hz			= OFF;
	m_TrkrSystemMsg.dualgates			= DISABLE;
	m_TrkrSystemMsg.auto_size_ratio		= 150;	// 1.50:1 gate to target ratio
	m_TrkrSystemMsg.vec_trans_time		= 4;
	m_TrkrSystemMsg.acquire_val_time	= 1;
}

///////////////////////////////////////////////////////////////////////////////
// Send the tracker a message
//
BOOL CCallbackDlg::SendTrackerMessage(void* pMsg, size_t MsgSize)
{
	int nSleepCount;

	// set message checksum
	SetChecksum(pMsg, MsgSize);

	// wait until the tracker is ready
	nSleepCount = 0;
	while( !TrkrPciReadyToSendCommandMessage(m_hTrackerBoard) )
	{
		// sleep 10ms
		Sleep(10);
		nSleepCount++;

		// timeout after 1 second
		if( nSleepCount > 100 )
		{
			TRACE("Timed out trying to send the tracker a message!\n");
			return FALSE;
		}
	}

	// send the message
	return TrkrPciSendCommandMessage(m_hTrackerBoard, pMsg, MsgSize);
}

///////////////////////////////////////////////////////////////////////////////
// Get a tracker status message
//
BOOL CCallbackDlg::GetStatusMessage(void* pMsg, size_t MsgSize)
{
	// wait until the tracker is ready
	if( !TrkrPciGetStatusMessage(m_hTrackerBoard, pMsg, MsgSize) )
	{
		TRACE("A tracker STATUS message is not available!\n");
		return FALSE;
	}

	// verify checksum
	if( !VerifyChecksum(pMsg, MsgSize) )
	{
		TRACE("Checksum of received STATUS message was invalid!\n");
		return FALSE;
	}

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCallbackDlg dialog

CCallbackDlg::CCallbackDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCallbackDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCallbackDlg)
	m_TrackErrorX = _T("");
	m_TrackErrorY = _T("");
	m_TrackState = _T("");
	m_TrackStatus = _T("");
	m_TargetSizeX = 0;
	m_TargetSizeY = 0;
	m_MountAz = 0.0;
	m_MountEl = 0.0;
	m_TrackMode = -1;
	m_FilteredTrackErrorX = _T("");
	m_FilteredTrackErrorX2 = _T("");
	m_FilteredTrackErrorY = _T("");
	m_FilteredTrackErrorY2 = _T("");
	m_TrackState2 = _T("");
	m_TrackStatus2 = _T("");
	m_TrackErrorX2 = _T("");
	m_TrackErrorY2 = _T("");
	m_TargetSizeX2 = 0;
	m_TargetSizeY2 = 0;
	m_TargetCount = 0;
	m_TargetCount2 = 0;
	m_TrackerOutput = -1;
	m_PollingRate = DATA_UPDATE_TIMER_INTERVAL;
	m_MessageRate = _T("");
	//}}AFX_DATA_INIT

	m_iTrackState = -1;
	m_iTrackStatus = -1;

	m_iTrackState2 = -1;
	m_iTrackStatus2 = -1;

	m_hTrackerBoard = NULL;

	m_MessageCount = 0;

	InitMessages();

	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCallbackDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCallbackDlg)
	DDX_Control(pDX, IDC_MESSAGE_RATE, m_MessageRateEditBox);
	DDX_Control(pDX, IDC_MOUNT_EL, m_MountElEdit);
	DDX_Control(pDX, IDC_MOUNT_AZ, m_MountAzEdit);
	DDX_Control(pDX, IDC_STATUS, m_TrackStatusEdit);
	DDX_Control(pDX, IDC_STATE, m_TrackStateEdit);
	DDX_Control(pDX, IDC_ERROR_Y, m_TrackErrorYEdit);
	DDX_Control(pDX, IDC_ERROR_X, m_TrackErrorXEdit);
	DDX_Control(pDX, IDC_TARGETSIZE_Y, m_TargetSizeYEdit);
	DDX_Control(pDX, IDC_TARGETSIZE_X, m_TargetSizeXEdit);
	DDX_Text(pDX, IDC_ERROR_X, m_TrackErrorX);
	DDX_Text(pDX, IDC_ERROR_Y, m_TrackErrorY);
	DDX_Text(pDX, IDC_STATE, m_TrackState);
	DDX_Text(pDX, IDC_STATUS, m_TrackStatus);
	DDX_Text(pDX, IDC_TARGETSIZE_X, m_TargetSizeX);
	DDX_Text(pDX, IDC_TARGETSIZE_Y, m_TargetSizeY);
	DDX_Text(pDX, IDC_MOUNT_AZ, m_MountAz);
	DDX_Text(pDX, IDC_MOUNT_EL, m_MountEl);
	DDX_Control(pDX, IDC_TARGETCOUNT2, m_TargetCount2Edit);
	DDX_Control(pDX, IDC_TARGETCOUNT, m_TargetCountEdit);
	DDX_Control(pDX, IDC_FILTERED_ERROR_Y2, m_FilteredTrackErrorY2Edit);
	DDX_Control(pDX, IDC_FILTERED_ERROR_Y, m_FilteredTrackErrorYEdit);
	DDX_Control(pDX, IDC_FILTERED_ERROR_X2, m_FilteredTrackErrorX2Edit);
	DDX_Control(pDX, IDC_FILTERED_ERROR_X, m_FilteredTrackErrorXEdit);
	DDX_Text(pDX, IDC_FILTERED_ERROR_X, m_FilteredTrackErrorX);
	DDX_Text(pDX, IDC_FILTERED_ERROR_X2, m_FilteredTrackErrorX2);
	DDX_Text(pDX, IDC_FILTERED_ERROR_Y, m_FilteredTrackErrorY);
	DDX_Text(pDX, IDC_FILTERED_ERROR_Y2, m_FilteredTrackErrorY2);
	DDX_Control(pDX, IDC_STATUS2, m_TrackStatus2Edit);
	DDX_Control(pDX, IDC_STATE2, m_TrackState2Edit);
	DDX_Control(pDX, IDC_ERROR_Y2, m_TrackErrorY2Edit);
	DDX_Control(pDX, IDC_ERROR_X2, m_TrackErrorX2Edit);
	DDX_Control(pDX, IDC_TARGETSIZE_Y2, m_TargetSizeY2Edit);
	DDX_Control(pDX, IDC_TARGETSIZE_X2, m_TargetSizeX2Edit);
	DDX_Text(pDX, IDC_STATE2, m_TrackState2);
	DDX_Text(pDX, IDC_STATUS2, m_TrackStatus2);
	DDX_Text(pDX, IDC_ERROR_X2, m_TrackErrorX2);
	DDX_Text(pDX, IDC_ERROR_Y2, m_TrackErrorY2);
	DDX_Text(pDX, IDC_TARGETSIZE_X2, m_TargetSizeX2);
	DDX_Text(pDX, IDC_TARGETSIZE_Y2, m_TargetSizeY2);
	DDX_Text(pDX, IDC_TARGETCOUNT, m_TargetCount);
	DDX_Text(pDX, IDC_TARGETCOUNT2, m_TargetCount2);
	DDX_Radio(pDX, IDC_OUTPUT_COMMAND, m_TrackerOutput);
	DDX_Text(pDX, IDC_DATA_UPDATE, m_PollingRate);
	DDX_Text(pDX, IDC_MESSAGE_RATE, m_MessageRate);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCallbackDlg, CDialog)
	//{{AFX_MSG_MAP(CCallbackDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_OUTPUT_COMMAND, OnTrackerOutput)
	ON_BN_CLICKED(IDC_OUTPUT_60HZ, OnTrackerOutput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCallbackDlg message handlers

BOOL CCallbackDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	OpenTrackerBoard();	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CCallbackDlg::OpenTrackerBoard()
{
	CString str;
	int nBoards;

	// verify tracker
	nBoards = TrkrPciGetNumberOfBoards();
	if( nBoards < 1 )
	{
		str.Format("No tracker boards found on the PCI bus!");
		TRACE("%s\n", str);
		AfxMessageBox(str);
		return FALSE;
	}

	str.Format("Found %d tracker boards on the PCI bus.", nBoards);
	TRACE("%s\n", str);
	AfxMessageBox(str);

	// open the tracker board
	m_hTrackerBoard = TrkrPciOpenBoard(0);
	if( m_hTrackerBoard == NULL )
	{
		str.Format("Failed to open the tracker board!");
		TRACE("%s\n", str);
		AfxMessageBox(str);
		return FALSE;
	}

	str.Format("Opened tracker board #0 successfully.");
	TRACE("%s\n", str);
	AfxMessageBox(str);

	if( !TrkrPciAttachWindowsMessage(m_hTrackerBoard, GetSafeHwnd(), WM_TRACKER_MESSAGE) )
	{
		str.Format("Failed to open the attach window handle to tracker board!");
		TRACE("%s\n", str);
		AfxMessageBox(str);
		return FALSE;
	}

	return TRUE;
}

BOOL CCallbackDlg::DestroyWindow() 
{
	// clean up
	KillTimer(DATA_UPDATE_TIMER_ID);
	TrkrPciCloseBoard(m_hTrackerBoard);
	
	return CDialog::DestroyWindow();
}


void CCallbackDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCallbackDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCallbackDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/////////////////////////////////////////////////////////////////////////////
// CCallbackDlg::HandleIncomingMessage(HANDLE hBoard)
//
// Handle an incoming message from the tracker
//
void CCallbackDlg::HandleIncomingMessage(HANDLE hBoard)
{
	STATUS_MSG TrkrStatusMsg;
	char TrashBuffer[2];

	// throw away any response messages
	TrkrPciGetResponseMessage(m_hTrackerBoard, (char*)TrashBuffer, 2);

	// get the status message
	if( GetStatusMessage(&TrkrStatusMsg, sizeof(STATUS_MSG)) )
		HandleStatusMessage(&TrkrStatusMsg);

	m_MessageCount++;
}

/////////////////////////////////////////////////////////////////////////////
// CCallbackDlg::HandleStatusMessage(const STATUS_MSG* pStatus)
//
// Handle an incoming status message from the tracker
//
void CCallbackDlg::HandleStatusMessage(const STATUS_MSG* pStatus)
{
	CString str;
	int iTemp = 0;
	double dTemp = 0;

	// if we are not too behind in processing incoming data, then update the screen
	BOOL bUpdateScreen = TRUE;

	// is this the primary gate?
	if( pStatus->gate == 0 )
	{
		// this is the primary gate
		ASSERT(pStatus->sync == GATE0_SYNC_WORD);

		// update target size X & Y
		if( m_TargetSizeX !=  pStatus->txsize )
		{
			m_TargetSizeX = pStatus->txsize;

			if( bUpdateScreen )
			{
				str.Format("%d", m_TargetSizeX);
				m_TargetSizeXEdit.SetWindowText(str);
			}
		}

		if( m_TargetSizeY != pStatus->tysize )
		{
			m_TargetSizeY = pStatus->tysize;

			if( bUpdateScreen )
			{
				str.Format("%d", m_TargetSizeY);
				m_TargetSizeYEdit.SetWindowText(str);
			}
		}

		// update target error X & Y
		double xerr = (double)pStatus->txerr / 32.0;
		str.Format("%0.3f", xerr);

		if( m_TrackErrorX != str )
		{
			m_TrackErrorX = str;
			if( bUpdateScreen )
				m_TrackErrorXEdit.SetWindowText(m_TrackErrorX);
		}

		double yerr = (double)pStatus->tyerr / 32.0;
		str.Format("%0.3f", yerr);

		if( m_TrackErrorY != str )
		{
			m_TrackErrorY = str;
			if( bUpdateScreen )
				m_TrackErrorYEdit.SetWindowText(m_TrackErrorY);
		}

		// update target pixel count
		if( m_TargetCount !=  pStatus->tcount )
		{
			m_TargetCount = pStatus->tcount;

			if( bUpdateScreen )
			{
				str.Format("%d", m_TargetCount);
				m_TargetCountEdit.SetWindowText(str);
			}
		}

		// update filtered error X & Y
		xerr = (double)pStatus->filtered_txerr / 32.0;
		str.Format("%0.3f", xerr);

		if( m_FilteredTrackErrorX != str )
		{
			m_FilteredTrackErrorX = str;
			if( bUpdateScreen )
				m_FilteredTrackErrorXEdit.SetWindowText(m_FilteredTrackErrorX);
		}

		yerr = (double)pStatus->filtered_tyerr / 32.0;
		str.Format("%0.3f", yerr);

		if( m_FilteredTrackErrorY != str )
		{
			m_FilteredTrackErrorY = str;
			if( bUpdateScreen )
				m_FilteredTrackErrorYEdit.SetWindowText(m_FilteredTrackErrorY);
		}

		// update track state and status
		if( m_iTrackState != pStatus->trk_state )
		{
			m_TrackState = TrackStateArray[pStatus->trk_state];
			if( bUpdateScreen )
				m_TrackStateEdit.SetWindowText(m_TrackState);
			m_iTrackState = pStatus->trk_state;
		}

		if( m_iTrackStatus != pStatus->status )
		{
			m_TrackStatus = GetTrackStatusString( pStatus->status );
			if( bUpdateScreen )
				m_TrackStatusEdit.SetWindowText(m_TrackStatus);
			m_iTrackStatus = pStatus->status;
		}
	}
	else
	{
		// this is the secondary gate
		ASSERT(pStatus->sync == GATE1_SYNC_WORD);

		// update target size X & Y
		if( m_TargetSizeX2 !=  pStatus->txsize )
		{
			m_TargetSizeX2 = pStatus->txsize;

			if( bUpdateScreen )
			{
				str.Format("%d", m_TargetSizeX2);
				m_TargetSizeX2Edit.SetWindowText(str);
			}
		}

		if( m_TargetSizeY2 != pStatus->tysize )
		{
			m_TargetSizeY2 = pStatus->tysize;

			if( bUpdateScreen )
			{
				str.Format("%d", m_TargetSizeY2);
				m_TargetSizeY2Edit.SetWindowText(str);
			}
		}

		// update target error X & Y
		double xerr = (double)pStatus->txerr / 32.0;
		str.Format("%0.3f", xerr);

		if( m_TrackErrorX2 != str )
		{
			m_TrackErrorX2 = str;
			if( bUpdateScreen )
				m_TrackErrorX2Edit.SetWindowText(m_TrackErrorX2);
		}

		double yerr = (double)pStatus->tyerr / 32.0;
		str.Format("%0.3f", yerr);

		if( m_TrackErrorY2 != str )
		{
			m_TrackErrorY2 = str;
			if( bUpdateScreen )
				m_TrackErrorY2Edit.SetWindowText(m_TrackErrorY2);
		}

		// update target pixel count
		if( m_TargetCount2 !=  pStatus->tcount )
		{
			m_TargetCount2 = pStatus->tcount;

			if( bUpdateScreen )
			{
				str.Format("%d", m_TargetCount2);
				m_TargetCount2Edit.SetWindowText(str);
			}
		}

		// update filtered error X & Y
		xerr = (double)pStatus->filtered_txerr / 32.0;
		str.Format("%0.3f", xerr);

		if( m_FilteredTrackErrorX2 != str )
		{
			m_FilteredTrackErrorX2 = str;
			if( bUpdateScreen )
				m_FilteredTrackErrorX2Edit.SetWindowText(m_FilteredTrackErrorX2);
		}

		yerr = (double)pStatus->filtered_tyerr / 32.0;
		str.Format("%0.3f", yerr);

		if( m_FilteredTrackErrorY2 != str )
		{
			m_FilteredTrackErrorY2 = str;
			if( bUpdateScreen )
				m_FilteredTrackErrorY2Edit.SetWindowText(m_FilteredTrackErrorY2);
		}
		
		// update track state and status
		if( m_iTrackState2 != pStatus->trk_state )
		{
			m_TrackState2 = TrackStateArray[pStatus->trk_state];
			if( bUpdateScreen )
				m_TrackState2Edit.SetWindowText(m_TrackState2);
			m_iTrackState2 = pStatus->trk_state;
		}

		if( m_iTrackStatus2 != pStatus->status )
		{
			m_TrackStatus2 = GetTrackStatusString( pStatus->status );
			if( bUpdateScreen )
				m_TrackStatus2Edit.SetWindowText(m_TrackStatus2);
			m_iTrackStatus2 = pStatus->status;
		}
	}

	// update mount azimuth and elevation
	iTemp = pStatus->azimuth_msw;
	iTemp = (iTemp << 16) & 0xFFFF0000;
	iTemp |= (int)pStatus->azimuth_lsw & 0xFFFF;
	dTemp = (double)iTemp / 10000.0;

	if( dTemp != m_MountAz )
	{
		m_MountAz = dTemp;

		if( bUpdateScreen )
		{
			str.Format("%0.4f", m_MountAz);
			m_MountAzEdit.SetWindowText(str);
		}
	}

	iTemp = pStatus->elevation_msw;
	iTemp = (iTemp << 16) & 0xFFFF0000;
	iTemp |= (int)pStatus->elevation_lsw & 0xFFFF;
	dTemp = (double)iTemp / 10000.0;

	if( dTemp != m_MountEl )
	{
		m_MountEl = dTemp;

		if( bUpdateScreen )
		{
			str.Format("%0.4f", m_MountEl);
			m_MountElEdit.SetWindowText(str);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCallbackDlg::SetTrackStatus(int status)
//
// Set the track status string
//
CString CCallbackDlg::GetTrackStatusString(int status)
{
	// set the status string
	if( status & BIT1 )
		return TrackStatusArray[1];		// Too Few Pixels
	else if( status & BIT2 )
		return TrackStatusArray[2];		// Too Many Pixels
	else if( status & BIT3 )
		return TrackStatusArray[3];		// X Position Fail
	else if( status & BIT4 )
		return TrackStatusArray[4];		// Y Position Fail
	else if( status & BIT5 )
		return TrackStatusArray[5];		// N Count Too Large
	else if( status & BIT6 )
		return TrackStatusArray[6];		// N Count Too Small
	else if( status & BIT7 )
		return TrackStatusArray[7];		// X Size Fail
	else if( status & BIT8 )
		return TrackStatusArray[8];		// Y Size Fail
	else if( status & BIT12 )
		return TrackStatusArray[12];	// Corr Match Fail

	return TrackStatusArray[0];			// OK
}

void CCallbackDlg::OnTimer(UINT nIDEvent) 
{
	if( nIDEvent == DATA_UPDATE_TIMER_ID )
	{
		// polling?
		if( m_TrackerOutput == 0 )
		{
			// send PING message
			if( !SendTrackerMessage(&m_TrkrPingMsg, sizeof(PING_MSG)) )
			{
				TRACE("Failed to send the tracker a PING message!\n");
			}
		}

		// compute messages per second
		double MessageRate = (double)m_MessageCount / ((double)m_PollingRate / 1000.0);
		m_MessageCount = 0;

		m_MessageRate.Format("%0.2f", MessageRate);
		m_MessageRateEditBox.SetWindowText(m_MessageRate);
	}
	
	CDialog::OnTimer(nIDEvent);
}

LRESULT CCallbackDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// handle tracker serial messages
	if( message == WM_TRACKER_MESSAGE )
	{
		HandleIncomingMessage( (HANDLE)lParam );
		return 0;
	}
	
	return CDialog::WindowProc(message, wParam, lParam);
}

void CCallbackDlg::OnTrackerOutput() 
{
	CString str;

	// get dialog data
	UpdateData(TRUE);

	// set output mode
	m_TrkrSystemMsg.out_60hz = m_TrackerOutput;

	if( !SendTrackerMessage(&m_TrkrSystemMsg, sizeof(SYSTEM_CTRL_MSG)) )
	{
		str.Format("Failed to send the tracker a SYSTEM message!");
		TRACE("%s\n", str);
		AfxMessageBox(str);
	}

	// reset timer
	if( m_PollingRate < 20 )
		m_PollingRate = 20;
	KillTimer(DATA_UPDATE_TIMER_ID);
	SetTimer(DATA_UPDATE_TIMER_ID, m_PollingRate, NULL);

	UpdateData(FALSE);
}
