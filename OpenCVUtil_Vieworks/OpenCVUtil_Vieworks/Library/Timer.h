#pragma once

enum TimerThreadWorkingType
{
	TIMERTHREAD_STOP = 0,
	TIMERTHREAD_RUNNING = 1,
	TIMERTHREAD_PAUSE = 2
};
typedef void(*TimerCallback_t)(void* pParent);
class CTimer 
{
public:
	CTimer(double TimeDuration, void* pParent ,TimerCallback_t callback);
	virtual ~CTimer(void);


	double					GetTimeInterval_Second();
	void					TimeStamp_Start();
	void					TimeStamp_Reset();

	void*					m_pParent;
	TimerCallback_t			m_pTimerCallback;

protected:
	LARGE_INTEGER			m_CPUFreqT;
	LARGE_INTEGER			m_StartTimeT;
	LARGE_INTEGER			m_EndTimeT;
	double					m_SecIntervalT;

	//LARGE_INTEGER			m_StartTimeGR;
	//LARGE_INTEGER			m_EndTimeGR;
	//double					m_SecIntervalGR;

	//LARGE_INTEGER			m_StartTimeGF;
	//LARGE_INTEGER			m_EndTimeGF;
	//double					m_SecIntervalGF;

private:

	double					m_Duration;

	/*****************************Timer Thread***********************************************/
	DWORD					WaitResult;
	BOOL			  		m_bTimerThreadStart;
	CWinThread*		  		m_pTimerThread;
	TimerThreadWorkingType	m_eTimerThreadWork;
	static UINT		  		TimerThreadFunction(LPVOID _mothod);

	void			  		TimerThreadGeneration();
	void			  		TimerThreadStop();
	void			  		TimerThreadClose();
	void					ThreadWork();
	/********************************************************************************************/


};
