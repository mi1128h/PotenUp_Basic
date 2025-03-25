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

private:
	vector<Bullet*> vBullets;
	int nLoadedBullets[(int)BulletType::length];
	Image* imageList[(int)BulletType::length];

	vector<Bullet*> vBasics;
	vector<BombBullet*> vBombs;
	vector<BounceBullet*> vBounces;
	vector<ConfettiBullet*> vConfettis;



};

