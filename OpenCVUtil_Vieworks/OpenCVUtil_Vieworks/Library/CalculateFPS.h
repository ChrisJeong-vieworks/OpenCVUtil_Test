#pragma once

class CCalculateFPS
{
public:
	CCalculateFPS(void);
	virtual ~CCalculateFPS(void);

private:
	
	LARGE_INTEGER	TimerFrequency; // 타이머 빈도수를 저장한다.
	LARGE_INTEGER	StartTime; // 프레임 카운트가 0일때 시간이 저장되는 변수

public:

	LARGE_INTEGER	TimeStampStart; 
	LARGE_INTEGER	TimeStampStop; 

	double			m_fFPS;
	int				m_nGrabNumber;
	int 			m_nGrabCount;
	double			CalculateFPS();
	void		    Start();
	void			Stop();
	double			GetProcessingTime();
};

