#pragma once
#include "GameObject.h"

/*
	�Լ� ������: �Լ��� �޸� �ּҸ� ������ �� �ִ� ����

	���� ������: ������ �޸� �ּҸ� ������ �� �ִ� ����

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

