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
class Enemy;
class Tank : public GameObject
{
private:
	FPOINT pos;
	int size;
	int hp;
	float damage;
	string name;
	RECT rcCollision;

	// ����
	FPOINT barrelEnd;
	int barrelSize;
	float barrelAngle;

	// �̻���
	vector<Bullet*> vBullets;
	int nLoadedBullets[(int)BulletType::length];
	vector<Bullet*> vBasics;
	vector<BombBullet*> vBombs;
	vector<BounceBullet*> vBounces;
	vector<ConfettiBullet*> vConfettis;

	int guidedFired{};

	int bombExplodeTime;
	int bounceNum;
	int confettiLife;

	int skillsCooldownTime[(int)BulletType::length];
	int skillsCooldownMaxTime[(int)BulletType::length];

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void Move(int dx, int dy);
	void Skill(BulletType type);
	void Fire();
	void FireBomb();
	void FireBounce();
	void FireConfetti();
	void RotateBarrel(float angle);
	void CalcBarrelEnd();
	void Dead();

	void ProccessMoveInput(WPARAM wParam);

	int GetHp() { return hp; }
	FPOINT GetPos() { return pos; }
	int GetSize() { return size; }
	void CheckCollideEnemy(Enemy* enemy);
	void SetBulletsTarget(vector<Enemy*>& enemies);
	Enemy* GetNearestEnemy(FPOINT pos, vector<Enemy*>& enemies);
	void AttackedByBullet(int damage) { hp -= damage; }

	void IncreaseFiredCnt() { guidedFired++; guidedFired %= 5; }

	int GetLoadedBulletsNum(BulletType type) { return nLoadedBullets[(int)type]; }
	int GetCreatedBulletsNum(BulletType type);
	void RenderInfo(HDC hdc);

	Tank();
	~Tank();
};

