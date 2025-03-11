#pragma once
#include "GameObject.h"

class Tank;
class Enemy;
class MainGame : public GameObject
{
private:
	HDC hdc{};
	PAINTSTRUCT ps{};
	HANDLE hTimer{}, hTimer2;
	int mousePosX{}, mousePosY{};
	wchar_t szText[128]{};

	Tank* tank;
	vector<Enemy*> enemies;
	int nDeadEnemies;

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void CreateEnemy();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

