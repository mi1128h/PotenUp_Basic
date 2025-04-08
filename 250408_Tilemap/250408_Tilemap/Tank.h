#pragma once
#include "GameObject.h"

class Missile;
class Tank : public GameObject
{
private:
	FPOINT pos;
	int size;
	float damage;
	string name;
	RECT rcCollision;

	// ����
	FPOINT barrelEnd;
	int barrelSize;
	float barrelAngle;	// ���� : ��(degree)	0 ~ 180		~	360
						//	    : ����(radian)0f ~ 3.14f	~	6.28f
	// �̻���
	int missileCount;
	//Missile* missile[10];
	Missile* missiles;

public:
	void Init();	
	void Release();	
	void Update();	
	void Render(HDC hdc);

	void Move();
	void Fire();
	void RotateBarrel(float angle);
	void Dead();

	inline FPOINT GetPos() { return pos; }
	inline int GetMissileCount() { return missileCount; }
	inline Missile* GetMissiles() { return missiles; }
	inline void SetBarrelAngle(float angle) { this->barrelAngle = angle; }

	Tank();
	~Tank();
};

