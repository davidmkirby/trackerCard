// TcpCommDlg.h : header file
//

#if !defined(AFX_TCPCOMMDLG_H__65154965_613B_484F_BDEE_E30BA106639D__INCLUDED_)
#define AFX_TCPCOMMDLG_H__65154965_613B_484F_BDEE_E30BA106639D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTcpCommDlg dialog

class CTcpCommDlg : public CDialog
{
protected:
	CTrackerTcpInterface	m_TrackerBoard;
	CTrackerMessage			m_PingMsg;
	CTrackerMessage			m_SystemMsg;

	int						m_MessageCount;

// Construction
public:
	CTcpCommDlg(CWnd* pParent = NULL);	// standard constructor

protected:
	BOOL	OpenTrackerBoard();

	// tracker incoming message handler
	void HandleIncomingMessage(CTrackerTcpInterface* pBoard);
	void HandleStatusMessage(const STATUS_MSG* pStatus);

	// helper functions
	CString	GetTrackStatusString(int status);

public:
// Dialog Data
	//{{AFX_DATA(CTcpCommDlg)
	enum { IDD = IDD_TCPCOMM_DIALOG };
	CButton	m_ConnectedCheckbox;
	CEdit	m_MessageRateEditBox;
	CEdit	m_MountElEdit;
	CEdit	m_MountAzEdit;
	CEdit	m_TrackStatusEdit;
	CEdit	m_TrackStateEdit;
	CEdit	m_TrackErrorYEdit;
	CEdit	m_TrackErrorXEdit;
	CEdit	m_TargetSizeYEdit;
	CEdit	m_TargetSizeXEdit;
	CString	m_TrackErrorX;
	CString	m_TrackErrorY;
	CString	m_TrackState;
	CString	m_TrackStatus;
	int		m_TargetSizeX;
	int		m_TargetSizeY;
	double	m_MountAz;
	double	m_MountEl;
	int		m_TrackMode;
	CEdit	m_TargetCount2Edit;
	CEdit	m_TargetCountEdit;
	CEdit	m_FilteredTrackErrorY2Edit;
	CEdit	m_FilteredTrackErrorYEdit;
	CEdit	m_FilteredTrackErrorX2Edit;
	CEdit	m_FilteredTrackErrorXEdit;
	int		m_GateSelect;
	CString	m_FilteredTrackErrorX;
	CString	m_FilteredTrackErrorX2;
	CString	m_FilteredTrackErrorY;
	CString	m_FilteredTrackErrorY2;
	CEdit	m_TrackStatus2Edit;
	CEdit	m_TrackState2Edit;
	CEdit	m_TrackErrorY2Edit;
	CEdit	m_TrackErrorX2Edit;
	CEdit	m_TargetSizeY2Edit;
	CEdit	m_TargetSizeX2Edit;
	CString	m_TrackState2;
	CString	m_TrackStatus2;
	CString	m_TrackErrorX2;
	CString	m_TrackErrorY2;
	int		m_TargetSizeX2;
	int		m_TargetSizeY2;
	int		m_TargetCount;
	int		m_TargetCount2;
	int		m_TrackerOutput;
	int		m_PollingRate;
	CString	m_MessageRate;
	CString	m_IPAddress;
	//}}AFX_DATA

	int		m_iTrackState;
	int		m_iTrackStatus;
	int		m_iTrackState2;
	int		m_iTrackStatus2;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTcpCommDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTcpCommDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnTrackerOutput();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TCPCOMMDLG_H__65154965_613B_484F_BDEE_E30BA106639D__INCLUDED_)
