#pragma once
#include "GameObject.h"

class Tank;
class MainGame : public GameObject
{
private:
	HDC hdc{};
	PAINTSTRUCT ps{};
	HANDLE hTimer{};
	int mousePosX{}, mousePosY{};
	wchar_t szText[128]{};

	Tank* tank;

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

