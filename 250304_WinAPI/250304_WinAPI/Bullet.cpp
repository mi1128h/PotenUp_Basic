#include "Bullet.h"
#include "CommonFunction.h"

void Bullet::Init(POINT pos, float angle)
{
	isLoaded = true;
	position = pos;
	fireAngle = angle;
	speed = 20.0f;
	size = 10;
	rcCollision = GetRectAtCenter(position.x, position.y, size, size);
}

void Bullet::Release()
{
}

void Bullet::Update()
{
	if (isLoaded) return;

	Move();
	CheckWallCollision();
}

void Bullet::Render(HDC hdc)
{
	if (isLoaded) return;

	RenderEllipseAtCenter(hdc, position.x, position.y, size, size);
}

void Bullet::Move()
{
	position.x += cosf(TORADIAN(fireAngle)) * speed;
	position.y -= sinf(TORADIAN(fireAngle)) * speed;
}

void Bullet::CheckWallCollision()
{
	rcCollision = GetRectAtCenter(position.x, position.y, size, size);
	if (IsOutOfRange(position, WINSIZE_X, WINSIZE_Y)) isLoaded = true;
}

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void BombBullet::SetBombValues(int time, float angle)
{
	countDown = time;
	angle_360 = angle;
}

void BombBullet::Update()
{
	if(countDown) countDown--;
	Bullet::Update();
}

void BombBullet::Move()
{
	if (countDown > 0) Bullet::Move();
	else {
		position.x += cosf(TORADIAN(angle_360)) * speed;
		position.y -= sinf(TORADIAN(angle_360)) * speed;
	}
}

void BounceBullet::SetBounceNum(int cnt)
{
	bounceNum = cnt;
}

void BounceBullet::CheckWallCollision()
{
	rcCollision = GetRectAtCenter(position.x, position.y, size, size);
	if (IsOutOfRange(position, WINSIZE_X, WINSIZE_Y)) {
		if (!bounceNum) isLoaded = true;
		else {
			bounceNum--;
			bool isUpsideDown = IsOutOfRange({ WINSIZE_X / 2, position.y }, WINSIZE_X, WINSIZE_Y);
			fireAngle = 180 * (isUpsideDown ? 2 : 1) - fireAngle;
			position.x = ClampInt(position.x, 0, WINSIZE_X);
			position.y = ClampInt(position.y, 0, WINSIZE_Y);
		}
	}
}

void ConfettiBullet::SetConfettiValues(int life)
{
	colors[0] = uid_200_255(dre);
	colors[1] = uid_0_255(dre);
	colors[2] = uid_0_255(dre);
	lifeTime = life * uid_1_2(dre);
}

void ConfettiBullet::Update()
{
	BombBullet::Update();
	if (countDown <= 0) {
		speed = uid_0_10(dre);
		lifeTime--;
	}
	if (lifeTime <= 0) isLoaded = true;
}

void ConfettiBullet::Render(HDC hdc)
{
	if (isLoaded) return;
	if (countDown > 0) {
		Bullet::Render(hdc);
	}
	else {
		HBRUSH hBrush = CreateSolidBrush(RGB(colors[0], colors[1], colors[2]));
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

		RenderRectAtCenter(hdc, position.x, position.y, lifeTime, lifeTime);

		SelectObject(hdc, hOldBrush);
		DeleteObject(hBrush);
	}
}
