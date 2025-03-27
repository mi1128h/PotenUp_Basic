#pragma once
#include "GameObject.h"

enum class BulletType {
	Basic,
	Bounce,
	Bomb,
	Confetti,
	length
};

class BulletFactory;
class BulletManager : public GameObject
{
public:
	BulletManager();
	~BulletManager();

	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void SetBulletValues(float angle, float damage,
		float explodeTime, int bounceNum, float confettiLife);
	void Fire(BulletType type, FPOINT position);

private:
	std::unique_ptr<BulletFactory> bulletFactoryList[(int)BulletType::length];

};

