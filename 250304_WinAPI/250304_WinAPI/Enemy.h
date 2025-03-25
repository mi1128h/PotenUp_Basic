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

	bool rush;
	float rushElapsedTime;
	bool fireBullet;

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
	void Fire();

	void SetRush(bool rush) { this->rush = rush; }
	bool GetRush() { return rush; }
	float GetRushElapsedTime() { return rushElapsedTime; }
	void SetFireBullet(bool fire) { fireBullet = fire; }
	bool GetFireBullet() { return fireBullet; }

	bool IsDead() { return hp <= 0; }
	FPOINT GetPos() { return position; }
	int GetSize() { return size; }
	float GetDamage() { return damage; }
	void AttackedByBullet(int damage) { hp -= damage; }
	void AttackedByTank() { hp = 0; }

	void CheckWallCollision();

	static void ReleaseBullets();
	static void UpdateBullets();
	static void RenderBullets(HDC hdc);
	static void CheckBulletsCollision(Tank* tank);
	static void InitLoadedBullets();
};

