#pragma once
#include "config.h"
#include "Singleton.h"

class Timer;
class TimeManager : public Singleton<TimeManager>
{
public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

private:
	Timer* timer;
	wchar_t szText[128];
};

