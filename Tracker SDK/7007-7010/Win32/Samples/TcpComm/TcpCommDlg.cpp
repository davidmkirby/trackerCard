// TcpCommDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TcpComm.h"
#include "TcpCommDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// defines
#define DATA_UPDATE_TIMER_ID			10
#define DATA_UPDATE_TIMER_INTERVAL		500		// 1/2 second

#define DATA_POLLING_TIMER_ID			11
#define DATA_POLLING_TIMER_INTERVAL		250		// 1/4 second

#define WM_TRACKER_MESSAGE	(WM_USER + 100 + 87)

#define DEFAULT_TRACKER_IP_ADDRESS		"192.168.1.100"


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
// CTcpCommDlg dialog

CTcpCommDlg::CTcpCommDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTcpCommDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTcpCommDlg)
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
	m_TrackerOutput = 1;
	m_PollingRate = DATA_POLLING_TIMER_INTERVAL;
	m_MessageRate = _T("");
	m_IPAddress = _T("");
	//}}AFX_DATA_INIT

	m_iTrackState = -1;
	m_iTrackStatus = -1;

	m_iTrackState2 = -1;
	m_iTrackStatus2 = -1;

	m_MessageCount = 0;

	m_IPAddress = DEFAULT_TRACKER_IP_ADDRESS;
	m_TrackerBoard.m_HostAddress = m_IPAddress;

	m_SystemMsg.SetDefaultSystem();
	m_PingMsg.SetType(PING_MSG_TYPE);

	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTcpCommDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTcpCommDlg)
	DDX_Control(pDX, IDC_CONNECTED, m_ConnectedCheckbox);
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
	DDX_Text(pDX, IDC_IP_ADDRESS, m_IPAddress);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTcpCommDlg, CDialog)
	//{{AFX_MSG_MAP(CTcpCommDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_OUTPUT_COMMAND, OnTrackerOutput)
	ON_BN_CLICKED(IDC_OUTPUT_60HZ, OnTrackerOutput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTcpCommDlg message handlers

BOOL CTcpCommDlg::OnInitDialog()
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
	SetTimer(DATA_UPDATE_TIMER_ID, DATA_UPDATE_TIMER_INTERVAL, NULL);

	OnTrackerOutput();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CTcpCommDlg::OpenTrackerBoard()
{
	m_TrackerBoard.SetNotifyWindow(GetSafeHwnd());
	return m_TrackerBoard.Open();
}

BOOL CTcpCommDlg::DestroyWindow()
{
	// clean up
	KillTimer(DATA_UPDATE_TIMER_ID);
	KillTimer(DATA_POLLING_TIMER_ID);
	m_TrackerBoard.Close();

	return CDialog::DestroyWindow();
}


void CTcpCommDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTcpCommDlg::OnPaint()
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
HCURSOR CTcpCommDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/////////////////////////////////////////////////////////////////////////////
// CTcpCommDlg::HandleIncomingMessage(CTrackerTcpInterface* pBoard)
//
// Handle an incoming message from the tracker
//
void CTcpCommDlg::HandleIncomingMessage(CTrackerTcpInterface* pBoard)
{
	CTrackerMessage msg;

	ASSERT(pBoard);
	if( pBoard == NULL )
		return;

	// handle incoming messages
	while( pBoard->GetMessage(msg) )
	{
		if( msg.GetType() == STATUS_MSG_TYPE )
		{
			HandleStatusMessage(msg.GetStatus());
			m_MessageCount++;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTcpCommDlg::HandleStatusMessage(const STATUS_MSG* pStatus)
//
// Handle an incoming status message from the tracker
//
void CTcpCommDlg::HandleStatusMessage(const STATUS_MSG* pStatus)
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
// CTcpCommDlg::SetTrackStatus(int status)
//
// Set the track status string
//
CString CTcpCommDlg::GetTrackStatusString(int status)
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

void CTcpCommDlg::OnTimer(UINT nIDEvent)
{
	if( nIDEvent == DATA_POLLING_TIMER_ID )
	{
		// polling?
		if( m_TrackerOutput == 0 )
		{
			// send PING message
			if( !m_TrackerBoard.SendMessage(m_PingMsg) )
			{
				TRACE("Failed to send the tracker a PING message!\n");
			}
		}
	}

	if( nIDEvent == DATA_UPDATE_TIMER_ID )
	{
		if( m_TrackerBoard.IsConnected() )
		{
			m_ConnectedCheckbox.SetCheck(1);

			// compute messages per second
			double MessageRate = (double)m_MessageCount / ((double)DATA_UPDATE_TIMER_INTERVAL / 1000.0);
			m_MessageCount = 0;

			m_MessageRate.Format("%0.2f", MessageRate);
			m_MessageRateEditBox.SetWindowText(m_MessageRate);
		}
		else
		{
			m_ConnectedCheckbox.SetCheck(0);
			m_MessageCount = 0;
			m_MessageRateEditBox.SetWindowText("");
		}
	}

	CDialog::OnTimer(nIDEvent);
}

LRESULT CTcpCommDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// handle tracker messages
	if( message == WM_TRACKER_TCP )
	{
		HandleIncomingMessage( (CTrackerTcpInterface*)lParam );
		return 0;
	}

	return CDialog::WindowProc(message, wParam, lParam);
}

void CTcpCommDlg::OnTrackerOutput()
{
	CString str;

	// get dialog data
	UpdateData(TRUE);

	// set output mode
	m_SystemMsg.GetSystem()->out_60hz = m_TrackerOutput;

	if( !m_TrackerBoard.SendMessage(m_SystemMsg) )
	{
		str.Format("Failed to send the tracker a SYSTEM message!");
		TRACE("%s\n", str);
		AfxMessageBox(str);
	}

	// reset timer
	if( m_PollingRate < 20 )
		m_PollingRate = 20;
	KillTimer(DATA_POLLING_TIMER_ID);
	SetTimer(DATA_POLLING_TIMER_ID, m_PollingRate, NULL);

	UpdateData(FALSE);
}

// user pressed return/enter key
void CTcpCommDlg::OnOK() 
{
	// get dialog data
	UpdateData(TRUE);

	m_IPAddress.TrimRight();
	m_IPAddress.TrimLeft();

	// update dialog data
	UpdateData(FALSE);

	if( m_TrackerBoard.m_HostAddress != m_IPAddress )
	{
		m_TrackerBoard.Close();
		m_TrackerBoard.m_HostAddress = m_IPAddress;
		
		OpenTrackerBoard();
	}

	// setup output and polling
	OnTrackerOutput();
}
