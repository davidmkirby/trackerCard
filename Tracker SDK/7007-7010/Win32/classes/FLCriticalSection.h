/////////////////////////////////////////////////////////////////////////////////////
// FLCriticalSection.h
//
#ifndef	_FLCRITICALSECTION_
#define _FLCRITICALSECTION_

/////////////////////////////////////////////////////////////////////////////////////
// class FLCriticalSection
/////////////////////////////////////////////////////////////////////////////////////
class FLCriticalSection
{
protected:
	CRITICAL_SECTION	m_CriticalSection;
	int					m_Counter;

public:
	FLCriticalSection()
		:m_Counter(0)	
		{ ::InitializeCriticalSection(&m_CriticalSection); }

	~FLCriticalSection()	
		{ ::DeleteCriticalSection(&m_CriticalSection); }

	void		Lock()					{ Enter(); }
	void		Unlock()				{ Leave(); }
	int			GetLockCount() const	{ return m_Counter; }
#if(_WIN32_WINNT >= 0x0400)
	bool		TryLock()				{ return TryEnter(); }
#endif

protected:
   bool TryEnter();	// Non-blocking try
   void Enter()	{::EnterCriticalSection(&m_CriticalSection); m_Counter++; } // Blocking try	
   void Leave()	{m_Counter--; ::LeaveCriticalSection(&m_CriticalSection); } // Exit
};


#if(_WIN32_WINNT>=0x0400)
/////////////////////////////////////////////////////////////////////////////////////
// Non-blocking try - only available for NT4/2000
//
inline bool FLCriticalSection::TryEnter()
{
	if( ::TryEnterCriticalSection(&m_CriticalSection) )
	{
		m_Counter++; // only increment if try successful
		return true;
	}

	return false; 
}
#endif

/////////////////////////////////////////////////////////////////////////////////////
// class FLCriticalSectionSetUp -helper to Unlock on the way out
/////////////////////////////////////////////////////////////////////////////////////
class FLCriticalSectionSetUp
{
protected:
	FLCriticalSection&	m_CriticalSection;

public:
	FLCriticalSectionSetUp(FLCriticalSection& CriticalSection)
		:m_CriticalSection(CriticalSection)
		{ m_CriticalSection.Lock(); }

	~FLCriticalSectionSetUp()
		{ m_CriticalSection.Unlock(); }
};

/////////////////////////////////////////////////////////////////////////////////////

#endif // _FLCRITICALSECTION_
