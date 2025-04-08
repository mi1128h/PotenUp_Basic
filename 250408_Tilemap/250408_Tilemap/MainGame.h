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
	
	TilemapTool* tilemapTool;

	Timer* timer;

public:
	virtual HRESULT Init() override;	// override (�θ�Ŭ������ ���� �Լ��̸�, ������ �ٸ��� �����ϰ� ���� ��)
					// <-> overload (���� �Լ� �̸�, �Ű����� Ÿ�԰� ������ �ٸ��� �ٸ� �Լ��� ó��)
	virtual void Release() override;	
	virtual void Update() override;	
	void Render();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

