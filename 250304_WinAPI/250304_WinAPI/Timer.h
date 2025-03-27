#pragma once
#include "config.h"

class Timer
{
private:
	bool isHardware;				// ���� Ÿ�̸Ӹ� ����� �� �ִ��� ����
	float timeScale;				// ��� �������� �ʴ� �������� ������
									// �������� �ð����� ȯ��
	float timeElapsed;				// ������ �ð��� ���� �ð��� �����
	__int64 currTime;				// ���� �ð�
	__int64 lastTime;				// ���� �ð�
	__int64 periodFrequency;		// ���� Ÿ�̸� ���ļ� (�ʴ� ������)

	float fpsTimeElapsed;			// ������ ��� �ð� (1�� Ȯ��)
	unsigned long fpsFrameCount;	// �ʴ� ������ ��
	unsigned long FPS;

public:
	void Init();
	void Release();
	void Tick();
	float GetCurrTime();

	inline unsigned long GetFPS() { return FPS; }
	inline float GetDeltaTime() { return timeElapsed; }
};

