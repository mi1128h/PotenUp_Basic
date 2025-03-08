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
	rcCollision = GetRectAtCenter(position.x, position.y, size, size);
	if (IsOutOfRange(position, WINSIZE_X, WINSIZE_Y)) isLoaded = true;
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
