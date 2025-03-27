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
	bool isHardware;			//���� Ÿ�̸Ӹ� ����� �� �ִ��� ����
	float timeScale;			//��� �������� �ʴ� �������� ������ �������� �ð�����ȯ��
	float timeElapsed;			//������ �ð��� ���� �ð��� �����
	__int64 currTime;			//���� �ð�
	__int64 prevTime;			//���� �ð�
	__int64 periodFrequency;	//���� Ÿ�̸��� ���ļ� (�ʴ� ������)

	float fpsElapsedTime; //������ ��� �ð� (1�� Ȯ��)
	unsigned long fpsFrameCount; //�ʴ� ������ ��
	unsigned long fps; 

};

