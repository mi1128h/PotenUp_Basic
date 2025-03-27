#include "Timer.h"

void Timer::Init()
{
	isHardware = true;
	timeScale = 0.0f;
	timeElapsed = 0.0f;
	currTime = 0;
	prevTime = 0;
	periodFrequency = 0;

	fpsElapsedTime = 0.0f;
	fpsFrameCount = 0;
	fps = 0;
	
	isHardware = ::QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency);
	if (isHardware)
	{
		::QueryPerformanceCounter((LARGE_INTEGER*)&prevTime);
		timeScale = 1.0f / periodFrequency;
	}
	else
	{
		prevTime = timeGetTime();
		timeScale = 0.001f;
	}
}

void Timer::Release()
{
}

void Timer::Tick()
{
	if (isHardware)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	}
	else
	{
		currTime = timeGetTime();
	}

	timeElapsed = (currTime - prevTime) * timeScale;

	fpsElapsedTime += timeElapsed;
	fpsFrameCount++;
	if (fpsElapsedTime >= 1.0f)
	{
		fps = fpsFrameCount;
		fpsFrameCount = 0;
		fpsElapsedTime = 0.0f;
	}
	prevTime = currTime;
}

float Timer::GetCurrTime()
{
	__int64 time;
	if (isHardware)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&time);
	}
	else
	{
		time = timeGetTime();
	}

	return time * timeScale;
}
