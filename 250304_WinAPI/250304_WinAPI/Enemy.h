#pragma once
#include "GameObject.h"

class Tank;
class Bullet;
class Image;
class Enemy : public GameObject
{
private:
	FPOINT position;
	float dx, dy;
	int moveCnt;
	Tank* target;
	int hp;
	int size;
	float speed;
	float damage;
	int bulletsNum;
	int fireInterval;
	int elapsedFireTime;
	float bulletSpeed;
	Image* image;
	int animationFrame;
	int elapsedFrame;

	static vector<Bullet*> vBullets;
	static int nLoadedBullets;

public:
	void Init(float x, float y, Tank* tank=NULL);
	void SetValuesByRound(float hp, int maxBulletNum, float speed, float size, int fireSpeed, float bulletSpeed);
	void Release();
	void Update();
	void Render(HDC hdc);

	void HorizontalMove();
	void Move();
	bool IsDead() { return hp <= 0; }
	FPOINT GetPos() { return position; }
	int GetSize() { return size; }
	float GetDamage() { return damage; }
	void AttackedByBullet(int damage) { hp -= damage; }
	void AttackedByTank() { hp = 0; }
	void Fire();

	static void ReleaseBullets();
	static void UpdateBullets();
	static void RenderBullets(HDC hdc);
	static void CheckBulletsCollision(Tank* tank);
	static void InitLoadedBullets();
};

