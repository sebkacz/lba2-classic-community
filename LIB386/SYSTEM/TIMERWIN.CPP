//-------------------------------------------------------------------------
#include	<SYSTEM/ADELINE.H>
#include	<SYSTEM/WINSYS.H>
#include	<SYSTEM/TIMERWIN.H>

//-------------------------------------------------------------------------
volatile uint32_t	TimerSystemHR	;
volatile uint32_t	TimerRefHR	;

//-------------------------------------------------------------------------
volatile int32_t	TimerLock	;

//-------------------------------------------------------------------------
volatile int32_t	CmptFrame	;
volatile int32_t	NbFramePerSecond;

//-------------------------------------------------------------------------
volatile int32_t	CmptMemoTimerRef;

//-------------------------------------------------------------------------
	uint32_t	LastTime	;
	uint32_t	LastEvaluate	;

//-------------------------------------------------------------------------
static	uint32_t	MemoTimerRefHR	;

//----------------------------------------------------------------------------
WINDOW_PROC_PTR	OldTimerWindowProc;

//----------------------------------------------------------------------------
int32_t	TimerWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		LastTime = LastEvaluate = timeGetTime();
		ManageTime()	;
		break		;

	case WM_SETFOCUS:
		if(!AppActive)
		{
			UnlockTimer()	;
		}
		break		;

	case WM_KILLFOCUS:
		if(AppActive)
		{
			LockTimer()	;
		}
		break		;
	}

	return OldTimerWindowProc(hWnd, message, wParam, lParam);
}

//-------------------------------------------------------------------------
void	ManageTime()
{
	int32_t		time	;

	TimerSystemHR = timeGetTime() ;

	if(!TimerLock)
	{
		TimerRefHR += TimerSystemHR - LastTime 	;
	}

	LastTime = TimerSystemHR		;

	time = TimerSystemHR - LastEvaluate	;

	if(time >= 1000)
	{
		NbFramePerSecond = (CmptFrame*1000 + time/2) / time	;
		CmptFrame	 = 0					;
		LastEvaluate	+= (time/1000)*1000			;
	}
}

//-------------------------------------------------------------------------
void	SaveTimer()
{
	if(!CmptMemoTimerRef++)
	{
		ManageTime()			;
		MemoTimerRefHR = TimerRefHR	;
	}
}

//-------------------------------------------------------------------------
void	RestoreTimer()
{
	if(CmptMemoTimerRef)
	{
		if(!--CmptMemoTimerRef)
		{
			ManageTime()			;
			TimerRefHR = MemoTimerRefHR	;
		}
	}
}

//-------------------------------------------------------------------------
void	SetTimerHR(uint32_t timer)
{
	LockTimer()		;
	TimerRefHR = timer	;
	UnlockTimer()		;
}

//-------------------------------------------------------------------------
void	LockTimer()
{
	ManageTime()	;
	TimerLock++	;
}

//-------------------------------------------------------------------------
void	UnlockTimer()
{
	if(TimerLock)
	{
		ManageTime()	;
		TimerLock--	;
	}
}

//-------------------------------------------------------------------------
