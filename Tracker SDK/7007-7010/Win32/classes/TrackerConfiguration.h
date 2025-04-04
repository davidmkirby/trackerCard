///////////////////////////////////////////////////////////////////////////////
// TrackerConfiguration.h
//
// Tracker message configuration class
//

/*******************************************************************************
* Copyright (c) 2013 Electro-Optical Imaging, Inc. All Rights Reserved
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

#pragma once

#include "TrackerMessage.h"
#include "TrackerInterface.h"


///////////////////////////////////////////////////////////////////////////////
// CTrackerConfiguration
//
class CTrackerConfiguration
{
	friend UINT BeginQueryThread(LPVOID pParm);

protected:
	// tracker interface pointer
	CTrackerInterface*		m_pTrackerInterface;

	// tracker configuration message array
	CTrackerMessageArray	m_MessageArray;

	// tracker query array and status
	CTrackerMessageArray	m_QueryArray;
	int						m_QueryIndex;
	int						m_QueryReceived;
	int						m_QueryTimedOut;

	BOOL					m_bQueryRunning;
	BOOL					m_bAbortQueryThread;
	CCriticalSection		m_QueryThreadCrit;

protected:
	// internal helper functions
	BOOL					HasSubtype(int type) const;
	int						GetSubtype(const CTrackerMessage* pMessage) const;
	BOOL					IsSubtype(int nIndex, int subtype) const;

	double					GetLensFov(const CTrackerMessage* pMessage) const;
	double					GetLensMaximumFov(const CTrackerMessage* pMessage) const;

	void					QueryThread();
	BOOL					AddLensQueriesToArray();
//	BOOL					AddCameraQueriesToArray();	// DEPRECATED

public:
	CTrackerConfiguration(void);
	~CTrackerConfiguration(void);

public:
	// General Utility
	BOOL					IsEmpty() { return m_MessageArray.IsEmpty(); }
	void					RemoveAll() { m_MessageArray.RemoveAll(); }
	int						GetSize() const { return m_MessageArray.GetSize(); }
	CTrackerMessage*		GetAt(int nIndex) { return m_MessageArray.GetAt(nIndex); }
	const CTrackerMessage*	GetAt(int nIndex) const { return m_MessageArray.GetAt(nIndex); }

	// Message Handling
	int						GetMessageIndex(int type, int subtype=-1) const;
	CTrackerMessage*		GetMessage(int type, int subtype=-1);
	const CTrackerMessage*	GetMessage(int type, int subtype=-1) const;

	BOOL					AddMessage(const CTrackerMessage* pMessage);

	BOOL					RemoveMessage(int type, int subtype=-1);
	BOOL					RemoveMessage(const CTrackerMessage* pMessage);
	void					RemoveAllLensMessages();
	void					RemoveAllCameraMessages();

	// Tracker Configuration Query
	int						GetQueryIndex() const { return m_QueryIndex; }
	int						GetQueryMessagesReceived() const { return m_QueryReceived; }
	int						GetQueryMessagesTimedOut() const { return m_QueryTimedOut; }

	BOOL					QueryAllMessages(CTrackerInterface* pTrackerInterface);
	BOOL					IsQueryRunning() const { return m_bQueryRunning; }
	BOOL					IsQueryComplete() const { return !m_bQueryRunning; }
	void					AbortQuery();

	// Lens Handling
	BOOL					QueryActiveLens(CTrackerInterface* pTrackerInterface);
	double					GetSystemMaximumFov() const;
	int						GetActiveVideoSource() const;
	double					GetActiveLensFov() const;
	BOOL					GetActiveLensMessage(CTrackerMessage& message) const;

	// Lens Helper Functions
	BOOL					IsLensMessageType(int msgType) const;
	BOOL					IsLensMessageType(const CTrackerMessage* pMessage) const;
	int						GetLensMessageType(int lensType) const;

};
