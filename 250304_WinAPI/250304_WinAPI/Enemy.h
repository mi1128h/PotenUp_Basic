#pragma once
#include "GameObject.h"

class Tank;
class Enemy : public GameObject
{
private:
	FPOINT position;
	Tank* target;
	int hp;
	int size;
	float speed;
	float damage;

public:
	void Init(Tank* tank);
	void Release();
	void Update();
	void Render(HDC hdc);

	void Move();
	bool IsDead() { return hp <= 0; }
	FPOINT GetPos() { return position; }
	int GetSize() { return size; }
	float GetDamage() { return damage; }
	void AttackedByBullet(int damage) { hp -= damage; }
	void AttackedByTank() { hp = 0; }
};

