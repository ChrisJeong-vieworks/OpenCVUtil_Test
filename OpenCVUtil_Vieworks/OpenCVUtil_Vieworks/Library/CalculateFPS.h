#pragma once

class CCalculateFPS
{
public:
	CCalculateFPS(void);
	virtual ~CCalculateFPS(void);

private:
	
	LARGE_INTEGER	TimerFrequency; // Ÿ�̸� �󵵼��� �����Ѵ�.
	LARGE_INTEGER	StartTime; // ������ ī��Ʈ�� 0�϶� �ð��� ����Ǵ� ����

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

