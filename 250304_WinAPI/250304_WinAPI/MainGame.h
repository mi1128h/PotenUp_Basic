#pragma once
#include "GameObject.h"

class Tank;
class Enemy;
class RoundManager;
class Image;
class AnimCharacter;
class AnimBackground;
class EnemyManager;
class Rocket;
class MainGame : public GameObject
{
private:
	HDC hdc{};
	PAINTSTRUCT ps{};
	HANDLE hTimer{}, hTimer2;
	int mousePosX{}, mousePosY{};
	wchar_t szText[128]{};

	RoundManager* roundManager;

	Image* backBuffer;
	AnimBackground* background;

	EnemyManager* enemyManager;
	Rocket* rocket;

public:
	void Init();
	void Release();
	void Update();
	void Render();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

