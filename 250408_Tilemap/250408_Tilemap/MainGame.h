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
	virtual HRESULT Init() override;	// override (부모클래스와 같은 함수이름, 로직을 다르게 구현하고 싶을 때)
					// <-> overload (같은 함수 이름, 매개변수 타입과 갯수가 다르면 다른 함수로 처리)
	virtual void Release() override;	
	virtual void Update() override;	
	void Render();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

