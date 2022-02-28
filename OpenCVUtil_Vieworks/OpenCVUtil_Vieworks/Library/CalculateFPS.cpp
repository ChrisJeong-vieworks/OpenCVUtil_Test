#include "../pch.h"
#include "CalculateFPS.h"

CCalculateFPS::CCalculateFPS(void)
{
	m_nGrabCount = 0;
	m_nGrabNumber = 0;
	m_fFPS = 0;
	QueryPerformanceFrequency(&TimerFrequency);
	QueryPerformanceCounter(&StartTime);
}

CCalculateFPS::~CCalculateFPS(void)
{

}

double CCalculateFPS::CalculateFPS()
{
	m_nGrabCount++;
	if (m_nGrabCount > 50)
	{
		LARGE_INTEGER CurrentTime;
		QueryPerformanceCounter(&CurrentTime);
		m_fFPS =  m_nGrabCount / (((double)CurrentTime.QuadPart - (double)StartTime.QuadPart) / (double)TimerFrequency.QuadPart);
		QueryPerformanceCounter(&StartTime);
		m_nGrabCount = 0;
	}
	return m_fFPS;
}

 void CCalculateFPS::Start()
 {
    QueryPerformanceCounter(&TimeStampStart);
 }

void CCalculateFPS::Stop()
{
   QueryPerformanceCounter(&TimeStampStop);
}

double CCalculateFPS::GetProcessingTime()
{
	static double duration = 0;
	duration =(((double)TimeStampStop.QuadPart - (double)TimeStampStart.QuadPart) / (double)TimerFrequency.QuadPart);
	return duration * 1000;
}