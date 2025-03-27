#pragma once
#include "config.h"

class Timer
{
public:
	void Init();
	void Release();
	void Tick();

	float GetCurrTime();
	unsigned long GetFPS() { return fps; }

private:
	bool isHardware;			//고성능 타이머를 사용할 수 있는지 여부
	float timeScale;			//결과 진동수를 초당 진동수로 나눠서 진동수를 시간으로환산
	float timeElapsed;			//마지막 시간과 현재 시간의 경과량
	__int64 currTime;			//현재 시간
	__int64 prevTime;			//이전 시간
	__int64 periodFrequency;	//고성능 타이머의 주파수 (초당 진동수)

	float fpsElapsedTime; //프레임 경과 시간 (1초 확인)
	unsigned long fpsFrameCount; //초당 프레임 수
	unsigned long fps; 

};

