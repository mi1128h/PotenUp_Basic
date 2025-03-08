#pragma once
#include "GameObject.h"

enum class SkillType {
	Basic,
	Bounce,
	Bomb,
	length
};

class Bullet;
class BombBullet;
class BounceBullet;
class Tank : public GameObject
{
private:
	POINT pos;
	int size;
	float damage;
	string name;
	RECT rcCollision;
	
	// 포신
	POINT barrelEnd;
	int barrelSize;
	float barrelAngle;

	// 미사일
	vector<Bullet*> vBullets;
	int nLoadedBullets[(int)SkillType::length];
	vector<Bullet*> vBasics;
	vector<BombBullet*> vBombs;
	vector<BounceBullet*> vBounces;

	int bombExplodeTime;
	int bounceNum;

	int skillsCooldownTime[(int)SkillType::length];
	int skillsCooldownMaxTime[(int)SkillType::length];

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void Move();
	void Skill(SkillType type);
	void Fire();
	void FireBomb();
	void FireBounce();
	void RotateBarrel(float angle);
	void Dead();

	int GetLoadedBulletsNum(SkillType type) { return nLoadedBullets[(int)type]; }
	int GetCreatedBulletsNum(SkillType type);
	void RenderBulletsNum(HDC hdc);

	Tank();
	~Tank();
};

