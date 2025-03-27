#pragma once

#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "Winmm.lib")

#include <Windows.h>
#include <string>
#include <iostream>
#include <random>
#include <bitset>
#include <vector>
#include <map>
#include <memory>

using namespace std;

#include "KeyManager.h"
#include "ImageManager.h"
#include "TimerManager.h"

// �����Ϸ����� �ش� �ڵ带 �ڿ� ���ǵ� �ڵ�� �����Ѵ�
#define WINSIZE_X 600
#define WINSIZE_Y 800

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
// extern ������ �Լ��� �ٸ� ���Ͽ� ���ǵǾ� �ִٴ� ����� �˸��� Ű����

#define TORADIAN(degree) 3.141592f / 180.0f * degree
#define TODEGREE(radian) 180.0f / 3.141592f * radian

typedef struct tagFPOINT
{
	float x;
	float y;
} FPOINT;

extern random_device rd;
extern default_random_engine dre;
extern uniform_int_distribution<int> uid_0_255;
extern uniform_int_distribution<int> uid_0_WINSIZEX;