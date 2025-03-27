#pragma once
#include "config.h"
#include "Bullet.h"

class BulletFactory
{
public:
	BulletFactory() {}
	virtual ~BulletFactory();

	void AddBullet(int cnt);
	virtual std::unique_ptr<Bullet> CreateBullet() = 0;
	std::unique_ptr<Bullet>& GetBullet();
	virtual void InitBullet(std::unique_ptr<Bullet>& bullet, int cnt, int totalCnt) = 0;
	void UpdateFirePosition(FPOINT position) { this->position = position; }
	virtual void SetSpecialValues(float angle, float damage,
		float explodeTime, int bounceNum, float confettiLife);

protected:
	FPOINT position{};
	float angle{};
	float damage{};

private:
	std::vector<std::unique_ptr<Bullet>> bulletList;
};

class BasicBulletFactory : public BulletFactory
{
public:
	BasicBulletFactory() {}
	virtual ~BasicBulletFactory();

private:
	virtual std::unique_ptr<Bullet> CreateBullet() override;
	void InitBullet(std::unique_ptr<Bullet>& bullet, int cnt, int totalCnt) override;
	void SetSpecialValues(float angle, float damage,
		float explodeTime, int bounceNum, float confettiLife) override;
};

class BombBulletFactory : public BulletFactory
{
public:
	BombBulletFactory() {}
	virtual ~BombBulletFactory();

private:
	virtual std::unique_ptr<Bullet> CreateBullet() override;
	void InitBullet(std::unique_ptr<Bullet>& bullet, int cnt, int totalCnt) override;
	void SetSpecialValues(float angle, float damage,
		float explodeTime, int bounceNum, float confettiLife);

	float explodeTime{};
};

class BounceBulletFactory : public BulletFactory
{
public:
	BounceBulletFactory() {}
	virtual ~BounceBulletFactory();

private:
	virtual std::unique_ptr<Bullet> CreateBullet() override;
	void InitBullet(std::unique_ptr<Bullet>& bullet, int cnt, int totalCnt) override;
	void SetSpecialValues(float angle, float damage,
		float explodeTime, int bounceNum, float confettiLife);

	int bounceNum{};
};

class ConfettiBulletFactory : public BulletFactory
{
public:
	ConfettiBulletFactory() {}
	virtual ~ConfettiBulletFactory();

private:
	virtual std::unique_ptr<Bullet> CreateBullet() override;
	void InitBullet(std::unique_ptr<Bullet>& bullet, int cnt, int totalCnt) override;
	void SetSpecialValues(float angle, float damage,
		float explodeTime, int bounceNum, float confettiLife);

	float confettiLife{};
};