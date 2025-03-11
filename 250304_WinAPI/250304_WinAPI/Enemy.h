#pragma once
#include "GameObject.h"

class Tank;
class Enemy : public GameObject
{
private:
	POINT position;
	Tank* target;
	int hp;
	int size;
	float speed;

public:
	void Init(Tank* tank);
	void Release();
	void Update();
	void Render(HDC hdc);

	void Move();
	bool CheckTargetCollision();
	bool isDead() { return hp <= 0; }
};

