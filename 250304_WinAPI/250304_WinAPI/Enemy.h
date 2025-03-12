#pragma once
#include "GameObject.h"

class Tank;
class Bullet;
class Enemy : public GameObject
{
private:
	FPOINT position;
	Tank* target;
	int hp;
	int size;
	float speed;
	float damage;
	int bulletsNum;
	int fireSpeed;
	int elapsedFireTime;

	static vector<Bullet*> vBullets;
	static int nLoadedBullets;

public:
	void Init(Tank* tank);
	void SetValuesByRound(float hp, int maxBulletNum, float speed, float size, int fireSpeed);
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
	void Fire();

	static void UpdateBullets();
	static void RenderBullets(HDC hdc);
};

