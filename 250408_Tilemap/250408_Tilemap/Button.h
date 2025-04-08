#pragma once
#include "GameObject.h"

/*
	함수 포인터: 함수의 메모리 주소를 저장할 수 있는 변수

	변수 포인터: 변수의 메모리 주소를 저장할 수 있는 변수

	int a = 10;
	int* pA = &a;

	void Sum(int a, int b);
	void (*pFunc)(int, int) = sum;
*/

enum class ButtonState
{
	NONE,
	DOWN,
	UP,
};

class Image;
class Button : public GameObject
{
public:
	HRESULT Init(int posX, int posY);
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

public:
	void SetFunction(std::function<void(void)> func) { buttonFunc = func; }

private:
	ButtonState state;
	Image* image;
	RECT rc;
	POINT pos;

	std::function<void(void)> buttonFunc;
};

