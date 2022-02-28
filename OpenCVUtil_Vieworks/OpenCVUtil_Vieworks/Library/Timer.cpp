#include "../pch.h"
#include "Timer.h"

CTimer::CTimer(double TimeDuration, void* pParent ,TimerCallback_t callback)
: m_pTimerCallback(callback),
  m_pParent(pParent)
{
	QueryPerformanceFrequency(&m_CPUFreqT);
 	QueryPerformanceCounter(&m_StartTimeT);
	
	m_pTimerThread = NULL;
	m_Duration = TimeDuration;

	m_SecIntervalT = 0;
	//m_SecIntervalGR = 0;
	//m_SecIntervalGF = 0;

	TimerThreadGeneration();
	
}

CTimer::~CTimer(void)
{
	TimerThreadClose();
}

double CTimer::GetTimeInterval_Second() //Start ÂïÈù ÀÌÈÄ·Î ¸î ÃÊ°¡ Áö³µ´ÂÁö? 
{
	QueryPerformanceCounter(&m_EndTimeT);
	m_SecIntervalT = (double)(m_EndTimeT.QuadPart - m_StartTimeT.QuadPart) / m_CPUFreqT.QuadPart;
	return m_SecIntervalT;
}

void CTimer::TimeStamp_Start()
{
	QueryPerformanceCounter(&m_StartTimeT);
}

void CTimer::TimeStamp_Reset()
{
	QueryPerformanceCounter(&m_StartTimeT);
}

void CTimer::TimerThreadGeneration()
{
	if (m_pTimerThread == NULL)
	{
		m_pTimerThread = AfxBeginThread(TimerThreadFunction, this);
		if (m_pTimerThread == NULL)
		{
			return;
		}
		m_pTimerThread->m_bAutoDelete = FALSE;
		m_eTimerThreadWork = TIMERTHREAD_RUNNING;
	}
	else
	{
		if (m_eTimerThreadWork == TIMERTHREAD_PAUSE)
		{
			m_pTimerThread->ResumeThread();
			m_eTimerThreadWork = TIMERTHREAD_RUNNING;
		}
	}
}

void CTimer::TimerThreadStop()
{
	if (m_pTimerThread == NULL)
	{
		return;
	}
	else
	{
		m_eTimerThreadWork = TIMERTHREAD_PAUSE;
	}
}

void CTimer::TimerThreadClose()
{
	if (m_pTimerThread == NULL)
	{
		return;
	}
	else
	{
		m_eTimerThreadWork = TIMERTHREAD_STOP;
		DWORD dwResult;
		::GetExitCodeThread(m_pTimerThread->m_hThread, &dwResult);
		WaitResult = ::WaitForSingleObject(m_pTimerThread->m_hThread, INFINITE);
		if (WaitResult == WAIT_OBJECT_0)
		{
			delete m_pTimerThread;
			m_pTimerThread = NULL;
			TRACE("Viewer Thread Closed\n");
		}
		else if (WaitResult == WAIT_TIMEOUT)
		{
			TRACE("Viewer Thread Running!\n");
		}
	}
}

UINT CTimer::TimerThreadFunction(LPVOID _mothod)
{
	CTimer* pDlg = (CTimer*)_mothod;
	int num = 0;
	pDlg->ThreadWork();
	return 0;
}

void CTimer::ThreadWork()
{
	while (1)
	{
		if (m_eTimerThreadWork == TIMERTHREAD_RUNNING)
		{
			//Sleep(1); 		
			if (GetTimeInterval_Second() >= m_Duration)
			{
				//TRACE("Time elapsed : .%2f \n", GetTimeInterval_Second());
				TimeStamp_Reset();
				if (m_pTimerCallback != NULL)//Callback ÇÔ¼ö
				{
					m_pTimerCallback(m_pParent);
				}
			}	
		}
		else if (m_eTimerThreadWork == TIMERTHREAD_PAUSE)
		{

		}
		else if (m_eTimerThreadWork == TIMERTHREAD_STOP)
		{
			TRACE("THREAD STOP\n");
			break;
		}
	}
}
