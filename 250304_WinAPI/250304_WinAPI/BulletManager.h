#pragma once
#include "GameObject.h"

enum class BulletType {
	Basic,
	Bounce,
	Bomb,
	Confetti,
	length
};

class Bullet;
class BombBullet;
class BounceBullet;
class ConfettiBullet;
class Image;
class BulletManager : public GameObject
{
public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void Fire(BulletType type, FPOINT position, float angle, float damage);
	Bullet* GetBasicBullet();
	BombBullet* GetBombBullet();
	BounceBullet* GetBounceBullet();
	ConfettiBullet* GetConfettiBullet();

private:
	vector<Bullet*> vBullets;

	vector<Bullet*> vBasics;
	vector<BombBullet*> vBombs;
	vector<BounceBullet*> vBounces;
	vector<ConfettiBullet*> vConfettis;



};

