#pragma once
#include "GameObject.h"

enum class SkillType {
	None,
	Bomb,
	Skill2, // change this later,,
	length
};

class BombBullet;
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
	vector<BombBullet*> vBullets;
	int nLoadedBullets;

	int bombExplodeTime;

	int skillsCooldownTime[(int)SkillType::length];
	const int skillsCooldownMaxTime[(int)SkillType::length]{ 3,10,15 };

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void Move();
	void Skill(SkillType type);
	void Fire();
	void FireBomb();
	void RotateBarrel(float angle);
	void Dead();

	Tank();
	~Tank();
};

