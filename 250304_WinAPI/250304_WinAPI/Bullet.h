#pragma once
#include "GameObject.h"
class Bullet : public GameObject
{
protected:
	bool isLoaded{};
	POINT position{};
	float fireAngle{};
	float speed{};
	int size{};
	RECT rcCollision{};

public:
	void Init(POINT pos, float angle);
	void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual void Move();
	bool IsLoaded() { return isLoaded; }
	void Fire() { isLoaded = false; }
	virtual void CheckWallCollision();

	Bullet();
	~Bullet();
};

class BombBullet : public Bullet
{
protected:
	int countDown{};	// one direction(fireAngle) while countdown
	float angle_360{};	// new direction after countdown

public:
	void SetBombValues(int time, float angle);
	void Update() override;
	void Move() override;
};

class BounceBullet : public Bullet
{
private:
	int bounceNum{};

public:
	void SetBounceNum(int cnt);
	void CheckWallCollision() override;
};

class ConfettiBullet : public BombBullet
{
private:
	int colors[3];
	int lifeTime;

public:
	void SetConfettiValues(int life);
	void Update() override;
	void Render(HDC hdc) override;
};