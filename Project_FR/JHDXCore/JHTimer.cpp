#include "JHTimer.h"

float g_fProgramTime;
float g_SecondPerFrame;
bool JHTimer::Init()
{
	
	m_DWStartTime = timeGetTime();
	return true;
	
}
bool JHTimer::Frame()
{
	DWORD FCurrentTime = timeGetTime();
	m_SecondPerFrame = (float)(FCurrentTime - m_DWStartTime) / 1000;
	m_fProgramTime += m_SecondPerFrame;
	g_SecondPerFrame = m_SecondPerFrame;
	g_fProgramTime = m_fProgramTime;
	static int fps;
	static float SecondTimer = 0.0f;
	SecondTimer += m_SecondPerFrame;
	if (SecondTimer>=1.0f)
	{
		m_iFPS = fps;
		SecondTimer = 0.0f;
		fps = 0;
	}
	fps++;

	m_DWStartTime = FCurrentTime;
	return true;
}
int	JHTimer::GetFPS()
{
	return m_iFPS;
}
bool JHTimer::Render()
{
	swprintf_s(m_SzBuffer, L"%10.0f %10.04f %d",
		m_fProgramTime,
		m_SecondPerFrame,
		m_iFPS);
	return true;
}
bool JHTimer::Release()
{
	return true;
}
JHTimer::JHTimer()
{
	m_fProgramTime = 0.0f;
}


JHTimer::~JHTimer()
{
}
