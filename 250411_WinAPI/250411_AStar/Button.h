#pragma once
#include "GameObject.h"
#include <functional>

/*
	�Լ� ������ : �Լ��� �޸� �ּҸ� ������ �� �ִ� ����
	(����)������ : ������ �޸� �ּҸ� ������ �� �ִ� ����

	int a = 10;
	int* pA = &a;	// ���� a�� �޸� �ּҸ� ����
	
	void sum(int a, int b);
	void (*pFunc)(int, int) = sum;	// �Լ� sum�� �޸� �ּҸ� ����

	sum(10, 20);
	pFunc(10, 20);

	int getRandom(void);
	int (*pFunc)(void);
	pFunc = getRandom;
*/

typedef void (*ButtonFunc)(void);

enum class ButtonState
{
	None, Down, Up
};

class Image;
class Button : public GameObject
{
private:
	ButtonState state;
	Image* image;
	RECT rc;
	POINT pos;

	ButtonFunc buttonFunc1;
	//GameObject* obj;

	std::function<void(void)> buttonFunc;

public:
	virtual HRESULT Init(int posX, int posY);
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	//void SetFunction(ButtonFunc func, GameObject* obj)
	//{
	//	buttonFunc = func;
	//	this->obj = obj;
	//}

	void SetFunction(std::function<void(void)> func)
	{
		buttonFunc = func;
	}

	//void SetFunction(ButtonFunc func)
	//{
	//	buttonFunc1 = func;
	//}
};

