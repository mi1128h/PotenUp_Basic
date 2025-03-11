#pragma once

#include <Windows.h>
#include <string>
#include <iostream>
#include <random>

using namespace std;

// �����Ϸ����� �ش� �ڵ带 �ڿ� ���ǵ� �ڵ�� �����Ѵ�
#define WINSIZE_X 1080
#define WINSIZE_Y 500

extern HWND g_hWnd;
// extern ������ �Լ��� �ٸ� ���Ͽ� ���ǵǾ� �ִٴ� ����� �˸��� Ű����

#define TORADIAN(degree) 3.141592f / 180.0f * degree
#define TODEGREE(radian) 180.0f / 3.141592f * radian

extern random_device rd;
extern default_random_engine dre;
extern uniform_int_distribution<int> uid_0_10;
extern uniform_int_distribution<int> uid_200_255;
extern uniform_int_distribution<int> uid_0_255;
extern uniform_int_distribution<int> uid_1_2;
extern uniform_int_distribution<int> uid_0_WINSIZEX;