#pragma once
#include "GameObject.h"

class Timer;
class Image;
class EnemyManager;
class TilemapTool;
class MainGame : public GameObject
{
private:
	HDC hdc;
	PAINTSTRUCT ps;
	wchar_t szText[128];

	Image* backBuffer;
	Image* backGround;
	EnemyManager* enemyManager;

	TilemapTool* tilemapTool;

	Timer* timer;

public:
	void Init();	// override (�θ�Ŭ������ ���� �Լ��̸�, ������ �ٸ��� �����ϰ� ���� ��)
					// <-> overload (���� �Լ� �̸�, �Ű����� Ÿ�԰� ������ �ٸ��� �ٸ� �Լ��� ó��)
	void Release();	
	void Update();	
	void Render();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

