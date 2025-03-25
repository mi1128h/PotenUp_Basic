#pragma once
#include "GameObject.h"

class Image;
class BulletManager;
class Rocket : public GameObject
{
public:
	void Init();
	void Release();
	void Update();
	void ProcessInput();
	void Animate();
	void Render(HDC hdc);

	void Move();
	void SetDelta(int dx, int dy) { this->dx = dx; this->dy = dy; }

	FPOINT GetPos() { return position; }

private:
	FPOINT position;
	float dx, dy;
	float speed;
	float damage;

	Image* image;

	BulletManager* bulletManager;
};

